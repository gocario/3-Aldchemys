#include "fs.h"

#include <3ds/srv.h>
#include <3ds/svc.h>

Result fsInitialized = 0;
Handle sdmcHandle;
FS_archive sdmcArchive;

Result FS_ReadFile(char* path, void* dst, FS_archive* fsArchive, Handle* fsHandle, u32* bytesRead, u64 maxSize)
{
	if (!path || !dst || !fsArchive) return -1;

	Result ret;
	u64 size;
	Handle fileHandle;

	ret = FSUSER_OpenFile(fsHandle, &fileHandle, *fsArchive, FS_makePath(PATH_CHAR, path), FS_OPEN_READ, FS_ATTRIBUTE_NONE);

	if (!ret)
	{
		ret = FSFILE_GetSize(fileHandle, &size);
		if (ret || size > maxSize) ret = -2;
	}

	if (!ret)
	{
		ret = FSFILE_Read(fileHandle, bytesRead, 0, dst, size);
		if (ret || *bytesRead < size) ret = -3;
	}

	ret = FSFILE_Close(fileHandle);

	return ret;
}


Result FS_WriteFile(char* path, void* src, FS_archive* fsArchive, Handle* fsHandle, u32* bytesWritten, u64 size)
{
	if (!path || !src || !fsArchive) return -1;

	Result ret;
	Handle fileHandle;

	ret = FSUSER_OpenFile(fsHandle, &fileHandle, *fsArchive, FS_makePath(PATH_CHAR, path), FS_OPEN_WRITE | FS_OPEN_CREATE, FS_ATTRIBUTE_NONE);

	if (!ret)
	{
		ret = FSFILE_Write(fileHandle, bytesWritten, 0L, src, size, FS_WRITE_FLUSH);
		if (ret || *bytesWritten < size) ret = -3;
	}


	ret = FSFILE_Close(fileHandle);

	return ret;
}


Result FS_FilesysInit()
{
	Result ret;

	ret = srvGetServiceHandle(&sdmcHandle, "fs:USER");
	if (ret) return ret;

	sdmcArchive = (FS_archive) { ARCH_SDMC, (FS_path) { PATH_EMPTY, 1, (u8*) "" }, 0, 0 };
	ret = FSUSER_OpenArchive(&sdmcHandle, &sdmcArchive);

	return ret;
}


Result FS_FilesysExit()
{
	FSUSER_CloseArchive(&sdmcHandle, &sdmcArchive);
	svcCloseHandle(sdmcHandle);
	return 0;
}
