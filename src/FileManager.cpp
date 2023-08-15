#include "FileManager.h"


FileManager::FileManager(){

}

void FileManager::saveFile(){


}

void FileManager::loadFile(){


}

int FileManager::mountFS(){
    int mountStatus = pico_mount(true);
    return mountStatus;
}

void FileManager::listDir(){
    printf("File list\n");
    int dir = pico_dir_open("/");
    if (dir < 0)
        return;
    struct lfs_info info;
    while (pico_dir_read(dir, &info) > 0)
        printf("%s\n", info.name);
    pico_dir_close(dir);
	printf("End of list\n");
}