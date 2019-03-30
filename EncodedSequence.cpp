#include "EncodedSequence.h"
using namespace std;

/*std::ostream &operator<<(std::ostream &os, const EncodedSequences &es){
    es.ostream(os);
    return os;
}*/

EncodedSequence::EncodedSequence(size_t n):
n(0), N(n ? getByte(n)+1:0), t(N ? new char[N]:NULL) {}

EncodedSequence::EncodedSequence(const EncodedSequence &es):
n(es.n),N(n ? getByte(n)+1:0),t(N ? new char[N]:NULL) {
    size_t N=getByte(n)+1;
    copy(es.t, es.t+N ,t);
}
EncodedSequence::~EncodedSequence(){
    clear();
}

EncodedSequence &EncodedSequence::operator=(const EncodedSequence &es){
    if(this != &es){
        
        clear();
        n=es.n;
        size_t N=getByte(n)+1;
        t= n ? new char[N] :
        copy(es.t, es.t +N, t);
    }
    return *this ;
}

void EncodedSequence::clear(){
    if(N){
        delete[]t;
        t=NULL;
        n=0;
        N=0;
    }
}

void EncodedSequence::reserve(size_t n){
    size_t N=getByte(n)+1;
    if(N > this->N){ //si N est plus grand que mon tableau actuel
        char *t = new char [N];
        copy(this->t , this->t+this->N,t);
        delete[]this->t;
        this->t=t;
        this->N=N;
    }
}

size_t EncodedSequence::getByte(size_t i){
    return i ? (i-1)>>2:0;
}

size_t EncodedSequence::getPosBytes(size_t i){
    return i ? (i-1)&3:0;
}

char EncodedSequence::encode(char c) const {
    return(((c=='a')||(c=='A'))
    ? 0 :
    (((c=='t')||(c=='T')||(c=='u')||(c=='U'))
    ? 1 :
    (((c=='g')||(c=='G'))
    ? 2 :
    (((c=='c')||(c=='C'))
    ? 3:
    (lrand48()&3)))));
}

char EncodedSequence::decode(char c) const {
    return((c==0)
    ? 'A' :
    ((c==1)
    ?'T' :
    ((c==2)
    ? 'G' :
    'C')));
}

char EncodedSequence::operator[](size_t i) const {
    if(i>n) {
        throw "out of boundaries"; 
    }
    char c=t[getByte(i)]; // recupere l'octet
    c>>=(3-getPosBytes(i))<<1; // correpond a une multiplication par 2
    return decode(c&3);
}

void EncodedSequence::setNucleo(size_t i, char c) {
    reserve(i);
    if(i>n){
        n=i;
    }
    char &b = t[getByte(i)];
    size_t shift = ((3-getPosBytes(i))<<1);
    b &= ~(3<<shift);
    b |= (encode(c)<<shift);
}

void EncodedSequence::toStream(std::ostream &os) const {
    for (size_t i=1; i<=n ; i++){
        os<< (*this)[i];
    }
}

EncodedSequences EncodedSequence::operator+=(char c){
    reserve(++n);
    char &B = t[getByte(n)];
    size_t shift = ((3-getPosBytes(n))<<1);
    B |= (encode(c)<<shift);
    return *this;

}

EncodedSequences EncodedSequence::reverseComplement() const {
    
}

;
