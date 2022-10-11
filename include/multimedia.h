#ifndef _MULTIMEDIA_H_
#define _MULTIMEDIA_H_

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

using namespace std;

/** @brief This class describes a generic Multimedia object. 
 * A Multimedia object is only described by a name and a pathname.
 * This class wille be further used for heritage.
 * @see Photo, @see Video, @see Film.
 */

class Multimedia {
    friend class GenericTable;
    private:
        string name;
        string pathname;

    protected:
        // Constructors are protected, so that Multimedia objects can't be created outside a table.
        /* Constructors */
        Multimedia() {};
        /**
         * @brief Constructs a new Multimedia object.
         * @param name_ : name of Multimedia.
         * @param pathname_ : location of Multimedia object on disk.
         */
        Multimedia(string name_, string pathname_): name(name_), pathname(pathname_) {};


    public:
        /* Getters */
        string getName () const {return name;};
        string getPath () const {return pathname;};
        virtual string getClassName() const {return "Multimedia";};

        /* Setters */
        void setName (string name_) {name=name_;};
        void setPath (string path_) {pathname=path_;};

        /* Others */

        /**
         * @brief Displays name and pathname on "out".
         * 
         * @param out 
         * @return Name and pathname of Multimedia object.
         */
        virtual string displayParam(ostream  & out) const{
            out << "name : " << getName() << "\n" << "path : " << getPath() << "\n" << endl;
            return ("name : " + getName() + "\n" + "path : " + getPath() + "\n");
        };

        /**
         * @brief Plays Multimedia object. Only used for heritage.
         * 
         */
        virtual void play() const {};

        /**
         * @brief Saves Multimedia object's parameters in given file f.
         * Parameters are written as in following example.
         * "Photo example multimedia/example.jpeg"
         * @param f : file to save object in.
         */
        virtual void saveInFile(std::ostream&f) const {
            f  << getClassName() << " " << getName() << " " << getPath() << "\n";
        }

        /**
         * @brief Reads given line in a file, on which parameters of Multimedia Object are saved, and creates matching object.
         * 
         * @param parameters line on which parameters of the object are written.
         */
        virtual void createFromFile(string parameters);

        /* Destructor */
        ~Multimedia() {cerr << "multimedia object " << getName() << " destructed \n";};
};

using multimediaPtr = shared_ptr<Multimedia>;

#endif