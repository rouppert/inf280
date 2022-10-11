#include "video.h"

void Video::createFromFile(string parameters) {
    istringstream iss(parameters);
    string word ="";
    iss >> word;
    for (int i = 0; i < 3; i++) {
        iss >> word;
        switch(i) {
            case 0: length = stoi(word);
            case 1: setName(word);
            case 2: setPath(word);
        }
    }
}

void Video::saveInFile(std::ostream&f) const {
    f  << getClassName() << " " << getLength() << " " << getName() << " " << getPath() << "\n";
}