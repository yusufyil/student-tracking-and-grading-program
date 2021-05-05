#ifndef fonksiyonlar
#define fonksiyonlar
typedef struct{
	int vizeNotu;
	int finalNotu;
	int odevNotu;
	float ortalamaNot;
}not;

typedef struct{
	char ogrNo[15];
	char ogrAd[15];
	char ogrSoyad[20];
	char ogrMail[30];
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
