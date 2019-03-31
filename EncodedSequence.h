#ifndef __ENCODEDSEQUENCE_H__
#define __ENCODEDSEQUENCE_H__
#include <stddef.h>
#include <ostream>


class EncodedSequence{
private:
    size_t n; //taille sequence
    size_t N; // Taille de la séquence en Bytes
    char * t; //tableau


    static size_t getByte(size_t i);
    static size_t getPosByte(size_t i);
    

public:
    //constructeurs
    EncodedSequence();
    EncodedSequence(size_t n=0);
    EncodedSequence(const EncodedSequence &es); //constructeur par copie
    
    //destructeur
    ~EncodedSequence();
    void clear();


    EncodedSequence &operator=(const EncodedSequence &es);
    char operator[](size_t i) const ;
    EncodedSequence operator+=(char c);
    //EncodedSequence operator()(size_t start, size_t l=(size_t)-1) const;
    friend std::ostream& operator<<(std::ostream &os, const EncodedSequence &es);


    void setNucl(size_t i, char c);
    void reserve(size_t n);
    EncodedSequence reverseComplement() const;
    char encode(char c) const;
    char decode(char c) const;

    void toStream (std::ostream &os) const;
        
    }
;
#endif

