/**
 * @brief	Ficheiro com todas as fun��es relativas �s opera��es
 * @file	operations.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
* @brief	Criar nova opera��o
* @param	id			Identificador da opera��o
* @param	jobID		Identificador do trabalho
* @param	position	Posi��o da opera��o relativamente ao trabalho
* @return	Nova opera��o
*/
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


/**
* @brief	Inserir nova opera��o no in�cio da lista de opera��es
* @param	head	Lista de opera��es
* @param	new		Nova opera��o
* @return	Lista de opera��es atualizada
*/
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


/**
* @brief	Remover uma opera��o da lista de opera��es
* @param	head	Apontador para a lista de opera��es
* @param	id		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
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


/**
* @brief	Armazenar lista de opera��es em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeOperations(char fileName[], Operation* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	FILE* file = NULL;

	if ((file = fopen(fileName, "wb")) == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return false;
	}

	Operation* current = head;
	FileOperation currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.id = current->id;
		currentInFile.jobID = current->jobID;
		currentInFile.position = current->position;
		fwrite(&currentInFile, sizeof(FileOperation), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de opera��es de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de opera��es
*/
Operation* readOperations(char fileName[])
{
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	Operation* head = NULL;
	Operation* current = NULL;
	FileOperation currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileOperation), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newOperation(currentInFile.id, currentInFile.jobID, currentInFile.position);
		head = insertOperationAtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Libertar a lista de opera��es da mem�ria
* @param	head	Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
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


/**
* @brief	Mostrar a lista de opera��es na consola
* @param	head	Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
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


/**
* @brief	Procurar por uma opera��o na lista de opera��es
* @param	head	Lista de opera��es
* @param	id		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
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


/**
* @brief	Obter o m�nimo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operations		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	jobID			Identificador do trabalho
* @param	minExecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�nimo
* @return	Quantidade de tempo
*/
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
				if (currentExecution->operationID == currentOperation->id) // se encontrar a execu��o de opera��o relativa � opera��o
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


/**
* @brief	Obter o m�ximo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operations		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	jobID			Identificador do trabalho
* @param	maxExecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�ximo
* @return	Quantidade de tempo
*/
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
				if (currentExecution->operationID == currentOperation->id) // se encontrar a execu��o de opera��o relativa � opera��o
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


/**
* @brief	Obter a m�dia de tempo necess�rio para completar uma opera��o, considerando todas as alternativas poss�veis
* @param	head			Lista de execu��es
* @param	operationID		Identificador da opera��o
* @return	Valor da m�dia de tempo
*/
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
		if (current->operationID == operationID) // se encontrar a execu��o de opera��o relativa � opera��o
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