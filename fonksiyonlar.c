#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "fonksiyonlar.h"
void ogrenciEkle(ogrenci o1){
	FILE *fp;
	int k;
	for(k=0;k<1000;k++){
		char adres[40]=".\\database\\";
		char dosyaAdi[4];
		itoa(k,dosyaAdi,10);
		strcat(adres,dosyaAdi);
		strcat(adres,".txt");
		fp=fopen(adres,"r");
		if(fp==NULL){
			fp=fopen(adres,"w+");
			fprintf(fp,"%s\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%f", o1.ogrNo, o1.ogrAd, o1.ogrSoyad, o1.ogrMail, o1.ogrTelNo, o1.notlar.vizeNotu, o1.notlar.finalNotu, o1.notlar.odevNotu, o1.notlar.ortalamaNot);
			fclose(fp);
			break;
		}
		else{
			fclose(fp);
			continue;
		}

	}
}
void ogrenciSil(char *no){
	//char *no yerine ogrenci no verilecek
	FILE *fp;
	int k;
	for(k=0;k<1000;k++){
		char adres[40]=".\\database\\";
		char dosyaAdi[4];
		char kayitno[10];
		itoa(k,dosyaAdi,10);
		strcat(adres,dosyaAdi);
		strcat(adres,".txt");
		fp=fopen(adres,"r");
		if(fp!=NULL){
			fscanf(fp," %s", kayitno);
			if(!strcmp(kayitno,no)){
				fclose(fp);
				char dosyaAdres[40]=".\\database\\";
				char dosyaNo[4];
				itoa(k,dosyaNo,10);
				strcat(dosyaAdres,dosyaNo);
				strcat(dosyaAdres,".txt");
				remove(dosyaAdres);
				gotoxy(10,18);printf("       ***OGRENCI KAYDI BASARIYLA SILINDI***       ");
				return;
			}
		}
		fclose(fp);
	}
	gotoxy(10,18);printf("DOSYA SILINEMEDI! YANLIS OGRENCI NO GIRMIS OLABILIRSINIZ\n");
}
ogrenci ogrenciBul(char *no){
// bulunmak istenen ogrencinin nosu ile cag�r�l�yor bu fonksiyon
	FILE *fp;
	ogrenci o1;
	int k;
	for(k=0;k<1000;k++){
		char adres[40]=".\\database\\";
		char dosyaAdi[4];
		char kayitno[10];
		itoa(k,dosyaAdi,10);
		strcat(adres,dosyaAdi);
		strcat(adres,".txt");
		fp=fopen(adres,"r");
		if(fp!=NULL){
			fscanf(fp,"%s", kayitno);
			if(!strcmp(kayitno,no)){
				strcpy(o1.ogrNo, kayitno);
				fscanf(fp, " %s %s %s %s %d %d %d %f", o1.ogrAd, o1.ogrSoyad, o1.ogrMail, o1.ogrTelNo, &o1.notlar.vizeNotu, &o1.notlar.finalNotu, &o1.notlar.odevNotu, &o1.notlar.ortalamaNot);
				ogrGoster(o1);
				fclose(fp);
				return o1;
			}
		}
	fclose(fp);
	}
	gotoxy(10,22); printf("OGRENCI KAYDI BULUNAMADI!");
	return o1;
}
void ogretmenOlustur(void){
	//eger ogretmen varsa yenisini olusturmaz eger yoksa varsay�lan olarak asagidaki degerleri atar
	ogretmen ort;
	strcpy(ort.sifre, "marmara");
	ort.odevKatsayi=25;
	ort.vizeKatsayi=25;
	ort.finalKatsayi=50;
	FILE *fp;
	fp=fopen(".\\database\\0gretmen.txt","r");
	if(fp==NULL){
		fp=fopen(".\\database\\0gretmen.txt","w+");
		fprintf(fp,"%s\n%d\n%d\n%d", ort.sifre, ort.odevKatsayi, ort.vizeKatsayi, ort.finalKatsayi);
	}
	fclose(fp);
}
ogretmen ogretmenOku(void){
	//ogretmen sifresi s�nav katsayilar� gibi bilgileri okuyup ogretmen turunden geri g�nderir
	FILE *fp;
	ogretmen ort;
	fp=fopen(".\\database\\0gretmen.txt","r");
	if(fp==NULL){
		printf("hata! ogretmen bilgileri okunamiyor dosya silinmis olabilir\n");
	}
	else{
		fscanf(fp," %s %d %d %d", ort.sifre, &ort.odevKatsayi, &ort.vizeKatsayi, &ort.finalKatsayi);
	}
	fclose(fp);
	return ort;
}
float ogrenciOrtalama(int odev, int vize, int final){
	//tek bir ogrencinin ortalamas�n� hesaplay�p geri d�nd�r�r
	ogretmen o1;
	o1=ogretmenOku();
	float ortalama=0;
	ortalama=((float)(odev*o1.odevKatsayi+vize*o1.vizeKatsayi+final*o1.finalKatsayi)/(float)100);
	return ortalama;
}
int sifreKontrol(char *input){
	//eger sifre dogruysa 0 geri d�ner yanl�ssa 1 geri d�ner
	ogretmen o1;
	o1=ogretmenOku();
	if(!strcmp(input, o1.sifre)){
		//sifreler ayni 0 geri d�n�yorum
		return 0;
	}
	return 1;
}
void ogretmenGuncelle(char *yeniSifre, int yeniOdevKatsayi, int yeniVizeKatsayi, int yeniFinalKatsayi){
	//ogretmen sifresi veya s�nav katsayilari guncellenecekse bu fonksiyonla yap�l�r ogretmen olusutr sadece program bas�nda kullan�labilir!
	ogretmen o1;
	FILE *fp;
	strcpy(o1.sifre, yeniSifre);
	o1.odevKatsayi=yeniOdevKatsayi;
	o1.vizeKatsayi=yeniVizeKatsayi;
	o1.finalKatsayi=yeniFinalKatsayi;
	remove(".\\database\\0gretmen.txt");
	fp=fopen(".\\database\\0gretmen.txt","w+");
	fprintf(fp,"%s\n%d\n%d\n%d", o1.sifre, o1.odevKatsayi, o1.vizeKatsayi, o1.finalKatsayi);
	fclose(fp);
}

