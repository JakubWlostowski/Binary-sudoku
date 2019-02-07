#pragma once
#ifndef FUNKCJE_H
#define FUNKCJE_H
#include<stdio.h>
#include"conio2.h"
#include<cstdlib>
#include<time.h>
#define OK 1 // flaga prawda
#define NOK 0 // flga falsz (kolumny)
#define NOK1 -1 // flaga falsz (wiersze)
#define SZEROKOSC_LEGENDY 45 // szerokosc legendy
#define X 1 // polozenie X legendy
#define Y 1 // polozenie Y legendy
#define WYSOKOSC_PLANSZY 0 // wysokosc planszy
#define MAX 40 // max wypelnienie
#define MIN 20 // min wypelnienie
#define ESC 0x1b // kod klawisza esc

typedef struct pole
{
	char znak;
	int kolor;
	int mod;
	int kolor_tla;
	int pole_jednoznaczne;
	pole()
	{
		kolor = 1;
		mod = 1;
		kolor_tla = 0;
		pole_jednoznaczne = 1;
	}
}pole_t;

void ustawPlansza(pole_t **plansza, int n);

void usunPlansza(pole_t**plansza, int n);

int sprawdz_regule1(pole_t**plansza, int n, char znak, int x, int y);

int sprawdz_regule2(pole_t**plansza, int n, char znak, int x, int y);

int sprawdz_czy_ostatnie_miejsce_w_kolumnie(pole_t**plansza, int n, int x);

int sprawdz_czy_ostatnie_miejsce_w_wierszu(pole_t**plansza, int n, int y);

int sprawdz_tablice(pole_t*tablica1, pole_t*tablica2, int n);

int sprawdz_regule3(pole_t**plansza, int n, char znak, int x, int y);

void pisz(pole_t**plansza, int n, int x, int y, char znak);

void zeruj_tablice(pole_t**plansza, int n);

int sprawdzenie_regul(pole_t**plansza, int n, char znak, int x, int y);

void losuj(pole_t**plansza, int n);

void podpowiedz(pole_t**plansza, int n, int x, int y, char znak);

void sprawdzenie_ukonczenia(pole_t**plansza, int n);

void pola_jednoznaczne(pole_t**plansza, int n);

void wypelnij_pola_zerami(pole_t**plansza, int n);

void wypelnij_pola_jedynkami(pole_t**plansza, int n);

void rysuj(pole_t **plansza, int n, int x, int y);

void kolor(pole_t**plansza, int n);

void czysc_kolor(pole_t**plansza, int n);

void legenda(pole_t**plansza, int n, int x, int y, int zero, int zn);

void wpiszxy(int x, int y, char znak);

void ramka(int n);


#endif // !FUNKCJE_H
