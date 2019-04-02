#include <iostream>
#include <cstring>
#include <fstream>


#include "SequenceFastQ.h"
#include "utilities.h"

using namespace std;

// Constructeurs 

SequenceFastQ::SequenceFastQ(const char* &f, const size_t pos, size_t size, string head) : 
    SequenceFastX(f, pos, size, head),
    m_score(NULL) {}

SequenceFastQ::SequenceFastQ(const SequenceFastQ &seq) : 
    SequenceFastX(seq),
    m_score(seq.m_score){}

SequenceFastQ::SequenceFastQ(const SequenceFastX &seq) : 
    SequenceFastX(seq),
    m_score(NULL){}

SequenceFastQ::SequenceFastQ(){}

// Destructeur
SequenceFastQ::~SequenceFastQ(){
    
    if (m_score){
        delete[] m_score;
    }

}



// set score
void SequenceFastQ::setScore(const string &s)
{
	if (m_score) 
	{
		delete [] m_score;
	}

    m_score= myStringDup(s);

}


char* SequenceFastQ::getScore() const{

    return m_score;

}


// Si on parse pour récupérer la séquence, on peut récuperer le score en même temps

string SequenceFastQ::getSeq() {

    cout << " file : " << m_file << endl;
    ifstream ifs(m_file,ios_base::in);
    string sequence;
    string score;

    if(ifs) {

        ifs.seekg(m_pos_seq);

        char c;
        while (ifs.peek() != '\n'){  
            c = ifs.get();
        }

        for(unsigned int p = 0 ; p <= m_size; ++p) {
            c = ifs.get(); 
            if (isNucl(c)){
                sequence += c;
            }
        }
        //cout << "sequence " << sequence << endl;
        //c = ifs.get();
        c = ifs.get(); // On mange le '/n fin de sequence'

        do {
            c = ifs.get();
        } while (c != '\n') ; 
        // on mange la ligne du +
        
        for(unsigned int q = 0 ; q <= m_size; ++q) {
            c = ifs.get(); 
            if(!isSpace(c)){
                score += c;
            }
        }
        setScore(score);


    } else{

        throw string("File has been moved or removed.");
    }

    ifs.close();
    return sequence;

}

//operateur affichage
ostream& operator<<(ostream &os, const SequenceFastQ &s)
 {
    s.toStream(os);
    return os;
 } 


void SequenceFastQ::toStream(ostream &os) const{
    SequenceFastX::toStream(os);
    cout << "Score qualité : "<< m_score << endl;

}


// void SequenceFastQ::testMethode() const {
//     cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << "Coucou" << endl;
// }


/*

    ifstream ifs(m_file,ios_base::in);
    string sequence;
    string score;

    if(ifs) {

        ifs.seekg(m_pos_seq);
        string line;
        getline(ifs, line);

        while(getline(ifs,line)&& line[0] != '>' && line[0] != ';' && line[0] != '@'){

        	if (getline(ifs,line) && line[0]=='+') 
        	{
        		if (line != m_head) 
        		{
        			throw string("Error while parcing");
        		}
        	}

        	else if (getline(ifs,line) && StringNotSeq(line)) 
        	{

        		for(size_t i = 0; i<line.size(); i++) {


               		if (line[i] != '\0') {

                    	score +=line[i];
                	}

            	}

        	}

        	else if (getline(ifs,line) && !StringNotSeq(line))
        	{

            	for(size_t i = 0; i<line.size(); i++) {


                	if (line[i] != '\0') {

                    	sequence +=line[i];
                	}

            	}

        	}

        }

        ifs.close();

        if (sequence.size() == score.size()) 
        {
        	setScore(score);
        	return sequence;
        }
        else 
        {
        	throw string("Error in file");
        }


    } else{

        throw string("File has been moved or removed.");
    }

}*/