#VAR
CXX = g++ 
CXX_FLAGS = -std=c++11 -Wall -ansi -pedantic 
LDFLAGS =
PROG = test
FILE = sequence.fasta
FILE2 = arabidopsis.fasta
FILE3 = sequence.fastq
FILE4 = sequence2.fastq

#  EncodedSequences.cpp
SOURCES = \
  FastXFile.cpp \
  main.cpp \
  SequenceFastA.cpp \
  SequenceFastQ.cpp \
  SequenceFastX.cpp \
  utilities.cpp

#  EncodedSequences.h

HEADERS = \
  FastXFile.h \
  SequenceFastA.h \
  SequenceFastQ.h \
  SequenceFastX.h \
  utilities.h

OBJ=$(SOURCES:.cpp=.o)

all : $(PROG)

$(PROG): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

#Compilation

.SUFFIXES: .cpp .h .o

.cpp.o:
	$(CXX) $(CXX_FLAGS) -c  $< -c

EncodedSequences.o: EncodedSequences.cpp EncodedSequences.h

FastXFile.o: FastXFile.cpp FastXFile.h SequenceFastX.h SequenceFastA.h utilities.h

main.o: main.cpp FastXFile.h SequenceFastX.h SequenceFastA.h

SequenceFastA.o: SequenceFastA.cpp SequenceFastA.h SequenceFastX.h

SequenceFastQ.o: SequenceFastQ.cpp SequenceFastQ.h SequenceFastX.h

SequenceFastX.o: SequenceFastX.cpp SequenceFastX.h

utilities.o: utilities.cpp utilities.h

#Execution
run :
	./$(PROG) $(FILE3)

# Suppression des .o

clear :
	rm -f $(OBJ)
	rm -f $(PROG)

