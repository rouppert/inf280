#ifndef _PHOTO_H_
#define _PHOTO_H_

#include <iostream>
#include <string>
#include <memory>
#include "../include/multimedia.h"

using namespace std;

/**
 * @brief This class describes a Photo. A Photo is a Multimedia object, which has a longitude and a latitude.
 * @see Multimedia
 */

class Photo:public Multimedia {
    friend class GenericTable;
    private:
        int longitude;
        int latitude;

    protected:
        /**
         * @brief Constructs a new Photo object.
         * 
         * @param long_ : longitude of the video.
         * @param lat_ : latitude of the video.
         * @param name_ 
         * @param pathname_ 
         */
        Photo(int long_ = 0, int lat_ = 0, string name_ = "default name", string pathname_ = "default pathname"): Multimedia(name_, pathname_), longitude(long_), latitude(lat_) {};

    public:
        /**
         * @brief Sets longitude of the video.
         */
        void setLong (int long_) {longitude = long_;};
        /**
         * @brief Sets latitude of the video.
         */
        void setLat (int lat_) {latitude = lat_;};

        /**
         * @return longitude of the video. 
         */
        int getLong () const {return longitude;};
        /**
         * @return latitude of the video. 
         */
        int getLat () const {return latitude;};
        string getClassName() const override {return "Photo";};

        /**
         * @brief Displays parameters of the video on "out".
         * Overrides Multimedia original method.
         * @param out : output stream for parameters.
         * @return parameters of the video. 
         */
        string displayParam(ostream  & out) const override {
            out << "longitude : " << getLong() << "\n" << "latitude : " << getLat() << "\n" << "name : " << getName() << "\n" << " path : " << getPath() << "\n" << endl;
            return ("longitude : " + to_string(getLong()) + "\n" + "latitude : " + to_string(getLat()) + "\n" + "name : " + getName() + "\n" + " path : " + getPath());
        };

        /**
         * @brief Opens photo on ImageJ.
         * Overrides Multimedia original method.
         * 
         */
        void play() const override {system (("display " + getPath() + " &").c_str());};

        void createFromFile(string parameters) override;

        void saveInFile(std::ostream&f) const override;

        /* Destructeur */
        ~Photo () {cerr << "photo " << getName() << " destructed";};
};

using photoPtr = shared_ptr<Photo>;

#endif