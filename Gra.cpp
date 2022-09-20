#include "Gra.h"

Gra::Gra()
	: czyDalejGrac(true), menu(0, 71, 100, wysStdMenu, 0, " ", nullptr)
{
	srand(time(NULL));
	int szerokosc = 100; // tymczasowo - normalnie wczytywane z pliku konfiguracyjnego (a gdy nie ma to wyj¹tek!) // 100, 40
	int wysokosc = 40;

	interfejs = new GUI(szerokosc, wysokosc, &menu);

	///plansze.push_back(new Plansza(0, 0, "plansze/Plansza2.txt", this)); // plansza music byc tworzona po interfejsie, bo inaczej gracza GUI* nullptr
	
	//menu = interfejs->getMenu();
	
	//plansze.push_back(new Plansza(0, 0, 70, 30, this));
	//plansze.push_back(new Plansza(0, 0, 70, 30, this));
	
	///interfejs->setPlansza(plansze[0]);
	//gracz = plansze[0]->generujGracza(interfejs->getMenu(), interfejs);
	///interfejs->dodajGracza(gracz);
	

	/*plansze[0]->ukryj();
	system("pause");
	plansze[0]->wyswietl();
	system("pause");
	interfejs->ukryj();
	system("pause");
	interfejs->wyswietl();
	system("pause");*/
}

Gra::~Gra()
{
	dealokuj();
}

Przedmiot* Gra::generujPrzedmiot()
{
	if (rand() % 2) // 50% na bron, 50% na miksture
	{
		return generujBron();
	}
	else
	{
		return generujMiksture();
	}
}

Mikstura* Gra::generujMiksture()
{
	string nazwaPrzedmiotu;
	switch (rand() % 5)
	{
	case 0:
		nazwaPrzedmiotu = "Mikstura uzdrawiajaca";
		break;
	case 1:
		nazwaPrzedmiotu = "Odwar ziolowy\t";
		break;
	case 2:
		nazwaPrzedmiotu = "Herbata magiczna";
		break;
	case 3:
		nazwaPrzedmiotu = "Mikstura lecznicza";
		break;
	case 4:
		nazwaPrzedmiotu = "Fajna mikstura\t";
		break;
	}
	mikstury.push_back(new Mikstura((rand() % 10) + 3, nazwaPrzedmiotu, (rand() % 5) + 2));
	return mikstury.back();
}

Bron* Gra::generujBron()
{
	string nazwaPrzedmiotu;
	switch (rand() % 5)
	{
	case 0:
		nazwaPrzedmiotu = "Miecz krotki\t";
		break;
	case 1:
		nazwaPrzedmiotu = "Szabla\t\t";
		break;
	case 2:
		nazwaPrzedmiotu = "Rapier\t\t";
		break;
	case 3:
		nazwaPrzedmiotu = "Szpada\t\t";
		break;
	case 4:
		nazwaPrzedmiotu = "Topor\t\t";
		break;
	}
	bronie.push_back(new Bron((rand() % 10) + 3, nazwaPrzedmiotu, (rand() % 5) + 2));
	return bronie.back();
}

void Gra::zacznijGre()
{
	interfejs->wyswietl();
	for (int i = 0; i < 3; i++) gracz->wezPrzedmiot(generujPrzedmiot());
	for (int i = 0; i < 40; i++) plansze[0]->getHandlarz().wezPrzedmiot(generujPrzedmiot());
	
	while (czyDalejGrac) gracz->wykonujeRuch();
	koniecGry();
}

void Gra::koniecGry()
{
	czyDalejGrac = false;
	//system("cls");
	interfejs->wskaz(0, 0);
	cout << "Koniec gry ";
	//dealokuj();
	system("pause");
}

void Gra::dealokuj()
{
	if (gracz != nullptr)
	{
		delete gracz;
		gracz = nullptr;
	}
	while (plansze.empty() == false)
	{
		//Plansza* doUsuniecia = plansze[plansze.size() - 1];
		//delete doUsuniecia;
		plansze.pop_back();
	}
	while (bronie.empty() == false)
	{
		//Bron* doUsuniecia = bronie[bronie.size() - 1];
		//delete doUsuniecia;
		bronie.pop_back();
	}
	while (mikstury.empty() == false)
	{
		//Mikstura* doUsuniecia = mikstury[mikstury.size() - 1];
		//delete doUsuniecia;
		mikstury.pop_back();
	}
	if (interfejs != nullptr)
	{
		delete interfejs;
		interfejs = nullptr;
	}
}

