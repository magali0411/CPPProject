#include <iostream>
#include <cstring>


#include "SequenceFastA.h"

using namespace std;

SequenceFastA::SequenceFastA(string sequence, size_t size, string head) : SequenceFastX(sequence, size, head){

	cout << "FastaSeq created" << endl;

}

SequenceFastA::SequenceFastA(const SequenceFastA &seq) {

	m_sequence = seq.m_sequence;
	m_size = seq.m_size;
	m_head = seq.m_head;
} 

SequenceFastA::SequenceFastA(){}

SequenceFastA::~SequenceFastA(){

}

