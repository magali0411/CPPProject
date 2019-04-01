#ifndef SEQUENCEFASTA_H_INCLUDED
#define SEQUENCEFASTA_H_INCLUDED

#include<iostream>
#include "SequenceFastX.h"


class SequenceFastA : public SequenceFastX
{

	private :


	public :

	//Constructeur 
	SequenceFastA();
	SequenceFastA(const char* &f, const size_t pos, size_t size, std::string head);

	// Constructeur par copie
	SequenceFastA(const SequenceFastA &seq);
	SequenceFastA(const SequenceFastX &seq);


	// Destructeur
	~SequenceFastA();

	//surcharge 2S

};

#endif //SEQUENCEFASTA_H_INCLUDED
