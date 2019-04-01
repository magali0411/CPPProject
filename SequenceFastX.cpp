#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>


#include "SequenceFastX.h"
#include "utilities.h"

using namespace std;



// Constructeur

SequenceFastX::SequenceFastX(): 
    m_file(NULL),
    m_seqName(NULL),
    m_head(""),
    m_size(0),
    m_pos_seq(0),
    m_txGC(0)
    {}
    
SequenceFastX::SequenceFastX(const char* &f, const size_t pos, size_t size, std::string head) :
    m_file(NULL),
    m_seqName(NULL), 
    m_head(""),
    m_size(0),
    m_pos_seq(0),
    m_txGC(0)
{
    setFile(f);
    setPosSeq(pos);
    setSize(size);
    setHead(head);
}


// Destructeur
SequenceFastX::~SequenceFastX()
{ 
    clear();
}

//cleaner
void SequenceFastX::clear()
{
    if (m_seqName) {
        delete [] m_seqName;
        m_seqName =NULL;
    }
    if (m_file) {
        delete [] m_file;
        m_file =NULL;
    }
    m_head = "";
    m_size=0;
    m_pos_seq=0;
    m_txGC = 0;
}


// Constructeur par copie
SequenceFastX::SequenceFastX(const SequenceFastX &seq) : 
    m_file(myStrDup(seq.m_file)),
    m_seqName(myStrDup(seq.m_seqName)),
    m_head(seq.m_head),
    m_size(seq.m_size),
    m_pos_seq(seq.m_pos_seq),
    m_txGC(seq.m_txGC)
    {}


//operateur par copie
SequenceFastX &SequenceFastX::operator=(const SequenceFastX &seq){ 
    if(&seq != this) {
        m_file = myStrDup(seq.m_file);
        m_seqName = myStrDup(seq.m_seqName);
        m_pos_seq = seq.m_pos_seq;
        m_size = seq.m_size;
        m_txGC = seq.m_txGC;
        m_head = seq.m_head;
    }
    return *this;
} 

//operateur affichage
ostream& operator<<(ostream &os, const SequenceFastX &s)
{
    s.toStream(os);
    return os;
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
        clear();
    }

    m_file = myStrDup(f);
}



size_t SequenceFastX::getPosition() const
{
    return m_pos_seq;
}

void SequenceFastX::setPosSeq(const size_t pos)
{
    if (pos >= 0) {
        m_pos_seq = pos;
    } else {
        cerr << "Wrong conversion" << endl;
        m_pos_seq = 0;
    }
}



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
    os <<"Source file: " << m_file << endl;
}

// Sequence
string SequenceFastX::getSeq() const {

    ifstream ifs(m_file,ios_base::in);
    string sequence = "";

    if(ifs) {

        ifs.seekg(m_pos_seq);

        char c;
        while (ifs.peek() != '\n'){  
            c = ifs.get();
        }

        for(unsigned int p; p <= m_size; ++p) {
            c = ifs.get(); 
            if (isNucl(c)){
                sequence += c;
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

// taux GC
double SequenceFastX::GC(string &seq) const{

    double txGC(0);

    for(size_t i = 0 ; i <= m_size; ++i) {
        
        if (seq[i] == 'G' || seq[i] == 'C'){
            txGC ++; 
        }
    }

    return ((txGC /m_size) *100);

}


// Encoded sequence

EncodedSequence SequenceFastX::EncodeSeq() const
{

    size_t l= m_size;
    EncodedSequence es(l);
    string sequence = getSeq();
    char c;

    if (StringNotSeq(sequence)) {
        throw "Degenerated alphabet detected. Format non supported.";
    }
    for(size_t p =0; p< m_size; ++p){

        c = sequence[p];    
        es.setNucl(p,c);
            //cout << "------  " << c << endl;

    }

    return es;
}

