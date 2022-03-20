/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos �s operations
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#pragma region operations

Operation* newOperation(int id, int jobID, int position)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se n�o houver mem�ria para alocar
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
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	FILE* file = NULL;
	file = fopen(fileName, "a");
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
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
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(Operation), 1, file)) // ler todos os elementos da lista do ficheiro
	{
		if (head == NULL) // ler o primeiro elemento
		{
			head = last = (Operation*)malloc(sizeof(Operation));
		}
		else // ler os restantes elementos
		{
			last->next = (Operation*)malloc(sizeof(Operation));
			last = last->next;
		}

		last->id = current->id;
		last->jobID = current->jobID;
		last->position = current->position;
		last->next = NULL; // o pr�ximo elemento da lista n�o existe, portanto � nulo
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

	printf("Opera��es: ");
	while (current != NULL)
	{
		printf("ID: %d, ID Trabalho: %d, Posi��o: %d -> ", current->id, current->jobID, current->position);
		current = current->next;
	}
	printf("\n");

	return true;
}

#pragma endregion

#pragma region execu��o de opera��es

OperationExecution* newOperationExecution(int operationID, int machineID, int usageTime)
{
	OperationExecution* new = (OperationExecution*)malloc(sizeof(OperationExecution));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->usageTime = usageTime;
	new->next = NULL;

	return new;
}

OperationExecution* insertOperationExecutionAtStart(OperationExecution* head, OperationExecution* operationExecutionToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = operationExecutionToInsert;
	}
	else // se existir algum elemento na lista
	{
		operationExecutionToInsert->next = head;
		head = operationExecutionToInsert;
	}

	return head;
}

bool writeOperationsExecution(char fileName[], OperationExecution* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	FILE* file = NULL;
	file = fopen(fileName, "a");
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return false;
	}

	OperationExecution* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(OperationExecution), 1, file);
		current = current->next;
	}

	if (fwrite == 0) // se nenhum elemento foi escrito no ficheiro
	{
		return false;
	}

	fclose(file);

	return true;
}

OperationExecution* readOperationsExecution(char fileName[])
{
	OperationExecution* current = (OperationExecution*)malloc(sizeof(OperationExecution));
	OperationExecution* head = NULL;
	OperationExecution* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "r");
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(OperationExecution), 1, file)) // ler todos os elementos da lista do ficheiro
	{
		if (head == NULL) // ler o primeiro elemento
		{
			head = last = (OperationExecution*)malloc(sizeof(OperationExecution));
		}
		else // ler os restantes elementos
		{
			last->next = (OperationExecution*)malloc(sizeof(OperationExecution));
			last = last->next;
		}

		last->operationID = current->operationID;
		last->machineID = current->machineID;
		last->usageTime = current->usageTime;
		last->next = NULL; // o pr�ximo elemento da lista n�o existe, portanto � nulo
	}

	fclose(file);

	return head;
}

bool displayOperationsExecution(OperationExecution* head)
{
	if (head == NULL)
	{
		return false;
	}

	OperationExecution* current = head;

	printf("Execu��o de Opera��es: ");
	while (current != NULL)
	{
		printf("ID Opera��o: %d, ID M�quina: %d, Tempo: %d -> ", current->operationID, current->machineID, current->usageTime);
		current = current->next;
	}
	printf("\n");

	return true;
}

#pragma endregion