
#include "FastXFile.h"
#include"SequenceFastX.h"




#include <iostream>


int main(int argc, char ** argv)
{

	try {
	
		const char * file = argv[1];
		FastXFile f1(file);
		//f1.setFilename(file);
	
		//size_t i = 1;
		std::cout << " Nombre de seq detectées :" << f1.getNbSeq() << std::endl;
	
		//SequenceFastX  * s1 = f1.getSequence(i);
		//std::cout << f1.getSequence(i) -> getHead() << std::endl;
		//std::cout << (*s1).getSeq() << std::endl;
		//std::string seq = (*s1).getSeq();
		//std::cout << (*s1).seqReverse(seq) << std::endl;
		//std::cout << (*s1).seqCompl(seq) << std::endl;


		//delete s1;
		//delete [] file;
	} catch (std::string &e) {
		std::cerr << e << std::endl;
	}

}
