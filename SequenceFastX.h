#ifndef SEQUENCEFASTX_H_INCLUDED
#define SEQUENCEFASTX_H_INCLUDED

#include<iostream>


class FastXFile;

class SequenceFastX{

    // ATTRIBUTS
    protected :
    
    const char* m_file;
    char* m_seqName;
    std::string m_head;
    size_t m_size;
    size_t m_pos_seq;
    float m_txGC;


    public :

    // Constructeur
    SequenceFastX();
    SequenceFastX(const char* &f, const size_t pos, size_t size, std::string head);
    SequenceFastX(const SequenceFastX &seq);


    //operateur par copie
    SequenceFastX &operator=(const SequenceFastX &seq);

    // clear 
    void clear();

    //Destructeur 
    virtual ~SequenceFastX() ;

    //my strdup()
    //const char * myStrDup (const char * s);

    // SETTERS & GETTERS 

    //nom de la séquence
    char* getName() const;
    void setName(const char*);


    //séquence nucléotidique
    std::string getSeq() const ;

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
    size_t getPosition() const;
    void setPosSeq(const size_t pos);

    // Methodo

    //Tostream
    void toStream(std::ostream &os) const;

    // Méthode calcul GC

    // reverse sequence 
    std::string seqReverse(const std::string &seq) const;

    // complement sequence
    std::string seqCompl(const std::string &seq) const;

    //Sequence encodée
 //   EncodedSequence Encode() const;


};

#endif // SEQUENCEFASTX_H_INCLUDED
