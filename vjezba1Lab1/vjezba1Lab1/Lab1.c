#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE (58)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)
#include<stdio.h>
#include<stdlib.h>

typedef struct student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Student;

int ReadNumberOfRowsInFile()
{
	int counter = 0;

	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("LAB1.txt", "r");
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}

	printf("%d", counter);

	fclose(filePointer);

	return counter;


}

int main() {

	int noRows = 0;
	Student* students = NULL;

	noRows = ReadNumberOfRowsInFile();


	return 0;
	
}