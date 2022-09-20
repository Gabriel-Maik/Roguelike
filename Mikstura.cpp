#include "Mikstura.h"

Mikstura::Mikstura(int _wartosc, string _nazwa, int _przywrocenieZycia)
	: Przedmiot(_wartosc, _nazwa), przywrocenieZycia(_przywrocenieZycia)
{
}

string Mikstura::opis() const
{
	string doWypisania(nazwa);
	const char* dukaty;
	if ((wartosc >= 2) && (wartosc <= 4)) dukaty = " Dukaty";
	else if (wartosc == 1) dukaty = " Dukat";
	else dukaty = " Dukatow";
	doWypisania.append("\tprzywrocenie zycia: ").append(std::to_string(przywrocenieZycia)).append("\twartosc: ").append(std::to_string(wartosc)).append(dukaty);
	return doWypisania;
}
