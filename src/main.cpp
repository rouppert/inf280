#include <iostream>
#include <string>
#include <fstream>
#include "video.h"
#include "photo.h"
#include "film.h"
#include "group.h"
#include "genericTable.h"

using namespace std;

GenericTable* table = new GenericTable();

int main(int argc, const char* argv[]){
    fstream f;
    f.open("Database.txt");
    if(!f) {
        cerr << "Can't open file " << "database.txt" << endl;
    }
    while(f) {
        table -> createObject(f);
    }
    f.close();
    fstream f1;
    f1.open("Database_copy.txt");
    for(auto it = table -> getTableBegin(); it != table -> getTableEnd(); it++) {
        table -> saveObject(f1, it -> second -> getName());
    }
    f1.close();
}

 
