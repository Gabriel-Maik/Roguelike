#pragma once
#include "Przedmiot.h"

class Bron :
	public Przedmiot
{
	int zwiekszenieAtaku;
public:
	Bron(int _wartosc, string _nazwa, int _zwiekszenieAtaku);
	int getZwiekszenieAtaku() const { return zwiekszenieAtaku; }
	virtual string opis() const override;
	virtual char typ() override { return 'B'; }
};


