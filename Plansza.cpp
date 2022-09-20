#include "Plansza.h"
#include "Gra.h"

Plansza::Plansza(int _x, int _y, int _szerokosc, int _wysokosc, Gra* _rozgrywka)
	: MozliweDoWyswietlenia(_x, _y, _szerokosc, _wysokosc), handlarz(nullptr), rozgrywka(_rozgrywka), iloscPotworow(0), gracz(nullptr)
{
	for (int i = 0; i < potworyMax; i++)
	{
		potwory[i] = nullptr;
	}
	zaladujPoziomStandardowy();
}

Plansza::Plansza(int _x, int _y, string nazwaPliku, Gra* _rozgrywka)
	: MozliweDoWyswietlenia(_x, _y, 1, 1), handlarz(nullptr), rozgrywka(_rozgrywka), iloscPotworow(0), gracz(nullptr)
{
	for (int i = 0; i < 10; i++)
	{
		potwory[i] = nullptr;
	}
	try
	{
		zaladujPoziomZPliku(nazwaPliku);
	}
	catch (std::exception blad)
	{
		dealokuj();
		std::cout << blad.what();
		cout << endl << "Zostanie wczytany poziom standardowy ";
		szerokosc = 70;
		wysokosc = 30;
		system("pause");
		system("cls");
		zaladujPoziomStandardowy();
	}
}

Plansza::~Plansza()
{
	dealokuj();
}

void Plansza::alokuj()
{
	pola = new char[(wysokosc * szerokosc)];
	wiersze = new char*[wysokosc];
	for (int i = 0; i < wysokosc; ++i)
	{
		wiersze[i] = pola + (i * szerokosc);
	}
}

char Plansza::getPole(int _x, int _y) const // uklad wzgledny
{
	if (((_x >= 0) && (_x <= (szerokosc - 1))) && ((_y >= 0) && (_y <= (wysokosc - 1)))) return wiersze[_y][_x];
	else return 'B'; // B - Blad
}

void Plansza::setPole(int _x, int _y, char naCo) // uklad wzgledny
{
	if (((_x >= 0) && (_x <= (szerokosc - 1))) && ((_y >= 0) && (_y <= (wysokosc - 1))))
	{
		wiersze[_y][_x] = naCo;
		wskaz(x + _x, y + _y);
		if (naCo == 'G') gracz->wyswietl();
		else if (naCo == 'H') handlarz->wyswietl();
		else if (naCo == 'P') getPotworPola(_x, _y).wyswietl();
		else cout << naCo;
		wskaz(x + szerokosc - 1, y + wysokosc - 1);
	}
}

void Plansza::wyswietl()
{
	for (int w = 0; w < wysokosc; w++)
	{
		wskaz(x, y + w);
		for (int k = 0; k < szerokosc; k++)
		{
			
			if (wiersze[w][k] == 'G') gracz->wyswietl();
			else if (wiersze[w][k] == 'H') handlarz->wyswietl();
			else if (wiersze[w][k] == 'P') getPotworPola(k, w).wyswietl();
			else cout << wiersze[w][k];
		}
	}
}

void Plansza::generujPotwora(int _x, int _y)
{
	if (iloscPotworow < potworyMax) //throw std::exception("Zbyt duza ilosc potworow w pliku");
	{
		int xP, yP;
		if ((_x == -1) || (_y == -1))
		{
			/*do
			{
				xP = rand() % szerokosc;
				yP = rand() % wysokosc;
			} while (wiersze[yP][xP] != ' ');*/
			losujWolnePole(xP, yP);
		}
		else
		{
			xP = _x;
			yP = _y;
		}
		potwory[iloscPotworow] = new Potwor((rand() % 3) + 10, rand() % 3, 1 + rand() % 3, xP, yP, this);
		iloscPotworow++;
		wiersze[yP][xP] = 'P';
	}
}

void Plansza::generujHandlarza(int _x, int _y)
{
	if (handlarz == nullptr)
	{
		int xH, yH;
		if ((_x == -1) || (_y == -1))
		{
			/*do
			{
				xH = rand() % szerokosc;
				yH = rand() % wysokosc;
			} while (wiersze[yH][xH] != ' ');*/
			losujWolnePole(xH, yH);
		}
		else
		{
			xH = _x;
			yH = _y;
		}
		handlarz = new Handlarz(10, 100, 1, xH, yH, this);
		wiersze[yH][xH] = 'H';
	}
	handlarz->wezPrzedmiot(rozgrywka->generujPrzedmiot());
}

