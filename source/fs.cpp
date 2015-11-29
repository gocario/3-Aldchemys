#include "fs.h"

#include <stdio.h>

Result fsInitialized = 0;
Handle sdmcHandle;
FS_archive sdmcArchive;

Result FS_ReadFile(char* path, void* dst, FS_archive* fsArchive, Handle* fsHandle, u32* bytesRead, u64 maxSize)
{
	if (!path || !dst || !fsArchive) return -1;

	Result ret;
	u64 size;
	Handle fileHandle;

	// printf("FS_ReadFile:\n");

	ret = FSUSER_OpenFile(fsHandle, &fileHandle, *fsArchive, FS_makePath(PATH_CHAR, path), FS_OPEN_READ, FS_ATTRIBUTE_NONE);
	// printf(" > FSUSER_OpenFile: %li\n", ret);

	if (!ret)
	{
		ret = FSFILE_GetSize(fileHandle, &size);
		// printf(" > FSFILE_GetSize: %li\n", ret);
		if (ret || size > maxSize) ret = -2;
	}

	if (!ret)
	{
		ret = FSFILE_Read(fileHandle, bytesRead, 0, dst, size);
		// printf(" > FSFILE_Read: %li\n", ret);
		if (ret || *bytesRead < size) ret = -3;
	}

	ret = FSFILE_Close(fileHandle);
	// printf(" > FSFILE_Close: %li\n", ret);

	return ret;
}


Result FS_WriteFile(char* path, void* src, FS_archive* fsArchive, Handle* fsHandle, u32* bytesWritten, u64 size)
{
	if (!path || !src || !fsArchive) return -1;

	Result ret;
	Handle fileHandle;

	// printf("FS_WriteFile:\n");

	ret = FSUSER_OpenFile(fsHandle, &fileHandle, *fsArchive, FS_makePath(PATH_CHAR, path), FS_OPEN_WRITE | FS_OPEN_CREATE, FS_ATTRIBUTE_NONE);
	// printf(" > FSUSER_OpenFile: %li\n", ret);

	if (!ret)
	{
		ret = FSFILE_Write(fileHandle, bytesWritten, 0L, src, size, FS_WRITE_FLUSH);
		// printf(" > FSFILE_Write: %li\n", ret);
		if (ret || *bytesWritten < size) ret = -3;
	}


	ret = FSFILE_Close(fileHandle);
	// printf(" > FSFILE_Close: %li\n", ret);

	return ret;
}


Result FS_FilesysInit()
{
	Result ret = 0;

	// printf("FS_FilesysInit:\n");

	if (fsInitialized == 0)
	{
		ret = srvGetServiceHandle(&sdmcHandle, "fs:USER");
		// printf(" > srvGetServiceHandle: %li\n", ret);
		if (ret) return ret;

		sdmcArchive = (FS_archive) { ARCH_SDMC, (FS_path) { PATH_EMPTY, 1, (u8*) "" }, 0, 0 };
		ret = FSUSER_OpenArchive(&sdmcHandle, &sdmcArchive);
		// printf(" > FSUSER_OpenArchive: %li\n", ret);

		fsInitialized = 1;
	}

	return ret;
}


Result FS_FilesysExit()
{
	Result ret = 0;

	// printf("FS_FilesysExit:\n");

	if (fsInitialized == 1)
	{
		ret = FSUSER_CloseArchive(&sdmcHandle, &sdmcArchive);
		// printf(" > FSUSER_CloseArchive: %li\n", ret);
		if (ret) return ret;

		ret = svcCloseHandle(sdmcHandle);
		// printf(" > svcCloseHandle: %li\n", ret);

		fsInitialized = 0;
	}

	return ret;
}
