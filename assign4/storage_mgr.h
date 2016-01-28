#ifndef STORAGE_MGR_H
#define STORAGE_MGR_H

#include "dberror.h"
#include <time.h>

/************************************************************
 *                    handle data structures                *
 ************************************************************/
typedef struct mHandle{

time_t current_time; //last updated date for file
FILE *fp;//File pointer
int fPagePos;//position of first page
int lPagePos;//position of last page
int noPages;//Total number of pages
int noEmpBlocks;//Number of Empty Blocks

} mgmtInfo_Handle;

typedef struct SM_FileHandle {
	char *fileName;
	int totalNumPages;
	int curPagePos;
	mHandle *mgmtInfo;
} SM_FileHandle;



typedef char* SM_PageHandle;

/************************************************************
 *                    interface                             *
 ************************************************************/
/* manipulating page files */
extern void initStorageManager (void);
extern RC createPageFile (char *fileName);
extern RC openPageFile (char *fileName, SM_FileHandle *fHandle);
extern RC closePageFile (SM_FileHandle *fHandle);
extern RC destroyPageFile (char *fileName);

/* reading blocks from disc */
extern RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage);
extern int getBlockPos (SM_FileHandle *fHandle);
extern RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);

/* writing blocks to a page file */
extern RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC appendEmptyBlock (SM_FileHandle *fHandle);
extern RC ensureCapacity (int numberOfPages, SM_FileHandle *fHandle);

#endif