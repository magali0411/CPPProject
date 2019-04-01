#include <stdlib.h>
#include <iostream>



#include "EncodedSequence.h"
using namespace std;


EncodedSequence::EncodedSequence(size_t n):
n(0), N(n ? getByte(n)+(1%4 !=0):0), t(N ? new char[N]:NULL) {
} // On établit N et on rajoute +1 seulement si nécéssaire

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
    size_t N=getByte(n)+(1%4 != 1) ;
    if(N > this->N){ //si N est plus grand que la taille actuelle reservée pour ma séquence
        char *t = new char [N];
        copy(this->t , this->t+this->N,t); // Copie de notre séquence encodée dans un new tab t
        delete[]this->t; 
        this->t=t;
        this->N=N;
    }
}

size_t EncodedSequence::getByte(size_t i){
    return i ? (i-1)>>2:0;
} // Décalage de deux vers la gauche du nombre de nucl de notre séquence
// Cela équivaut à diviser par 4 sa taille et donc obtenir la taille
// nécessaire pour stocker la séquence 

size_t EncodedSequence::getPosByte(size_t i){
    return i ? (i-1)&3:0;
} // masquage des bits autour du nucléotide demandé

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
    char c=t[getByte(i)]; // recupere l'octet dans lequel se trouve notre nucléotide i
    c>>=(3-getPosByte(i))<<1; // 11 - (nucl/2)
    return decode(c&3); // Masquage 
}

void EncodedSequence::setNucl(size_t i, char c) {
    reserve(i); // update de la taille reservée pour la sequence
    if(i>n){
        n=i;
    }// taile seq
    char &b = t[getByte(i)]; // adresse de l'octet dans lequel on va stocker le nucléotide
    size_t shift = ((3-getPosByte(i))<<1); //Décalage 
    b &= ~(3<<shift); // L'adresse dans l'octet est décalée
    b |= (encode(c)<<shift); // on encode c à l'adresse B au bon décalage
}

void EncodedSequence::toStream(std::ostream &os) const {
    for (size_t i=1; i<=n ; i++){
        os<< (*this)[i];
    }
}

//operateur affichage
ostream& operator<<(ostream &os, const EncodedSequence &es)
{
    es.toStream(os);
    return os;
} 

EncodedSequence EncodedSequence::operator+=(char c){
    reserve(++n);//  Ré-allocation de mémoire et incrémentation de n
    char &B = t[getByte(n)];
    size_t shift = ((3-getPosByte(n))<<1);
    B |= (encode(c)<<shift);
    return *this;

}// ajout rapide d'un char 


EncodedSequence EncodedSequence::reverseComplement() const {

    EncodedSequence es(n);
    EncodedSequence ref(*this);
    char c;
    char g;

    for(size_t p =0; p<= n; ++p){

        c = ref[n-p];
        if (c == 'A') { g ='T';}
        else if (c == 'T') { g ='A';}
        else if (c == 'G') { g ='C';}
        else{ g = 'G';}
        es.setNucl(p,g);
    }

    return es;
} // Un peu cassée, mais l'idée est là
