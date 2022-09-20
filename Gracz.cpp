#include "Gracz.h"
#include "Gra.h"
#include "GUI.h"
#include "Plansza.h"

Gracz::Gracz(int _zycieMax, int _iloscDukatow, int _atakBazowy, int _x, int _y, Gra* _rozgrywka, Plansza* _lokalizacja/*, Menu* _menu*/, GUI* _interfejs)
	: Postac(_zycieMax, _iloscDukatow,  _atakBazowy,  _x, _y, _lokalizacja), atakBazowy(_atakBazowy),/* menu(_menu),*/ interfejs(_interfejs), 
	rozgrywka(_rozgrywka), uzywanaBron(nullptr), przygotowanaMikstura(nullptr)
{
	if (atakBazowy < 0) atakBazowy = 0;
}

void Gracz::wykonujeRuch()
{
	char znak;
	do
	{
		znak = _getch();
		switch (znak)
		{
		case 'e':
		case 'E':
			//wyswietlEkwipunek();
			//wybierzElementEkwipunku();
			uzyjPrzedmiot();
			break;
		case 'a':
		case 'A':
			idz('a');
			break;
		case 'W':
		case 'w':
			idz('w');
			break;
		case 'd':
		case 'D':
			idz('d');
			break;
		case 's':
		case 'S':
			idz('s');
			break;
		case 'm':
		case 'M':
			wypijMiksture();
			break;
		case 'z':
		case 'Z':
			zdejmijBron();
			break;
		case 'x':
		case 'X':
			zdejmijMiksture();
			break;
		case 27: // Esc
			rozgrywka->czyDalejGrac = false;
			//lokalizacja->koniecGry();
			break;
		default:
			znak = 0;
			break;
		}
	} while (znak == 0);
}

void Gracz::wyswietl() const
{
	lokalizacja->graczowy();
	cout << 'G';
	lokalizacja->zwykly();
}

void Gracz::dodajDukaty(int ile)
{
	iloscDukatow += ile;
	if (iloscDukatow < 0) iloscDukatow = 0;
	interfejs->aktualizujDukaty(iloscDukatow);
}

void Gracz::operator+=(int punktyZycia)
{
	zycie += punktyZycia;
	if (zycie > zycieMax) zycie = zycieMax;
	else if (zycie < 0) zycie = 0;
	interfejs->aktualizujZycie(zycie, zycieMax);
}

void Gracz::operator-=(int punktyZycia)
{
	zycie -= punktyZycia;
	if (zycie < 0) zycie = 0;
	else if (zycie > zycieMax) zycie = zycieMax;
	interfejs->aktualizujZycie(zycie, zycieMax);
}
/*
void Gracz::wyswietlEkwipunek()
{
	/*
	if (ekwipunek.size() == 0)
	{
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string fraza("Ekwipunek jest pusty.");
		if (fraza.length() > lokalizacja->getSzerokosc()) cout << fraza.substr(0, lokalizacja->getSzerokosc());
		else cout << fraza;
		cout << endl;
		system("pause");
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		cout << "                     " << endl << "                                          ";
		lokalizacja->wskaz(lokalizacja->getX() + lokalizacja->getSzerokosc() - 1, lokalizacja->getY() + lokalizacja->getWysokosc() - 1);
	}
	else
	{
		string tytul("Wybierz przedmiot");
		string* opcje;
		opcje = new string[ekwipunek.size() + 1];
		for (int i = 0; i < ekwipunek.size(); i++)
		{
			//interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc() + i);
			opcje[i] = ekwipunek[i]->opis();
		}
		opcje[ekwipunek.size()] = "Wyjdz";
		int wybor = menu->noweMenu(ekwipunek.size() + 1, tytul, opcje);
		*/
		
		//return wybor;
		/*
		if (wybor < ekwipunek.size())
		{
			//ekwipunek[wybor]->uzywaGracz(*this, wybor);
			uzyjPrzedmiot(wybor);
		}*/
	/*}
}*/

