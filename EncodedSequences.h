#ifndef __ENCODEDSEQUENCES_H__
#define __ENCODEDSEQUENCES_H__
#include <stddef.h>
#include <ostream>


class EncodedSequences{
private:
    size_t n; //taille sequence
    size_t N;
    char * t; //tableau
    static size_t getByte(size_t i);
    static size_t getPosBytes(size_t i);
    

public:
    //constructeurs
    EncodedSequences();
    EncodedSequences(size_t n=0);
    EncodedSequences(const EncodedSequences &es); //constructeur par copie
    EncodedSequences &operator=(const EncodedSequences &es);
    //destructeur
    ~EncodedSequences();
    char operator[](size_t i) const ;
    void setNucleo(size_t i, char c);
    void reserve(size_t n);
    void toStream (std::ostream &os) const;
    void clear();
    EncodedSequences operator+=(char c);
    EncodedSequences reverseComplement() const;
    EncodedSequences operator()(size_t start, size_t l=(size_t)-1) const;
    char encode(char c) const;
    char decode(char c) const;
    
    //std::ostream& operator<<(std::ostream &os, const EncodedSequences &es);
}
;
#endif

