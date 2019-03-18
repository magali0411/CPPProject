#ifndef __FASTXFILE_H__
#define __FASTXFILE_H__
#include <ostream>
#include <fstream>

#include "SequenceFastX.h"
#include "SequenceFastA.h"

class SequenceFastX;

class FastXFile {
    private:
        const char* m_filename;
        int m_format;
        size_t* m_position;
        size_t m_nbSeq;
        void myparse();


    public:
        //constructeurs
        FastXFile(const char* f);
        FastXFile(const FastXFile &f); // constructeur par copie
        //operateur d'affection
        FastXFile &operator=(const FastXFile &f);
        //destructeur 
        ~FastXFile();

        //Getters & Setters
        size_t getNbSeq() const ;
        const char * getFileName() const;
        void setFilename(const char* &f);
        std::string getFormat() const;
        void setFormat(int format);

        //methodes
        void toStream(std::ostream &os) const;
        char operator[](size_t i) const ;
        void clear();
        SequenceFastX* getSequence(size_t i) const;
        friend std::ostream& operator<<(std::ostream &os, const FastXFile &f); 
        bool seqCheck(size_t posheader) const;
}
;
#endif //FASTXFILE_H
