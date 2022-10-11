#include "genericTable.h"

const Photo* GenericTable::createPhoto(int long_, int lat_, string name_, string pathname_) {
    Photo* newPhoto = new Photo(long_, lat_, name_, pathname_);
    multimediaTable.insert(pair<string, Multimedia*>(name_, newPhoto));
    return newPhoto;
}

const Video* GenericTable::createVideo(int length_ , string name_, string pathname_) {
    Video* newVideo = new Video(length_ , name_, pathname_);
    multimediaTable.insert(pair<string, Multimedia*>(name_, newVideo));
    return newVideo;
}


const Film* GenericTable::createFilm(int length_, string name_, string pathname_, int chapNumb_, int chapLeng_[]) {
    Film* newFilm = new Film(length_, name_, pathname_, chapNumb_, chapLeng_);
    multimediaTable.insert(pair<string, Multimedia*>(name_, newFilm));
    return newFilm;
}

const Group* GenericTable::createGroup(initializer_list<Multimedia*> init, string name_) {
    Group* newGroup = new Group(init, name_);
    groupTable.insert(pair<string, Group*>(name_, newGroup));
    return newGroup;
}


Multimedia* GenericTable::searchMultimedia(string name_) {
    auto it = multimediaTable.find(name_);
    if (it == multimediaTable.end()) {
        cout << "object " << name_ << " not found";
        return nullptr;
    }
    else {
        return (it -> second);
    }
}

Group* GenericTable::searchGroup(string name_) {
    auto it = groupTable.find(name_);
    it -> second -> displayObjectsNames();
    return it -> second;
}

void GenericTable::createObject(istream & f) {
    string parameters;
    getline(f, parameters);
    istringstream iss(parameters);
    string objectType;
    iss >> objectType;
    if (objectType == "Multimedia") {
        Multimedia* newMultimedia = new Multimedia();
        newMultimedia ->createFromFile(parameters);
        multimediaTable.insert(pair<string, Multimedia*>(newMultimedia->getName(), newMultimedia));
    }

    if (objectType == "Photo") {
        Photo* newPhoto = new Photo();
        newPhoto ->createFromFile(parameters);
        multimediaTable.insert(pair<string, Photo*>(newPhoto->getName(), newPhoto));
    }

    if (objectType == "Video") {
        Video* newVideo = new Video();
        newVideo ->createFromFile(parameters);
        multimediaTable.insert(pair<string, Video*>(newVideo->getName(), newVideo));
    }

    if (objectType == "Film") {
        Film* newFilm = new Film();
        newFilm ->createFromFile(parameters);
        multimediaTable.insert(pair<string, Film*>(newFilm->getName(), newFilm));
    }
}

void GenericTable::saveObject(ostream & f, string name_) {
    if (searchMultimedia(name_) != NULL) {
        searchMultimedia(name_) -> saveInFile(f);
    }
}