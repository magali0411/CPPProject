#include <iostream>
#include <cstring>
#include <fstream>


#include "SequenceFastX.h"

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

// Constructeur

SequenceFastX::SequenceFastX(): m_seqName(NULL), m_file(NULL), m_pos_seq(0) {}
    
SequenceFastX::SequenceFastX(const char* &f, const size_t pos, size_t size, std::string head) : m_seqName(NULL), m_pos_seq(pos)
{

    setHead(head);
    setSize(size);
    setFile(f);

}


// Destructeur
SequenceFastX::~SequenceFastX()
{ 
    if (m_seqName){
        delete[] m_seqName;
    }

    if(m_file){
        delete [] m_file;
    }

}

//cleaner
void SequenceFastX::clear()
{
    m_seqName=NULL;
    m_file=NULL;
    m_head = "";
    m_size=0;
    //m_pos_seq=0;
    m_txGC = 0;
}


// Constructeur par copie
SequenceFastX::SequenceFastX(const SequenceFastX &seq) : m_pos_seq(seq.m_pos_seq)
{
    if (m_seqName){

        delete[] m_seqName;
    }

    if(m_file) {
        delete[] m_file;
    }

    m_seqName= myStrDup(seq.m_seqName);
    m_size = seq.m_size;
    m_head = seq.m_head; 
    m_file = myStrDup(seq.m_file);
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



const char * SequenceFastX::getFile() const
{
    return m_file;
}

void SequenceFastX::setFile(const char* &f)
{

    if (m_file){

        delete [] m_file;
    }

    m_file = myStrDup(f);
}



const size_t SequenceFastX::getPosition() const
{
    return m_pos_seq;
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
    os <<"Fichier mère: " << m_file << endl;
}

// Sequence
string SequenceFastX::getSeq() const {

    ifstream ifs(m_file,ios_base::in);
    string sequence;

    if(ifs) {

        ifs.seekg(m_pos_seq);
        string line;
        getline(ifs, line);
        while(getline(ifs,line)&& line[0] != '>' && line[0] != ';' && line[0] != '@'){

            for(size_t i = 0; i<line.size(); i++) {


                if (line[i] != '/0') {

                    sequence +=line[i];
                }

            }
        }


    } else{

        throw string("File has been moved or removed.");
    }

    return sequence;

}

// complement sequence
string SequenceFastX::seqCompl(const string &seq) const 
{

    size_t size = seq.size();
    string res;

    for(size_t i=0; i<size ;i++) {

        switch(seq[i])
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
            res.push_back('-');
            break;
        }
    }   

    return res;
}

// Sequence reverse
string SequenceFastX::seqReverse(const std::string &seq) const
{
    size_t size = seq.size();
    string rev;

    for (size_t i=size; i > 0; i--)
    {
        rev += (seq[i-1]);

    }
    return rev;
}


