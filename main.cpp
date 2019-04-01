
#include "FastXFile.h"
#include"SequenceFastX.h"
#include"SequenceFastQ.h"
#include"SequenceFastA.h"
#include"EncodedSequence.h"




#include <iostream>




int main(int argc, char ** argv)
{

	try {
	
		//const char * file = argv[1];
		//const char* file = malloc(sizeof(argv[1] +1));
		FastXFile f1(argv[1]);
		//f1.setFilename(file);
	
		//size_t i = 1;

		std::cout << f1.getFormat() << std::endl;


		SequenceFastQ * s1 = new SequenceFastQ(*f1.getSequence(2));
		//std::cout << (*(s1)).getFile()<< std::endl;
		std::cout << f1 << std::endl;
		//std::cout << (*(s1)).getSeq()<< std::endl;
		std::string ss =  (*(s1)).getSeq();
		
		//std::cout << (*(s1)).GC(ss)<< std::endl;


		std::cout << *(s1) << std::endl;



		delete s1;


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
		std::cerr << e << std::endl;
	}

}
