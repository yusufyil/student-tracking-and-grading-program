#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
// bulunmak istenen ogrencinin nosu ile cagýrýlýyor bu fonksiyon
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
				printf("%s\n", o1.ogrAd);
				fclose(fp);
				return o1;
			}
			
		}
	fclose(fp);
	}	
}
void ogretmenOlustur(void){
	//eger ogretmen varsa yenisini olusturmaz eger yoksa varsayýlan olarak asagidaki degerleri atar
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
	//ogretmen sifresi sýnav katsayilarý gibi bilgileri okuyup ogretmen turunden geri gönderir
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
	//tek bir ogrencinin ortalamasýný hesaplayýp geri döndürür
	ogretmen o1;
	o1=ogretmenOku();
	float ortalama=0;
	ortalama=((float)(odev*o1.odevKatsayi+vize*o1.vizeKatsayi+final*o1.finalKatsayi)/(float)100);
	return ortalama;
}
int sifreKontrol(char *input){
	//eger sifre dogruysa 0 geri döner yanlýssa 1 geri döner
	ogretmen o1;
	o1=ogretmenOku();
	if(!strcmp(input, o1.sifre)){
		//sifreler ayni 0 geri dönüyorum
		return 0;
	}
	return 1;
}
void ogretmenGuncelle(char *yeniSifre, int yeniOdevKatsayi, int yeniVizeKatsayi, int yeniFinalKatsayi){
	//ogretmen sifresi veya sýnav katsayilari guncellenecekse bu fonksiyonla yapýlýr ogretmen olusutr sadece program basýnda kullanýlabilir!
	ogretmen o1;
	FILE *fp;
	strcpy(o1.sifre, yeniSifre);
	o1.odevKatsayi=yeniOdevKatsayi;
	o1.vizeKatsayi=yeniVizeKatsayi;
	o1.finalKatsayi=yeniFinalKatsayi;
	fp=fopen(".\\database\\0gretmen.txt","w+");
	fprintf(fp," %s %d %d %d", o1.sifre, o1.odevKatsayi, o1.vizeKatsayi, o1.finalKatsayi);
}



