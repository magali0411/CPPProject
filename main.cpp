
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

		SequenceFastX * s1 =  f1.getSequence(3);

		std::cout <<"Format détécté : " << f1.getFormat() << std::endl;

		//std::cout << (*(s1)).getFile()<< std::endl;
		std::cout << f1 << std::endl;



		std::string ss =  (*(s1)).getSeq();
		//(*(s1)).seqReverse(ss);

		std::cout << "Sequence brute : " << std::endl;
		std::cout << ss << std::endl;

		//std::cout << (*(s1)).GC(ss)<< std::endl;


///////////// ENCODEGAE SEQUENCE /////////////////////////////////


		//std::cout << *(s1) << std::endl;
		//(*(s1)).toStream(std::cout);

		std::cout << "----------- ENCODE ------------- "<< std::endl;


		EncodedSequence es = (*s1).EncodeSeq();

		std::cout << "Encoded Sequence : "<< std::endl;
		std::cout << es << std::endl;

		std::cout << "First char : " << es[0] << std::endl;

		std::cout << "Reverted compl Encoded Sequence : "<< std::endl;

		std::cout << es.reverseComplement() << std::endl;


//////////////////////////////////////////////////////////

		delete s1;
		


///////////// APPEL METHODE SEQX /////////////////////

		// TRanstypage pour arriver à nos fins...

/*		SequenceFastQ * s2;
		s2 = dynamic_cast<SequenceFastQ *>(s1); 

		std::cout << "T'es cassé ?" << std::endl;


		std::cout << s2 -> getScore() << std::endl;
		std::cout << s2 -> getSeq() << std::endl;


		delete s2;
		*/



//////////////////////////////////////////////////////



/*		SequenceFastQ * sq = new SequenceFastQ(*s1);
		//std::cout << (*sq).Score() << std::endl;

		std::string seq = (*sq).getSeq();

		(*sq).setName("Séquence n°1") ;
		std::cout << *sq << std::endl;


		//std::cout << (*sq).seqReverse(seq) << std::endl;

		std::cout << "----------- ENCODE ------------- "<< std::endl;
		EncodedSequence es = (*s1).EncodeSeq();
		std::cout << es << std::endl;
		std::cout << es[1] << std::endl;
		es += 'A';
		std::cout << es << std::endl;
		es.setNucl(2, 'C');
		std::cout << es << std::endl;
		std::cout << es.reverseComplement() << std::endl;



		

		delete s1;
		delete sq;
*/


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
		std::cerr << "ERREUR:" << e << std::endl;
	}

}
