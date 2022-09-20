#pragma once
//#include <iostream>
#include "Postac.h"
#include "Bron.h"
#include "Mikstura.h"
#include <conio.h>

class Gra;
class Plansza;
class GUI;
class Gracz : public Postac
{
	Bron* uzywanaBron;
	Mikstura* przygotowanaMikstura;
	Gra* rozgrywka;
	//Menu* menu;
	GUI* interfejs;
	int atakBazowy;
public:
	Gracz(int _zycieMax, int _iloscDukatow, int _atakBazowy, int _x, int _y, Gra* _rozgrywka, Plansza* _lokalizacja, /*Menu* _menu,*/ GUI* _interfejs);
	void wykonujeRuch();
	virtual void wyswietl() const override;
	virtual void dodajDukaty(int ile) override;
	virtual void operator+=(int punktyZycia) override;
	virtual void operator-=(int punktyZycia) override;
	//virtual void wyswietlEkwipunek() override; // potencjalne miejsce do bledu, bo menu moze byc za male i co wtedy?
	void zmienBron(Bron* naTaka, int ktoraTo);
	void zmienMiksture(Mikstura* naTaka, int ktoraTo);
	bool czyMaMiksture();
	int getZycieMax() { return zycieMax; }
	void uzyjPrzedmiot();
	void wypijMiksture();
	void zdejmijBron();
	void zdejmijMiksture();
};

