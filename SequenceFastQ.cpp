#include <iostream>
#include <cstring>
#include <fstream>


#include "SequenceFastQ.h"
#include "utilities.h"

using namespace std;

// Constructeurs 

SequenceFastQ::SequenceFastQ(const char* &f, const size_t pos, size_t size, string head) : 
    SequenceFastX(f, pos, size, head){
    }

SequenceFastQ::SequenceFastQ(const SequenceFastQ &seq) : 
    SequenceFastX(seq){}

SequenceFastQ::SequenceFastQ(){}

// Destructeur

/*SequenceFastQ::~SequenceFastQ(){
    if (m_seqName){
        delete[] m_seqName;
    }

    if(m_file){
        delete[] m_file;
    }

}*/



// set score
void SequenceFastQ::setScore(string &s)
{

	if (m_score) 
	{
		delete [] m_score;
	}
	strcpy(m_score, s.c_str());
}

// Specialisation getSeq

// Sequence
string SequenceFastQ::Score() const {

    ifstream ifs(m_file,ios_base::in);
    string sequence;
    string score;

    cout << "THIS ONNNNE" << endl;

    if(ifs) {

        ifs.seekg(m_pos_seq);

        char c;
        while (ifs.peek() != '\n'){  
            c = ifs.get();
        }

        for(unsigned int p; p <= m_size; ++p) {
            c = ifs.get(); 
            if (isNucl(c)){
                sequence += c;
            }
        }

        c = ifs.get(); // On mange le '/n fin de sequence'

        do {
            c = ifs.get();
        } while (ifs.peek() != '\n') ; 
        // on mange la ligne du +
        
        for(unsigned int q; q <= m_size; ++q) {
            c = ifs.get(); 
            if (isNucl(c)){
                score += c;
            }
        }

    } else{

        throw string("File has been moved or removed.");
    }

    return score;

}

/*
string SequenceFastQ::getSeq() {

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