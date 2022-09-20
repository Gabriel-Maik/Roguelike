#pragma once
#include "Postac.h"
#include <iostream>

class Plansza;
class Gracz;
class Potwor :
	public Postac
{
public:
	Potwor(int _zycieMax, int _iloscDukatow, int _atak, int _x, int _y, Plansza* _lokalizacja);
	virtual void wyswietl() const override;
};

