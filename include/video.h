#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <iostream>
#include <string>
#include <memory>
#include "multimedia.h"

using namespace std;

/**
 * @brief This class describes a Video. A Video is a Multimedia object which has a length.
 * @see Multimedia
 */

class Video:public Multimedia {
    friend class GenericTable;
    private:
        int length;

    protected:
        /* Constructors */
        Video() {};
        /**
         * @brief Constructs a new Video object.
         * 
         * @param length_ : length of the video.
         * @param name_ 
         * @param pathname_ 
         */
        Video(int length_, string name_, string pathname_): Multimedia(name_, pathname_), length(length_){};

    public:
        /* Setters */
        void setLength (int length_) {length = length_;};

        /* Getters */
        int getLength () const {return length;};
        string getClassName() const override {return "Video";};

        /* Others */
        /**
         * @brief Displays parameters of the video (name, pathname, length) on "out".
         * Overrides original Multimedia method.
         * @param out : output stream for parameters.
         * @return parameters of the video (name, pathname, length).
         */
        virtual string displayParam(ostream  & out) const override {
            out << "length : " << getLength() << "\n" << "name : " << getName() << "\n" << "path : " << getPath() << "\n" << endl;
            return ("length : " + to_string(getLength()) + "\n" + "name : " + getName() + "\n" + "path : " + getPath() + "\n");
        };

        /**
         * @brief Plays video using mpv.
         * Overrides original Multimedia method.
         */
        void play() const override  {system (("mpv " + getPath() + " &").c_str());};

        void createFromFile(string parameters) override;

        void saveInFile(std::ostream&f) const override;

        /* Destructor */
        ~Video () {cerr << "video " << getName() << " destructed";};
};

using videoPtr = shared_ptr<Video>;

#endif