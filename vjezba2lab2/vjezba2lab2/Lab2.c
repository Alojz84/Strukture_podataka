#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

typedef struct _osoba* Pozicija;

typedef struct _osoba {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int GodinaRodenja;
	Pozicija next;
}Osoba;

Pozicija StvoriOsobu();
int UpisP(Pozicija);
int Ispis(Pozicija);
int UpisK(Pozicija);
Pozicija Trazi(Pozicija);
Pozicija TraziPrev(Pozicija);
int Brisi(Pozicija);

int main() {

	Osoba Head = { .ime = {0}, .prezime = {0}, .GodinaRodenja = 0, .next = NULL };
	int odabir = 0;

	do {

		printf("\n");
		printf("\nOdabirom broja biras radnju koju zelis: 1) Unos elementa na pocetak 2)Ispis liste 3)Unos elemenata na kraj 4)Trazi osobu po prezimenu 5)Brisi osobu :");
		scanf("%d", &odabir);
		switch (odabir) {

		case 1:
			UpisP(&Head);
			break;

		case 2:
			Ispis(Head.next);
			break;

		case 3:
			UpisK(&Head);
			break;

		case 4:
			Trazi(&Head);
			break;

		case 5:
			Brisi(&Head);
			break;

		case 0:
			printf("\nIzasli ste iz menija!");
			break;

		default:
			printf("\nNetocan unos broja za odabir!");
		}



	} while (odabir != 0);

	return EXIT_SUCCESS;
}

Pozicija StvoriOsobu() {

	Pozicija NovaOsoba = NULL;
	char NovoIme[MAX_SIZE] = { 0 };
	char NovoPrez[MAX_SIZE] = { 0 };
	int NovaGod = 0;

	NovaOsoba = (Pozicija)malloc(sizeof(Osoba));

	//Provjera alociranja memorije

	if (!NovaOsoba) {
		printf("\nMemorija nije dobro alocirana!");
		return NULL;
	}

	printf("\nUnesi ime :");
	scanf("%s", NovoIme);

	printf("\nUnesi prezime :");
	scanf("%s", NovoPrez);

	printf("\nUnesi godinu rodenja: ");
	scanf("%d", &NovaGod);

	strcpy(NovaOsoba->ime, NovoIme);
	strcpy(NovaOsoba->prezime, NovoPrez);
	NovaOsoba->GodinaRodenja = NovaGod;

	return NovaOsoba;
}

int UpisP(Pozicija P) {
	Pozicija NovaOsoba=NULL;
	NovaOsoba = StvoriOsobu();

	if (!NovaOsoba) {
		printf("Nije dobra alokacija memorije! ");
		return NULL;
	}

	NovaOsoba->next = P->next;
	P->next = NovaOsoba;

	return EXIT_SUCCESS;
}

int Ispis(Pozicija P) {

	while (P != NULL) {
		printf("%s \t %s \t %d\n", P->ime, P->prezime, P->GodinaRodenja);
		P = P->next;
	}
	return EXIT_SUCCESS;
}

int UpisK(Pozicija P) {
	Pozicija NovaOsoba=NULL;
	NovaOsoba = StvoriOsobu();

	if (!NovaOsoba) {
		printf("\nGreska u alokaciji memorije!");
		return NULL;
	}

	while (P->next != NULL)
		P = P->next;

	NovaOsoba->next = P->next;
	P->next = NovaOsoba;

	return EXIT_SUCCESS;
}

Pozicija Trazi(Pozicija P) {

	char prez[MAX_SIZE];

	printf("\nUpisi prezime osobe koju zelis pronaci: ");
	scanf("%s", prez);

	while (P != NULL && strcmp(P->prezime, prez))
		P = P->next;

	if (P == NULL)
		printf("\nNe postoji osoba sa tim prezimenom");
	else
		printf("%s \t %s \t %d\n", P->ime, P->prezime, P->GodinaRodenja);

	return P;
}

Pozicija TraziPrev(Pozicija P) {

	Pozicija prev = P;
	P = P->next;

	char prez[MAX_SIZE];

	printf("\nUpisi prezime osobe koju zelis pronaci: ");
	scanf("%s", prez);

	while (P != NULL && strcmp(P->prezime, prez)) {
		prev = P;
		P = P->next;
	}
	if (P == NULL)
		return P;
	else
		return prev;
}

int Brisi(Pozicija P) {
	Pozicija prev;
	prev = TraziPrev(P);

	if (prev != NULL) {
		P = prev->next;
		prev->next = P->next;
		free(P);
	}
	else
		printf("Ne postoji osoba sa tim prezimenom!");

	return EXIT_SUCCESS;
}