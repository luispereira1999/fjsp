/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos a operações
Desenvolvedor(es):   Luís Pereira (18446)
Última atualização:  25/03/2022
Criação:             18/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Operation* newOperation(int id, int jobID, int position)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se não houver memória para alocar
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

// trocar a ordem da posição de uma operação, num determinado job
bool changeOperationPosition(Operation** head, Job* jobs, int jobID, int oldPosition, int newPosition)
{
	if (*head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	if (oldPosition == newPosition) // se as posições forem as mesmas
	{
		return false;
	}

	if (!searchJob(jobs, jobID)) // se o job não existir
	{
		return false;
	}

	Operation* currentOperationX = *head, * previousOperationX = NULL; // para a antiga
	Operation* currentOperationY = *head, * previousOperationY = NULL; // para a nova

	// procurar pela antiga posição
	while (currentOperationX && currentOperationX->position != oldPosition || currentOperationX->jobID != jobID)
	{
		previousOperationX = currentOperationX;
		currentOperationX = currentOperationX->next;
	}

	// procurar pela nova posição
	while (currentOperationY && currentOperationY->position != newPosition || currentOperationY->jobID != jobID)
	{
		previousOperationY = currentOperationY;
		currentOperationY = currentOperationY->next;
	}

	if (currentOperationX == NULL || currentOperationY == NULL) // se as operações relativas à antiga ou nova posição não foram encontradas
	{
		return false;
	}

	if (previousOperationX != NULL) // se a operação anterior não for o head da lista
	{
		previousOperationX->next = currentOperationY;
	}
	else // senão fazer que operação anterior seja o head
	{
		*head = currentOperationY;
	}

	if (previousOperationY != NULL) // se a operação nova não for o head da lista
	{
		previousOperationY->next = currentOperationX;
	}
	else // senão fazer com que operação anterior seja o head
	{
		*head = currentOperationX;
	}

	// trocar elementos
	Operation* tempOperation = currentOperationY->next;
	currentOperationY->next = currentOperationX->next;
	currentOperationX->next = tempOperation;

	return true;
}

bool deleteOperation(Operation** head, int id)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* current = *head;
	Operation* previous = NULL;

	if (current != NULL && current->id == id) { // se o elemento que será apagado é o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->id != id) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL) // se o elemento não foi encontrado
	{
		return false;
	}

	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return true;
}

bool writeOperations(char fileName[], Operation* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	FILE* file = NULL;
	file = fopen(fileName, "wb");
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
	if (file == NULL) // se não foi possível abrir o ficheiro
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
		last->next = NULL; // o próximo elemento da lista não existe, portanto é nulo
	}

	fclose(file);

	return head;
}

bool freeOperations(Operation* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

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
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Operation* current = head;

	printf("Operações:\n");
	while (current != NULL)
	{
		printf("ID: %d, ID Trabalho: %d, Posição: %d\n", current->id, current->jobID, current->position);
		current = current->next;
	}

	return true;
}

Operation* getOperation(Operation* head, int id)
{
	if (head == NULL) // se a lista estiver vazia
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

// obter o mínimo de tempo necessário para completo um job e as respetivas execução de operações
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

	while (currentOperation != NULL) // percorrer lista de operações
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (currentOperationExecution != NULL) // percorrer lista de execução de operações
			{
				if (currentOperationExecution->operationID == currentOperation->id) // se encontrar a execucação de operação relativa à operação
				{
					// guardar execução de operação com menor tempo de utilização
					if (currentOperationExecution->usageTime < time)
					{
						time = currentOperationExecution->usageTime;
						minOperationExecution = newOperationExecution(currentOperationExecution->operationID, currentOperationExecution->machineID, currentOperationExecution->usageTime);
					}
				}

				currentOperationExecution = currentOperationExecution->next;
			}

			*minOperationsExecution = insertOperationAtStart(*minOperationsExecution, minOperationExecution);

			// repor lista percorrida (currentOperationExecution), para que se for necessário voltar a percorrer o while da execução de operações de novo
			freeOperationsExecution(currentOperationExecution);
			currentOperationExecution = NULL;
			currentOperationExecution = operationsExecution;
			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 99990; // resetar tempo para a próxima iteração
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// obter o máximo de tempo necessário para completo um job e as respetivas execução de operações
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

	while (currentOperation != NULL) // percorrer lista de operações
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (currentOperationExecution != NULL) // percorrer lista de execução de operações
			{
				if (currentOperationExecution->operationID == currentOperation->id) // se encontrar a execucação de operação relativa à operação
				{
					// guardar execução de operação com maior tempo de utilização
					if (currentOperationExecution->usageTime > time)
					{
						time = currentOperationExecution->usageTime;
						maxOperationExecution = newOperationExecution(currentOperationExecution->operationID, currentOperationExecution->machineID, currentOperationExecution->usageTime);
					}
				}

				currentOperationExecution = currentOperationExecution->next;
			}

			*maxOperationsExecution = insertOperationExecutionAtStart(*maxOperationsExecution, maxOperationExecution);

			// repor lista percorrida (currentOperationExecution), para que se for necessário voltar a percorrer o while da execução de operações de novo
			freeOperationsExecution(currentOperationExecution);
			currentOperationExecution = NULL;
			currentOperationExecution = operationsExecution;
			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 0; // resetar tempo de utilização para a próxima iteração
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// Obter a média de tempo necessário para completar uma operação, considerando todas as alternativas possíveis
float getAverageTimeToCompleteOperation(OperationExecution* operationsExecution, int operationID)
{
	if (operationsExecution == NULL) // se a lista estiver vazia
	{
		return -1.0f;
	}

	int sum = 0;
	float average = 0;
	float numberOfOperationsExecution = 0;

	OperationExecution* currentOperationExecution = operationsExecution;

	while (currentOperationExecution != NULL)
	{
		if (currentOperationExecution->operationID == operationID) // se encontrar a execucação de operação relativa à operação
		{
			sum += currentOperationExecution->usageTime;
			numberOfOperationsExecution++;
		}
		currentOperationExecution = currentOperationExecution->next;
	}

	if (numberOfOperationsExecution > 0) // para não permitir divisão por 0
	{
		average = sum / numberOfOperationsExecution;
	}

	return average;
}