void Plansza::generujGracza(int _x, int _y)
{
	if (gracz == nullptr)
	{
		int xG, yG;
		if ((_x == -1) || (_y == -1))
		{
			losujWolnePole(xG, yG);
		}
		else
		{
			xG = _x;
			yG = _y;
		}
		rozgrywka->generujGracza(this, xG, yG);
		wiersze[yG][xG] = 'G';
	}
}

Potwor& Plansza::getPotworPola(int _x, int _y) const
{
	if (wiersze[_y][_x] != 'P') throw std::exception("Potwora nie ma na podanym polu, wiec nie mozna go podac.");
	for (int i = 0; i < potworyMax; i++)
	{
		if ((potwory[i]->getX() == _x) && (potwory[i]->getY() == _y)) return *(potwory[i]);
	}
}

Handlarz& Plansza::getHandlarz() const
{
	if (handlarz == nullptr) throw std::exception("Nie ma handlarza, wiec nie mozna go podac.");
	return *handlarz;
}

void Plansza::zaladujPoziomStandardowy()
{
	alokuj();
	for (int w = 0; w < wysokosc; w++)
	{
		for (int k = 0; k < szerokosc; k++)
		{
			if ((w == 0) || (w == (wysokosc - 1))) wiersze[w][k] = '#';
			else if ((k == 0) || (k == (szerokosc - 1))) wiersze[w][k] = '#';
			else wiersze[w][k] = ' ';
		}
	}
	int xG = 0;
	int yG = 0;
	losujWolnePole(xG, yG);
	rozgrywka->generujGracza(this, xG, yG);
	generujHandlarza();
	for (int i = 0; i < potworyMax; i++) { generujPotwora(); }
}

void Plansza::zaladujPoziomZPliku(string nazwaPliku)
{
	std::ifstream plik;
	plik.open(nazwaPliku, std::ifstream::in);
	if (plik.good() == false)
	{
		string opisBledu("Pliku o nazwie/sciezce dostepu \"");
		opisBledu.append(nazwaPliku).append("\" nie odnaleziono");
		throw std::exception(opisBledu.c_str());
	}
	string linia;
	std::getline(plik, linia);
	istringstream strumien(linia);
	strumien >> szerokosc;
	strumien >> wysokosc;
	if ((szerokosc > 200) || (szerokosc < 56) || (wysokosc < 3) || (wysokosc > 30)) throw std::exception("Nieobslugiwane wymiary planszy");
	alokuj();
	char znak;
	for (int w = 0; w < wysokosc; w++)
	{
		string linia2;
		std::getline(plik, linia2);
		for (int k = 0; k < szerokosc; k++)
		{
			znak = linia2[k];
			if (znak == '-') znak = ' ';
			wiersze[w][k] = znak;
			if (znak == 'P')
			{
				if (iloscPotworow < potworyMax) generujPotwora(k, w);
				else wiersze[w][k] = ' ';
			}
			else if (znak == 'H')
			{
				if (handlarz == nullptr) generujHandlarza(k, w);
				else wiersze[w][k] = ' ';
			}
			else if (znak == 'G')
			{
				if (gracz == nullptr) rozgrywka->generujGracza(this, k, w);
				else wiersze[w][k] = ' ';
			}
		}
	}
	plik.close();
}

void Plansza::dealokuj()
{
	for (int i = 0; i < iloscPotworow; i++)
	{
		//if (potwory[i] != nullptr) 
		delete potwory[i];
	}
	iloscPotworow = 0;
	delete handlarz;
	delete[] wiersze;
	delete[] pola;
}

void Plansza::usunPotwora(Potwor* doUsuniecia)
{
	for (int i = 0; i < potworyMax; i++)
	{
		if (potwory[i] == doUsuniecia)
		{
			wiersze[potwory[i]->getY()][potwory[i]->getX()] = ' ';
			delete (potwory[i]);
			//potwory[i] = nullptr;
			iloscPotworow--;
			potwory[i] = potwory[iloscPotworow];
			potwory[iloscPotworow] = nullptr; // dodano
			break;
		}
	}
	if (iloscPotworow == 0) // UWAGA - to jest tymczasowo
	{
		ukryj();
		wskaz(0, 0);
		cout << "Loch zostal oczyszczony.";
		wskaz(0, 1);
		rozgrywka->czyDalejGrac = false;
	}
}

void Plansza::handel()
{
	string* opcje;
	opcje = new string[3];
	opcje[0] = "Pokaz mi swoje towary";
	opcje[1] = "Mam cos do sprzedania";
	opcje[2] = "Wyjdz";
	int tryb = rozgrywka->obsluzNoweMenu(3, string("Witaj w moim sklepie. W czym moge Ci sluzyc?"), opcje);
	if (tryb == 0)
	{
		handlarz->sprzedajPrzedmiot(handlarz->wybierzElementEkwipunku(), gracz);
	}
	else if (tryb == 1)
	{
		gracz->sprzedajPrzedmiot(gracz->wybierzElementEkwipunku(), handlarz);
	}
	
}

