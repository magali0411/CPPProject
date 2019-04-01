#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <string>

bool isSpace(char c);
bool isNucl(char c);
bool StringNotSeq(const std::string &s);
char* myStrDup (const char* s); //permet de faire une copie d'un tableau de char
char* myStringDup (const std::string str) ;
#endif
