#include "FastXFile.h"
#include "utilities.h"


#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std ;

/*char FastXFile::operator[](size_t i) const {

}*/


// constructeur 
FastXFile::FastXFile(const char* f):
    m_filename(NULL),m_format(UNDEF),m_position(NULL),m_nbSeq(0) {
    setFilename(f); 
    }

//constructeur par copie 
FastXFile::FastXFile(const FastXFile &f):
    m_filename(myStrDup(f.m_filename)),
    m_format(f.m_format),
    m_position(f.m_position ? new size_t [f.m_nbSeq] : NULL),
    m_nbSeq(f.m_nbSeq)
{
    for (size_t i=0 ; i<m_nbSeq ; i++){
        m_position[i]=f.m_position[i];
    }
}

void FastXFile::clear(){
    if (m_filename) {
    	delete [] m_filename;
    	m_filename = NULL;
    }
    if (m_position) {
    	delete [] m_position;
	    m_position = NULL;
	}
    m_format = UNDEF;
    m_nbSeq=0;
}


//destructeur
FastXFile::~FastXFile(){
	clear();
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
        m_filename = myStrDup(f.m_filename);
        m_position = f.m_nbSeq ? new size_t[f.m_nbSeq] : NULL;
        m_nbSeq = f.m_nbSeq;
        m_format = f.m_format;
	    for (size_t i=0 ; i<m_nbSeq ; i++){
    	    m_position[i]=f.m_position[i];
	    }
    }
    return *this;
} 

// Getters & Setters 
string FastXFile::getFormat() const 
{
	if(m_format == FASTA)
	{
		return "fastA";
	}
	if(m_format == FASTQ)
	{
		return "fastQ";
	}
	return "Non défini";
}

