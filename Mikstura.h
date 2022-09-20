#pragma once
#include "Przedmiot.h"

class Mikstura :
	public Przedmiot
{
	int przywrocenieZycia;
public:
	Mikstura(int _wartosc, string _nazwa, int _przywrocenieZycia);
	int getPrzywrocenieZycia() const { return przywrocenieZycia; }
	virtual string opis() const override;
	virtual char typ() override { return 'M'; }
};

