#ifndef _GROUP_H_
#define _GROUP_H_

#include <stdlib.h>
#include <iostream>
#include <memory>
#include <list>
#include "multimedia.h"

using namespace std;

class Group:public list<Multimedia*> {
    friend class GenericTable;
    private:
        string name;

    protected:
        /* Constructeur */
        Group(initializer_list<Multimedia*> init, string name): list<Multimedia*>(init), name(name) {};

    public:
        /* Setters */
        void setName(string name_) {name = name_;};

        /* Getters */
        string getName() {return name;};

        /* Autres */
        string displayObjectsNames();

        /* Desctructeur */
        ~Group() {};
};

using groupPtr = shared_ptr<Group>;

#endif