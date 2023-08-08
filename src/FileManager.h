#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include "../libs/lfs/littlefs-lib/pico_hal.h"

class FileManager{

private:

public:
    //Constructor
    FileManager();
    void LoadFile();
    void SaveFile();


};

#endif