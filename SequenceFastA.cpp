#include <iostream>
#include <cstring>


#include "SequenceFastA.h"

using namespace std;

SequenceFastA::SequenceFastA(const char* &f, const size_t pos, size_t size, string head) : 
	SequenceFastX(f, pos, size, head){
	}

SequenceFastA::SequenceFastA(const SequenceFastA &seq) : 
	SequenceFastX(seq){}

SequenceFastA::SequenceFastA(const SequenceFastX &seq) : 
    SequenceFastX(seq){}

SequenceFastA::SequenceFastA(){}

SequenceFastA::~SequenceFastA(){}


