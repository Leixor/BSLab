//
//  RootDirectory.cpp
//  mkfs.myfs
//
//  Created by Mika Auer on 21.11.18.
//  Copyright © 2018 Oliver Waldhorst. All rights reserved.
//

#include "RootDirectory.h"
#include <string>

RootData directory[ROOT_DIRECTORY_SIZE];

/**
   * Gives you a RootData Object from the root directory
 
    * \param path The path or name of the file you want to get the root data of
 */
RootData* getRootData(const char* path){
    for(int i = 0; i < ROOT_DIRECTORY_SIZE; i++){
        std::string name = directory[i].name;
        if(name.compare(path)){
            return &directory[i];
        }
    }
    
    return nullptr;
}

/**
 *Adds RootData to your RootDirectory
 
 *\param data The data you want to add to the directory
 *\param index The index that the data should be written to, if -1 write to the first free index
 
 *\return Bool shows if it worked or if directory is full
 */
bool addToRootDirectory(RootData data, int index = -1){
    if (index >= 0 && index < ROOT_DIRECTORY_SIZE){
        directory[index] = data;
        return true;
    }else{
        for(int i = 0; i < ROOT_DIRECTORY_SIZE; i++){
            if(directory[i].name == NULL){
                directory[i] = data;
                return true;
            }
        }
    }
    return false;
}

RootData* RootDirectory::getRootDirectory()
{
    return this->directory;
}
