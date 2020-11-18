#ifndef MyFiles
#define MyFiles

#include "FileManager.h"

FILEPTR DREC_Home;
FILEPTR DREC_Current;

void initialize_MyFiles();

void MyFiles_update_Current(FILEPTR new_directory);

#endif