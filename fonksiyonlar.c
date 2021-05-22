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
				printf("ogrenci kaydi silindi\n");
				return;
			}
		}
		fclose(fp);
	}
	printf("dosya silinemedi.. yanlis ogrenci no girilmis olabilir\n");
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
				fclose(fp);
				return o1;
			}	
		}
	fclose(fp);
	}
	//eger ogrenci bulunamad�ysa ortalama notu -1 yap�p return ediyorum
	o1.notlar.ortalamaNot=-1;
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
	fp=fopen(".\\database\\0gretmen.txt","w+");
	fprintf(fp," %s %d %d %d", o1.sifre, o1.odevKatsayi, o1.vizeKatsayi, o1.finalKatsayi);
}


// OKUMA FONKSİYONLARI - YAKUB


void ogrNoAl(char *okulNo){
	
	char ogrNo [100];
	int girisDeneme = 1;
	
	printf("Lütfen öğrenci numarasını giriniz: ");
	
	do{
		
	if(girisDeneme==1)
	scanf(" %s", ogrNo);
	else{
		printf("Lütfen 5 ile 14 karakter arasında geçerli bir öğrenci numarası giriniz. \n");
  		scanf(" %s", ogrNo);	
		  }
	girisDeneme ++;	
}while(!(strlen(ogrNo)>5  && strlen(ogrNo)<=14));
	
	strcpy(okulNo ,ogrNo);
	
}
void ogrAdAl(char *ogrAd){
	
	char gecici[50];
	int girisDeneme = 1;
	printf("Lütfen öğrenci adını giriniz: ");
	
	do{
		
	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		printf("Lütfen maksimum karakter sayısı 14 olacak şekilde geçerli bir öğrenci adı giriniz. \n");
  		scanf(" %s", gecici);	
		  }
	girisDeneme ++;	
}while(!(strlen(gecici)<=14));

	strcpy(ogrAd ,gecici);
	
	
}
void ogrSoyadAl(char *ogrSoyad){
		
	char gecici[50];
	int girisDeneme = 1;
	printf("Lütfen öğrencinin soyadını giriniz: ");
	
	do{
		
	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		printf("Lütfen maksimum karakter sayısı 19 olacak şekilde geçerli bir soyisim giriniz. \n");
  		scanf(" %s", gecici);	
		  }
	girisDeneme ++;	
}while(!(strlen(gecici)<=14));

	strcpy(ogrSoyad ,gecici);

}

