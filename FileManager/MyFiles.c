#include "MyFiles.h"
#include "FileManager.h"
#include "../ErrorHandler/ErrorTable.h"

void initialize_MyFiles(){
	DREC_Home = new_Directory("Home");
	DREC_Current = DREC_Home;
}

void MyFiles_update_Current(FILEPTR new_directory){
	DREC_Current = new_directory;
}