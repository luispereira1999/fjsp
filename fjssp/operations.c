/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos �s operations
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
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
	new->jobID = jobID;
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

bool updateOperation(Operation** head, Operation* operationToUpdate, int id)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* current = *head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			current = operationToUpdate;
			return true;
		}
		current = current->next;
	}

	return false;
}

bool deleteOperation(Operation** head, int id)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* current = *head;
	Operation* previous = NULL;

	if (current != NULL && current->id == id) { // se o elemento que ser� apagado � o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->id != id) // procurar o elemento a ser apagado
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

bool writeOperations(char fileName[], Operation* head)
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

	Operation* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Operation), 1, file);
		current = current->next;
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
	file = fopen(fileName, "rb");
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(Operation), 1, file) > 0) // ler todos os elementos da lista do ficheiro
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

bool freeOperations(Operation* head)
{
	Operation* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

bool displayOperations(Operation* head)
{
	if (head == NULL)
	{
		return false;
	}

	Operation* current = head;

	printf("Opera��es:\n");
	while (current != NULL)
	{
		printf("ID: %d, ID Trabalho: %d, Posi��o: %d\n", current->id, current->jobID, current->position);
		current = current->next;
	}

	return true;
}

Operation* getOperation(Operation* head, int id)
{
	if (head == NULL)
	{
		return NULL;
	}

	Operation* current = head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			return current;
		}
		current = current->next;
	}

	return NULL;
}

// obter o m�nimo de tempo necess�rio para completo um job e as respetivas execu��o de opera��es
int getMinTimeToCompleteJob(Operation* operations, OperationExecution* operationsExecution, int jobID, OperationExecution** minOperationsExecution)
{
	if (operations == NULL || operationsExecution == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 99990;
	int counter = 0;

	Operation* currentOperation = operations;
	OperationExecution* currentOperationExecution = operationsExecution;
	Operation* minOperationExecution = NULL;

	while (currentOperation != NULL) // percorrer lista de opera��es
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo � opera��o
		{
			while (currentOperationExecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (currentOperationExecution->operationID == currentOperation->id) // se encontrar a execuca��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com menor tempo de utiliza��o
					if (currentOperationExecution->usageTime < time)
					{
						time = currentOperationExecution->usageTime;
						minOperationExecution = newOperationExecution(currentOperationExecution->operationID, currentOperationExecution->machineID, currentOperationExecution->usageTime);
					}
				}

				currentOperationExecution = currentOperationExecution->next;
			}

			*minOperationsExecution = insertOperationAtStart(*minOperationsExecution, minOperationExecution);

			// repor lista percorrida (currentOperationExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			freeOperationsExecution(currentOperationExecution);
			currentOperationExecution = NULL;
			currentOperationExecution = operationsExecution;
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 99990; // resetar tempo para a pr�xima itera��o
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// obter o m�ximo de tempo necess�rio para completo um job e as respetivas execu��o de opera��es
int getMaxTimeToCompleteJob(Operation* operations, OperationExecution* operationsExecution, int jobID, OperationExecution** maxOperationsExecution)
{
	if (operations == NULL || operationsExecution == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 0;
	int counter = 0;

	Operation* currentOperation = operations;
	OperationExecution* currentOperationExecution = operationsExecution;
	OperationExecution* maxOperationExecution = NULL;

	while (currentOperation != NULL) // percorrer lista de opera��es
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo � opera��o
		{
			while (currentOperationExecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (currentOperationExecution->operationID == currentOperation->id) // se encontrar a execuca��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com maior tempo de utiliza��o
					if (currentOperationExecution->usageTime > time)
					{
						time = currentOperationExecution->usageTime;
						maxOperationExecution = newOperationExecution(currentOperationExecution->operationID, currentOperationExecution->machineID, currentOperationExecution->usageTime);
					}
				}

				currentOperationExecution = currentOperationExecution->next;
			}

			*maxOperationsExecution = insertOperationExecutionAtStart(*maxOperationsExecution, maxOperationExecution);

			// repor lista percorrida (currentOperationExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			freeOperationsExecution(currentOperationExecution);
			currentOperationExecution = NULL;
			currentOperationExecution = operationsExecution;
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 0; // resetar tempo de utiliza��o para a pr�xima itera��o
		}

		currentOperation = currentOperation->next;
	}

	return counter;
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

bool deleteOperationExecution(OperationExecution** head, int operationID)
{
	if (*head == NULL)
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
		last->usageTime = current->usageTime;
		last->next = NULL; // o pr�ximo elemento da lista n�o existe, portanto � nulo
	}

	fclose(file);

	return head;
}

bool freeOperationsExecution(OperationExecution* head)
{
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
	if (head == NULL)
	{
		return false;
	}

	OperationExecution* current = head;

	printf("Execu��o de Opera��es:\n");
	while (current != NULL)
	{
		printf("ID Opera��o: %d, ID M�quina: %d, Tempo de Utiliza��o: %d\n", current->operationID, current->machineID, current->usageTime);
		current = current->next;
	}

	return true;
}

bool searchOperationExecution(OperationExecution* head, int operationID)
{
	if (head == NULL)
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

#pragma endregion