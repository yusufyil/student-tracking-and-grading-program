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
				int x;
				x=remove(dosyaAdres);
				printf("%d\n",x);
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


