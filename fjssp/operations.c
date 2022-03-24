/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos �s opera��es
Desenvolvedor(es):   Lu�s Pereira (18446)
�ltima atualiza��o:  25/03/2022
Cria��o:             18/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

Operation* insertOperationAtStart(Operation* head, Operation* new)
{
	if (searchOperation(head, new->id)) // n�o permitir inserir uma nova com o mesmo ID
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

// trocar a ordem da posi��o de uma opera��o, num determinado job
bool updateOperationPosition(Operation** operations, Job* jobs, int jobID, int oldPosition, int newPosition)
{
	if (*operations == NULL || jobs == NULL) // se as listas estiverem vazias
	{
		return false;
	}

	if (oldPosition == newPosition) // se as posi��es forem as mesmas
	{
		return false;
	}

	if (!searchJob(jobs, jobID)) // se o job n�o existir
	{
		return false;
	}

	Operation* currentOperationX = *operations, * previousOperationX = NULL; // para a antiga
	Operation* currentOperationY = *operations, * previousOperationY = NULL; // para a nova

	// procurar pela antiga posi��o
	while (currentOperationX && currentOperationX->position != oldPosition || currentOperationX->jobID != jobID)
	{
		previousOperationX = currentOperationX;
		currentOperationX = currentOperationX->next;
	}

	// procurar pela nova posi��o
	while (currentOperationY && currentOperationY->position != newPosition || currentOperationY->jobID != jobID)
	{
		previousOperationY = currentOperationY;
		currentOperationY = currentOperationY->next;
	}

	if (currentOperationX == NULL || currentOperationY == NULL) // se as opera��es relativas � antiga ou nova posi��o n�o foram encontradas
	{
		return false;
	}

	if (previousOperationX != NULL) // se a opera��o anterior n�o for o head da lista
	{
		previousOperationX->next = currentOperationY;
	}
	else // sen�o fazer que opera��o anterior seja o head
	{
		*operations = currentOperationY;
	}

	if (previousOperationY != NULL) // se a opera��o nova n�o for o head da lista
	{
		previousOperationY->next = currentOperationX;
	}
	else // sen�o fazer com que opera��o anterior seja o head
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
	if (current == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

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
	if (head == NULL) // se lista est� vazia
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
		printf("ID: %d, ID Trabalho: %d, Posi��o: %d;\n", current->id, current->jobID, current->position);
		current = current->next;
	}

	return true;
}

bool searchOperation(Operation* head, int id)
{
	if (head == NULL) // se lista est� vazia
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

// obter o m�nimo de tempo necess�rio para completo um job e as respetivas execu��es de opera��es
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

	while (currentOperation != NULL) // percorrer lista de opera��es
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo � opera��o
		{
			while (currentExecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (currentExecution->operationID == currentOperation->id) // se encontrar a execuca��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com menor tempo de utiliza��o
					if (currentExecution->runtime < time)
					{
						time = currentExecution->runtime;
						minExecution = newExecution(currentExecution->operationID, currentExecution->machineID, currentExecution->runtime);
					}
				}

				currentExecution = currentExecution->next;
			}

			*minExecutions = insertExecutionAtStart(*minExecutions, minExecution);

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			freeExecutions(currentExecution);
			currentExecution = NULL;
			currentExecution = executions;
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 99990; // resetar tempo para a pr�xima itera��o
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// obter o m�ximo de tempo necess�rio para completo um job e as respetivas execu��es de opera��es
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

	while (currentOperation != NULL) // percorrer lista de opera��es
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo � opera��o
		{
			while (currentExecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (currentExecution->operationID == currentOperation->id) // se encontrar a execuca��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com maior tempo de utiliza��o
					if (currentExecution->runtime > time)
					{
						time = currentExecution->runtime;
						maxExecution = newExecution(currentExecution->operationID, currentExecution->machineID, currentExecution->runtime);
					}
				}

				currentExecution = currentExecution->next;
			}

			*maxExecutions = insertExecutionAtStart(*maxExecutions, maxExecution);

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			freeExecutions(currentExecution);
			currentExecution = NULL;
			currentExecution = executions;
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 0; // resetar tempo de utiliza��o para a pr�xima itera��o
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}

// Obter a m�dia de tempo necess�rio para completar uma opera��o, considerando todas as alternativas poss�veis
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
		if (current->operationID == operationID) // se encontrar a execuca��o de opera��o relativa � opera��o
		{
			sum += current->runtime;
			numberOfExecutions++;
		}
		current = current->next;
	}

	if (numberOfExecutions > 0) // para n�o permitir divis�o por 0
	{
		average = sum / numberOfExecutions;
	}

	return average;
}