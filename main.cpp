
#include "FastXFile.h"
#include"SequenceFastX.h"




#include <iostream>


int main(int argc, char ** argv)
{

	const char * file = argv[1];
	FastXFile f1(file);
	f1.setFilename(file);
	size_t i = 0;
	
	//f1.getSequence(i) -> toStream(std::cout);
	std::cout << f1.getSequence(i) -> getHead() << std::endl;
	std::cout << f1.getSequence(i) -> getSeq() << std::endl;

	//f1.getSequence(i).getSeq();


}
