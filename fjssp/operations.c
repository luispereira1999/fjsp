/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos às operations
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Operation* newOperation(int id, int jobID, int position)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->jobID = id;
	new->position = position;
	new->next = NULL;

	return new;
}

Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = operationToInsert;
	}
	else // se existir algum elemento na lista
	{
		operationToInsert->next = head;
		head = operationToInsert;
	}

	return head;
}

bool writeOperations(char fileName[], Operation* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	FILE* file = NULL;
	file = fopen(fileName, "w");
	if (file == NULL) // se não foi possível abrir o ficheiro
	{
		return false;
	}

	Operation* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Operation), 1, file);
		current = current->next;
	}

	if (fwrite == 0) // se nenhum elemento foi escrito no ficheiro
	{
		return false;
	}

	fclose(file);

	return true;
}

Operation* readOperations(char fileName[])
{
	Operation* current = (Operation*)malloc(sizeof(Operation));
	Operation* head = NULL;
	Operation* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "r");
	if (file == NULL) // se não foi possível abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(Operation), 1, file)) // ler todos os elementos da lista do ficheiro
	{
		if (head == NULL) // ler o primeiro elemento
		{
			head = last = (Job*)malloc(sizeof(Job));
		}
		else // ler os restantes elementos
		{
			last->next = (Operation*)malloc(sizeof(Operation));
			last = last->next;
		}

		last->id = current->id;
		last->jobID = current->jobID;
		last->position = current->position;
		last->next = NULL; // o próximo elemento da lista não existe, portanto é nulo
	}

	fclose(file);

	return head;
}

bool displayOperations(Operation* head)
{
	if (head == NULL)
	{
		return false;
	}

	Operation* current = head;

	printf("Operações: ");
	while (current != NULL)
	{
		printf("ID: %d, ID Trabalho: %d, Posição: %d -> ", current->id, current->jobID, current->position);
		current = current->next;
	}
	printf("\n");

	return true;
}

PerformOperation* newPerformOperation(int operationID, int machineID, int usageTime)
{
	PerformOperation* new = (PerformOperation*)malloc(sizeof(PerformOperation));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->usageTime = usageTime;
	new->next = NULL;

	return new;
}

PerformOperation* insertPerformOperationAtStart(PerformOperation* head, PerformOperation* performOperationToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = performOperationToInsert;
	}
	else // se existir algum elemento na lista
	{
		performOperationToInsert->next = head;
		head = performOperationToInsert;
	}

	return head;
}