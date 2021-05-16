#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <locale.h>
#include "fonksiyonlar.h"

int main (void){

    setlocale(LC_ALL, "Turkish");
    system("COLOR 0A");

	ogretmenOlustur();
	gotoxy(13,8);printf("MARMARA OGRENCI SISTEMINE HOSGELDINIZ!");
	gotoxy(13,13);printf("HERHANGI BIR TUSA BASINIZ");
	getch();
    menu();
	return 0;
}
