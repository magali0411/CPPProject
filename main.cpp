
#include "FastXFile.h"
#include"SequenceFastX.h"




#include <iostream>


int main(int argc, char ** argv)
{

	try {
	
		//const char * file = argv[1];
		//const char* file = malloc(sizeof(argv[1] +1));
		FastXFile f1(argv[1]);
		//f1.setFilename(file);
	

		//std::cout << " Nombre de seq detectées :" << f1.getNbSeq() << std::endl;
		
		f1.getSequence(1);

		size_t i = 1;
		//SequenceFastX * s1 = f1.getSequence(i);
		std::cout << (f1.getSequence(i)).getHead() << std::endl;
		std::cout << (f1.getSequence(i)).getSeq() << std::endl;
		std::cout << (f1.getSequence(i)).getSize() << std::endl;

		std::cout << (f1.getSequence(i)).seqReverse((f1.getSequence(i)).getSeq()) << std::endl;


		//std::cout << s1.getHead() << std::endl;
		//std::cout << (*s1).getSize() << std::endl;

		//std::string seq = (*s1).getSeq();
		//std::cout << (*s1).seqReverse(seq) << std::endl;
		//std::cout << (*s1).seqCompl(seq) << std::endl;


		//delete s1;
		//delete [] file;

	} catch (std::string &e) {
		std::cerr << e << std::endl;
	}

}