void Gracz::zmienBron(Bron* naTaka, int ktora)
{
	if (uzywanaBron == nullptr)
	{
		uzywanaBron = naTaka;
		ekwipunek[ktora] = nullptr;
		ekwipunek.erase(ekwipunek.begin() + ktora);
	}
	else
	{
		//Bron* temp = uzywanaBron;
		ekwipunek[ktora] = nullptr;
		ekwipunek.erase(ekwipunek.begin() + ktora);
		ekwipunek.push_back(uzywanaBron);
		uzywanaBron = naTaka;
	}
	atak = atakBazowy + uzywanaBron->getZwiekszenieAtaku();
	std::sort(ekwipunek.begin(), ekwipunek.end(), porownaniePrzedmiotow);
}

void Gracz::zmienMiksture(Mikstura* naTaka, int ktora)
{
	if (przygotowanaMikstura == nullptr)
	{
		przygotowanaMikstura = naTaka;
		ekwipunek[ktora] = nullptr;
		ekwipunek.erase(ekwipunek.begin() + ktora);
	}
	else
	{
		//Mikstura* temp = przygotowanaMikstura;
		ekwipunek[ktora] = nullptr;
		ekwipunek.erase(ekwipunek.begin() + ktora);
		ekwipunek.push_back(przygotowanaMikstura);
		przygotowanaMikstura = naTaka;
	}
	std::sort(ekwipunek.begin(), ekwipunek.end(), porownaniePrzedmiotow);
}

bool Gracz::czyMaMiksture()
{
	if (przygotowanaMikstura != nullptr) return true;
	else return false;
}

void Gracz::uzyjPrzedmiot()
{
	int ktory = wybierzElementEkwipunku();
	if ((ktory > -1) && (ktory < ekwipunek.size()))
	{
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		char typ = ekwipunek[ktory]->typ();
		if (typ == 'B')
		{
			cout << ekwipunek[ktory]->getNazwa() << endl << " - Dobyto";
			zmienBron((Bron*)ekwipunek[ktory], ktory);
		}
		else if (typ == 'M')
		{
			cout << ekwipunek[ktory]->getNazwa() << endl << " - Przygotowano do wypicia";
			zmienMiksture((Mikstura*)ekwipunek[ktory], ktory);
		}
		else if (typ == 'P') cout << ekwipunek[ktory]->getNazwa() << endl << " - Nie mozna uzyc";
		cout << endl;
		system("pause");
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string pustaLinia(lokalizacja->getSzerokosc() + 30, ' ');
		//cout << pustaLinia << endl << pustaLinia << endl << pustaLinia;
		cout << pustaLinia;
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc() + 1);
		cout << pustaLinia;
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc() + 2);
		cout << pustaLinia;
	}
	interfejs->wskaz(lokalizacja->getX() + lokalizacja->getSzerokosc() - 1, lokalizacja->getY() + lokalizacja->getWysokosc() - 1);
}

void Gracz::wypijMiksture()
{
	if (przygotowanaMikstura != nullptr)
	{
		*this += przygotowanaMikstura->getPrzywrocenieZycia();
		rozgrywka->usunPrzedmiot(przygotowanaMikstura);
		przygotowanaMikstura = nullptr;
	}
}

void Gracz::zdejmijBron()
{
	
	if (uzywanaBron != nullptr)
	{
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		cout << uzywanaBron->getNazwa() << endl << " - schowano do ekwipunku" << endl;
		wezPrzedmiot(uzywanaBron);
		atak = atakBazowy;
		uzywanaBron = nullptr;
		system("pause");
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string pustaLinia(lokalizacja->getSzerokosc() + 30, ' ');
		cout << pustaLinia << endl << pustaLinia << endl << pustaLinia;
		interfejs->wskaz(lokalizacja->getX() + lokalizacja->getSzerokosc() - 1, lokalizacja->getY() + lokalizacja->getWysokosc() - 1);
	}
	
}

void Gracz::zdejmijMiksture()
{
	if (przygotowanaMikstura != nullptr)
	{
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		cout << przygotowanaMikstura->getNazwa() << endl << " - schowano do ekwipunku" << endl;
		wezPrzedmiot(przygotowanaMikstura);
		przygotowanaMikstura = nullptr;
		system("pause");
		interfejs->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string pustaLinia(lokalizacja->getSzerokosc() + 30, ' ');
		cout << pustaLinia << endl << pustaLinia << endl << pustaLinia;
		interfejs->wskaz(lokalizacja->getX() + lokalizacja->getSzerokosc() - 1, lokalizacja->getY() + lokalizacja->getWysokosc() - 1);
	}
}

