#pragma once
#include <string>
#include <iostream>
#include "MozliweDoWyswietlenia.h"
#include <conio.h>

using std::string;
using std::cout;
using std::endl;

class Menu : public MozliweDoWyswietlenia
{
	int iloscOpcji;
	string tytul;
	string* opcje;
	int wybor;
	void operator=(Menu& inneMenu) = delete;
	Menu(Menu& inneMenu) = delete;
	virtual void wyswietl() override;
	void wyswietlZmianeOpcji(char znak, int wybor);
public:
	Menu(int _x, int _y, int _szerokosc, int _wysokosc, int _iloscOpcji, string _tytul, string* _opcje);
	~Menu();
	int noweMenu(int _iloscOpcji, string _tytul, string* _opcje);// int _x = x, int _y = y, int _szerokosc = szerokosc, int _wysokosc = wysokosc);
	int noweMenu(int _iloscOpcji, string _tytul, string* _opcje, int _x, int _y, int _szerokosc, int _wysokosc);
	int wybierz();
};

