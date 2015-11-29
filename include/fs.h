#ifndef FS_H
#define FS_H

#include <3ds.h>

extern Result fsInitialized;
extern Handle sdmcHandle;
extern FS_archive sdmcArchive;

Result FS_ReadFile(char* path, void* dst, FS_archive* fsArchive, Handle* fsHandle, u32* bytesRead, u64 maxSize);
Result FS_WriteFile(char* path, void* src, FS_archive* fsArchive, Handle* fsHandle, u32* bytesWritten, u64 size);

Result FS_FilesysInit();
Result FS_FilesysExit();

#endif // FS_H
