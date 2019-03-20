
#include "FastXFile.h"
#include"SequenceFastX.h"




#include <iostream>


int main(int argc, char ** argv)
{

	const char * file = argv[1];
	FastXFile f1(file);
	//f1.setFilename(file);
	//size_t i = 0;
	
	//SequenceFastX  * s1 = f1.getSequence(i);
	//std::cout << f1.getSequence(i) -> getHead() << std::endl;
	//std::cout << (*s1).getSeq() << std::endl;
	//std::string seq = (*s1).getSeq();
	//std::cout << (*s1).seqReverse(seq) << std::endl;
	//std::cout << (*s1).seqCompl(seq) << std::endl;


	//delete s1;


}
