
#include "FastXFile.h"
#include"SequenceFastX.h"
#include"SequenceFastQ.h"
#include"SequenceFastA.h"




#include <iostream>


int main(int argc, char ** argv)
{

	try {
	
		//const char * file = argv[1];
		//const char* file = malloc(sizeof(argv[1] +1));
		FastXFile f1(argv[1]);
		//f1.setFilename(file);
	
		size_t i = 1;

		SequenceFastX * s1 = new SequenceFastX(*f1.getSequence(i));
		std::cout << (*(s1)).getFile()<< std::endl;

/*
		SequenceFastQ * sq = new SequenceFastQ(*s1);
		std::cout << (*sq).Score() << std::endl;

		//std::string seq = (*sq).getSeq();
		std::cout << (*sq).seqReverse((*sq).getSeq()) << std::endl;*/
		

		delete s1;
		//delete sq;



		//std::cout << (*s1).getSeq() << std::endl;
		//std::cout << (*s1).getSize() << std::endl;

		//SequenceFastQ sq;
		//SequenceFastX * seq = f1.getSequence(1);
		//seq = &sq;

		//std::cout << (*seq).getFile() << std::endl;

		//std::cout << (sq)


		//SequenceFastX s = f1.getSequence(i);
		//SequenceFastX * seq = &s;

		//SequenceFastX * seq = &sq;
		//std::cout << (f1.getSequence(i)).seqReverse((f1.getSequence(i)).getSeq()) << std::endl;
		//f1.DelReadN() ;
		//std::cout << s1.getHead() << std::endl;
		//std::cout << (*s1).getSize() << std::endl;

		//std::cout << (*s1).seqCompl(seq) << std::endl;
		//delete [] file;

	} catch (std::string &e) {
		std::cerr << e << std::endl;
	}

}
