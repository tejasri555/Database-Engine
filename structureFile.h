#define STRING_SIZE 255

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Cell{
	char *value;
	int version;
	Cell *next;
}Cell;

typedef struct Columns{
	char *name;
	Cell *cell;
	Columns *next;
}Columns;

typedef struct Rows{
	Columns *columns;
	int rowId;
	int commitVersion;
	Rows *next;
}Rows;

Rows *rowHead = NULL;

Rows *createRowNode(){
	Rows *newNode = (Rows *)malloc(sizeof(Rows));
	newNode->columns = NULL;
	newNode->next = NULL;

	return newNode;
}

Columns *createColumnsNode(){
	Columns *newNode = (Columns *)malloc(sizeof(Columns));
	newNode->name = (char *)malloc(sizeof(char)* STRING_SIZE);
	newNode->cell = NULL;
	newNode->next = NULL;

	return newNode;
}

Cell *createCellNode(){
	Cell *newNode = (Cell *)malloc(sizeof(Cell));
	newNode->value = (char *)malloc(sizeof(char)* STRING_SIZE);
	newNode->next = NULL;

	return newNode;
}

Cell *getCellHead(Cell *cellHead, char *value){

	Cell *tempNode = cellHead;

	Cell *newNode = createCellNode();
	strcpy(newNode->value, value);

	if (cellHead == NULL)
		newNode->version = 1;
	else
		newNode->version = cellHead->version + 1;

	newNode->next = cellHead;
	cellHead = newNode;

	return cellHead;
}

Columns *getColumnHead(Columns *columnHead, char *columnName, char *value){

	Columns *tempNode = columnHead;
	while (tempNode != NULL){
		if (strcmp(tempNode->name, columnName) == 0){
			tempNode->cell = getCellHead(tempNode->cell, value);
			return columnHead;
		}
		tempNode = tempNode->next;
	}

	tempNode = columnHead;
	Columns *newNode = createColumnsNode();
	strcpy(newNode->name, columnName);
	newNode->cell = getCellHead(newNode->cell, value);

	if (columnHead == NULL){
		columnHead = newNode;
	}
	else{
		while (tempNode->next != NULL){
			tempNode = tempNode->next;
		}
		tempNode->next = newNode;
	}
	return columnHead;
}

int getCommitVersion(Rows *row){
	int version = INT_MIN;
	Columns *tempNode = row->columns;
	while (tempNode != NULL){
		Cell *cellHead = tempNode->cell, *temp = cellHead;
		while (temp != NULL){
			if (temp->version > version)
				version = temp->version;
			temp = temp->next;
		}
		tempNode = tempNode->next;
	}
	return version;
}


void printDetails(Rows *row){
	Columns *tempNode = row->columns;
	while (tempNode != NULL){
		Cell *cellHead = tempNode->cell, *temp = cellHead;
		while (temp != NULL){
			if (temp->version <= row->commitVersion){
				printf("%-15s: %-15s\n", tempNode->name, temp->value);
				break;
			}
			temp = temp->next;
		}
		tempNode = tempNode->next;
	}
}