#ifndef _RUN_FILE_H_
#define _RUN_FILE_H_

#include "DEV_Config.h"

#define fileNumber 2000
#define fileLen 100

char sdTest(void);
void sdInitTest(void);

void run_mount(void);
void run_unmount(void);

void file_cat(void);

void sdScanDir(void);

char isFileExist(const char *path);
void setFilePath(void);

void updatePathIndex(void);
void file_sort();
void file_shuffle();

#endif
