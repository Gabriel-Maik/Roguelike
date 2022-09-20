#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Przedmiot // mozna zrobic operator <<
{
protected:
	int wartosc;
	string nazwa;
public:
	Przedmiot(int wartosc, string nazwa);
	int getWartosc() const{ return wartosc; }
	string getNazwa() const { return nazwa; }
	virtual string opis() const;
	virtual char typ() { return 'P'; }
};