/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos a execu��o de opera��es
Desenvolvedor(es):   Lu�s Pereira (18446)
�ltima atualiza��o:  25/03/2022
Cria��o:             23/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

OperationExecution* newOperationExecution(int operationID, int machineID, int runtime)
{
	OperationExecution* new = (OperationExecution*)malloc(sizeof(OperationExecution));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->runtime = runtime;
	new->next = NULL;

	return new;
}

OperationExecution* insertOperationExecutionAtStart(OperationExecution* head, OperationExecution* new)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = new;
	}
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}

// inserir execu��o da opera��o ordenada pelo ID da opera��o
OperationExecution* insertOperationExecutionByOperation(OperationExecution* head, OperationExecution* new)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = new; // inserir no in�cio
	}
	else
	{
		OperationExecution* current = head;
		OperationExecution* previous = NULL;

		while (current && current->operationID < new->operationID) // 
		{
			previous = current;
			current = current->next;
		}

		if (previous == NULL) // inserir no meio
		{
			new->next = head;
			head = new;
		}
		else // inserir no fim
		{
			previous->next = new;
			new->next = current;
		}
	}

	return head;
}

// atualizar as unidades de tempo necess�rias para a execu��o da opera��o
bool updateRuntime(OperationExecution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL) // se lista est� vazia
	{
		return false;
	}

	OperationExecution* current = *head;

	while (current != NULL)
	{
		if (current->operationID == operationID && current->machineID == machineID)
		{
			current->runtime = runtime;
			return true;
		}
		current = current->next;
	}

	return false;
}

bool deleteOperationExecution(OperationExecution** head, int operationID)
{
	if (*head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	OperationExecution* current = *head;
	OperationExecution* previous = NULL;

	if (current != NULL && current->operationID == operationID) { // se o elemento que ser� apagado � o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->operationID != operationID) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL) // se o elemento n�o foi encontrado
	{
		return false;
	}

	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return true;
}

bool writeOperationsExecution(char fileName[], OperationExecution* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	FILE* file = NULL;
	file = fopen(fileName, "wb");
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

	fclose(file);

	return true;
}

OperationExecution* readOperationsExecution(char fileName[])
{
	OperationExecution* current = (OperationExecution*)malloc(sizeof(OperationExecution));
	if (current == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	OperationExecution* head = NULL;
	OperationExecution* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "rb");
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
		last->runtime = current->runtime;
		last->next = NULL; // o pr�ximo elemento da lista n�o existe, portanto � nulo
	}

	fclose(file);

	return head;
}

bool freeOperationsExecution(OperationExecution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	OperationExecution* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

bool displayOperationsExecution(OperationExecution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	OperationExecution* current = head;

	while (current != NULL)
	{
		printf("ID Opera��o: %d, ID M�quina: %d, Tempo de Execu��o: %d;\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	return true;
}

bool searchOperationExecution(OperationExecution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	OperationExecution* current = head;

	while (current != NULL)
	{
		if (current->operationID == operationID)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}