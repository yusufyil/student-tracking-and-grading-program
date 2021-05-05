#ifndef fonksiyonlar
#define fonksiyonlar
typedef struct{
	int vizeNotu;
	int finalNotu;
	int odevNotu;
	float ortalamaNot;
}not;

typedef struct{
	char ogrNo[10];
	char ogrAd[10];
	char ogrSoyad[10];
	char ogrMail[20];
	char ogrTelNo[15];
	not notlar;
}ogrenci;
typedef struct{
	char sifre[20];
	int odevKatsayi;
	int vizeKatsayi;
	int finalKatsayi;
}ogretmen;
void ogrenciEkle(ogrenci o1);
void ogrenciSil(char *no);
ogrenci ogrenciBul(char *no);
void ogretmenOlustur(void);
ogretmen ogretmenOku(void);
float ogrenciOrtalama(int odev, int vize, int final);
int sifreKontrol(char *input);
void ogretmenGuncelle(char *yeniSifre, int yeniOdevKatsayi, int yeniVizeKatsayi, int yeniFinalKatsayi);
#endif