// OKUMA FONKSİYONLARI - YAKUB

void ogrNoAl(char *okulNo){

	char ogrNo [100];
	int girisDeneme = 1;

	gotoxy(10,9);printf("Lutfen ogrenci numarasini girinizi: ");
	do{

	if(girisDeneme==1)
	scanf(" %s", ogrNo);
	else{
		gotoxy(10,9);
		printf("\x1b[2K");//clear line
		printf("Lutfen 5 ile 14 karakter arasinda gecerli bir ogrenci numarasi giriniz: ");
  		scanf(" %s", ogrNo);
        }
	girisDeneme ++;
    }while(!(strlen(ogrNo)>5  && strlen(ogrNo)<=14));

	strcpy(okulNo ,ogrNo);
}

void ogrAdAl(char *ogrAd){

	char gecici[50];
	int girisDeneme = 1;
	gotoxy(10,11);printf("Lutfen ogrenci adini giriniz: ");

	do{

	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		gotoxy(10,11);
		printf("\x1b[2K");//clear line
		printf("Lutfen maksimum karakter sayisi 14 olacak sekilde gecerli bir ogrenci adi giriniz: ");
  		scanf(" %s", gecici);
        }
	girisDeneme ++;
    }while(!(strlen(gecici)<=14));

	strcpy(ogrAd ,gecici);
}

void ogrSoyadAl(char *ogrSoyad){

	char gecici[50];
	int girisDeneme = 1;

	gotoxy(10,13);printf("Lutfen ogrencinin soyadini giriniz: ");

	do{

	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		gotoxy(10,13);
		printf("\x1b[2K");//clear line
		printf("Lutfen maksimum karakter sayisi 19 olacak sekilde gecerli bir soyad giriniz: ");
  		scanf(" %s", gecici);
        }
	girisDeneme ++;
}while(!(strlen(gecici)<=14));

	strcpy(ogrSoyad ,gecici);
}

