#ifndef SEQUENCEFASTX_H_INCLUDED
#define SEQUENCEFASTX_H_INCLUDED

#include<iostream>


char* myStrDup (const char* s);
// Check not nucleotide
bool notNucl(std::string &s);

class FastXFile;

class SequenceFastX{

    // ATTRIBUTS
    protected :
    
    char* m_seqName;
    const char* m_file;
    std::string m_head;
    size_t m_size;
    const size_t m_pos_seq;

    float m_txGC;


    public :

    // Constructeur
    SequenceFastX();
    SequenceFastX(const char* &f, const size_t pos, size_t size, std::string head);
    SequenceFastX(const SequenceFastX &seq);

    //Destructeur 
    virtual ~SequenceFastX() ;

    //my strdup()
    //const char * myStrDup (const char * s);

    //cleaner
    void clear();

    // SETTERS & GETTERS 

    //nom de la séquence
    char* getName() const;
    void setName(const char*);


    //séquence nucléotidique
    std::string getSeq() const;

    // Retourne les infos relatives à une séquence aka l'header
    std::string getHead() const;
    void setHead(std::string header);

    //longueur séquence
    size_t getSize() const;
    void setSize(size_t size);

    //fichier mère
    const char * getFile() const;
    void setFile(const char* &f);

    //position séquence
    const size_t getPosition() const;

    // Methodo

    //Tostream
    void toStream(std::ostream &os) const;

    // Méthode calcul GC

    // reverse sequence 
    std::string seqReverse(const std::string &seq) const;

    // complement sequence
    std::string seqCompl(const std::string &seq) const;


};

#endif // SEQUENCEFASTX_H_INCLUDED
