#include "Bron.h"

Bron::Bron(int _wartosc, string _nazwa, int _zwiekszenieAtaku)
	: Przedmiot(_wartosc, _nazwa), zwiekszenieAtaku(_zwiekszenieAtaku)
{
}

string Bron::opis() const
{
	string doWypisania(nazwa);
	const char* dukaty;
	if ((wartosc >= 2) && (wartosc <= 4)) dukaty = " Dukaty";
	else if (wartosc == 1) dukaty = " Dukat";
	else dukaty = " Dukatow";
	doWypisania.append("\tzwiekszenie ataku: ").append(std::to_string(zwiekszenieAtaku)).append("\twartosc: ").append(std::to_string(wartosc)).append(dukaty);
	return doWypisania;
}


