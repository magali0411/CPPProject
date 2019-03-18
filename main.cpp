
#include "FastXFile.h"
#include"SequenceFastX.h"




#include <iostream>


int main(int argc, char ** argv)
{
	try {
		const char * file = argv[1];
		FastXFile f1(file);
		f1.setFilename(file);
		size_t i = 1;
	
		f1.getSequence(i) -> toStream(std::cout);
	
		//std::cout << f1.getFormat() << std::endl;
	}

	catch (std::exception const &exc)
    {
        std::cerr << "Exception caught " << exc.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught\n";
    }

	//f1.getSequence(i).getSeq();

	/*std::cout << "essai 2 " << std::endl;
	SequenceFastX s1;
	s1 = f1.getSequence(i);
	s1.setName(seq);
	s1.toStream(std::cout);*/



}
