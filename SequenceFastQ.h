#ifndef SEQUENCEFASTQ_H_INCLUDED
#define SEQUENCEFASTQ_H_INCLUDED

#include<iostream>
#include "SequenceFastX.h"


class SequenceFastQ : public SequenceFastX
{
	private :

	char* m_score;


	public :

	//Constructeur 
	SequenceFastQ();
	SequenceFastQ(const char* &f, const size_t pos, size_t size, std::string head);
	// Constructeur par copie
	SequenceFastQ(const SequenceFastQ &seq);

	// Destructeur
	virtual ~SequenceFastQ();

	//Getters & setters
	void setScore(std::string &s);
	char* getScore() const;

	//Specialisation getSeq
	std::string getSeq();


}
;
#endif