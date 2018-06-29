#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "API.h"
char*filename(int row_id)
{
	char *a = (char*)malloc(sizeof(char) * 5);
	int i = 0;
	while (row_id > 0)
	{
		a[i] = row_id % 10;
		i++;
		row_id = row_id / 10;
	}
	a[i++] = '_';
	a[i] = '\0';
	return a;
}
void insertRow(){

	char choice, index = 0;

	char **columnNames = (char **)malloc(sizeof(char*)* MIN_SIZE);
	char **values = (char **)malloc(sizeof(char*)* MIN_SIZE);
	int i = 0, j = 0;
	do{
		columnNames[index] = (char *)malloc(sizeof(char)* STRING_SIZE);
		values[index] = (char *)malloc(sizeof(char)* STRING_SIZE);

		printf("\nEnter column name: ");
		fflush(stdin);
		gets(columnNames[index]);
		i++;
		printf("\nEnter value: ");
		fflush(stdin);
		gets(values[index]);

		index++;

		printf("\nDo you want to insert another column? [Y/N]");
		scanf("%c", &choice);

	} while (choice == 'y' || choice == 'Y');

	int id=putData(columnNames, values, index, -1);
	for (int j = 0; j < i; j++)
	{
		FILE*fp = fopen(strcat(filename(id), columnNames[j]), "a");
		fprintf(fp, "%s\n", values[j]);
		fclose(fp);
	}
}

void getRow(){
	int id;

	printf("\nEnter the id: ");
	scanf("%d", &id);

	getData(id);
}

void putRow(){

	int id;
	printf("\nEnter id: ");
	scanf("%d", &id);

	char choice, index = 0;
	int i = 0;
	char **columnNames = (char **)malloc(sizeof(char*)* MIN_SIZE);
	char **values = (char **)malloc(sizeof(char*)* MIN_SIZE);
	do{
		columnNames[index] = (char *)malloc(sizeof(char)* STRING_SIZE);
		values[index] = (char *)malloc(sizeof(char)* STRING_SIZE);


		printf("\nEnter column name: ");
		fflush(stdin);
		gets(columnNames[index]);

		printf("\nEnter value: ");
		fflush(stdin);
		gets(values[index]);

		index++;
		i++;
		printf("\nDo you want to insert another column? [Y/N]");
		scanf("%c", &choice);

	} while (choice == 'y' || choice == 'Y');

}

void deleteRow(){
	int id;

	printf("\nEnter id: ");
	scanf("%d", &id);

	deleteData(id);
}

int main(){

	int choice;

	while (1){
		printf("\n1. Insert Row");
		printf("\n2. Get Row Data");
		printf("\n3. Put Row Data");
		printf("\n4. Delete Row Data");
		printf("\n5. Exit");
		printf("\n\nEnter your choice: ");
		scanf("%d", &choice);

		switch (choice){
		case 1: insertRow();
			break;
		case 2: getRow();
			break;
		case 3: putRow();
			break;
		case 4: deleteRow();
			break;
		case 5: exit(1);
		default: printf("\nInvalid Option");
		}
	}

	system("pause");
	return 0;
}