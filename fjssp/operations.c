/**
 * @brief	Ficheiro com todas as fun��es relativas �s opera��es
 * @file	operations.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief Carrega dados das opera��es de um ficheiro CSV para uma lista em mem�ria
 * @param fileName		Nome do ficheiro
 * @return A lista de opera��es do ficheiro CSV
 */
Operation* loadOperations(char* fileName)
{
	char line[FILE_LINE_SIZE];
	int a = 0, b = 0, c = 0;

	Operation* operation = NULL;
	Operation* operations = NULL;

	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	while (!feof(file))
	{
		if (fgets(line, FILE_LINE_SIZE, file) != NULL)
		{
			// exemplo: 1;1;1
			sscanf(line, "%d;%d;%d", &a, &b, &c);
			operation = newOperation(a, b, c);
			operations = insertOperation_AtStart(operations, operation);
		}
	}

	fclose(file);

	return operations;
}


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
Operation* insertOperation_AtStart(Operation* head, Operation* new)
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
* @brief	Atualizar a posi��o de uma opera��o X pela posi��o de uma opera��o Y, e vice-versa
* @param	head			Apontador para a lista de execu��es
* @param	xOperationID	Identificador de uma opera��o qualquer X
* @param	yOperationID	Identificador de uma opera��o qualquer Y
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updatePosition(Operation** head, int xOperationID, int yOperationID)
{
	if (*head == NULL) // se lista est� vazia
	{
		return false;
	}

	if (xOperationID == yOperationID) // se forem iguais
	{
		return false;
	}

	Operation* xOperation = NULL;
	Operation* yOperation = NULL;

	xOperation = getOperation(*head, xOperationID);
	yOperation = getOperation(*head, yOperationID);

	if (xOperation == NULL || yOperation == NULL) // se as opera��es n�o foram encontradas
	{
		return false;
	}

	Operation* current = *head;

	while (current != NULL)
	{
		if (current->id == xOperation->id) // trocar a posi��o da opera��o X pela posi��o da opera��o Y
		{
			current->position = yOperation->position;
		}
		if (current->id == yOperation->id) // trocar a posi��o da opera��o Y pela posi��o da opera��o X
		{
			current->position = xOperation->position;
		}

		current = current->next;
	}

	return true;
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
* @brief	Remover opera��o pelo identificador do trabalho
* @param	head			Apontador para a lista de opera��es
* @param	jobID			Identificador do trabalho
* @return	Inteiro com o identificador da opera��o removida
*/
int deleteOperation_ByJob(Operation** head, int jobID)
{
	if (*head == NULL) // se a lista estiver vazia
	{
		return -1;
	}

	Operation* current = *head;
	Operation* previous = NULL;
	int operationDeleted = 0;

	if (current != NULL && current->jobID == jobID) { // se o elemento que ser� apagado � o primeiro da lista
		operationDeleted = current->id;
		*head = current->next;
		free(current);

		return operationDeleted;
	}

	while (current != NULL && current->jobID != jobID) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL) // se o elemento n�o foi encontrado
	{
		return -1;
	}

	operationDeleted = current->id;
	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return operationDeleted;
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

	if ((file = fopen(fileName, "wb")) == NULL) // erro ao abrir o ficheiro
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
	FILE* file = NULL;

	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Operation* head = NULL;
	Operation* current = NULL;
	FileOperation currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileOperation), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newOperation(currentInFile.id, currentInFile.jobID, currentInFile.position);
		head = insertOperation_AtStart(head, current);
	}

	fclose(file);

	return head;
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
* @brief	Procurar por uma opera��o atrav�s do identificador do trabalho, na lista de opera��es
* @param	head			Lista de opera��es
* @param	jobID			Identificador do trabalho
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchOperation_ByJob(Operation* head, int jobID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Operation* current = head;

	while (current != NULL)
	{
		if (current->jobID == jobID)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}


/**
* @brief	Obter uma opera��o da lista de opera��es
* @param	head	Lista de opera��es
* @param	id		Identificador da opera��o
* @return	Opera��o encontrada (ou NULL se n�o encontrou)
*/
Operation* getOperation(Operation* head, int id)
{
	if (head == NULL) // se lista est� vazia
	{
		return NULL;
	}

	Operation* current = head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			Operation* operation = newOperation(current->id, current->jobID, current->position); // criar c�pia da opera��o
			return operation;
		}
		current = current->next;
	}

	return NULL;
}


/**
* @brief	Obter o m�nimo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operations		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	jobID			Identificador do trabalho
* @param	minExecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�nimo
* @return	Quantidade de tempo
*/
int getMinTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions)
{
	if (operations == NULL || executions == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 999;
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

			*minExecutions = insertExecution_AtStart_AtList(*minExecutions, minExecution);

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			currentExecution = NULL;
			currentExecution = executions;
		
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 999; // resetar tempo para a pr�xima itera��o
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
int getMaxTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions)
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

			*maxExecutions = insertExecution_AtStart_AtList(*maxExecutions, maxExecution);

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
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
float getAverageTime_ToCompleteOperation(Execution* head, int operationID)
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