#include "stdafx.h"
#include "FileReader_.h"
#include <iostream>
using namespace std;

FileReader_::FileReader_()
{
	a_n = 0;
}

void FileReader_::llegeixFitxer()
{
	cout << "Entra el nom del fitxer:" << endl;
	string nom_fitxer;
	cin >> nom_fitxer;
	ifstream in_file(nom_fitxer.c_str());
	if (in_file.is_open())
	{
		if (!in_file.eof()) {
			compute_file(in_file);
		}
		else {
			cout << "fitxer vuid" << endl;
		}

	}
	else {
		cout << "No s'ha trobat el fitxer" << endl;
	}
}

void FileReader_::compute_file(ifstream &in_file) {
	Paraula sparaula;
	string paraula;
	passar_separadors(in_file);
	while (!in_file.eof()) {
		paraula = passar_paraula(in_file);
		transform(paraula.begin(), paraula.end(), paraula.begin(), ::tolower);
		sparaula.paraula = paraula;
		bool existeix = false;
		int pos;
		search_element(sparaula.paraula, existeix, pos);
		if (!existeix) {
			sparaula.vegades = 1;
			incertarOrdenadament(sparaula);
		}
		else {
			a_t[pos].vegades++;
		}
		passar_separadors(in_file);
	}
}

void FileReader_::search_element(string paraula, bool& is_there, int & pos_element)const {
	//Pre: 0<=v.n<=MAX, v.t[0..v.n-1] ordenat creixentment
	//Post: retorna cert si x és un dels elements de v.t[0..v.n-1] i la posicio, fals
	//altrament
	int low = 0;
	int hight = a_n - 1;
	int pos = 0;
	while (low <= hight && !is_there) {
		pos = (low + hight) / 2;
		if (a_t[pos].paraula == paraula) is_there = true;
		else if (a_t[pos].paraula < paraula)low = pos + 1;
		else hight = pos - 1;
	}
	if (is_there)pos_element = pos;
	else pos_element = low;
	//incert_to_position(vector, pos, app);
}
void  FileReader_::incertarOrdenadament(Paraula araula) {
	//Pre: 0<=v.n<MAX, v.t[0..n-1] ordenat creixentment
	//Post: x inserit ordenadament a v.t

	int i = a_n;
	while (i > 0 && araula.paraula<a_t[i - 1].paraula) {
		a_t[i] = a_t[i - 1];
		i--;
	}
	a_t[i] = araula;
	a_n++;
}
void FileReader_::mostraHistograma()const {
	cout << "Recompte de les paraules:" << endl;
	for (unsigned i = 0; i < a_n; i++) {
		cout << a_t[i].paraula << ": " << a_t[i].vegades << endl;
	}
}

unsigned  FileReader_::getSize()const {
	return a_n;
}


bool FileReader_::es_separador(char lletra) {
	/*Pre: cert
	Post: retorna cert si lletra és un separador, fals altrament */
	bool separador = true;
	if (lletra >= 'a' && lletra <= 'z') separador = false;
	else if (lletra >= 'A' && lletra <= 'Z') separador = false;
	else {
	}
	return separador;
}

void FileReader_::passar_separadors(ifstream& fitxer) {
	/*Pre: fitxer obert
	Post: s?han llegit tots els separadors del fitxer*/
	char lletra = ' ';
	while (!fitxer.eof() && es_separador(lletra)) {
		fitxer.get(lletra);
	}
	if (!fitxer.eof()) fitxer.unget(); //pot no ser necessari 
}

string FileReader_::passar_paraula(ifstream& fitxer) {
	/*Pre: fitxer vàlid i apunt de llegir el 1r carácter d?una paraula
	Post: s?ha llegit tota una paraula del fitxer */
	char lletra = fitxer.get();
	string paraula;
	while (!fitxer.eof() && !es_separador(lletra)) {
		//tractar, si cal, el caràcter llegit (lletra) 
		paraula += lletra;
		fitxer.get(lletra);
	}
	if (!fitxer.eof()) fitxer.unget(); //pot no ser necessari 
	return paraula;
}