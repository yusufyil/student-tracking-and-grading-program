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
void ogrNoAl(char *okulNo){
	// bu fonksiyon ile ogrencinin okul nosu girilecek
	//once 100 veya 150 boyutlu bir char arrayý olusuturulacak 
	//daha sonra bir while döngüsü ile bu arrayýn boyunun 5 -14 arasýnda olup olmadýgý kontrol edilecek
	// 5-14 arasýnda bir deger girilince while bitecek ve strcpy ile girilen deger okulNo ya aktarýlacak
}
void ogrAdAl(char *ogrAd){
	// ogrenci adi maximum 14 olabilir
	// yine no mantigi ile kullanicidan bir string girmesi istenecek
	//eger girilen string cok buyukse veya cok kucukse tekrar girmesi istenecek
	//eger istenen aralýkta ise girilen deger strcpy ile ogrAd a kopyalanacak ve fonksiyon bitecek
}
void ogrSoyadAl(char *ogrSoyad){
	//yukaridakilerle ayni mantik sadece soyadi daha uzun olabilir 19 belirledim struct ta
}
void ogrMailAl(char *ogrMail){
	//yukariyla ayni mantik sadece array daha buyuk 29 karakter max 10 karakter min alinabilir
}
void ogrTelNoAl(char *telNo){
	//yine ayni mantýk max 14 min 10 boyutlu olabilir
}
int ogrVizeNotuAl(){
	//int vize belirlenir
	//kullanýcýdan bir deger girmesini isteriz eger deger 0-100 aralýgýnda degil ise gecersiz giris deyip tekrar girmesini isteriz
	//girilen deger 0-100 arasýnda olunca donguden cýkýp o degeri return vize yaparýz
}
int ogrFinalNotuAl(){
	//vize ile birebir ayni mantik sadece printf icine vize notu giriniz degil final notu giriniz yazmali
}
int ogrOdevNotuAl(){
	//yine ayni mantik sadece printf ici farkli
}
void ogretmenKatsayiAl(int *odev, int *vize, int *final){
	//burada ogrenci ders notunu hesaplarken vize final ve odev katsayisini güncelliyoruz
	//mesela vize %25 odev %25 final %50 gibi
	//once 3 tane int tipinden degisken tanýmlanýr daha sonra
	// bir while dongusu icinde icinde bunlara katsayi atanmasi isteir
	//vize katsayiyisini girinizz gibi
	// while dongusunun sonunda bu degerler toplanýr eger 100 degilse tekrar girmesi istenir
	//mesela vize 40 final 60 odev 10 olamaz toplamý 110 ediyor
	//eger toplamý 100 edecek degerler girilirse while dan cýkýlýr
	// son olarak *odev=odevkatsayi *vize=vize katsayi gibi atamalarla 3 degiskene de katsayilar atanir
}
void ogretmenSifreGuncelle(char *yeniSifre){
	//yine ogrencino almayla benzer mantik
}