void FastXFile::setFormat(FastXFile::Format format)
{
	if (format == UNDEF) {
		throw "Format non valide";
	}
	m_format = format;
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

static void updateBuffer(ifstream &ifs, char *buffer, size_t bufsize, size_t &p, size_t &nb) {
	cerr << "Current position p = " << p << ", nb = " << nb;
	if (p < nb) {
		cerr << "buffer[" << p << "] = '" << buffer[p] << "'" << endl;
	}
	if (++p >= nb) {
		ifs.read(buffer, bufsize);
		nb = ifs.gcount();
		p = 0;
	}
	cerr << "Now, p = " << p << " and nb = " << nb << endl;
}

static void file_error_message(const char *m_filename, size_t ligne, size_t colonne, char c) {
	stringstream str;
	str << "Fichier '" << m_filename
		<< "', ligne " << ligne
		<< ", colonne " << colonne
		<< " : Format non reconnu (caractère '" << c << "')";
	throw str.str();
}


void FastXFile::myparse(){

	ifstream ifs(m_filename,ios_base::in);
	if (!ifs){
		throw "unable to open this file"; 
	}
	const int BufferSize = 1024; 
	char buffer[BufferSize];

	size_t nb = 0, p = 0;
	updateBuffer(ifs, buffer, BufferSize, p, nb);
	size_t ligne = 0, colonne = 0;

	char c = '\n';

	while ((p < nb) && (isSpace(buffer[p]))){ 
		if (buffer[p] == '\n') {
			++ligne;
			colonne = 0;
		} else {
			++colonne;
		}
		updateBuffer(ifs, buffer, BufferSize, p, nb);
	} // On saute les espaces au début du fichier

	if (p) { 
		c = buffer[p - 1];
	} //si p n'est pas au début du buffer, on initialise le char c au début
    
	if (p < nb){
		if (c == '\n') {
			if ((buffer[p] == '>')||(buffer[p] == ';')) { 
				setFormat(FASTA);
			} else {
				if (buffer[p] == '@') {
					setFormat(FASTQ);
				} else {
					file_error_message(m_filename, ligne + 1, colonne + 1, buffer[p]);
				}
			}
		} else {
			file_error_message(m_filename, ligne + 1, colonne, c);
		}
	}

	while ((p < nb) && (buffer[p] != '\n')) {
		++colonne;
		updateBuffer(ifs, buffer, BufferSize, p, nb);
	}
	++ligne;
	colonne = 0;

	if (p < nb) {
		if(m_format == FASTA) {
			do {
				c = buffer[p];
				//string s;
				//getline(ifs,s);
				//m_nbSeq += ((s[0] ==  '>') || (s[0] == ';'));
				if (!isSpace(c) || !isNucl(c)) {
					if (colonne) {
						file_error_message(m_filename, ligne + 1, colonne + 1, c);
					} else {
						if ((c == '>') || (c == ';')) {
							++m_nbSeq;
							while (c != '\n') {
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++colonne;
							}
							++ligne;
							colonne = 0;
						} else {
							file_error_message(m_filename, ligne + 1, colonne + 1, c);
						}
					}
				} else {
					if (c == '\n') {
						++ligne;
						colonne = (size_t) -1;
					}
				}
				++colonne;
				updateBuffer(ifs, buffer, BufferSize, p, nb);
			} while (p < nb);

			m_position = new size_t [m_nbSeq]; // tableau de la taille du nb de sequences
			m_nbSeq = 0 ;
			ifs.clear();
			//string s;
			ifs.seekg(0); // seeqg positionne le marqueur à la position entre ()
			size_t offset = 0; // recupere la position du marqueur dans le flux

			p = nb = 0;
			do {
				updateBuffer(ifs, buffer, BufferSize, p, nb);
				c = buffer[p];
				if ((c == '>') || (c == ';')) {
					m_position[m_nbSeq++] = offset;
				}
				offset++;
			} while (p < nb);
		} else {
			if (m_format == FASTQ) {
				int etat = 0; // 0 pour entete, 1 pour séquence, 2 pour sépareur et 3 pour qualité
				string entete = "";
				size_t l1 = 0, l2 = 0;
				do {
					c = buffer[p];
					//string s;
					//getline(ifs,s);
					//m_nbSeq += ((s[0] ==  '>') || (s[0] == ';'));
					switch (etat) {
						case 0: {
							if (c == '@') {
								++m_nbSeq;
								entete = "";
								l1 = l2 = 0;
								while ((p < nb) && (c != '\n')) {
									entete += c;
									updateBuffer(ifs, buffer, BufferSize, p, nb);
									++colonne;
								}
								++ligne;
								colonne = 0;
								etat = 1;
							} else {
								file_error_message(m_filename, ligne + 1, colonne + 1, c);
							}
							break;
						}
						case 1: {
							if (!isSpace(c) || !isNucl(c)) {
								if (colonne) {
									file_error_message(m_filename, ligne + 1, colonne + 1, c);
								} else {
									if (c == '+') {
										etat = 2;
										++colonne;
									} else {
										file_error_message(m_filename, ligne + 1, colonne + 1, c);
									}
								}
							} else {
								l1 += isNucl(c);
								++colonne;
								if (c == '\n') {
									++ligne;
									colonne = 0;
								}
							}
							break;
						}
						case 2: {
							while ((p < nb) && (c != '\n')) {
								if (c != entete[colonne]) {
									file_error_message(m_filename, ligne + 1, colonne + 1, c);
								}
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++colonne;
							}
							++ligne;
							colonne = 0;
							etat = 3;
							break;
						}
						default: {
							while ((p < nb) && (l2 < l1)) {
								l2 += !isSpace(c);
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++colonne;
								if (c == '\n') {
									++ligne;
									colonne = 0;
								}
							}
							while ((p < nb) && isSpace(c)) {
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++colonne;
								if (c == '\n') {
									++ligne;
									colonne = 0;
								}
							}
							--p;
							--colonne;
							etat = 0;
							// update l1 pour séquence m_position[m_nbSeq - 1]
						}
					}
					updateBuffer(ifs, buffer, BufferSize, p, nb);
				} while (p < nb);


				m_position = new size_t [m_nbSeq]; // tableau de la taille du nb de sequences
				m_nbSeq = 0 ;
				ifs.clear();
				//string s;
				ifs.seekg(0); // seeqg positionne le marqueur à la position entre ()
				size_t offset = 0; // recupere la position du marqueur dans le flux

				p = nb = 0;
				etat = 0; // 0 pour entete, 1 pour séquence, 2 pour sépareur et 3 pour qualité
				size_t l = 0;
				do {
					c = buffer[p];
					//string s;
					//getline(ifs,s);
					//m_nbSeq += ((s[0] ==  '>') || (s[0] == ';'));
					switch (etat) {
						case 0: {
							m_position[m_nbSeq++] = offset;
							l = 0;
							while ((p < nb) && (c != '\n')) {
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++offset;
							}
							etat = 1;
							break;
						}
						case 1: {
							if (!isSpace(c) || !isNucl(c)) {
								if (c == '+') {
									etat = 2;
								}
							} else {
								l += isNucl(c);
							}
							break;
						}
						case 2: {
							while ((p < nb) && (c != '\n')) {
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++offset;
							}
							etat = 3;
							break;
						}
						default: {
							while ((p < nb) && l) {
								l -= !isSpace(c);
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++offset;
							}
							while ((p < nb) && isSpace(c)) {
								updateBuffer(ifs, buffer, BufferSize, p, nb);
								++offset;
							}
							--p;
							--offset;
							etat = 0;
						}
					}
					updateBuffer(ifs, buffer, BufferSize, p, nb);
					++offset;
				} while (p < nb);
			}
		}
        for(unsigned int i=0; i < m_nbSeq; i++){

        	cout << "Tableau à l'indice " << i <<": "<< m_position[i] << endl;
        }
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
			while (ifs && (isSpace(ifs.peek()))){ 
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

		// Rajouter une boucle pour check si il y'a des nucléotides

		ifs.close();

	} else {

		throw logic_error("No file");
	}

	return format;
}

SequenceFastX* FastXFile::getSequence(size_t i) const{

	//cout << "position de la séquence : " << m_pos[i] << endl;
	--i;
	// verif
	if (i > m_nbSeq) {
		throw "Sequence out of range";
	} else {

	//string sequence; 
	string header;
	string line;
	const char* name = myStrDup(m_filename);
	size_t pos_debut = m_position[i];
	size_t length(0);
	SequenceFastX * seq = NULL;

	ifstream ifs(m_filename,ios_base::in);


	if(ifs && seqCheck(pos_debut)){


		ifs.seekg(pos_debut);
		getline(ifs, line);
		header = line;

		//cout << line << endl;
		//cout<< notNucl(line) << endl;

        while(getline(ifs,line) && line[0] != '>' && line[0] != ';' && line[0] != '@'){

        	if (!StringNotSeq(line)) {

        		cout << line << endl;

        		for(size_t i = 0; i<line.size(); i++) {

            		if (line[i] != ' ' && line[i] != '\0') {

            			length ++;
            		//sequence +=line[i];
            		}

            	}

        	}
        }

        //cout << "Longueur de séquence :" << length << endl;

		//cout << "sequence :"<< sequence << endl;
		//cout << "length :"<< length << endl;

		/*if (m_format == 1) {

        	seq = new SequenceFastA(name, pos_debut, length, header);

        } 
        
        if (m_format == 2 ){

           	seq = new SequenceFastX(name, pos_debut, length, header);
        }*/
		ifs.close();
		delete [] name;

	}else {

		throw string("Error in file.");
	}
	return seq;
	}

}

