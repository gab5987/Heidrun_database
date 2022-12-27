//  Created by Gabriel Gonçalves Novalski in late 2022
//
//  Here`s where one would put some copyright stuff, but I don`t give a damn about that.
//  This is a free software, and you can do whatever you want with it.

// Instead of all the copyright/licence thing, grab a poem: 

// The Normal Monster sings in the Green Sahara
// The voice and offal of the image of God
// make Celtic noises in these lyrical hells
// Hurricanes of reasoned musics reap the uncensored earth
// The loquent consciousness of living things pours in torrential languages
// The elderly colloquists the Spirit and the Flesh are out of tongue
// The Spirit is impaled upon the phallus
// A gravid day spawns gutteral gargoyles upon the Tower of Babel
// Empyrean emporium where the rejector-recreator Joyce flashes the giant reflector on the sub rosa

#ifndef __heidrun_h__
#define __heidrun_h__

// We need those stuff to acces the SD Card!
#include <FS.h>  // FileSystem Lib
#include <SD.h>  // SD Methods Lib
#include <SPI.h> // SPI thingo

#include <Arduino.h>

#include "num_codes.h"

class Heidrun_db {
    public:
        int8_t begin();
        int8_t createDatabase(char *dbName);
        int8_t createTable(char *dbName, char *tableName, char *columns);
};

#endif