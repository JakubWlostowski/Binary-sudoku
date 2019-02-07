
#include"funkcje.h"


void ustawPlansza(pole_t **plansza, int n)
{
	FILE* plik;
	char nazwa_pliku[25];
	sprintf(nazwa_pliku, "plansza%dx%d.txt", n, n);
	plik = fopen(nazwa_pliku, "r");
	char bufor[272];
	fread(bufor, sizeof(char), 272, plik);
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			while (bufor[k] == '\n') {
				k++;
			}

			plansza[j][i].znak = bufor[k];
			if (plansza[j][i].znak == '0' || plansza[j][i].znak == '1')
			{
				plansza[j][i].mod = 0;
			}
			k++;
		}
	}
	fclose(plik);
}

void usunPlansza(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++) {
		delete[] plansza[i];
	}
	delete[] plansza;
}


int sprawdz_regule1(pole_t**plansza, int n, char znak, int x, int y)
{

	if (y >= 1 && y<n - 1 && plansza[x][y - 1].znak == znak && plansza[x][y + 1].znak == znak)
		return NOK;
	else if (y>=2 && plansza[x][y - 2].znak == znak && plansza[x][y - 1].znak == znak)
		return NOK;
	else if (y<n - 2 && plansza[x][y + 1].znak == znak && plansza[x][y + 2].znak == znak)
		return NOK;
	else if (x >= 1 && x<n - 1 && plansza[x - 1][y].znak == znak && plansza[x + 1][y].znak == znak)
		return NOK;
	else if (x >= 2 && plansza[x - 2][y].znak == znak && plansza[x - 1][y].znak == znak)
		return NOK;
	else if (x<n - 2 && plansza[x + 1][y].znak == znak && plansza[x + 2][y].znak == znak)
		return NOK;
	return OK;
}

int sprawdz_regule2(pole_t**plansza, int n, char znak, int x, int y)
{
	int licznik = 0;
	for (int i = 0; i < n; i++)
	{
		if (plansza[x][i].znak == znak) licznik++;
		if (licznik >= n / 2) return NOK;
	}
	licznik = 0;
	for (int i = 0; i < n; i++)
	{
		if (plansza[i][y].znak == znak) licznik++;
		if (licznik >= n / 2) return NOK1;
	}

	return OK;

}

int sprawdz_czy_ostatnie_miejsce_w_kolumnie(pole_t**plansza, int n, int x)
{
	int licznik = 0;
	for (int i = 0; i < n; i++)
	{

		if (plansza[x][i].znak == '.') licznik++;
		if (licznik > 1) return NOK;
	}
	if (licznik == 0) return NOK;

	return OK;

}

int sprawdz_czy_ostatnie_miejsce_w_wierszu(pole_t**plansza, int n, int y)
{
	int licznik = 0;
	for (int i = 0; i < n; i++)
	{

		if (plansza[i][y].znak == '.') licznik++;
		if (licznik > 1) return NOK;
	}
	if (licznik == 0) return NOK;

	return OK;

}

int sprawdz_tablice(pole_t*tablica1, pole_t*tablica2, int n)//porownuje 2 tablice
{
	for (int i = 0; i < n; i++)
	{
		if (tablica1[i].znak != tablica2[i].znak)
			return NOK;

	}
	return OK;
}

int sprawdz_regule3(pole_t**plansza, int n, char znak, int x, int y)
{
	pole_t *kolumna;
	pole_t *wiersz;



	if (sprawdz_czy_ostatnie_miejsce_w_kolumnie(plansza, n, x) == OK)
	{
		kolumna = new pole_t[n];
		for (int i = 0; i < n; i++)
		{
			kolumna[i].znak = plansza[x][i].znak; // zapisuje kolumne ktora chce porownac ze wszystkimi innymi kolumnami
		}
		kolumna[y].znak = znak; //powstala kolumna przez przypisanie wartosci

		pole_t*kolumna2; //kolumna ktora trzeba sprawdzic
		for (int i = 0; i<n; i++)
		{
			if (i == x) continue; //zeby nie sprawdzac tej samej kolumny
			kolumna2 = new pole_t[n];
			for (int j = 0; j < n; j++)
			{
				kolumna2[j].znak = plansza[i][j].znak;
			}
			if (sprawdz_tablice(kolumna, kolumna2, n) == OK)
			{
				delete[] kolumna;
				delete[] kolumna2;
				return NOK;
			}
			delete[] kolumna2;
		}
		delete[] kolumna;
	}


	if (sprawdz_czy_ostatnie_miejsce_w_wierszu(plansza, n, y) == OK)
	{
		wiersz = new pole_t[n];
		for (int i = 0; i < n; i++)
		{
			wiersz[i].znak = plansza[i][y].znak;
		}
		wiersz[x].znak = znak; //powstaly wiersz przez przypisanie wartosci

		pole_t*wiersz2; //wiersz ktory trzeba sprawdzic
		for (int i = 0; i<n; i++)
		{
			if (i == y) continue;
			wiersz2 = new pole_t[n];
			for (int j = 0; j < n; j++)
			{
				wiersz2[j].znak = plansza[j][i].znak;
			}
			if (sprawdz_tablice(wiersz, wiersz2, n) == OK)
			{
				delete[] wiersz;
				delete[] wiersz2;
				return NOK1;
			}
			delete[] wiersz2;
		}
		delete[] wiersz;
	}

	return OK;

}

