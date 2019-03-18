#include <iostream>
#include <cstring>


#include "SequenceFastX.h"
//#include "FastXFile.h"

using namespace std;

//myStrDup
char* myStrDup (const char* s){ //permet de faire une copie d'un tableau de char
    char* res=NULL;
    if(s){
        size_t n = strlen(s)+1; //taille du tableau s +1
        res = new char[n]; // initialise le tableau avec la taille recup
        for (size_t i=0; i<n; ++i){
            res[i]=s[i];
        } 
    }
    return res;
}

// Destructeur
SequenceFastX::~SequenceFastX()
{ 
    if (m_seqName){
        delete[] m_seqName;
    }

}

// Constructeur

SequenceFastX::SequenceFastX(): m_seqName(NULL){}
    
SequenceFastX::SequenceFastX(std::string sequence, size_t size, std::string head)
{

    setHead(head);
    setSize(size);
    m_sequence = sequence;

}

// Constructeur par copie
SequenceFastX::SequenceFastX(const SequenceFastX &seq){
    if (m_seqName){

        delete[] m_seqName;
    }

    m_seqName=myStrDup(seq.m_seqName);
    m_size = seq.m_size;
    m_head = seq.m_head; 
}



// Getters & Setter

char* SequenceFastX::getName() const
{
    return m_seqName;
}
void SequenceFastX::setName(const char* s)
{
    if(m_seqName){
        delete[] m_seqName;
    }
    m_seqName = myStrDup(s);
}

string SequenceFastX::getHead() const
{
    return m_head;
}

void SequenceFastX::setHead(string h) {

    m_head = h;
}


size_t SequenceFastX::getSize() const
{
    return m_size;
}

void SequenceFastX::setSize(size_t size) 
{

    if (size > 0) {
        m_size = size;
    } else {
        m_size = 0;
        throw string("Inexistent sequence");
    }

}

// position
// const char* SequenceFastX::getSeq() const
// {
//     return m_seq;
// }

/*void SequenceFastX::setPos(const char* &seq)
{
    m_seq = myStrDup(seq);
}
*/
// Tostream
void SequenceFastX::toStream(ostream &os) const{
    if(m_seqName != NULL){
        os << "File: " << m_seqName << endl;
    } else {
        os << "File: " << "<no name>" << endl;
    }
    os << "Informations: " << m_head << endl;
}


/*
vector<char> SequenceFastX::seqCompl() const
{

    size_t l = m_seq.size();
    vector<char> res;
    for (size_t i =0; i < l; i++)
    {
        switch(m_seq[i])
        {
        case'A' :
            res.push_back('T') ;
            break;

        case'T' :
            res.push_back('A') ;
            break;

        case'C' :
            res.push_back('G') ;
            break;

        case'G' :
            res.push_back('C') ;
            break;
        default :
            res.push_back('X');
            break;
        }
    }
    for(int i(0); i < res.size() ; i ++)
    {
        cout << res[i] ;
    }
    return res;
}

vector<char> SequenceFastX::seqRev() const
{
    size_t l = m_seq.size();
    vector<char> res;
    for (size_t i =l; i > 0; i--)
    {
        res.push_back(m_seq[i-1]);
    }
    for(int i(0); i < res.size() ; i ++)
    {
        cout << res[i] ;
    }
    return res;
}*/

