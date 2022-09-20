#include "Handlarz.h"
#include "Plansza.h"

Handlarz::Handlarz(int _zycieMax, int _iloscDukatow, int _atak, int _x, int _y, Plansza* _lokalizacja)
	: Postac(_zycieMax, _iloscDukatow, _atak, _x, _y, _lokalizacja)
{
}

void Handlarz::wyswietl() const
{
	lokalizacja->handlarzowy();
	cout << "H";
	lokalizacja->zwykly();
}

