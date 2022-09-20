#include "Postac.h"
#include "Plansza.h"

Postac::Postac(int _zycieMax, int _iloscDukatow, int _atak, int _x, int _y, Plansza* _lokalizacja)
	: zycieMax(_zycieMax), iloscDukatow(_iloscDukatow), atak(_atak), x(_x), y(_y), zycie(_zycieMax), lokalizacja(_lokalizacja)
{
	if (atak < 0) atak = 0;
	if (zycieMax < 1) zycieMax = 1;
	if (zycie < 1) zycie = 1;
	if (iloscDukatow < 0) iloscDukatow = 0;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
}

void Postac::idz(char gdzie)
{
	int xNowy = x;
	int yNowy = y;
	if (gdzie == 'a') // lewo
	{
		xNowy -= 1;
	}
	else if (gdzie == 's') // dó³
	{
		yNowy += 1;
	}
	else if (gdzie == 'd') // prawo
	{
		xNowy += 1;
	}
	else if (gdzie == 'w') // góra
	{
		yNowy -= 1;
	}
	else throw std::exception("Nieprawidlowy kierunek jako argument metody idz() klasy Postac");
	switch (lokalizacja->getPole(xNowy, yNowy))
	{
	case 'H': // powoduje interakcje z handlarzem
		///interakcjaZHandlarzem(lokalizacja->getHandlarz());
		///break;
	case 'P': // powoduje interakcje z potworem
		///interakcjaZPotworem(lokalizacja->getPotworPola(xNowy, yNowy));
		///break;
	case 'G': // powoduje interakcje z graczem
		///interakcjaZGraczem(lokalizacja->getGracz());
		// METODA planszy
		lokalizacja->interakcjaPostaci(*this, xNowy, yNowy);
		break;
	case '#': // postac próbuje wejœæ w œcianê - nic nie rób
	case 'B': // podane wspolrzedne nie mieszcza sie w planszy - nic nie rób
		break;
	case ' ': // przemiesc sie
		//lokalizacja->wskaz(lokalizacja->getX() + x, lokalizacja->getY() + y);
		lokalizacja->setPole(xNowy, yNowy, lokalizacja->getPole(x, y));
		lokalizacja->setPole(x, y, ' ');
		x = xNowy;
		y = yNowy;
		break;
	}
}

int Postac::wybierzElementEkwipunku() const
{
	/* // stare wyswietlanie bez mozliwosci wyboru - sam podglad
	lokalizacja->ukryj();
	if (ekwipunek.size() == 0)
	{
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY());
		string fraza("Ekwipunek jest pusty.");
		if (fraza.length() > lokalizacja->getSzerokosc()) cout << fraza.substr(0, lokalizacja->getSzerokosc());
		else cout << fraza;
	}
	else
	{
		for (int i = 0; i < ekwipunek.size(); i++)
		{
			lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + i);
			string opis = ekwipunek[i]->opis();
			if (opis.length() > lokalizacja->getSzerokosc()) cout << opis.substr(0, lokalizacja->getSzerokosc());
			else cout << opis;
		}
	}
	cout << endl;
	system("pause");
	lokalizacja->wyswietl();*/
	int wybor = -1;
	if (ekwipunek.size() == 0)
	{
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string fraza("Ekwipunek jest pusty.");
		if (fraza.length() > lokalizacja->getSzerokosc()) cout << fraza.substr(0, lokalizacja->getSzerokosc());
		else cout << fraza;
		cout << endl;
		system("pause");
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string pustaLinia(lokalizacja->getSzerokosc() + 30, ' ');
		cout << pustaLinia << endl << pustaLinia;
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
		wybor = lokalizacja->obsluzNoweMenu(ekwipunek.size() + 1, tytul, opcje);
	}
	return wybor;
}

void Postac::operator+=(int punktyZycia)
{
	zycie += punktyZycia;
	if (zycie > zycieMax) zycie = zycieMax;
	else if (zycie < 0) zycie = 0;
}

void Postac::operator-=(int punktyZycia)
{
	zycie -= punktyZycia;
	if (zycie < 0) zycie = 0;
	else if (zycie > zycieMax) zycie = zycieMax;
}

void Postac::wezPrzedmiot(Przedmiot* podarunek)
{
	ekwipunek.push_back(podarunek);
	std::sort(ekwipunek.begin(), ekwipunek.end(), porownaniePrzedmiotow);
}

Przedmiot* Postac::oddajPrzedmiot(int ktory)
{
	if ((ktory >= 0) && (ktory < ekwipunek.size()))
	{
		Przedmiot* doOddania = ekwipunek[ktory];
		ekwipunek.erase(ekwipunek.begin() + ktory);
		return doOddania;
	}
	else return nullptr;
}

void Postac::dodajDukaty(int ile)
{
	iloscDukatow += ile;
	if (iloscDukatow < 0) iloscDukatow = 0;
}

void Postac::sprzedajPrzedmiot(int ktory, Postac* komu)
{
	if ((ktory > -1) && (ktory < ekwipunek.size()))
	{
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		if (ekwipunek[ktory]->getWartosc() <= komu->getDukaty())
		{
			Przedmiot* doSprzedania = ekwipunek[ktory];
			cout << doSprzedania->getNazwa();
			ekwipunek[ktory] = nullptr;
			ekwipunek.erase(ekwipunek.begin() + ktory);
			komu->dodajDukaty(-1 * (doSprzedania->getWartosc()));
			dodajDukaty(doSprzedania->getWartosc());
			lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc() + 1);
			const char* dukaty;
			if ((doSprzedania->getWartosc() >= 2) && (doSprzedania->getWartosc() <= 4)) dukaty = " Dukaty";
			else if (doSprzedania->getWartosc() == 1) dukaty = " Dukat";
			else dukaty = " Dukatow";
			if (lokalizacja->getPole(komu->getX(), komu->getY()) == 'G') cout << " - kupiono za ";
			else cout << " - sprzedano za ";
			cout << doSprzedania->getWartosc() << " " << dukaty;
			komu->wezPrzedmiot(doSprzedania);
			lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc() + 2);
		}
		else
		{
			cout << "Za malo dukatow, zeby dokonac transakcji.";
			lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc() + 1);
		}
		system("pause");
		lokalizacja->wskaz(lokalizacja->getX(), lokalizacja->getY() + lokalizacja->getWysokosc());
		string pustaLinia(lokalizacja->getSzerokosc() + 30, ' ');
		cout << pustaLinia << endl << pustaLinia << endl << pustaLinia;
		lokalizacja->wskaz(lokalizacja->getX() + lokalizacja->getSzerokosc() - 1, lokalizacja->getY() + lokalizacja->getWysokosc() - 1);
	}
}

bool porownaniePrzedmiotow(Przedmiot* i, Przedmiot* j) 
{ 
	bool czyWczesniej;
	if (i->typ() == j->typ())
	{
		if (i->getNazwa() == j->getNazwa())
		{
			czyWczesniej = (i->getWartosc() < j->getWartosc());
		}
		else
		{
			czyWczesniej = (i->getNazwa() < j->getNazwa());
		}
	}
	else czyWczesniej = (i->typ() < j->typ());
	return czyWczesniej; 
}