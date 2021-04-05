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
#endif
