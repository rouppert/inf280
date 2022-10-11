#ifndef _GENERICTABLE_H_
#define _GENERICTABLE_H_

#include "group.h"
#include "photo.h"
#include "film.h"
#include "video.h"
#include <stdlib.h>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;

/**
 * @brief This class describes a table of objects. Thes objects could be either groups or multimedia objects (video, photo, ...).
 * 
 */

class GenericTable {
    private :
        map <string, Group*> groupTable;
        map <string, Multimedia*> multimediaTable;

    public:
        map <string, Multimedia*>::iterator getTableBegin() {return multimediaTable.begin();}

        map <string, Multimedia*>::iterator getTableEnd() {return multimediaTable.end();}

        const Photo* createPhoto(int long_, int lat_, string name_, string pathname_);

        const Video* createVideo(int length_ , string name_, string pathname_);

        const Film* createFilm(int length_, string name_, string pathname_, int chapNumb_, int chapLeng_[]);

        const Group* createGroup(initializer_list<Multimedia*> init, string name_);

        Multimedia* searchMultimedia(string name_);

        Group* searchGroup(string name_);

        void createObject(istream & f);

        void saveObject(ostream & f, string name_);
};

using tablePtr = shared_ptr<GenericTable>;

#endif