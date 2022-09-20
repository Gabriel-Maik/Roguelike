#pragma once
#define potworyMax 10
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "MozliweDoWyswietlenia.h"
#include "Handlarz.h"
#include "Gracz.h"
#include "Potwor.h"
//#include "Postac.h"

//using std::vector;
using std::string;
using std::istringstream;

class Gra;
class Plansza : public MozliweDoWyswietlenia
{
	char* pola;
	char** wiersze;
	void alokuj();	// Potencjalne miejsce do utworzenia wyj¹tku - niepowodzenie alokacji pamiêci
	Plansza(Plansza& innaPlansza) = delete;
	void operator=(Plansza& innaPlansza) = delete;
	void zaladujPoziomStandardowy();
	void zaladujPoziomZPliku(string nazwaPliku);
	Handlarz* handlarz;
	Potwor* potwory[potworyMax];
	int iloscPotworow;
	Gracz* gracz;
	Gra* rozgrywka;
public: // zaladuj handlarzy i potwory
	Plansza(int _x, int _y, int _szerokosc, int _wysokosc, Gra* _rozgrywka);
	Plansza(int _x, int _y, string nazwaPliku, Gra* _rozgrywka);
	~Plansza();
	char getPole(int _x, int _y) const; // potencjalne miejsce do utworzenia wyjatku - niepoprawny numer pola
	void setPole(int _x, int _y, char naCo);
	virtual void wyswietl() override;
	void generujPotwora(int _x = -1, int _y = -1);
	void generujHandlarza(int _x = -1, int _y = -1);
	void generujGracza(int _x = 1, int _y = 1);
	Potwor& getPotworPola(int _x, int _y) const; // wyjatek dla nieprawidlowych danych
	Handlarz& getHandlarz() const; // wyjatek gdy nie ma handlarza
	Gracz& getGracz() const { return *gracz; }
	void setGracz(Gracz* _gracz) { gracz = _gracz; }
	//Gra* getRozgrywka() const { return rozgrywka; }
	void dealokuj();
	void usunPotwora(Potwor* doUsuniecia); // UWAGA!!! - tymczasowo konczy gre
	void handel();
	void losujWolnePole(int& _x, int& _y);
	void interakcjaPostaci(Postac& postac, int _x, int _y); // _x, _y drugiej postaci
	void walka(Potwor& potwor);
	int obsluzNoweMenu(int _iloscOpcji, string _tytul, string* _opcje);
	//void koniecGry() const;
};

