
#include "FastXFile.h"
#include"SequenceFastX.h"
#include"SequenceFastQ.h"
#include"SequenceFastA.h"
#include"EncodedSequence.h"




#include <iostream>




int main(int argc, char ** argv)
{

	// SequenceFastA ta;
	// SequenceFastQ tq;
	// std::cout << "TA:";
	// ta.testMethode();
	// std::cout << "TQ:";
	// tq.testMethode();


	// SequenceFastX *ptr;

	// ptr = &ta;
	// std::cout << "TA:";
	// ptr->testMethode();

	// ptr = &tq;
	// std::cout << "TQ:";
	// ptr->testMethode();

	// return 0;

	try {

		FastXFile f1(argv[1]);

		//f1.setFilename(argv[1]);
	
		//size_t i = 1;

		SequenceFastX * s1 =  f1.getSequence(2);

		std::cout <<"Format détécté : " << f1.getFormat() << std::endl;

		//std::cout << (*(s1)).getFile()<< std::endl;
		std::cout << f1 << std::endl;
		std::string ss =  (*(s1)).getSeq();


		std::cout << "Sequence brute : " << std::endl;
		std::cout << ss << std::endl;

		std::cout << "Sequence Reverted : " << std::endl;
		std::cout << (*(s1)).seqReverse(ss) << std::endl ;

		std::cout << "Seq compl : " << std::endl;
		std::cout << (*s1).seqCompl(ss) << std::endl;



		std::cout << "Entete : " << std::endl;
		std::cout << s1 -> getHead() << std::endl;

		std::cout << "Taille séquence: " << std::endl;
		std::cout << (*s1).getSize() << std::endl;

		std::cout << "Taux GC : " << std::endl;
		std::cout << (*(s1)).GC(ss)<< std::endl;


///////////// ENCODEGAE SEQUENCE /////////////////////////////////


		//std::cout << *(s1) << std::endl;
		//(*(s1)).toStream(std::cout);

		std::cout << "----------- ENCODE ------------- "<< std::endl;


		EncodedSequence es = (*s1).EncodeSeq();

		std::cout << "Encoded Sequence : "<< std::endl;
		std::cout << es << std::endl;
		//std::cout << es[115] << std::endl;

		std::cout << "First char : " << es[0] << std::endl;

		std::cout << "Rev compl  : "<< std::endl;

		std::cout << es.reverseComplement() << std::endl;


//////////////////////////////////////////////////////////		


///////////// APPEL METHODE SEQX /////////////////////

		// TRanstypage pour arriver à nos fins...
/*
		std :: cout << "---------- DYNAMIC CAST ---------" << std::endl;
		SequenceFastQ * s2;
		s2 = dynamic_cast<SequenceFastQ *>(s1); 


		std::cout << s2 -> getScore() << std::endl;
		std::cout << s2 -> getSeq() << std::endl;


		delete s2;*/
		


//////////////////////////////////////////////////////

/*		SequenceFastQ * sq = new SequenceFastQ(*s1);
		//std::cout << (*sq).Score() << std::endl;

		std::string seq = (*sq).getSeq();

		(*sq).setName("Séquence n°1") ;
		std::cout << *sq << std::endl;

		delete s1;

		delete sq;*/


		//std::cout << (*sq).seqReverse(seq) << std::endl;

	
		delete s1;

	} catch (std::string &e) {
		std::cerr << "ERREUR:" << e << std::endl;
	}

}
