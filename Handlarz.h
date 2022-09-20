#pragma once
#include "Postac.h"
#include <iostream>

class Plansza;
class Handlarz : public Postac
{
public:
	Handlarz(int _zycieMax, int _iloscDukatow, int _atakBazowy, int _x, int _y, Plansza* _lokalizacja);
	virtual void wyswietl() const override;
};

