#include "GUI.h"

GUI::GUI(int _szerokosc, int _wysokosc, MozliweDoWyswietlenia* _menu, MozliweDoWyswietlenia* _plansza, Gracz* _gracz) // zmiana rozmiaru okna konsoli
	: MozliweDoWyswietlenia(0, 0, _szerokosc, _wysokosc), /*menu(0, 0, _szerokosc, 10, 0, " ", nullptr),*/ /*ktoraPlansza(0),*/ 
	gracz(_gracz), menu(_menu)
{
	ustawWielkoscKonsoli(_szerokosc, _wysokosc);
	setPlansza(_plansza);
}

GUI::GUI() // domyslny - brak zmiany rozmiaru okna konsoli
	: MozliweDoWyswietlenia(0, 0, 100, 100), /*menu(0, 0, 1, 1, 0, " ", nullptr),*/ gracz(nullptr), plansza(nullptr), menu(nullptr)
{
}

void GUI::ustawWielkoscKonsoli(int X, int Y)
{
	//**************************************************************
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE); // uchwyt do okna konsoli
	SMALL_RECT windowSize = { 0, 0, X - 1, Y - 1 }; // struktura przechowujaca koordynaty lewego gornego rogu i prawego dolnego, konsoli
	COORD dwSize = { X, Y }; // struktura przechowuje wielkosc bufora
	HWND uchwytKonsoli = GetConsoleWindow(); // zmienna przechowuje uchwyt do okna konsoli

	//**************************************************************

	//ustawia maxymalny rozmiar konsoli
	//MoveWindow(uchwytKonsoli, 0, 0, 5000, 5000, TRUE);

	//zmiana wielkosci okna konsoli
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	//zmiana wielkosci bufora konsoli
	SetConsoleScreenBufferSize(wHnd, dwSize);
}

void GUI::wyswietl()
{
	//plansze[ktoraPlansza]->wyswietl();
	plansza->wyswietl();
	aktualizujDukaty(gracz->getDukaty());
	aktualizujZycie(gracz->getZycie(), gracz->getZycieMax());
	// do zrobienia (iloœæ dukatow, zycia itp. oraz rozkazanie wyswietlenia przez menu lub plansze)
}

void GUI::aktualizujDukaty(int ileTeraz)
{
	string iloscDukatow("Dukaty: ");
	iloscDukatow.append(std::to_string(ileTeraz)).append("    ");;
	zolty();
	wskaz(plansza->getSzerokosc(), 1);
	if (iloscDukatow.length() > szerokosc - plansza->getSzerokosc()) cout << iloscDukatow.substr(0, szerokosc - plansza->getSzerokosc());
	else cout << iloscDukatow;
	wskaz(szerokosc - 1, wysokosc - 1);
	zwykly();
}

void GUI::aktualizujZycie(int ileTeraz, int aIleMax)
{
	string iloscZycia("Zycie: ");
	iloscZycia.append(std::to_string(ileTeraz)).append("/").append(std::to_string(aIleMax)).append("    ");
	czerwony();
	wskaz(plansza->getSzerokosc(), 0);
	if (iloscZycia.length() > szerokosc - plansza->getSzerokosc()) cout << iloscZycia.substr(0, szerokosc - plansza->getSzerokosc());
	else cout << iloscZycia;
	wskaz(szerokosc - 1, wysokosc - 1);
	zwykly();
}

void GUI::setPlansza(MozliweDoWyswietlenia* _plansza)
{
	plansza = _plansza;
	if ((menu != nullptr) && (plansza != nullptr))
	{
		menu->setX(0);
		menu->setY(plansza->getWysokosc());
		szerokosc = plansza->getSzerokosc() + 30;
		wysokosc = plansza->getWysokosc() + 10;
		ustawWielkoscKonsoli(szerokosc, wysokosc);
		menu->setSzerokosc(/*plansza->getSzerokosc()*/szerokosc);
		menu->setWysokosc(wysokosc - plansza->getWysokosc() - 1);
	}
}
