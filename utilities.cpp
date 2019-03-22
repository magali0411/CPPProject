#include "utilities.h"
#include <cstring>

using namespace std;

bool isSpace(char c) {
	return ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'));
}

// Char is nucl
bool isNucl(char c)
{

    return ((c == 'A') || (c == 'a')
        || (c == 'T') || (c == 't')
        || (c == 'C') || (c == 'c')
        || (c == 'G') || (c == 'g')
        || (c == 'N') || (c == 'n'));
}

// Not nucl
bool StringNotSeq(const string &s)
{

    bool notnucl = false;

    for(size_t i = 0; i<s.size(); i++) {

        if (!(isNucl(s[i])))
        {

            if(s[i] != '\n' || s[i] != ' ') {
                notnucl = true;
                break;
            }

        }

    }
    return notnucl;

}

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
