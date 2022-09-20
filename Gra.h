#pragma once
#define wysStdMenu 10
#include <vector>
#include <time.h>
#include "GUI.h"
//#include "Przedmiot.h"
#include "Mikstura.h"
#include "Bron.h"
#include "Gracz.h"
#include "Plansza.h"
#include "Menu.h"

using std::vector;

class Gra
{
	GUI* interfejs;
	Gracz* gracz;
	//Menu* menu;
	Menu menu;
	vector<Mikstura*> mikstury;
	vector<Bron*> bronie;
	vector<Plansza*> plansze;
	Gra(Gra& innaGra) = delete;
	void operator=(Gra& innaGra) = delete;
	void dealokuj();
	void zacznijGre(); // prowizorycznie
	///void wczytajPlansze(string& nazwa);
public:
	void menuGlowne();
	bool czyDalejGrac;
	///void walka(Potwor& potwor); // gracz walczy z potworem
	Gra(); // zaladuj mikstury, bronie i plansze
	~Gra();
	Przedmiot* generujPrzedmiot(); // brak generowania nazw
	Bron* generujBron();
	Mikstura* generujMiksture();
	Plansza* getPlansza(int ktora) const { return plansze[ktora]; }
	void koniecGry();
	void generujGracza(Plansza* _plansza, int _x, int _y);
	void wyswietlGUI() { interfejs->wyswietl(); }
	void usunPrzedmiot(Przedmiot* _przedmiot);
	int obsluzNoweMenu(int _iloscOpcji, string _tytul, string* _opcje);
};

