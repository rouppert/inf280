#include "multimedia.h"

void Multimedia::createFromFile(string parameters) {
    istringstream iss(parameters);
    string word ="";
    iss >> word;
    for (int i = 0; i < 2; i++) {
        iss >> word;
        switch(i) {
            case 0: name = word;
            case 1: pathname = word;
        }
    }
}