void ogrMailAl(char *ogrMail){
    char gecici[50];
	int girisDeneme = 1;
	gotoxy(10,15);printf("Lutfen ogrencinin mail adresini giriniz: ");

	do{

	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		if(strlen(gecici)<10){
			gotoxy(10,15);
			printf("\x1b[2K");//clear line
			printf("Lutfen 10 karakterden fazla olacak sekilde gecerli bir mail adresi giriniz: ");
            scanf(" %s", gecici);
		}
		else if (strlen(gecici)>29) {
			gotoxy(10,15);
			printf("\x1b[2K");//clear line
			printf("Lutfen 30 karakterden daha az olacak sekilde gecerli bir mail adresi giriniz: ");
            scanf(" %s", gecici);
		}

        }
	girisDeneme ++;
}while(!(strlen(gecici)<=29 && strlen(gecici)>10) );

	strcpy(ogrMail ,gecici);
}

void ogrTelNoAl(char *telNo){

    char gecici[50];
	int girisDeneme = 1;
	gotoxy(10,17);printf("Lutfen ogrencinin telefon numarasini giriniz: ");

	do{

	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		if(strlen(gecici)<10){
			gotoxy(10,17);
			printf("\x1b[2K");//clear line
			printf("Lutfen 10 karakterden fazla olacak sekilde gecerli bir telefon numarasi giriniz: ");
  		scanf(" %s", gecici);
		}
		else if (strlen(gecici)>=14){
			gotoxy(10,17);
			printf("\x1b[2K");//clear line
			printf("Lutfen 15 karakterden daha az olacak sekilde gecerli bir telefon numarasi giriniz: ");
            scanf(" %s", gecici);
		}
        }
	girisDeneme ++;
}while(!(strlen(gecici)<=14 && strlen(gecici)>=10) );
	strcpy(telNo ,gecici);
}

int ogrVizeNotuAl(){

	int vize;
	int girisDeneme = 1;

	gotoxy(10,19);printf("Lutfen vize notunu giriniz: ");

	do{
		if(girisDeneme==1)
		scanf(" %d",&vize);
		else{
		gotoxy(10,19);
		printf("\x1b[2K");//clear line
		printf("lutfen 0 ile 100 arasinda olacak gecerli bir not giriniz: ");
		scanf(" %d",&vize);
		}
		girisDeneme ++;
	}
	while(!(vize<=100 && vize>=0) );

	return vize;
}

int ogrFinalNotuAl(){

	int final;
	int girisDeneme = 1;

	gotoxy(10,20);printf("Lutfen final notunu giriniz: ");

	do{
		if(girisDeneme==1)
		scanf(" %d",&final);
		else{
		gotoxy(10,20);
		printf("\x1b[2K");//clear line
		printf("lutfen 0 ile 100 arasinda olacak gecerli bir not giriniz: ");
		scanf(" %d",&final);
		}
		girisDeneme ++;
	}
	while(!(final<=100 && final>=0) );

	return final;

}

int ogrOdevNotuAl(){
    int odev;
	int girisDeneme = 1;

	gotoxy(10,21);printf("Lutfen odev notunu giriniz: ");

	do{
		if(girisDeneme==1)
		scanf(" %d",&odev);
		else {
		gotoxy(10,21);
		printf("\x1b[2K");//clear line
		printf("lutfen 0 ile 100 arasinda olacak gecerli bir not giriniz: ");
		scanf(" %d",&odev);
		}
		girisDeneme ++;
	}
	while(!(odev<=100 && odev>=0) );

	return odev;
}

void ogretmenKatsayiAl(int *odev, int *vize, int *final){
	int odevK, vizeK, finalK;
	int girisDeneme = 1;
	gotoxy(10,14);printf("Lutfen odev, vize ve final katsayilarini sirasi ile girerek enter tusuna basiniz.\n");

	do{
	if (girisDeneme ==1){
		gotoxy(10,15);printf("Odev katsayisi:");
		scanf(" %d", &odevK);
		gotoxy(10,16);printf("Vize katsayisi:");
		scanf(" %d", &vizeK);
		gotoxy(10,17);printf("Final katsayisi:");
		scanf(" %d", &finalK);
		girisDeneme++;
	}

	else
	 {
	 	gotoxy(10,14);
	 	printf("Katsayilar toplaminin 100 olmasi gerekmektedir, lutfen katsayilir tekrar sirayla giriniz.\n");
	 	gotoxy(10,15);
	 	printf("Odev katsayisi:");
		scanf(" %d", &odevK);
		gotoxy(10,16);
		printf("Vize katsayisi:");
		scanf(" %d", &vizeK);
		gotoxy(10,17);
		printf("Final katsayisi:");
		scanf(" %d", &finalK);
	 }

	}while (!(odevK+vizeK+finalK==100));



	*odev=odevK;
	*vize=vizeK;
	*final=finalK;

}

