#include "film.h"

void Film::setChaptersLength(int chapLeng_[], int chapNumb_) {
    chaptersNumber = chapNumb_;
    for(int i = 0; i < chapNumb_; i++) {
        chaptersLength[i] = chapLeng_[i];
    }
}

string Film::displayChaptersLength () const {
    string chaptersLengthStr = "";
    for(int i = 0; i<chaptersNumber; i++) {
        chaptersLengthStr += "Chapter " + to_string(i) + " : " + to_string(chaptersLength[i]) + "\n";
        cout << "Chapter " << i << " : " << chaptersLength[i] << "\n" << endl;
    }
    return chaptersLengthStr;
}

void Film::createFromFile(string parameters) {
    istringstream iss(parameters);
    string word ="";
    iss >> word;

    for (int i = 0; word != "\n"; i++) {
        iss >> word;
        switch(i) {
            case 0: setLength(stoi(word));
            case 1: setName(word);
            case 2: setPath(word);
            case 3: chaptersNumber = stoi(word); 
        }
        if (i > 3) {
            chaptersLength[i - 4] = stoi(word);
        }
    }
}

void Film::saveInFile(std::ostream&f) const {
    f  << getClassName() << " " << getLength() << " " << getName() << " " << getPath();
    for (int i=0; i<chaptersNumber; i++) {
        f << " " << chaptersLength[i];
    }
    f << "\n";
}