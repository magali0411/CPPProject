#VAR
CXX = g++ 
CXX_FLAGS = -Wall -ansi -pedantic 
OUT = test
FILE = sequence.fasta
FILE2 = arabidopsis.fasta

all : SequenceFastA.o SequenceFastX.o FastXFile.o main.o 
	$(CXX) $(CXX_FLAGS) $^ -o $(OUT)

#Compilation

SequenceFastA.o : SequenceFastA.cpp SequenceFastA.h
	$(CXX) $(CXX_FLAGS) -c  SequenceFastA.cpp -o $@

SequenceFastX.o : SequenceFastX.cpp SequenceFastX.h
	$(CXX) $(CXX_FLAGS) -c  SequenceFastX.cpp -o $@


FastXFileX.o : FichierFastX.cpp FichierFastX.h
	$(CXX) $(CXX_FLAGS) -c  FichierFastX.cpp -o $@

main.o : main.cpp
	$(CXX) $(CXX_FLAGS) -c main.cpp -o $@


#Execution
run :
	./$(OUT) $(FILE)

# Suppression des .o

clear :
	rm -f *.o $(OUT)

