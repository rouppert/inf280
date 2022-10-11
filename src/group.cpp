#include "group.h"

string Group::displayObjectsNames() {
    string objectsNames = "";
    int i = 0;
    for (auto it = begin(); it != end(); it++) {
        objectsNames += (*it) -> getName();
        cout << "Object " << i << " : " << (*it) -> getName() << "\n" << endl;
        i++;
    }
    return objectsNames;
}