#ifndef SEQUENCEFASTQ_H_INCLUDED
#define SEQUENCEFASTQ_H_INCLUDED

#include<iostream>
#include "SequenceFastX.h"


class SequenceFastQ : virtual public SequenceFastX
{
	protected :
	char* m_score;

	public :


	//Constructeur 
	SequenceFastQ();
	SequenceFastQ(const char* &f, const size_t pos, size_t size, std::string head);
	SequenceFastQ(const SequenceFastQ &seq);
	SequenceFastQ(const SequenceFastX &seq);

	// Destructeur
	 ~SequenceFastQ();

	//Operateur
    friend std::ostream& operator<<(std::ostream &os, const SequenceFastQ &s); 


    //Méthodes
	void setScore(const std::string &s);
	char* getScore() const;
	//std::string SequenceFastQ::Score() const {

	//Specialisation getSeq, récupère le score en même temps
	virtual std::string getSeq();

	//surcharge 2S
    virtual void toStream(std::ostream &os) const;

	//virtual void testMethode() const;

}
;
#endif