#pragma once
#include <vector>
#include "MozliweDoWyswietlenia.h"
#include "Gracz.h"

class GUI : public MozliweDoWyswietlenia
{
	///Menu menu;
	MozliweDoWyswietlenia* menu;
	//vector<Plansza*> plansze;
	///Plansza* plansza;
	MozliweDoWyswietlenia* plansza;
	Gracz* gracz;
	//int ktoraPlansza;
public:
	GUI();
	GUI(int _szerokosc, int _wysokosc, MozliweDoWyswietlenia* _menu = nullptr, MozliweDoWyswietlenia* _plansza = nullptr, Gracz* _gracz = nullptr);
	void setPlansza(MozliweDoWyswietlenia* nowaPlansza); //{ plansze.push_back(nowaPlansza); }
	///Plansza* getPlansza() { return plansza; }
	MozliweDoWyswietlenia* getPlansza() { return plansza; }
	void dodajGracza(Gracz* _gracz) { gracz = _gracz; }
	virtual void wyswietl() override;
	///Menu* getMenu() { return &menu; }
	///MozliweDoWyswietlenia* getMenu() { return menu; }
	void aktualizujDukaty(int ileTeraz);
	void aktualizujZycie(int ileTeraz, int aIleMax);
	void ustawWielkoscKonsoli(int X, int Y);
};

