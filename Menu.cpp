#include "Menu.h"

Menu::Menu(int _x, int _y, int _szerokosc, int _wysokosc, int _iloscOpcji, string _tytul, string* _opcje)
	: MozliweDoWyswietlenia(_x, _y, _szerokosc, _wysokosc), iloscOpcji(_iloscOpcji), tytul(_tytul), wybor(0)
{
}

Menu::~Menu()
{
	if (opcje != nullptr) delete[] opcje;
}

int Menu::noweMenu(int _iloscOpcji, string _tytul, string* _opcje)
{
	if(_iloscOpcji > 0) iloscOpcji = _iloscOpcji;
	else iloscOpcji = 0;
	tytul = _tytul;
	opcje = _opcje;
	wybor = 0;
	return wybierz();
}

int Menu::noweMenu(int _iloscOpcji, string _tytul, string* _opcje, int _x, int _y, int _szerokosc, int _wysokosc)
{
	if (x >= 0) x = _x;
	if (y >= 0) y = _y;
	if (_szerokosc > 0) szerokosc = _szerokosc;
	if (_wysokosc > 0) wysokosc = _wysokosc;
	return noweMenu(_iloscOpcji, _tytul, _opcje);
}

void Menu::wyswietl()
{
	wskaz(x, y);
	if (tytul.length() > szerokosc) cout << tytul.substr(0, szerokosc);
	else cout << tytul;
	for (int i = 0; i < iloscOpcji; i++)
	{
		wskaz(x, y + i + 1);
		if (wybor == i) podswietlenie();
		if (opcje[i].length() > szerokosc) cout << opcje[i].substr(0, szerokosc);
		else cout << opcje[i];
		if (wybor == i) zwykly();
	}
	wskaz(x + szerokosc - 1, y);
}

void Menu::wyswietlZmianeOpcji(char znak, int wybor)
{
	wskaz(x, y + wybor + 1);
	podswietlenie();
	if (opcje[wybor].length() > szerokosc) cout << opcje[wybor].substr(0, szerokosc);
	else cout << opcje[wybor];
	zwykly();
	if (znak == 'w')
	{
		wskaz(x, y + wybor + 2);
		if (opcje[wybor + 1].length() > szerokosc) cout << opcje[wybor + 1].substr(0, szerokosc);
		else cout << opcje[wybor + 1];
	}
	else if (znak == 's')
	{
		wskaz(x, y + wybor);
		if (opcje[wybor - 1].length() > szerokosc) cout << opcje[wybor - 1].substr(0, szerokosc);
		else cout << opcje[wybor - 1];
	}
	wskaz(x + szerokosc - 1, y + wybor + 1);
}

int Menu::wybierz()
{
	char znak;
	wyswietl();
	do
	{
		znak = _getch();
		switch (znak)
		{
		case 'w':
		case 'W':
			if (wybor > 0)
			{
				wybor--;
				wyswietlZmianeOpcji('w', wybor);
			}
			//wyswietl();
			break;
		case 's':
		case 'S':
			if (wybor < iloscOpcji - 1)
			{
				wybor++;
				wyswietlZmianeOpcji('s', wybor);
			}
			//wyswietl();
			break;
		case 'e':
		case 'E':
		case 13:
		case ' ':
		default:
			break;
		}
	} while ((znak != 13) && (znak != ' ') && (znak != 'e') && (znak != 'E'));
	ukryj();
	wskaz(0, 0);
	wskaz(x + szerokosc - 1, y);
	delete[] opcje;
	opcje = nullptr;
	return wybor;
}