void Plansza::losujWolnePole(int& _x, int& _y)
{
	do
	{
		_x = rand() % szerokosc;
		_y = rand() % wysokosc;
	} while (wiersze[_y][_x] != ' ');
}

void Plansza::interakcjaPostaci(Postac& postac, int _x, int _y)
{
	if (getPole(postac.getX(), postac.getY()) == 'G') // gracz wchodzi w interakcje z...
	{
		if (getPole(_x, _y) == 'P') // ...potworem
		{
			walka(getPotworPola(_x, _y));
		}
		else if (getPole(_x, _y) == 'H') // ...handlarzem
		{
			handel();
		}
	}
	// inne interakcje poki co niezdefiniowane tzn. nic sie nie dzieje
}

void Plansza::walka(Potwor& potwor)
{
	int pozycja = 0;
	ukryj();
	wskaz(0, pozycja);
	podswietlenie();
	cout << "Gracz walczy z potworem";
	//temp
	pozycja++;
	if (pozycja > wysokosc - 1)
	{
		pozycja = 0;
		ukryj();
	}
	wskaz(0, pozycja);
	zwykly();
	cout << "Gracz, zycie: " << gracz->getZycie() << ", atak: " << gracz->getAtak();
	pozycja++;
	if (pozycja > wysokosc - 1)
	{
		pozycja = 0;
		ukryj();
	}
	wskaz(0, pozycja);
	cout << "Potwor, zycie: " << potwor.getZycie() << ", atak: " << potwor.getAtak();
	//
	pozycja += 1;
	while ((gracz > 0) && (potwor > 0))
	{
		char znak = _getch();
		pozycja += 1;
		if (pozycja > wysokosc - 1)
		{
			pozycja = 0;
			ukryj();
		}
		if ((znak == 'M') || (znak == 'm'))
		{
			if (gracz->czyMaMiksture())
			{
				int zyciePrzed = gracz->getZycie();
				gracz->wypijMiksture();
				zolty();
				wskaz(0, pozycja);
				cout << "Gracz wypija miksture i przywraca sobie " << gracz->getZycie() - zyciePrzed << " zycia.";
			}
			else
			{
				zolty();
				wskaz(0, pozycja);
				cout << "Gracz chce wypic miksture, ale nie przygotowal jej.";
			}
		}
		else
		{
			potwor -= gracz->getAtak();
			zolty();
			wskaz(0, pozycja);
			cout << "Gracz atakuje za " << (gracz->getAtak()) << ". Potworowi zostaje " << (potwor.getZycie()) << " zycia.";
		}
		if (potwor < 1)
		{
			pozycja += 2;
			if (pozycja > wysokosc - 1)
			{
				pozycja = 0;
				ukryj();
			}
			wskaz(0, pozycja);
			podswietlenie();
			cout << "Gracz wygrywa!";
			pozycja++;
			if (pozycja > wysokosc)
			{
				pozycja = 0;
				ukryj();
			}
			wskaz(0, pozycja);
			zolty();
			cout << "Znalezione dukaty: " << potwor.getDukaty();
			gracz->dodajDukaty(potwor.getDukaty());
			pozycja++;
			if (pozycja > wysokosc - 1)
			{
				pozycja = 0;
				ukryj();
			}
			wskaz(0, pozycja);
			zwykly();
			usunPotwora(&potwor);
			system("pause");
			break;
		}
		_getch();
		pozycja += 1;
		if (pozycja > wysokosc - 1) 
		{
			pozycja = 0;
			ukryj();
		}
		(*gracz) -= potwor.getAtak();
		czerwony();
		wskaz(0, pozycja);
		cout << "Potwor atakuje za " << (potwor.getAtak()) << ". Graczowi zostaje " << (gracz->getZycie()) << " zycia.";
		if (*gracz < 1)
		{
			pozycja += 2;
			if (pozycja > wysokosc - 1)
			{
				pozycja = 0;
				ukryj();
			}
			wskaz(0, pozycja);
			podswietlenie();
			cout << "Potwor wygrywa...";
			zwykly();
			cout << ' ';
			system("pause");
			rozgrywka->czyDalejGrac = false;
			break;
		}
	}
	system("cls");
	rozgrywka->wyswietlGUI();
}

int Plansza::obsluzNoweMenu(int _iloscOpcji, string _tytul, string * _opcje)
{
	return rozgrywka->obsluzNoweMenu(_iloscOpcji, _tytul, _opcje);
}

