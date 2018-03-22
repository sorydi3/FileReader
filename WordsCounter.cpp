// WordsCounter.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include"FileReader_.h"
using namespace std;

int main()
{
	FileReader_ file;
	file.llegeixFitxer();
	file.mostraHistograma();
	cout << "Hi ha "<< file.getSize() << " paraules diferents" << endl;
    return 0;
}

