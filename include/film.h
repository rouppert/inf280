#ifndef _FILM_H_
#define _FILM_H_

#include <iostream>
#include <string>
#include <memory>
#include "video.h"


using namespace std;

/**
 * @brief This class describes a film. A film is a video, which is divided into chapters.
 * @see Video
 */

class Film:public Video {
    friend class GenericTable;
    private:
        int chaptersNumber;
        int* chaptersLength = new int[chaptersNumber];

    protected:
        /* Constructors */
        Film(): Video() {};
        /**
         * @brief Construct a new Film object.
         * @param chapNumb_ : number of chapters in the film.
         * @param chapLeng_ : table of length of every chapter in the film.
         */
        Film(int length_, string name_, string pathname_, int chapNumb_, int chapLeng_[]): Video(length_, name_, pathname_) {setChaptersLength(chapLeng_, chapNumb_);};;

    public:
        /**
         * @brief Changes chapters plan in the film.
         * @param chapLeng_ : new table of chapters length.
         * @param chapNumb_ : size of this table.
         */
        void setChaptersLength (int chapLeng_[], int chapNumb_);

        /**
         * @return size of the film's chapters table. 
         */
        int getChaptersNumber () const {return chaptersNumber;};
        /**
         * @return chapters length table.
         */
        const int* getChaptersLength () const {return chaptersLength;};
        string getClassName() const override {return "Film";};

        /* Others */
        string displayChaptersLength () const;

        void createFromFile(string parameters) override;

        void saveInFile(std::ostream&f) const override;

        string displayParam(ostream  & out = cout) const override {
            string response = displayChaptersLength ();
            return response;
        };

        /* Destructor */
        ~Film() {delete chaptersLength;};
};

using videoPtr = shared_ptr<Video>;

#endif