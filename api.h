#define STRING_SIZE 255
#define MIN_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "StructureFile.h"

void getData(int id){
	Rows *tempNode = rowHead;
	int flag = 1;
	while (tempNode != NULL){
		if (tempNode->rowId == id){
			printDetails(tempNode);
			flag = 0;
			break;
		}
		tempNode = tempNode->next;
	}
	if (flag)
		printf("\nMember with ID %d not found\n", id);
}

int putData(char **columnNames, char **values, int index, int id){

	Rows *tempRowNode = rowHead;
	while (tempRowNode != NULL){
		if (tempRowNode->rowId == id){
			for (int i = 0; i < index; ++i)
				tempRowNode->columns = getColumnHead(tempRowNode->columns, columnNames[i], values[i]);
			tempRowNode->commitVersion += 1;
			return id;
		}
		tempRowNode = tempRowNode->next;
	}

	tempRowNode = rowHead;
	Rows *newRowNode = createRowNode();
	for (int i = 0; i < index; ++i){
		newRowNode->columns = getColumnHead(newRowNode->columns, columnNames[i], values[i]);
	}
	if (rowHead == NULL){
		newRowNode->rowId = 1;
		newRowNode->commitVersion = 1;
		rowHead = newRowNode;
	}
	else{
		while (tempRowNode->next != NULL){
			tempRowNode = tempRowNode->next;
		}
		newRowNode->rowId = tempRowNode->rowId + 1;
		newRowNode->commitVersion = getCommitVersion(newRowNode);
		tempRowNode->next = newRowNode;
	}
	return newRowNode->rowId;
}

void deleteData(int id){
	Rows *tempNode = rowHead, *prevNode = NULL;
	int flag = 1;

	if (rowHead != NULL && rowHead->next == NULL){
		if (tempNode->rowId == id)
			rowHead = NULL;
		free(tempNode);
		return;
	}

	while (tempNode != NULL){
		if (tempNode->rowId == id){
			prevNode->next = tempNode->next;
			free(tempNode);
			flag = 0;
			break;
		}
		prevNode = tempNode;
		tempNode = tempNode->next;
	}
	if (flag)
		printf("\nMember ID not found\n");
}