void ogrMailAl(char *ogrMail){
		char gecici[50];
	int girisDeneme = 1;
	printf("Lütfen öğrencinin mail adresini giriniz: ");
	
	do{
		
	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		if(strlen(gecici)<10){
			printf("Lütfen 10 karakterden fazla olacak şekilde geçerli bir mail adresi giriniz. \n");
  		scanf(" %s", gecici);	
		} else if (strlen(gecici)>29) {
			printf("Lütfen 30 karakterden daha az olacak şekilde geçerli bir mail adresi giriniz. \n");
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
	printf("Lütfen öğrencinin telefon numarasını giriniz: ");
	
	do{
		
	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		if(strlen(gecici)<10){
			printf("Lütfen 10 karakterden fazla olacak şekilde geçerli bir telefon numarası giriniz. \n");
  		scanf(" %s", gecici);	
		} else if (strlen(gecici)>=14) {
			printf("Lütfen 15 karakterden daha az olacak şekilde geçerli bir telefon numarsı giriniz. \n");
  		scanf(" %s", gecici);
		}
		
		  }
	girisDeneme ++;	
}while(!(strlen(gecici)<=14 && strlen(gecici)>10) );

	strcpy(telNo ,gecici);
	
}
int ogrVizeNotuAl(){
	
	int vize;
	int girisDeneme = 1;
	
	printf("Lütfen vize notunu giriniz:\n");
	
	do{
		if(girisDeneme==1)
		scanf(" %d",&vize);
		else {
		printf("lütfen 0 ile 100 arasında olacak geçerli bir not girniz. \n");
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
	
	printf("Lütfen vize notunu giriniz:\n");
	
	do{
		if(girisDeneme==1)
		scanf(" %d",&final);
		else {
		printf("lütfen 0 ile 100 arasında olacak geçerli bir not girniz. \n");
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
	
	printf("Lütfen ödev notunu giriniz:\n");
	
	do{
		if(girisDeneme==1)
		scanf(" %d",&odev);
		else {
		printf("lütfen 0 ile 100 arasında olacak geçerli bir not girniz. \n");
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
	printf("Lütfen ödev, vize ve final katsayılarını sırası ile girerek enter tuşuna basınız.\n");
	
	do{
	if (girisDeneme ==1){
		printf("Ödev katsayısı:");
		scanf(" %d", &odevK);
		printf("Vize katsayısı:");
		scanf(" %d", &vizeK);
		printf("Final katsayısı:");
		scanf(" %d", &finalK);
		girisDeneme++;
	}
	
	else 
	
	 {
	 	printf("Katsayılar toplamının 100 olması gerekmektedir, lütfen katsayılır tekrar sırayla giriniz.\n");
	 	printf("Ödev katsayısı:");
		scanf(" %d", &odevK);
		printf("Vize katsayısı:");
		scanf(" %d", &vizeK);
		printf("Final katsayısı:");
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
	printf("Lütfen belirlemek istediğiniz yeni şifrenizi girin: \n ");
	
	do{
		
	if(girisDeneme==1)
	scanf(" %s", gecici);
	else{
		if(strlen(gecici)<8){
			printf("Lütfen en az 8 karakter olacak şekilde yeni şifrenizi giriniz. \n");
  		scanf(" %s", gecici);	
		} else if (strlen(gecici)>29) {
			printf("Lütfen 29 karakterden daha az olacak şekilde yeni şifrenizi giriniz. \n");
  		scanf(" %s", gecici);
		}
		
		  }
	girisDeneme ++;	
}while(!(strlen(gecici)<=29 && strlen(gecici)>=8) );

	strcpy(yeniSifre ,gecici);

}




//ARAYUZ FONKSIYONLAR ~ HUSSAIN

void cikis(void){
    system("cls");
    gotoxy(0,7);
    printf(".....:::MARMARA SISTEMINI TERCIH ETTIGINIZ ICIN TESEKKURLER:::.....\n");
    printf("...................................................................\n\n\n");
    exit(1);
}

void ogretmenGirisi(void){
    int sec, ogretmenSecim=0;
    char ogretmenSifre[20];

    system("cls");
    gotoxy(13,5);
    printf("Username: Admin\n"); //ogretmen icin bir username olacak mi?
    gotoxy(13,7);
    printf("Sifreniz: ");
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
        gotoxy(10,17);printf("5) Ana Menu");
        gotoxy(10,19);printf("0) Cikis Yap");
        gotoxy(10,23);
        printf("SECIMINIZI YAPINIZ: ");
        scanf("%d", &ogretmenSecim);

        switch(ogretmenSecim)
        {
            case 1:
              //  ogrenciEkle();
                break;

            case 2:
                //ogrenciBul();
                break;

            case 3:
              //  ogrenciSil();
                break;

            case 4:
               // ogretmenGuncelle();
                break;

            case 5:
                menu();
                break;

            case 0:
                cikis();
                break;

            default:
            printf("HATALI GIRIS YAPTINIZ!");
        }
        system("cls");
        gotoxy(10,20);printf("----------------------------------------------------");
        gotoxy(10,21);printf("BASKA ISLEM YAPMAK ICIN HERHANGI BIR TUSA BASINIZ...");
        gotoxy(10,22);printf("----------------------------------------------------");
        getch();
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
    printf("OGRENCI NUMARANIZI GIRINIZ: "); //Ismiyle de yapabilir miyiz? How to check if valid?
    scanf("%d", &ogrenciUser);

        gotoxy(10,6); printf("YAPMAK ISTEDIGINIZ ISLEMI ASAGIDAN SECINIZ");
        gotoxy(10,7); printf("------------------------------------------");
        gotoxy(10,10);printf("1) Not/Transkript Goruntule\n");
        gotoxy(10,12);printf("2) Ana Menu\n");
        gotoxy(10,14);printf("0) Cikis Yap\n");
        gotoxy(10,18);
        printf("SECIMINIZI YAPINIZ: ");
        scanf("%d", &ogrenciSecim);

        switch(ogrenciSecim)
        {
            case 1:
                ogrenciBul(ogrenciUser); //Ne output cikacak? Sadece isim mi? Diger bilgiler de eklenmeli fonksiyona.
                break;

            case 2:
                menu();
                break;

            case 0:
                cikis();
                break;
        }
}

void menu(void){
    int girisSecim=0;

        system("cls");
        gotoxy(13,3);printf("<--:MENU:-->");
        gotoxy(13,6);printf("1 : OGRETMEN GIRISI\n");
        gotoxy(13,8);printf("2 : OGRENCI GIRISI\n");
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
