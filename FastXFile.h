#ifndef __FASTXFILE_H__
#define __FASTXFILE_H__
#include <ostream>

#include "SequenceFastX.h"
#include "SequenceFastA.h"
#include "SequenceFastQ.h"

class SequenceFastX;


class FastXFile {

    public :
    enum Format {
        UNDEF,
        FASTA,
        FASTQ
    };


    private:
        const char* m_filename;
        Format m_format;
        size_t* m_position;
        size_t* m_taille;
        size_t m_nbSeq;

        //Méthodes internes
        void myparse();
        void setFormat(Format format);
        bool seqCheck(size_t posheader) const;


    public:
        //constructeurs
        FastXFile(const char* f);
        FastXFile(const FastXFile &f); // constructeur par copie
        //operateurs
        FastXFile &operator=(const FastXFile &f);
        //char operator[](size_t i) const ;
        friend std::ostream& operator<<(std::ostream &os, const FastXFile &f); 


        //destructeur 
        ~FastXFile();

        //Getters & Setters
        size_t getNbSeq() const ;

        const char * getFileName() const;
        void setFilename(const char* &f);

        std::string getFormat() const;

        //methodes
        void toStream(std::ostream &os) const;
        
        void clear();
        SequenceFastX getSequence(size_t i) const;
}
;
#endif //FASTXFILE_H
