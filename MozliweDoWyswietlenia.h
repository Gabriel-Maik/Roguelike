#pragma once
#include <windows.h>
#include <iostream>
#include <cstdlib>

class MozliweDoWyswietlenia // mozna dodac obsluge kolorow tla i liter
{
	HANDLE uchwyt;
protected:
	int x; // po³o¿enie lewego górnego naro¿nika
	int y;
	int szerokosc;
	int wysokosc;
public:
	virtual void wyswietl() = 0;
	void wskaz(int x, int y); // uklad bezwzgledny
	void ukryj();
	MozliweDoWyswietlenia();
	MozliweDoWyswietlenia(int _x, int _y, int _szerokosc, int _wysokosc);
	int getX() const { return x; }
	void setX(int _x);
	int getY() const { return y; }
	void setY(int _y);
	int getSzerokosc() const { return szerokosc; }
	void setSzerokosc(int nowaSzerokosc);
	int getWysokosc() const { return wysokosc; }
	void setWysokosc(int nowaWysokosc);
	void podswietlenie() const { SetConsoleTextAttribute(uchwyt, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY); }
	void zwykly() const { SetConsoleTextAttribute(uchwyt, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); }
	void zolty() const { SetConsoleTextAttribute(uchwyt, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); }
	void czerwony() const { SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY); }
	//void czerwonyTlo() const { SetConsoleTextAttribute(uchwyt, BACKGROUND_RED | BACKGROUND_INTENSITY); }
	//void zielony() const { SetConsoleTextAttribute(uchwyt, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); }
	void potworny() const { SetConsoleTextAttribute(uchwyt, BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); }
	void graczowy() const { SetConsoleTextAttribute(uchwyt, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN); }
	void handlarzowy() const { SetConsoleTextAttribute(uchwyt, BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); }
};

