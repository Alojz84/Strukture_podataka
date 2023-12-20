#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 128

typedef struct _Dir* Position;
typedef struct _Stack* PosStack;

typedef struct _Dir {
	char* name;
	Position child;
	Position sibling;
}Dir;

typedef struct _Stack {
	Position direktorij;

	PosStack next;
	PosStack prev;
}Stack;

int stvoriDir(Position);
int ispisiDir(Position);
Position pristupiDir(Position, PosStack);
Position prethodni(Position, PosStack);
Position pronadi(char*, Position);
int push(PosStack, Position);
Position pop(PosStack);
int ispisi(PosStack, Position, Position);
PosStack pronadiposljednji(PosStack);

int main()
{
	Position root;
	root = (Position)malloc(sizeof(Dir));
	root->child = NULL;
	root->sibling = NULL;
	PosStack head;
	head = (PosStack*)malloc(sizeof(Stack));
	head->next = NULL;
	head->prev = NULL;
	root->name = (char*)malloc(MAX * sizeof(char));
	root->name = "C:";

	Position current = root;
	int n = 0;

	printf("MENU\n\n1 - Dodavanje direktorija\n2 - Otvaranje direktorija\n3 - Povratak na prethodni direktorij\n4 - Ispis sadrzaja direktorija\n5 - Izlazak iz programa\n");

	while (n != '0') {

		ispisi(head, root, current);
		scanf(" %c", &n);
		switch (n)
		{
		case '1':
			stvoriDir(current);
			break;
		case '2':
			current = pristupiDir(current, head);
			break;
		case '3':
			current = prethodni(current, head);
			break;
		case '4':
			ispisiDir(current);
			break;
		case '5':
			return 0;
			break;
		default:
			printf("\nKrivi unos!\n");
		}
	}

	return 0;
}
int ispisi(PosStack head, Position root, Position current)
{
	PosStack s;

	s = pronadiposljednji(head);

	if (head->next == NULL) {
		printf("%s>", root->name);
		return EXIT_SUCCESS;
	}

	while (s->prev != NULL) {
		printf("%s>", s->direktorij->name);
		s = s->prev;
	}

	printf("%s>", current->name);

	return EXIT_SUCCESS;
}
PosStack pronadiposljednji(PosStack head)
{
	PosStack s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}
int stvoriDir(Position current) {
	Position dir;
	dir = (Position)malloc(sizeof(Dir));
	dir->name = (char*)malloc(MAX * sizeof(char));

	if (!dir)
		printf("Greska u alociranju!\n");

	if (current->child != NULL) {
		current = current->child;
		while (current->sibling != NULL) {
			current = current->sibling;
		}
		current->sibling = dir;
	}

	else
		current->child = dir;
	printf("Upisite ime direktorija kojeg zelite dodati\n");
	scanf(" %s", dir->name);

	dir->sibling = NULL;
	dir->child = NULL;

	return EXIT_SUCCESS;
}
int ispisiDir(Position current) {
	if (current->child == NULL) {
		printf("Prazan direktorij!\n");
		return EXIT_SUCCESS;
	}

	current = current->child;

	printf("Direktoriji: \n");
	printf("\t%s\n", current->name);

	while (current->sibling != NULL) {
		printf("\t%s\n", current->sibling->name);
		current = current->sibling;
	}

	return EXIT_SUCCESS;
}

Position pronadi(char* name, Position current) {
	if (current->child == NULL) {
		printf("Prazan direktorij!");
		return EXIT_SUCCESS;
	}

	current = current->child;

	while (strcmp(name, current->name) != 0 && current->sibling != NULL) {
		current = current->sibling;
	}

	if (current->sibling == NULL) {
		if (strcmp(name, current->name) != 0)
			return NULL;
		else
			return current;
	}

	else
		return current;
}

int push(PosStack head, Position dir) {

	PosStack q = (PosStack)malloc(sizeof(Stack));

	q->next = head->next;
	q->prev = head;

	if (head->next != NULL) {
		head->next->prev = q;
	}

	head->next = q;
	q->direktorij = dir;

	return EXIT_SUCCESS;
}

Position pop(PosStack head) {

	PosStack q = (PosStack)malloc(sizeof(Stack));
	Position p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->direktorij;
	head->next = head->next->next;

	if (head->next != NULL)
		head->next->prev = head;

	free(q);

	return p;
}

Position prethodni(Position current, PosStack head)
{
	Position s;

	s = pop(head);

	if (s == NULL) {
		printf("Vec se nalazite u rootu!\n");
		s = current;
	}

	return s;
}

Position pristupiDir(Position current, PosStack head)
{
	Position s;
	char* name;
	name = (char*)malloc(MAX * sizeof(char));

	printf("Upisite ime direktorija kojem zelite pristupiti\n");
	scanf(" %s", name);

	if (current->child == NULL) {
		printf("Prazan direktorij!\n");
		return current;
	}

	s = pronadi(name, current);

	if (s == 0) {
		printf("Pogresan naziv direktorija!\n");
		return current;
	}

	push(head, current);

	return s;
}