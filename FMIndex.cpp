#include "utilities.h"

#include <iostream>
#include <libgen.h>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;



struct Cmp{ // Comparaison vue en cours
    const string &ref;
    size_t n;

    Cmp(const string &r):ref(r),n(r.size()){} // Constructeur 
    // REf = sequence, n = sa taille


    bool operator()(size_t i, size_t j) const { // opérateur de comparaison
      
        int v = 0;

        while(!v && (i<n) && (j<n)){

        	cout << "Ref[" << i << "] = "<< ref[i] << " -- Ref[" << j << "] = " << ref[j] <<endl;
 
            if(ref[i] < ref[j]){
                v=-1; // ref non ordonné
            } else {
                if(ref[i] > ref[j]){
                    v=1;
                    // ref bien ordonnée, on casse la boucle while
                }else{
                    ++i; // On passe aux chars suivant
                    ++j;
                }
            }
        }
        
        if(i==n){
            v=-1;

        }else{
            if(j==n) {
                v=1;
            }
        }
        
        return(v<0); // Sorted
    }
};





int main(int argc, char ** argv){



	// On part d'une ES de taille n 
	// On la décode 
	// La séquence :

	// ATCG
	// 0123

	// ATCG
	// GATC
	// CGAT
	// TCGA


	string sequence = "ATCACTTA";
	size_t n = sequence.length();

	// Création d'un vecteur

	vector<string> BWT(n+1);

	sequence += '$';

	//BWT[1] = sequence;

	string test = sequence + sequence; // Très très gourmand en place

	string shuffle = sequence;
	string seqatri = sequence;

	for(size_t j =0; j < n+1; ++j) {

		for (size_t i = 0; i < n+1 ; ++i) {

			shuffle[i] = test[n+i -j];
		}

		//cout << shuffle << endl;
		seqatri[j] = shuffle[n];
		BWT[j] = shuffle;
	}

	cout << "seq a trier : " << seqatri<< endl;

	vector<size_t> index(n+1);

    for(size_t i=0;i<n+1;++i){
        index[i] = i;
    }


   vector<string> BWTr(n+1);

   sort(index.begin(),index.end(), Cmp(seqatri)); //comparer les suffixes par ordre lexicographique 

    for(size_t i=0 ; i<n+1 ; ++i){
        //cout<<"-index["<<i<<":"<<index[i]<<"]=>"<<BWT[index[i]]<<endl;
        BWTr[i] = BWT[index[i]];
    }

    cout << "BWT AVANT : "  << endl;
    for(size_t i=0 ; i<n+1 ; ++i){
    	cout << BWT[i] << endl;
    }

    cout << "BWT APRES : "  << endl;

    for(size_t i=0 ; i<n+1 ; ++i){
    	cout << BWTr[i] << endl;
    }

// Extraction de la première et deuxième colonne 


   char F[n+1];
   char L[n+1];


    for(size_t i=0 ; i<n+1 ; ++i){
    	F[i] = BWTr[i][0];
    	L[i] = BWTr[i][n];
    }


    cout << " Colonne F " << endl;
    for(size_t i=0 ; i<n+1 ; ++i){
    	cout << F[i] ; 
    }

    cout << endl;

	cout << " Colonne L " << endl;
    for(size_t i=0 ; i<n+1 ; ++i){
    	cout << L[i];
    }

    cout << endl;


    // Création d'un alphabet

    cout << "---ALPHABET---" << endl;

    vector<char> alphabet (0);
    vector<size_t> ind (0);

    alphabet.push_back('$');
    ind.push_back(0);
    char c;
    size_t t = 0;

    cout << "vectors created" << endl;

    for(size_t i=0; i<n ; i++){
    	c = L[i];
    	if (c != alphabet[t]){
    		alphabet.push_back(c);
    		++t;
    		ind.push_back(i);
    	}
    }

    for(size_t i=0 ; i<=alphabet.size() ; ++i){
    	cout << alphabet[i];
    }

    cout << endl;

    for(size_t i=0 ; i<=alphabet.size() ; ++i){
    	cout << ind[i];
    }
    cout << endl;

    // Finalement FM INDEX

    cout << "------ FM INDEX ---------" << endl;







	return 0;
}