void ogretmenSifreGuncelle(char *yeniSifre){
    char gecici[50];
	int girisDeneme = 1;
	gotoxy(10,12);printf("Lutfen belirlemek istediginiz yeni sifrenizi girin: ");

	do{

	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		if(strlen(gecici)<8){
			gotoxy(10,12);
			printf("\x1b[2K");//clear line
			printf("Lutfen en az 8 karakter olacak sekilde yeni sifrenizi giriniz: ");
  		scanf(" %s", gecici);
		}
		else if (strlen(gecici)>29){
			gotoxy(10,12);
			printf("\x1b[2K");//clear line
			printf("Lutfen 29 karakterden daha az olacak sekilde yeni sifrenizi giriniz: ");
            scanf(" %s", gecici);
		}

        }
	girisDeneme ++;
}while(!(strlen(gecici)<=29 && strlen(gecici)>=8) );

	strcpy(yeniSifre ,gecici);
}

//~HUSSAIN
void head(int durum){
    system("cls");
    switch(durum){
    case 1:
        gotoxy(17,1); printf("--------------------------");
        gotoxy(20,2); printf("  OGRENCI EKLEME ");
        gotoxy(17,3); printf("--------------------------");
        gotoxy(10,6); printf("ASAGIDAKI BILGILERI DOLDURUNUZ");
        gotoxy(10,7); printf("------------------------------------------");
        break;

    case 2:
        gotoxy(17,1); printf("--------------------------");
        gotoxy(20,2); printf("  OGRENCI ARAMA ");
        gotoxy(17,3); printf("--------------------------");
        break;

    case 3:
        gotoxy(17,1); printf("--------------------------");
        gotoxy(20,2); printf("  OGRENCI SILME ");
        gotoxy(17,3); printf("--------------------------");
        break;

    case 4:
        gotoxy(17,1); printf("--------------------------");
        gotoxy(20,2); printf("  BILGILERI GUNCELLEME ");
        gotoxy(17,3); printf("--------------------------");
        gotoxy(10,6); printf("ASAGIDA YENI BILGILERINIZI GIRINIZ");
        gotoxy(10,7); printf("------------------------------------------");
        break;

    default:
        break;
    }
}

void ogrGoster(ogrenci o1){
    gotoxy(10,7); printf("----------------------------------------------------");
    gotoxy(10,8); printf("Ogrenci No:        %s", o1.ogrNo);
    gotoxy(10,10);printf("Ogrenci Adi:       %s", o1.ogrAd);
    gotoxy(10,12);printf("Ogrenci Soyadi:    %s ",o1.ogrSoyad);
    gotoxy(10,14);printf("Ogrenci Mail:      %s",o1.ogrMail);
    gotoxy(10,16);printf("Ogrenci Tel:       %s",o1.ogrTelNo);
    gotoxy(10,18);printf("Ogrenci Notu:      %d %d %d", o1.notlar.vizeNotu,o1.notlar.finalNotu, o1.notlar.odevNotu);
    gotoxy(10,20);printf("Ogrenci Ortalama:  %f",o1.notlar.ortalamaNot);
}

void tumuGoster(void){
	FILE *fp;
	ogrenci o1;
	int k,j=9;
	for(k=0;k<1000;k++){
		char adres[40]=".\\database\\", dosyaAdi[4], kayitno[10];
		itoa(k,dosyaAdi,10);
		strcat(adres,dosyaAdi); strcat(adres,".txt");
		fp=fopen(adres,"r");
		if(fp!=NULL){
			fscanf(fp,"%s", kayitno);
            strcpy(o1.ogrNo, kayitno);
            fscanf(fp, " %s %s %s %s %d %d %d %f", o1.ogrAd, o1.ogrSoyad, o1.ogrMail, o1.ogrTelNo, &o1.notlar.vizeNotu, &o1.notlar.finalNotu, &o1.notlar.odevNotu, &o1.notlar.ortalamaNot);
            gotoxy(10,j);
            printf("%-12s %-11s %-14s %-13s %-28s  %.2f",o1.ogrNo, o1.ogrAd, o1.ogrSoyad, o1.ogrTelNo, o1.ogrMail, o1.notlar.ortalamaNot);
            j++;
            fclose(fp);
		}
	fclose(fp);
	}
}

