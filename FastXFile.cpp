#include "FastXFile.h"


#include <cstring>
#include <iostream>
#include <fstream>
using namespace std ;

/*char FastXFile::operator[](size_t i) const {

}*/


// constructeur 
FastXFile::FastXFile(const char* f):
    m_filename(NULL),m_position(NULL),m_nbSeq(0),m_format(0) {
    setFilename(f); 
    }

//constructeur par copie 
FastXFile::FastXFile(const FastXFile &f){
    m_filename=myStrDup(f.m_filename), m_format= f.m_format,m_position=(f.m_position ? new size_t [f.m_nbSeq] : NULL), m_nbSeq=(f.m_nbSeq); 
    for (size_t i=0 ; i<m_nbSeq ; i++){
           m_position[i]=f.m_position[i];
       }
   }

void FastXFile::clear(){
    m_filename=NULL;
    m_position=NULL;
    m_format=0;
    m_nbSeq=0;   
}


//destructeur
FastXFile::~FastXFile(){
    if (m_filename){
        delete[] m_filename;
    }
    if (m_position){
        delete[] m_position;
    }
}
//operator <<
ostream& operator<<(ostream &os, const FastXFile &f){
    f.toStream(os);
    return os;
}


//operateur par copie
FastXFile &FastXFile::operator=(const FastXFile &f){ // & va chercher l'objet à l'adresse ne fait pas de copie 
    if(&f != this) {
        clear();
        m_filename = f.m_filename;
        m_position = f.m_position;
        m_nbSeq = f.m_nbSeq;
        m_format = f.m_format;
        }
    return *this;
    } 

// Getters & Setters 
string FastXFile::getFormat() const 
{
	if(m_format ==1)
	{
		return "fastA";
	}
	if(m_format ==2)
	{
		return "fastQ";
	}
}
void FastXFile::setFormat(int format)

{
	if(format ==1 || format ==2)
	{
		m_format = format;
	}
	else{

		throw "Unknow Format";
	}
}


//Definition nom fichier
void FastXFile::setFilename(const char * &f){
    if(m_filename){
        delete[] m_filename;
	}
	if (m_position){
		delete[] m_position;
		m_position = NULL;
    }
    m_nbSeq = 0;
    m_filename= myStrDup(f);
    if (m_filename){
        myparse();
    }
}

//Nombre de sequences
size_t FastXFile::getNbSeq() const {
    return m_nbSeq;
}

//Recuperation Nom du fichier 
const char* FastXFile::getFileName() const{
    return m_filename;
}

//ToStream
void FastXFile::toStream(ostream &os ) const{
    os<< "fichier: " << (m_filename ? m_filename: "pas de fichier") << endl ;
	os << "le fichier contient: " << m_nbSeq  <<" sequences" << endl;
}

void FastXFile::myparse(){

	ifstream ifs(m_filename,ios_base::in);
	if (!ifs){
		throw "unable to open this file"; 
	}

	char c = '\n';

	while (ifs && (isspace(ifs.peek()))){ 
		c = ifs.get();
	} // retirer les espaces
    
	if (ifs){
		if(c == '\n'){
			c = ifs.peek(); 
			if ((c == '>')||(c == ';')) { 
				c = '\n';
				//this <- setFormat(1);
				setFormat(1);
			}
			if (c == '@') {
				c = '\n';
				setFormat(2);
			}
		}
	}

	if (c != '\n'){
		throw string("error"); 
	}else{

		if(m_format==1) 
		{

			do{ 
        //penser ajouter traitement pour verifier que ce soit bien des nucléotides/prots dans le encodedSequence
			string s;
			getline(ifs,s);
			m_nbSeq += ((s[0] ==  '>') || (s[0] == ';'));
			}
			while (ifs);
		
			m_position = new size_t [m_nbSeq]; // tableau de la taille du nb de sequences 
			m_nbSeq = 0 ;
			ifs.clear();
			ifs.seekg(0); // seeqg positionne le marqueur à la position entre ()
			size_t p = ifs.tellg(); // recupere la position du marqueur dans le flux

			do{
				string s;
				getline(ifs,s);
				if ((s[0] ==  '>') || (s[0] == ';')){ 
					m_position[m_nbSeq ++]= p; // le tableau a la position du numero de la sequence prend 
                                    //la valeur p donc la position de debut de la sequence puis incremente de 1 le nb_seq
				}
				p = ifs.tellg();
			}
        	while (ifs);
		}

		else if(m_format ==2)
		{

			cout << "FastaQ detected, format= " << m_format << endl;
		}

/*        for(unsigned int i=0; i <= m_nbSeq; i++){

        	cout << "Tableau à l'indice " << i <<": "<< m_position[i] << endl;
        }*/
	}

	ifs.close();
}

// A faire avec une enum
bool FastXFile::seqCheck(size_t posheader) const{

	ifstream ifs(m_filename,ios_base::in);
	char c = '\0';
	bool format(false);

	if (ifs) {
		if (posheader < 0) {

			throw string("Out of range");

		} else {
			ifs.seekg(posheader);
			c = ifs.peek();

			// Si un espace est avant la sequence
			while (ifs && (isspace(ifs.peek()))){ 
				c = ifs.get();
			} 

			c = ifs.peek();

			// fastA
			if (m_format == 1 && (c == ';' || c == '>'))
			{
				format = true;
			}
			//fastQ
			else if (c == '@' && m_format == 2) 
			{
				format = true;

			} else {
				throw string("Format not supported");
			}
		}

		ifs.close();

	} else {

		throw logic_error("No file");
	}

	return format;
}

SequenceFastX* FastXFile::getSequence(size_t i) const{

	//cout << "position de la séquence : " << m_pos[i] << endl;

	// verif
	if (i >= m_nbSeq) {
		throw "Sequence out of range";
	} else {

	//string sequence; 
	string header;
	string line;
	const char* name = myStrDup(m_filename);
	size_t pos_debut = m_position[i];
	size_t length(0);
	SequenceFastX * seq;

	ifstream ifs(m_filename,ios_base::in);


	if(ifs && seqCheck(pos_debut)){

		ifs.seekg(pos_debut);
		getline(ifs, line);
		header = line;

        while(getline(ifs,line)&& line[0] != '>' && line[0] != ';' && line[0] != '@'){

        	for(size_t i = 0; i<line.size(); i++) {

            	if (line[i] != '/0') {

            		length ++;
            		//sequence +=line[i];
            	}

            }
        }

		//cout << "sequence :"<< sequence << endl;
		//cout << "length :"<< length << endl;

		if (m_format == 1) {

        	seq = new SequenceFastA(name, pos_debut, length, header);

        } 
        
        if (m_format == 2 ){

           	seq = new SequenceFastX(name, pos_debut, length, header);
        }
		ifs.close();
		delete [] name;

	}else {

		throw string("Error in file.");
	}
	return seq;
	}

}

