#include "Przedmiot.h"

Przedmiot::Przedmiot(int _wartosc, string _nazwa)
	: wartosc(_wartosc), nazwa(_nazwa)
{
}

string Przedmiot::opis() const
{
	string doWypisania(nazwa);
	const char* dukaty;
	if ((wartosc >= 2) && (wartosc <= 4)) dukaty = " Dukaty";
	else if (wartosc == 1) dukaty = " Dukat";
	else dukaty = " Dukatow";
	doWypisania.append("\twartosc: ").append(std::to_string(wartosc)).append(dukaty);
	return doWypisania;
}