void cikis(void){
    system("cls");
    gotoxy(0,7);
    printf(".....:::MARMARA SISTEMINI TERCIH ETTIGINIZ ICIN TESEKKURLER:::.....\n");
    printf("...................................................................\n\n\n");
    exit(1);
}

void baskaIslem(void){
    gotoxy(10,24);printf("----------------------------------------------------");
    gotoxy(10,25);printf("BASKA ISLEM YAPMAK ICIN HERHANGI BIR TUSA BASINIZ...");
    gotoxy(10,26);printf("----------------------------------------------------");
    getch();
}

int ogrenciCheck(char *no){
	FILE *fp;
	ogrenci o1;
	int k;
	for(k=0;k<1000;k++){
		char adres[40]=".\\database\\", dosyaAdi[4], kayitno[10];
		itoa(k,dosyaAdi,10);
		strcat(adres,dosyaAdi); strcat(adres,".txt");
		fp=fopen(adres,"r");
		if(fp!=NULL){
			fscanf(fp,"%s", kayitno);
			if(!strcmp(kayitno,no)){
				fclose(fp);
				return 1;
			}
		}else{
            return 0;
		}
	fclose(fp);
	}
}

void ogretmenGirisi(void){
    int sec, ogretmenSecim=0;
    char ogretmenSifre[20], temp[15];

    system("cls");
    gotoxy(13,5); printf("Username: Admin\n");
    gotoxy(13,7); printf("Sifreniz: ");
    scanf("%s", ogretmenSifre);

    if(sifreKontrol(ogretmenSifre)==0){
    do
    {
        system("cls");
        gotoxy(17,1); printf("--------------------------");
        gotoxy(20,2); printf("  OGRETMEN ARAYUZU ");
        gotoxy(17,3); printf("--------------------------");

            gotoxy(10,6); printf("YAPMAK ISTEDIGINIZ ISLEMI ASAGIDAN SECINIZ");
            gotoxy(10,7); printf("------------------------------------------");
            gotoxy(10,9); printf("1) Ogrenci Ekle\n");
            gotoxy(10,11);printf("2) Ogrenci Bul\n");
            gotoxy(10,13);printf("3) Ogrenci Sil\n");
            gotoxy(10,15);printf("4) Bilgilerimi Guncelle\n");
            gotoxy(10,17);printf("5) Tum Ogrencileri Goruntule");
            gotoxy(10,19);printf("6) Ana Menu");
            gotoxy(10,21);printf("0) Cikis Yap");
            gotoxy(10,25);
            printf("SECIMINIZI YAPINIZ: ");
            scanf("%d", &ogretmenSecim);

        ogrenci ogr; //struct
        switch(ogretmenSecim)
        {
            case 1:
                {
                head(1);
                    ogrNoAl(ogr.ogrNo);
                    ogrAdAl(ogr.ogrAd);
                    ogrSoyadAl(ogr.ogrSoyad);
                    ogrMailAl(ogr.ogrMail);
                    ogrTelNoAl(ogr.ogrTelNo);
                    ogr.notlar.vizeNotu=ogrVizeNotuAl();
                    ogr.notlar.finalNotu=ogrFinalNotuAl();
                    ogr.notlar.odevNotu=ogrOdevNotuAl();
                    ogr.notlar.ortalamaNot=ogrenciOrtalama(ogr.notlar.odevNotu, ogr.notlar.vizeNotu, ogr.notlar.finalNotu);
                ogrenciEkle(ogr);
                }
                break;

            case 2:
                head(2);
                gotoxy(10,6);printf("Bulmak istediginiz ogrencinin numarasini giriniz: ");
                scanf("%s",ogr.ogrNo);
                ogrenciBul(ogr.ogrNo);
                baskaIslem();
                break;

            case 3:
                head(3);
                gotoxy(10,9);printf("Silmek istediginiz ogrenci numarasini giriniz: ");
                scanf("%s", temp);
                gotoxy(10,17);printf("----------------------------------------------------");
                ogrenciSil(temp);
                gotoxy(10,19);printf("----------------------------------------------------");
                baskaIslem();
                break;

            case 4:
                {
                ogretmen ogret; //struct
                head(4);
                ogretmenSifreGuncelle(ogret.sifre);
                ogretmenKatsayiAl(&ogret.odevKatsayi, &ogret.vizeKatsayi, &ogret.finalKatsayi);
                ogretmenGuncelle(ogret.sifre, ogret.odevKatsayi, ogret.vizeKatsayi, ogret.finalKatsayi);
                baskaIslem();
                }
                break;

            case 5:
                system("cls");
                gotoxy(10,3);
                printf("<--:TUM OGRENCILERI GORUNTULE:-->");
                gotoxy(10,6);
                printf("Ogrenci No     Adi       Soyadi         Telefon No          Mail                   Ortalama");
                gotoxy(10,7);
                printf("---------------------------------------------------------------------------------------------------");
                tumuGoster();
                baskaIslem();

                break;

            case 6:
                menu();
                break;

            case 0:
                cikis();
                break;

            default:
            printf("HATALI GIRIS YAPTINIZ!");
        }
    	}while(ogretmenSecim!=0);
    }
    else{
        gotoxy(12,9); printf("-----------------------");
        gotoxy(13,10);printf("YANLIS SIFRE GIRDINIZ");
        gotoxy(12,11);printf("-----------------------");
        gotoxy(13,13);printf("1 : SIFREYI TEKRAR GIR");
        gotoxy(13,14);printf("2 : ANA MENU");
        gotoxy(13,17);
        printf("SECIM YAPINIZ: ");
        scanf("%d", &sec);

        if(sec==2)
            menu();
        else
            ogretmenGirisi();
    }
}

