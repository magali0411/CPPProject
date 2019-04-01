#ifndef SEQUENCEFASTQ_H_INCLUDED
#define SEQUENCEFASTQ_H_INCLUDED

#include<iostream>
#include "SequenceFastX.h"


class SequenceFastQ : public SequenceFastX
{
	public :

	char* m_score;


	public :

	//Constructeur 
	SequenceFastQ();
	SequenceFastQ(const char* &f, const size_t pos, size_t size, std::string head);
	// Constructeur par copie
	SequenceFastQ(const SequenceFastQ &seq);
	SequenceFastQ(const SequenceFastX &seq);

	// Destructeur
	 ~SequenceFastQ();

	//Getters & setters
	void setScore(const std::string &s);
	char* getScore() const;
	//std::string SequenceFastQ::Score() const {

	//Specialisation getSeq, récupère le score en même temps
	std::string getSeq();


}
;
#endif