int sprawdzenie_regul(pole_t**plansza, int n, char znak, int x, int y)
{
	if (sprawdz_regule1(plansza, n, znak, x, y) == OK && sprawdz_regule2(plansza, n, znak, x, y) == OK && sprawdz_regule3(plansza, n, znak, x, y) == OK)
		return OK;
	else return NOK;

}

void pisz(pole_t**plansza, int n, int x, int y, char znak)
{
	x = x - SZEROKOSC_LEGENDY -1;
	y = y - 2 - WYSOKOSC_PLANSZY;
	if (x >= n || y >= n || x<0 || y<0)
	{
		return;
	}
	else
	{
		if ((plansza[x][y].znak == '.' || plansza[x][y].mod == 1) && sprawdzenie_regul(plansza,n,znak,x,y)==OK)
		{
			plansza[x][y].znak = znak;
			plansza[x][y].kolor_tla = 9;
			plansza[x][y].kolor = 0;
		}
	}
}

void zeruj_tablice(pole_t**plansza, int n)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plansza[i][j].znak = '.';
			plansza[i][j].mod = 1;
		}
	}
}

void losuj(pole_t**plansza, int n)
{
	srand(time(NULL));
	zeruj_tablice(plansza, n);
	int random_ilosc = rand() % n*n;
	int random_max = rand() % (MAX - MIN)+MIN;
	int procent_wypelnienia = 0.01 * random_max*(n*n);
	int licznik = 0;
	for (int i = 0; i<random_ilosc , licznik<procent_wypelnienia; i++)
	{

		licznik++; // zlicza ile razy wykonala sie petla zeby program sie nie zawiesil
		int random_znak = rand() % 2;
		int randomx = 0;
		int randomy = 0;
		do
		{
			randomx = rand() % n;
			randomy = rand() % n;
		} while (plansza[randomx][randomy].znak != '.');

		int x = randomx;
		int y = randomy;
		char znak;
		if (random_znak == 0)
		{
			znak = '0';
		}
		else
			znak = '1';

		if (plansza[x][y].znak == '.'&& plansza[x][y].mod == 1 && sprawdzenie_regul(plansza,n,znak,x,y)==OK)
		{
			plansza[x][y].znak = znak;
			if (plansza[x][y].znak == '0' || plansza[x][y].znak == '1')
				plansza[x][y].mod = 0;
			else plansza[x][y].mod = 1;
		}
		else
			i--;
	}

}

void podpowiedz(pole_t**plansza, int n, int x, int y, char znak)
{
	x = x - SZEROKOSC_LEGENDY - 1;
	y = y - 2 - WYSOKOSC_PLANSZY;

	if (x >= n || y >= n || x<0 || y<0)
	{
		return;
	}

	if (plansza[x][y].mod == 0)
		cputs("To pole jest niemodyfikowalne\n");
	else {

		if (sprawdz_regule1(plansza, n, '0', x, y) == OK)
			cputs("");
		else cputs("Wpisanie zera spowoduje \n trzy takie same znaki obok siebie\n \n");

		if (sprawdz_regule1(plansza, n, '1', x, y) == OK)
			cputs("");
		else cputs("Wpisanie jedynki spowoduje \n trzy takie same znaki obok siebie\n \n");

		if (sprawdz_regule2(plansza, n, '0', x, y) == OK)
			cputs("");
		else if(sprawdz_regule2(plansza, n, '0', x, y) == NOK)
			cputs("Wpisanie zera spowoduje \n zbyt duza ilosc zer w kolumnie \n \n");

		else cputs("Wpisanie zera spowoduje \n zbyt duza ilosc zer w wierszu \n \n");

		if (sprawdz_regule2(plansza, n, '1', x, y) == OK)
			cputs("");
		else if(sprawdz_regule2(plansza, n, '1', x, y) == NOK)
			cputs("Wpisanie jedynki spowoduje \n zbyt duza ilosc jedynek w kolumnie \n \n");

		else cputs("Wpisanie jedynki spowoduje \n zbyt duza ilosc jedynek w wierszu \n \n");

		if (sprawdz_regule3(plansza, n, '1', x, y) == OK)
			cputs("");
		else if(sprawdz_regule3(plansza, n, '1', x, y) == NOK)
			cputs("Wpisanie jedynki spowoduje powielenie kolumny \n");

		else cputs("Wpisanie jedynki spowoduje powielenie wiersza \n");

		if (sprawdz_regule3(plansza, n, '0', x, y) == OK)
			cputs("");
		else if(sprawdz_regule3(plansza, n, '0', x, y) == NOK)
			cputs("Wpisanie zera spowoduje powielenie kolumny \n");
		else 
			cputs("Wpisanie zera spowoduje powielenie wiersza \n");

		if (sprawdzenie_regul(plansza,n,'0',x,y)==OK)
			cputs("Mozna wpisac zero\n");

		if (sprawdzenie_regul(plansza, n, '1', x, y) == OK)
			cputs("Mozna wpisac jeden\n");
	}

}