void Gra::generujGracza(Plansza* _plansza, int _x, int _y)
{
	if (_x < 0) _x = 0;
	if (_x < 0) _y = 0;
	gracz = new Gracz(20, 0, 3, _x, _y, this, _plansza, /*&menu,*/ interfejs);
	if (_plansza != nullptr)
	{
		_plansza->setGracz(gracz);
		_plansza->setPole(_x, _y, 'G');
		_plansza->ukryj();
	}
}

void Gra::usunPrzedmiot(Przedmiot * _przedmiot)
{
	if (_przedmiot->typ() == 'M')
	{
		Mikstura* doUsuniecia = (Mikstura*)_przedmiot;
		for (int i = 0; i < mikstury.size(); i++)
		{
			if (mikstury[i] == doUsuniecia)
			{
				mikstury.erase(mikstury.begin() + i);
				break;
			}
		}
	}
	else if (_przedmiot->typ() == 'B')
	{
		Bron* doUsuniecia = (Bron*)_przedmiot;
		for (int i = 0; i < bronie.size(); i++)
		{
			if (bronie[i] == doUsuniecia)
			{
				bronie.erase(bronie.begin() + i);
				break;
			}
		}
	}
}

void Gra::menuGlowne()
{
	string tytul("Menu Glowne");
	string* opcje;
	opcje = new string[4];
	opcje[0] = "Graj w poziom niestandardowy";
	opcje[1] = "Graj w poziom 1";
	opcje[2] = "Graj w poziom 2";
	opcje[3] = "Wyjdz";
	int wybor = menu.noweMenu(4, tytul, opcje, 0, 0, interfejs->getSzerokosc(), interfejs->getWysokosc());
	//int wybor = menu.noweMenu(2, tytul, opcje);
	//interfejs->setPlansza(plansze[0]);
	string nazwa;
	string sciezkaDostepu("plansze/");
	switch (wybor)
	{
	case 0:
		interfejs->wskaz(0, 0);
		cout << "Podaj nazwe planszy: ";
		std::cin >> nazwa;
		sciezkaDostepu.append(nazwa);
		plansze.push_back(new Plansza(0, 0, sciezkaDostepu, this));
		interfejs->setPlansza(plansze[0]);
		interfejs->dodajGracza(gracz);
		zacznijGre();
		break;
	case 1:
		plansze.push_back(new Plansza(0, 0, "plansze/plansza1.txt", this));
		interfejs->setPlansza(plansze[0]);
		interfejs->dodajGracza(gracz);
		zacznijGre();
		break;
	case 2:
		plansze.push_back(new Plansza(0, 0, "plansze/plansza2.txt", this));
		interfejs->setPlansza(plansze[0]);
		interfejs->dodajGracza(gracz);
		zacznijGre();
		break;
	case 3:
		czyDalejGrac = false;
		break;
	}
}

int Gra::obsluzNoweMenu(int _iloscOpcji, string _tytul, string* _opcje)
{
	int wysokoscPrzed = interfejs->getWysokosc();
	int wysMenuPrzed = menu.getWysokosc();
	if (_iloscOpcji + 1 > wysStdMenu)
	{
		interfejs->setWysokosc(interfejs->getWysokosc() + _iloscOpcji + 1 - menu.getWysokosc());
		interfejs->ustawWielkoscKonsoli(interfejs->getSzerokosc(), interfejs->getWysokosc());
		menu.setWysokosc(_iloscOpcji + 1);
	}
	int wybor = menu.noweMenu(_iloscOpcji, _tytul, _opcje);
	if (_iloscOpcji + 1 > wysStdMenu)
	{
		interfejs->setWysokosc(wysokoscPrzed);
		interfejs->ustawWielkoscKonsoli(interfejs->getSzerokosc(), interfejs->getWysokosc());
		menu.setWysokosc(wysMenuPrzed);
	}
	return wybor;
}