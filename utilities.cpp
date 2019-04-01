#include "utilities.h"
#include <cstring>

using namespace std;

enum
{
    BASE_A = 0x0, /* binary: 00 */
    BASE_T = 0x1, /* binary: 01 */
    BASE_G = 0x2, /* binary: 10 */
    BASE_C = 0x3 /* binary: 11 */
};


bool isSpace(char c) {
	return ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n') || (c=='\0'));
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

        if ((!(isNucl(s[i]))) || (s[i] == 'N'))
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


//StringDup
char* myStringDup (const string str){ //permet de faire une copie d'un string dans un char
    char* res=NULL;
    size_t n = str.length() + 1;
    res = new char[n];
    for (size_t i=0; i<n; ++i){
        res[i]=str[i];
    } 
    return res;
}
