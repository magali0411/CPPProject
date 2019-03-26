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
    os<< "File: " << (m_filename ? m_filename: "no name") << endl ;
	os << "File contains: " << m_nbSeq  <<" sequences" << endl;
}

// Fonction Buffer
static void updateBuffer(ifstream &ifs, char *buffer, size_t bufsize, size_t &p, size_t &nb) {
//	cerr << "Current position p = " << p << ", nb = " << nb << endl;
	if (p < nb) {
		cerr << "buffer[" << p << "] = '" << buffer[p] << "'" << endl;
	}
	if (++p >= nb) {
		ifs.read(buffer, bufsize); // On recharge le buffer
		nb = ifs.gcount(); // prend la valeur du nombre de c du buffer précédent
		p = 0;
		cout << "Buffer reloaded" << endl;
	} // Si on arrive à la fin du buffer
//	cerr << "Now, p = " << p << " and nb = " << nb << endl;
}

// Fonction error
static void file_error_message(const char *m_filename, size_t ligne, size_t colonne, char c) {
	stringstream str;
	str << "File '" << m_filename
		<< "', line " << ligne
		<< ", column " << colonne
		<< " : Format not supported(char '" << c << "' not allowed)";
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
	bool end = false;
	updateBuffer(ifs, buffer, BufferSize, p, nb);

	//Parcours du fichier
	size_t ligne = 0, colonne = 0;

////////////////////////////////////////
// Rajouter une fonction checkFormat //
//////////////////////////////////////

	colonne = 0;
	colonne = 0;
	char c = buffer[p];
	int etat = 0; // 0 : entete


	if(p < nb) {
		string entete = "";
		size_t l1 = 0, l2 = 0;

		do {

///////////// Saut espace A chauqe début de boucle //////////
			while ((p < nb) && (isSpace(buffer[p]))){ 
				if (buffer[p] == '\n') {
					++ligne;
					colonne = 0;
				} else {
					++colonne;
				}
				updateBuffer(ifs, buffer, BufferSize, p, nb); 
			} // On saute les espaces au début du fichier
//////////////////////////////////////////////////////
			cout << "char en debut de ligne " << c << buffer[p] << endl;
			cout << "current state " << etat << endl;
			cout << "line : " << ligne << "col : " << colonne << endl;

			c = buffer[p];

			switch (etat) {		
				case 0: {
					if (c == '@' || c =='>' || c==';') {
						++m_nbSeq;
						entete = "";
						l1 = l2 = 0; // Longueur de seq et score pour fastq
						while ((p < nb) && (buffer[p] != '\n')) { // Tant qu'on parse l'entete
							entete += buffer[p];
							updateBuffer(ifs, buffer, BufferSize, p, nb);
							++colonne;
						} // Fin de ligne
						if(buffer[p] == '\n')
						{
							++ligne; 
							colonne = 0; 
							c = buffer[p+1];
							etat = 1;
						} else {
							c = ' ';
							etat = 4;
							break;
						}

						cout << "ENTETE: " << entete << endl;


					} else {
						file_error_message(m_filename, ligne + 1, colonne + 1, c);
					}
					//c = buffer[p+1];

					//cout << "etat" << etat << endl;
					break;		
					//cout << "etat :" << etat << ", buffer : " << buffer[p] << "c :" << c << endl;

					}
				case 1: { // La séquence

					if (!isNucl(c)) {

/*						if (colonne) { // On ne devrait pas être au milieu d'un ligne
							cout << " acui " << endl;
							file_error_message(m_filename, ligne + 1, colonne + 1, c);
						} else { // Pas de sequence*/
							if (c == '+') { // Si c'est le séparateur fastq
								etat = 2;
								break;
								//++colonne;
							}if (c == '>') { // Si c'est le début fasta
								etat = 0;
								break;
								//++colonne;
							} else {
								// Fonction de suppr
								etat = 4;

							}
						//}

					} else {

						while ((p < nb) && (buffer[p] != '\n')) { // Tant qu'on est dans la ligne
							l1 += isNucl(buffer[p]);
							++colonne;
							updateBuffer(ifs, buffer, BufferSize, p, nb);
						} 
						cout << "LENGTH :" << l1 << endl;
						if((p< nb) && buffer[p] == '\n') 
						{
							++ligne;
							colonne = 0;
							//c = buffer[p+1]; Modif ici

						} else {
							if (isSpace(c)) // modification ici (isNucl)
							{
								etat = 4;
							}
						}
					} // fin de ligne
					//cerr << "state : " << etat << endl;
					//cerr << "c :" << c << "buff : " << buffer[p] << endl;
					break;
				}
				case 2: {
					size_t cpt = 1;
					c = buffer[p+1];
					while ((p < nb) && (buffer[p] != '\n') ){
						if(isSpace(c)) {
/*							while ((p < nb) && (isSpace(buffer[p]))){ 
								if (buffer[p] == '\n') {
									++ligne;
									colonne = 0;
								} else {
									++colonne;
								}
							updateBuffer(ifs, buffer, BufferSize, p, nb); 
							}*/
							break;
							//c = buffer[p+1];
							//cout << "detectée char :" << c << endl;
						} else {
							if (buffer[p+1] != entete[cpt]) { //modif
							//cout << "buf : " << buffer[p] << " +1 : " << buffer[p+1] << "ent : " << entete[cpt] << endl;
							file_error_message(m_filename, ligne + 1, colonne + 1, c);
							}
						}
						++colonne;
						++cpt;
						updateBuffer(ifs, buffer, BufferSize, p, nb);
						c = buffer[p+1];

					}
					if(p < nb && (buffer[p+1] == '\n')) {
						updateBuffer(ifs, buffer, BufferSize, p, nb);
						c = buffer[p+1];
						//++ligne;
						//colonne = 0;
						etat = 3;
					}
					else {

						file_error_message(m_filename, ligne + 1, colonne + 1, c);
					}

					break;
				}
				case 3: {

					//c = buffer[p+1];
					//cout << "length to reach : " << l1 << endl;
					string score = ""; 
					while ((p < nb) && buffer[p] != '\n') {

						//c = buffer[p+1];
						++ colonne;
						score += buffer[p];
						l2 += !isSpace(buffer[p]);
						updateBuffer(ifs, buffer, BufferSize, p, nb);
						
					}
					cout << "SCORE : " << score << endl;
					cout << "FINALE LENGTH :" << l2 << endl;
					
					if (buffer[p] == '\n') {
						//++ligne;
						//colonne = 0;
						updateBuffer(ifs, buffer, BufferSize, p, nb);
						c = buffer[p+1];
						etat = 0;
					} else {
						c = ' ';
						etat = 4;
					}


/*					if(l1 != score.size()) {
						cout << " hey" << endl;
						file_error_message(m_filename, ligne + 1, colonne + 1, c);
						break;
					}*/
					break;

				}
				case 4: {
					cout << "-----------------------" << endl;
					cout << "END OF FILE" << endl;
					cout << "-----------------------" << endl;
					end = true;
					break;
				}
				default : {
					
					while ((p < nb) && (isSpace(buffer[p]))){ 
						if (buffer[p] == '\n') {
							++ligne;
							colonne = 0;
						} else {
							++colonne;
						}
						updateBuffer(ifs, buffer, BufferSize, p, nb); 
					} // On saute les espaces 
					--p; // modif
					--colonne;
					etat = 0;
					l1 = l2 = 0; 

					//break;				}

				}
			}	
/*			
			cerr << "state : " << etat << endl;
			cerr << "c :" << c << "buff : " << buffer[p] << endl;
			cerr << " p : "<< p << " nb : " << nb << endl;
*/

		} while(p <= nb && !end);

		//updateBuffer(ifs, buffer, BufferSize, p, nb);
/*		cout << "p : " << p << " nb : " << nb << endl;
		cout << "case " << etat << endl;
*/
	}

	m_position = new size_t [m_nbSeq]; // tableau de la taille du nb de sequences
	m_nbSeq = 0 ;
	ifs.clear();
	ifs.seekg(0); // seeqg positionne le marqueur à la position entre ()
	size_t offset = 0; // recupere la position du marqueur dans le flux
	p = nb = 0;
	etat = 0; 
	end = false;
	size_t l = 0;
	c = ' ';

	do {
///////////// Saut espace A chauqe début de boucle //////////
		while ((p < nb) && (isSpace(buffer[p]))){ 
			++offset;
			updateBuffer(ifs, buffer, BufferSize, p, nb);
			if (buffer[p] == '\n') {
				c = buffer[p+1];
			} // C toujours égal au début de ligne
		} 

		l = 0;

//////////////////////////////////////////////////////
		//c = buffer[p];
		cout << "Etat en début de boucle : " << etat << endl;
		cout << "Char en début de boucle : " << buffer[p] << endl;
		//cout << "char début de ligne : " << c << endl;

		switch (etat) { // On ne refait pas toute nos vérifs pour alléger le code
			case 0: {

				if (buffer[p] == '@' || buffer[p] =='>' || buffer[p]==';') {

					m_position[m_nbSeq++] = offset;
					l = 0;
					while ((p < nb) && (buffer[p] != '\n')) {
						updateBuffer(ifs, buffer, BufferSize, p, nb);
						++offset;
					}
					if((p < nb) && (buffer[p])== '\n'){
						etat = 1;
					} else {
						cout << "this is why" << endl;
						c = ' ';
						etat = 4;
						break;
					}
					break;

				}
			}
			case 1: {

				if (!isNucl(buffer[p])) {

					if (buffer[p] == '+') {
						etat = 2;
						break;
					}
					if (buffer[p] == '>') {
						etat = 0;
						break;
					} else {

						etat = 4;
					}

				} else {
					while ((p < nb) && (buffer[p] != '\n')) {
						l += isNucl(buffer[p]);
						updateBuffer(ifs, buffer, BufferSize, p, nb);
					}

				}
				break;
			}
			case 2: {
				while ((p < nb) && (buffer[p] != '\n')) {
					if(isSpace(buffer[p])) {
						break;
					}

					updateBuffer(ifs, buffer, BufferSize, p, nb);
					++offset;
				}
				if (p<nb && ( buffer[p] == '\n'))
				{
					updateBuffer(ifs, buffer, BufferSize, p, nb);
					etat = 3;

				} 
				break;
			}
			case 3: {
				while ((p < nb) && l > 0) {
					l -= !isSpace(buffer[p]);
					updateBuffer(ifs, buffer, BufferSize, p, nb);
					++offset;
				}
				cout << "LENGTH : " << l << endl;

				while ((p < nb) && (isSpace(buffer[p]))){ 
					++offset;
					updateBuffer(ifs, buffer, BufferSize, p, nb);
				} 


				if (buffer[p+1] == '@' || buffer[p+1] == '>')
				{
					etat = 0;
					c = buffer[p+1];
				} else {
					c = ' ';
					etat = 4;
				}
				break;	
			}
			case 4: {
				cout << "-----------------------" << endl;
				cout << "END OF FILE" << endl;
				cout << "-----------------------" << endl;
				end = true;
				break;

			}
			default: {
/*				while ((p < nb) && l) {
				l -= !isSpace(c);
				updateBuffer(ifs, buffer, BufferSize, p, nb);
				++offset;
				}*/
/*				while ((p < nb) && isSpace(c)) {
				updateBuffer(ifs, buffer, BufferSize, p, nb);
				++offset;
				}*/
				--p;
				--offset;
				etat = 0;
			}
		}
		updateBuffer(ifs, buffer, BufferSize, p, nb);
		++offset;
	} while (p < nb && !end);

    for(unsigned int i=0; i < m_nbSeq; i++){
      	cout << "Tableau à l'indice " << i <<": "<< m_position[i] << endl;
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
			if (m_format == FASTA && (c == ';' || c == '>'))
			{
				format = true;
			}
			//fastQ
			else if (c == '@' && m_format == FASTQ) 
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

