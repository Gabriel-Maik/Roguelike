#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Przedmiot.h"
//#include "Plansza.h"

using std::cout;
using std::endl;

class Plansza;
class Postac // mozna zrobic operator <<
{
	//friend std::ostream& operator<<(std::ostream& s, const Postac& postac);
protected:
	int zycie;	// ilosc punktow zycia
	int zycieMax;
	int iloscDukatow;
	int x; // wspolrzednie polozenia na planszy
	int y;
	Plansza* lokalizacja;
	int atak;
	std::vector<Przedmiot*> ekwipunek;
	Postac(Postac& innaPostac) = delete;
	void operator=(Postac& innaPostac) = delete;
public:
	Postac(int _zycieMax, int _iloscDukatow, int _atak, int _x, int _y, Plansza* _lokalizacja);
	virtual void idz(char gdzie); // zastosowano wyjatek // char 'w', 's', 'a', 'd' - gora, dol, lewo, prawo 
	virtual void wyswietl() const = 0;
	void wezPrzedmiot(Przedmiot* podarunek);
	Przedmiot* oddajPrzedmiot(int ktory);
	virtual int wybierzElementEkwipunku() const;
	int getX() const { return x; }
	int getY() const { return y; }
	virtual void operator+=(int punktyZycia);
	virtual void operator-=(int punktyZycia);
	bool operator>(int punktyZycia) const { return (zycie > punktyZycia); }
	bool operator<(int punktyZycia) const { return (zycie < punktyZycia); }
	int getDukaty() const { return iloscDukatow; }
	virtual void dodajDukaty(int ile);
	int getZycie() const { return zycie; }
	int getAtak() const { return atak; }
	void sprzedajPrzedmiot(int ktory, Postac* komu);
};

bool porownaniePrzedmiotow(Przedmiot* i, Przedmiot* j);