void sprawdzenie_ukonczenia(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (plansza[i][j].znak == '.' && sprawdzenie_regul(plansza, n, '0', i, j) == NOK && sprawdzenie_regul(plansza, n, '1', i, j) == NOK)
			{
				plansza[i][j].kolor_tla = 4;
			}

		}

	}
}

void pola_jednoznaczne(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((plansza[i][j].znak == '.' && sprawdzenie_regul(plansza, n, '0', i, j) == OK && sprawdzenie_regul(plansza, n, '1', i, j) == NOK) || (plansza[i][j].znak == '.' && sprawdzenie_regul(plansza, n, '0', i, j) == NOK && sprawdzenie_regul(plansza, n, '1', i, j) == OK))
			{
				plansza[i][j].kolor_tla = 6;
				plansza[i][j].pole_jednoznaczne = 0;
			}
		}
	}
}

void wypelnij_pola_zerami(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (plansza[i][j].znak == '.' && plansza[i][j].pole_jednoznaczne == 0 && sprawdzenie_regul(plansza, n, '0', i, j) == OK && sprawdzenie_regul(plansza, n, '1', i, j) == NOK)
			{
				plansza[i][j].znak = '0';
				plansza[i][j].kolor_tla = 0;
			}

		}
	}
}

void wypelnij_pola_jedynkami(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (plansza[i][j].znak == '.' && plansza[i][j].pole_jednoznaczne == 0 && sprawdzenie_regul(plansza, n, '1', i, j) == OK && sprawdzenie_regul(plansza, n, '0', i, j) == NOK)
			{
				plansza[i][j].znak = '1';
				plansza[i][j].kolor_tla = 0;
			}
		}
	}
}

void rysuj(pole_t **plansza, int n, int x, int y)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gotoxy(x + i + 1, y + j + 1 + WYSOKOSC_PLANSZY);
			textbackground(plansza[i][j].kolor_tla);
			putch(plansza[i][j].znak);
		}
	}
}

void kolor(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (plansza[i][j].kolor == 1)
				plansza[i][j].kolor_tla = 0;
		}
	}
}

void czysc_kolor(pole_t**plansza, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plansza[i][j].kolor_tla = 0;
		}
	}
}

void legenda(pole_t**plansza, int n, int x, int y, int zero, int zn)
{

	char txt[32];
	gotoxy(X, Y + 1);
	cputs("Jakub Wlostowski 171559");
	gotoxy(X, Y + 2);
	cputs("Podpunkty: a,b,c,d,e,f,g,h,i,j,m");
	gotoxy(X, Y + 3);
	cputs("esc = wyjscie");
	gotoxy(X, Y + 4);
	cputs("strzalki = poruszanie");
	gotoxy(X, Y + 5);
	cputs("01 = wpisanie cyfry na plansze");
	gotoxy(X, Y + 6);
	cputs("n = nowa gra");
	gotoxy(X, Y + 7);
	cputs("o = losowo wypelniona plansza");
	gotoxy(X, Y + 8);
	cputs("p = podpowiedz");
	gotoxy(X, Y + 9);
	cputs("r = zmiana rozmiaru planszy");
	gotoxy(X, Y + 10);
	cputs("k = sprawdzenie mozliwosci ukonczenia gry");
	gotoxy(X, Y + 11);
	cputs("j = podswietlenie jednoznacznych pol");
	gotoxy(X, Y + 12);
	cputs("w = wypelnienie jednoznacznych pol");
	gotoxy(X, Y + 13);
	sprintf(txt, "x = %d y= %d", x - SZEROKOSC_LEGENDY, y - WYSOKOSC_PLANSZY-1);
	cputs(txt);
	// wypisujemy na ekranie kod ostatnio naciœniêtego klawisza
	if (zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
	else sprintf(txt, "kod klawisza: 0x%02x", zn);
	gotoxy(X, Y + 14);
	cputs(txt);
	gotoxy(X, Y + 18);
	if (zn == 'p')
		podpowiedz(plansza, n, x, y, zn);


}

void wpiszxy(int x, int y, char znak)
{
	gotoxy(x, y);
	putch(znak);
}


void ramka(int n)
{
	for (int i = 0; i < n; i++)
	{
		wpiszxy(SZEROKOSC_LEGENDY + i + 1, 1 + WYSOKOSC_PLANSZY, '-');
		wpiszxy(SZEROKOSC_LEGENDY, i + 2 + WYSOKOSC_PLANSZY, '|');
		wpiszxy(SZEROKOSC_LEGENDY + n + 1, i + 2 + WYSOKOSC_PLANSZY, '|');
		wpiszxy(SZEROKOSC_LEGENDY + i + 1, n + 2 + WYSOKOSC_PLANSZY, '-');

	}
}
