#include "photo.h"

void Photo::createFromFile(string parameters) {
    istringstream iss(parameters);
    string word ="";
    iss >> word;
    for (int i = 0; i < 4; i++) {
        iss >> word;
        cout << word;
        switch(i) {
            case 0: longitude = stoi(word);
            case 1: latitude = stoi(word);
            case 2: setName(word);
            case 3: setPath(word);
        }
    }
}

void Photo::saveInFile(std::ostream&f) const {
    f  << getClassName() << getLong() << " " << getLat() << " " << getName() << " " << getPath() << "\n";
}