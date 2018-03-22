#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include <fstream>
using namespace std;
class FileReader_
{
public:
	FileReader_();
	void llegeixFitxer();
	unsigned getSize()const;
	void mostraHistograma() const;
private:
	unsigned static const MAX = 25000;
	struct  Paraula
	{
		string paraula;
		unsigned vegades;
	};
	Paraula a_t[MAX];
	unsigned a_n;
	void compute_file(ifstream &in_file);
	void  search_element(string paraula, bool& is_there, int & pos_element)const;
	void  incertarOrdenadament(Paraula paraula);
	bool es_separador(char lletra);
	void passar_separadors(ifstream& fitxer);
	string passar_paraula(ifstream& fitxer);
};

