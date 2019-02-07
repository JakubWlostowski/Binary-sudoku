#include<stdio.h>
#include"conio2.h"
#include<cstdlib>
#include<time.h>
#include"funkcje.h"
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


int main() {
	int zn = 0, x = SZEROKOSC_LEGENDY+1, y = WYSOKOSC_PLANSZY+2, attr = 7, back = 0, zero = 0;
	int n = 12;
	char ostatni_znak = ' ';
	
	pole_t** plansza;
	
	plansza = new pole_t*[n];
	for (int i = 0; i < n; i++) {
		plansza[i] = new pole_t[n];
	}
	ustawPlansza(plansza, 12);

	
#ifndef __cplusplus
	Conio2_Init();
#endif
	
	settitle("Jakub Wlostowski 171559");
	do {
		textbackground(BLACK);
		// czyœcimy ekran: wype³niamy spacjami z ustawionym kolrem t³a
		clrscr();
		// ustawiamy kolor tekstu na jasnoszary (7 == LIGHTGRAY)
		textcolor(7);
	
		legenda(plansza, n, x, y, zero, zn);
		ramka(n);

		// czekamy na naciœniêcie klawisza i odczytujemy jego kod,
		// wiêkszoœæ kodów klawiszy odpowiada ich znakom, np.
		// a to 'a', 2 to '2', + to '+', ale niektóre klawisze
		// specjalne, np. strza³ki s¹ zg³aszane jako dwa kolejne znaki,
		// z których pierwszy jest zerem, np. strza³ka w górê
		// to zero i 'H'
		zero = 0;
		rysuj(plansza, n, SZEROKOSC_LEGENDY, Y);		
		kolor(plansza, n);
		gotoxy(x, y);
		zn = getch();		
		// nie chcemy, aby klawisz 'H' dzia³a³ jako strza³ka w górê
		// wiêc sprawdzamy, czy pierwszym znakiem by³o zero
		
		if (zn == 0) {
			zero = 1;		// je¿eli tak, to czytamy
			zn = getch();		// kolejny znak wiedz¹c ju¿,
			if (zn == 0x48) y--;	// ¿e bêdzie to znak specjalny
			else if (zn == 0x50) y++;
			else if (zn == 0x4b) x--;
			else if (zn == 0x4d) x++;
		}
		//zero = 0;
		//if (zn == ' ') attr = (attr + 1) % 16;
		//else if (zn == 0x0d) back = (back + 1) % 16;

		else if (zn == '0' || zn == '1') {
			pisz(plansza, n, x, y, zn);

		}
		else if (zn == 'n' || zn=='N')
		{
			n = 12;
			plansza = new pole_t*[n];
			for (int i = 0; i < n; i++) {
				plansza[i] = new pole_t[n];
			}
			ustawPlansza(plansza, 12);
			czysc_kolor(plansza, n);
		}
		else if (zn == 'o' || zn=='O')
		{
			losuj(plansza, n);
			czysc_kolor(plansza, n);
		}
		else if (zn == 'k' || zn=='K')
			sprawdzenie_ukonczenia(plansza, n);
		else if (zn == 'j' || zn == 'J')
		{
			pola_jednoznaczne(plansza, n);
		}
		
		else if ((zn == 'w' || zn=='W') && (ostatni_znak=='j'|| ostatni_znak=='J'))
		{
			wypelnij_pola_jedynkami(plansza, n);
			wypelnij_pola_zerami(plansza, n);
		}
		else if (zn == 'r' || zn=='R')
		{
			gotoxy(X, Y + 15);
			cputs("Podaj rozmiar: \n");
			char cyfra1 = ' ';
			char cyfra2 = ' ';
			char rozmiar[3];
			cyfra1 = getch();
			putchar(cyfra1);
			cyfra2 = getch();
			putchar(cyfra2);
			sprintf(rozmiar, "%c%c", cyfra1, cyfra2);
			int pomoc = atoi(rozmiar);
			if (pomoc < 29)
			{
				n = pomoc;
				if (n % 2 == 1)
					n++;
				if (n == 4)
				{
					n = 4;
					plansza = new pole_t*[n];
					for (int i = 0; i < n; i++)
					{
						plansza[i] = new pole_t[n];
					}
					ustawPlansza(plansza, 4);
				}
				else if (n == 8)
				{
					n = 8;
					plansza = new pole_t*[n];
					for (int i = 0; i < n; i++)
					{
						plansza[i] = new pole_t[n];
					}
					ustawPlansza(plansza, 8);
				}
				else if (n == 12)
				{
					n = 12;
					plansza = new pole_t*[n];
					for (int i = 0; i < n; i++)
					{
						plansza[i] = new pole_t[n];
					}
					ustawPlansza(plansza, 12);
				}
				else if (n == 16)
				{
					n = 16;
					plansza = new pole_t*[n];
					for (int i = 0; i < n; i++)
					{
						plansza[i] = new pole_t[n];
					}
					ustawPlansza(plansza, 16);
				}
				else
				{
					plansza = new pole_t*[n];
					for (int i = 0; i < n; i++)
					{
						plansza[i] = new pole_t[n];
					}
					rysuj(plansza, n, x, y);
					losuj(plansza, n);
				}
			}
			
		}	
		ostatni_znak = zn;
	} while (zn != ESC);
	usunPlansza(plansza, n);
	
	return 0;
	}
