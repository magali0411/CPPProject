#ifndef SEQUENCEFASTX_H_INCLUDED
#define SEQUENCEFASTX_H_INCLUDED

#include<iostream>


char* myStrDup (const char* s);

class SequenceFastX{

    // ATTRIBUTS
    protected :
    
    char* m_seqName;

    std::string m_head;
    size_t m_size;
    std::string m_sequence;

    float m_txGC;


    public :

    // Constructeur
    SequenceFastX();
    SequenceFastX(std::string sequence, size_t size, std::string head);
    SequenceFastX(const SequenceFastX &seq);


    //Destructeur 
    ~SequenceFastX() ;

    //my strdup()
    //const char * myStrDup (const char * s);

    // SETTERS & GETTERS 

    //nom de la séquence
    char* getName() const;
    void setName(const char*);


    //séquence nucléotidique
    const std::string getSeq() const;
    void setSeq(char* seq);

    // Retourne les infos relatives à une séquence aka l'header
    std::string getHead() const;
    void setHead(std::string header);

    //longueur séquence
    size_t getSize() const;
    void setSize(size_t size);

    //sequence
    //const char* getSeq() const;
    //void setSeq(const char* &seq);

    // Methodo

    //Tostream
    void toStream(std::ostream &os) const;

    // Méthode calcul GC


    // Séquence complémentaire

    //Séquence reverse


};

#endif // SEQUENCEFASTX_H_INCLUDED
