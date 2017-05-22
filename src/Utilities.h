/* Utilities.h */
/* Classe com algumas funcoes uteis em diferentes trechos da aplicação */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>
using namespace std;

class Utilities {
private:

public:
	/*! Inicializa a classe */
	static void Init()
	{
		srand (time(NULL)); // Initialize random seed
	}

	/*!
	  Gera um numero aleatorio entre um minimo e um maximo, ambos incluidos
      \param min inteiro com o limite minimo do numero aleatorio (inclusive)
	  \param max inteiro com o limite maximo do numero aleatorio (inclusive)
	  \return Retorna um numero aleatorio entre [min,max]
    */
	// Generates a random number between min [inclusive] and max [inclusive]
	static int GetRandom(int min, int max)
	{
		return rand()%(max-min)+min;
	}

	// Funcao auxiliar para ordenacao de vetores em ordem crescente
	static bool ascending(int i, int j)
	{
		return (i<j);
	}

	/*! Trata a entrada de dados do utilizador de forma a obriga-lo a digitar um 
	    inteiro entre min e max (ambos inclusive)
		Retorna o inteiro digitado
	*/
	static int readInt(string message, int min, int max)
	{
		stringstream readInt;
		string auxReadInt;
		int num = 0;
		cout << message;
		while(true){
			fflush(stdin);
			num = 0;
			getline(cin,auxReadInt);
			readInt.str(auxReadInt);
			readInt >> num;
			if(num == 0){
				cout << "\n<<The number entered has a invalid format>>" << endl;
				readInt.clear();
				auxReadInt.clear();
			}
			else 
				if(num < min || num > max){
					cout << "\n<<Number must be between " << min << " and " << max << ">>" << endl;
					readInt.clear();
					auxReadInt.clear();
				}
				else
					return num;
			cout << "\nReenter: ";
		}
	}

	/*! Trata a entrada de dados do utilizador de forma a obriga-lo a digitar uma 
	    string dentre as opçoes 'option'
		Retorna a string digitada.
	*/
	static string readString(string message, string option, int numOpt)
	{
		vector<string> opt;
		string aux;
		int posIni=0, posEnd=0;
		string auxReadString;
		for(int i=0 ; i<numOpt ; i++){
			posEnd = option.find(",",posIni);
			aux = option.substr(posIni, posEnd-posIni);
			opt.push_back(aux);
			posIni = (posEnd-posIni) + 1;
		}
		cout << message;
		while(true){
			auxReadString.clear();
			fflush(stdin);
			getline(cin,auxReadString);
			for(int i=0 ; i<numOpt ; i++)
				if(auxReadString == opt[i])
					return opt[i]; 
			cout << "\n<<Acceptable answers: [ ";
			for (int i=0 ; i<numOpt ; i++){
				cout << opt[i];
				if(i<numOpt-1)
					cout << " or ";
			}
			cout << " ]>>\n" << "\nReenter: ";
		}
	}
};

#endif