void ogrenciGirisi(void){
    int ogrenciSecim=0;
    char ogrenciUser[15];

    system("cls");
    gotoxy(17,1); printf("--------------------------");
    gotoxy(20,2); printf("  OGRENCI ARAYUZU ");
    gotoxy(17,3); printf("--------------------------");
    gotoxy(10,7);
    printf("OGRENCI NUMARANIZI GIRINIZ: ");
    scanf("%s", ogrenciUser);

    if(ogrenciCheck(ogrenciUser)!=0){

        do{
            system("cls");
            gotoxy(10,6); printf("YAPMAK ISTEDIGINIZ ISLEMI ASAGIDAN SECINIZ");
            gotoxy(10,7); printf("------------------------------------------");
            gotoxy(10,10);printf("1) Profil/Not Goruntuleme\n");
            gotoxy(10,12);printf("2) Ana Menu\n");
            gotoxy(10,14);printf("0) Cikis Yap\n");
            gotoxy(10,18);
            printf("SECIMINIZI YAPINIZ: ");
            scanf("%d", &ogrenciSecim);

            switch(ogrenciSecim)
            {
                case 1:
                    ogrenciBul(ogrenciUser);
                    baskaIslem();
                    break;

                case 2:
                    menu();
                    break;

                case 0:
                    cikis();
                    break;
            }
        }while(ogrenciSecim!=0);

    }
    else{
       gotoxy(10,22); printf("YANLIS OGRENCI NUMARASI GIRDINIZ!");
       baskaIslem();
       menu();
    }
}

void menu(void){
    int girisSecim=0;

        system("cls");
        gotoxy(13,3); printf("<--:MENU:-->");
        gotoxy(13,6); printf("1 : OGRETMEN GIRISI\n");
        gotoxy(13,8); printf("2 : OGRENCI GIRISI\n");
        gotoxy(13,10);printf("0 : CIKIS YAP\n");
        gotoxy(13,14);
        printf("SECIMINIZI YAPINIZ: ");
        scanf("%d",&girisSecim);

        switch(girisSecim)
        {
        case 1:
            ogretmenGirisi();
            break;

        case 2:
            ogrenciGirisi();
            break;

        case 0:
            cikis();
            break;

        default:
            printf("HATALI GIRIS YAPTINIZ!\n\n");
        }
}

void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
