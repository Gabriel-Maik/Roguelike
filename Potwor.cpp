#include "Potwor.h"
#include "Gracz.h"
#include "Plansza.h"

Potwor::Potwor(int _zycieMax, int _iloscDukatow, int _atak, int _x, int _y, Plansza* _lokalizacja)
	: Postac(_zycieMax, _iloscDukatow, _atak, _x, _y, _lokalizacja)
{
}

void Potwor::wyswietl() const
{
	lokalizacja->potworny();
	std::cout << "P";
	lokalizacja->zwykly();
}


