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
	char sifre[30];
	int odevKatsayi;
	int vizeKatsayi;
	int finalKatsayi;
}ogretmen;
void gotoxy(int x, int y);
void ogrenciEkle(ogrenci o1);
void ogrenciSil(char *no);
ogrenci ogrenciBul(char *no);
void ogretmenOlustur(void);
ogretmen ogretmenOku(void);
float ogrenciOrtalama(int odev, int vize, int final);
int sifreKontrol(char *input);
void ogretmenGuncelle(char *yeniSifre, int yeniOdevKatsayi, int yeniVizeKatsayi, int yeniFinalKatsayi);
void ogrNoAl(char *okulNo);
void ogrAdAl(char *ogrAd);
void ogrSoyadAl(char *ogrSoyad);
void ogrMailAl(char *ogrMail);
void ogrTelNoAl(char *telNo);
int ogrVizeNotuAl();
int ogrFinalNotuAl();
int ogrOdevNotuAl();
void ogretmenKatsayiAl(int *odev, int *vize, int *final);
void ogretmenSifreGuncelle(char *yeniSifre);
void head(int durum);
void baskaIslem(void);
void tumuGoster(void);
char* harfliNot(ogrenci o1);
void ogrGoster(ogrenci o1);
int ogrenciCheck(char *no);
void ogretmenGirisi(void);
void ogrenciGirisi(void);
void menu(void);
#endif
