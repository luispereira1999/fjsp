/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos às operações
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

Operation* insertOperationAtStart(Operation* head, Operation* new)
{
	if (searchOperation(head, new->id)) // não permitir inserir uma nova com o mesmo ID
	{
		return NULL;
	}

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

// trocar a ordem da posição de uma operação, num determinado job
bool updateOperationPosition(Operation** operations, Job* jobs, int jobID, int oldPosition, int newPosition)
{
	if (*operations == NULL || jobs == NULL) // se as listas estiverem vazias
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

	Operation* currentOperationX = *operations, * previousOperationX = NULL; // para a antiga
	Operation* currentOperationY = *operations, * previousOperationY = NULL; // para a nova

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
		*operations = currentOperationY;
	}

	if (previousOperationY != NULL) // se a operação nova não for o head da lista
	{
		previousOperationY->next = currentOperationX;
	}
	else // senão fazer com que operação anterior seja o head
	{
		*operations = currentOperationX;
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
	if (current == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

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

	while (current != NULL)
	{
		printf("ID: %d, ID Trabalho: %d, Posição: %d;\n", current->id, current->jobID, current->position);
		current = current->next;
	}

	return true;
}

bool searchOperation(Operation* head, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Operation* current = head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}

// obter o mínimo de tempo necessário para completo um job e as respetivas execuções de operações
int getMinTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions)
{
	if (operations == NULL || executions == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 99990;
	int counter = 0;

	Operation* currentOperation = operations;
	Execution* currentExecution = executions;
	Execution* minExecution = NULL;

	while (currentOperation != NULL) // percorrer lista de operações
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (currentExecution != NULL) // percorrer lista de execução de operações
			{
				if (currentExecution->operationID == currentOperation->id) // se encontrar a execucação de operação relativa à operação
				{
					// guardar execução de operação com menor tempo de utilização
					if (currentExecution->runtime < time)
					{
						time = currentExecution->runtime;
						minExecution = newExecution(currentExecution->operationID, currentExecution->machineID, currentExecution->runtime);
					}
				}

				currentExecution = currentExecution->next;
			}

			*minExecutions = insertExecutionAtStart(*minExecutions, minExecution);

			// repor lista percorrida (currentExecution), para que se for necessário voltar a percorrer o while da execução de operações de novo
			freeExecutions(currentExecution);
			currentExecution = NULL;
			currentExecution = executions;
			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 99990; // resetar tempo para a próxima iteração
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// obter o máximo de tempo necessário para completo um job e as respetivas execuções de operações
int getMaxTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions)
{
	if (operations == NULL || executions == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 0;
	int counter = 0;

	Operation* currentOperation = operations;
	Execution* currentExecution = executions;
	Execution* maxExecution = NULL;

	while (currentOperation != NULL) // percorrer lista de operações
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (currentExecution != NULL) // percorrer lista de execução de operações
			{
				if (currentExecution->operationID == currentOperation->id) // se encontrar a execucação de operação relativa à operação
				{
					// guardar execução de operação com maior tempo de utilização
					if (currentExecution->runtime > time)
					{
						time = currentExecution->runtime;
						maxExecution = newExecution(currentExecution->operationID, currentExecution->machineID, currentExecution->runtime);
					}
				}

				currentExecution = currentExecution->next;
			}

			*maxExecutions = insertExecutionAtStart(*maxExecutions, maxExecution);

			// repor lista percorrida (currentExecution), para que se for necessário voltar a percorrer o while da execução de operações de novo
			freeExecutions(currentExecution);
			currentExecution = NULL;
			currentExecution = executions;
			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 0; // resetar tempo de utilização para a próxima iteração
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// Obter a média de tempo necessário para completar uma operação, considerando todas as alternativas possíveis
float getAverageTimeToCompleteOperation(Execution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return -1.0f;
	}

	int sum = 0;
	float average = 0;
	float numberOfExecutions = 0;

	Execution* current = head;

	while (current != NULL)
	{
		if (current->operationID == operationID) // se encontrar a execucação de operação relativa à operação
		{
			sum += current->runtime;
			numberOfExecutions++;
		}
		current = current->next;
	}

	if (numberOfExecutions > 0) // para não permitir divisão por 0
	{
		average = sum / numberOfExecutions;
	}

	return average;
}