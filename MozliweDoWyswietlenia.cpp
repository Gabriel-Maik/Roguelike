#include "MozliweDoWyswietlenia.h"

MozliweDoWyswietlenia::MozliweDoWyswietlenia()
	: uchwyt(GetStdHandle(STD_OUTPUT_HANDLE)), x(0), y(0), szerokosc(1), wysokosc(1)
{
}

MozliweDoWyswietlenia::MozliweDoWyswietlenia(int _x, int _y, int _szerokosc, int _wysokosc)
	: x(_x), y(_y), szerokosc(_szerokosc), wysokosc(_wysokosc), uchwyt(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

void MozliweDoWyswietlenia::setX(int _x)
{
	if (_x >= 0) x = _x;
}

void MozliweDoWyswietlenia::setY(int _y)
{
	if (_y > 0) y = _y;
}

void MozliweDoWyswietlenia::setSzerokosc(int nowaSzerokosc)
{
	if (nowaSzerokosc > 0) szerokosc = nowaSzerokosc;
}

void MozliweDoWyswietlenia::setWysokosc(int nowaWysokosc)
{
	if (nowaWysokosc > 0) wysokosc = nowaWysokosc;
}

void MozliweDoWyswietlenia::wskaz(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(uchwyt, c);
}

/* // settery
void MozliweDoWyswietlenia::setSzerokosc(int nowaSzerokosc)
{
	if (nowaSzerokosc > 0) szerokosc = nowaSzerokosc;
}

void MozliweDoWyswietlenia::setWysokosc(int nowaWysokosc)
{
	if (nowaWysokosc > 0) wysokosc = nowaWysokosc;
}*/

void MozliweDoWyswietlenia::ukryj()
{
	for (int w = 0; w < wysokosc; w++)
	{
		wskaz(x, y + w);
		for (int k = 0; k < szerokosc; k++)
		{
			std::cout << ' ';
		}
	}
}