/**
 * @brief	Ficheiro com todas as fun��es relativas �s opera��es.
 * @file	operations.c
 * @author	Lu�s Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief	Criar nova opera��o
 * @param	operationID		Identificador da opera��o
 * @param	jobID			Identificador do trabalho
 * @param	position		Ordem da opera��o a ser executada
 * @param	name			Nome da opera��o
 * @return	Nova opera��o
*/
Operation* newOperation(int operationID, int jobID, int position, const char* name)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->jobID = jobID;
	new->position = position;
	strncpy(new->name, name, NAME_SIZE - 1);
	new->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
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
	if (searchOperation(head, new->operationID)) // n�o permitir inserir uma nova com o mesmo ID
	{
		return NULL;
	}

	if (head == NULL)
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
 * @brief	Atualizar a posi��o de uma opera��o X pela posi��o de uma opera��o Y e, vice-versa
 * @param	head			Apontador para a lista de execu��es de opera��es
 * @param	xOperationID	Identificador de uma opera��o qualquer X
 * @param	yOperationID	Identificador de uma opera��o qualquer Y
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updateOperation_Position(Operation** head, int xOperationID, int yOperationID)
{
	if (*head == NULL)
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
		if (current->operationID == xOperation->operationID) // trocar a posi��o da opera��o X pela posi��o da opera��o Y
		{
			current->position = yOperation->position;
		}
		if (current->operationID == yOperation->operationID) // trocar a posi��o da opera��o Y pela posi��o da opera��o X
		{
			current->position = xOperation->position;
		}

		current = current->next;
	}

	return true;
}


/**
 * @brief	Remover uma opera��o da lista de opera��es
 * @param	head			Apontador para a lista de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteOperation(Operation** head, int operationID)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* current = *head;
	Operation* previous = NULL;

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


/**
 * @brief	Remover opera��o pelo identificador do trabalho
 * @param	head			Apontador para a lista de opera��es
 * @param	jobID			Identificador do trabalho
 * @return	Inteiro com o identificador da opera��o removida
*/
int deleteOperation_ByJob(Operation** head, int jobID)
{
	if (*head == NULL)
	{
		return -1;
	}

	Operation* current = *head;
	Operation* previous = NULL;
	int operationDeleted = 0;

	if (current != NULL && current->jobID == jobID) { // se o elemento que ser� apagado � o primeiro da lista
		operationDeleted = current->operationID;
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

	operationDeleted = current->operationID;
	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return operationDeleted;
}


/**
 * @brief	Ler lista de opera��es a partir do c�digo
 * @return	A lista de opera��es
*/
Operation* readOperations_Example()
{
	Operation* operations = NULL;
	Operation* operation = NULL;

	// opera��es para o trabalho 1
	operation = newOperation(1, 1, 1, "Opera��o J1-O1");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(2, 1, 2, "Opera��o J1-O2");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(3, 1, 3, "Opera��o J1-O3");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(4, 1, 4, "Opera��o J1-04");
	operations = insertOperation_AtStart(operations, operation);
	
	// opera��es para o trabalho 2
	operation = newOperation(5, 2, 1, "Opera��o J2-01");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(6, 2, 2, "Opera��o J2-02");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(7, 2, 3, "Opera��o J2-03");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(8, 2, 4, "Opera��o J2-04");
	operations = insertOperation_AtStart(operations, operation);
	
	// opera��es para o trabalho 3
	operation = newOperation(12, 3, 1, "Opera��o J3-01");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(13, 3, 2, "Opera��o J3-02");
	operations = insertOperation_AtStart(operations, operation);
	
	// opera��es para o trabalho 4
	operation = newOperation(14, 4, 1, "Opera��o J4-01");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(15, 4, 2, "Opera��o J4-02");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(16, 4, 3, "Opera��o J4-03");
	operations = insertOperation_AtStart(operations, operation);

	return operations; // 13 opera��es
}


/**
 * @brief	Ler lista de opera��es de ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	Lista de opera��es
*/
Operation* readOperations_Binary(char fileName[])
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
		current = newOperation(currentInFile.operationID, currentInFile.jobID, currentInFile.position, currentInFile.name);
		head = insertOperation_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief	Carrega dados dos opera��es de um ficheiro .csv para uma lista em mem�ria
 * @param	fileName	Nome do ficheiro
 * @return	A lista de opera��es do ficheiro .csv
*/
Operation* readOperations_Text(char fileName[])
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	char line[FILE_LINE_SIZE];
	int operationID = 0;
	int jobID = 0;
	int position = 0;
	char name[NAME_SIZE];

	Operation* operation = NULL;
	Operation* operations = NULL;

	while (fgets(line, FILE_LINE_SIZE, file) != NULL)
	{
		if (sscanf(line, "%d;%d;%d;%99[^\n]", &operationID, &jobID, &position, name) == 4) // ignora o cabe�alho do .csv
		{
			operation = (Operation*)malloc(sizeof(Operation));
			if (operation == NULL)
			{
				fclose(file);
				return NULL;
			}

			operation->operationID = operationID;
			operation->jobID = jobID;
			operation->position = position;
			strncpy(operation->name, name, NAME_SIZE - 1);
			operation->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
			operation->next = operations;

			operations = operation;
		}
	}

	fclose(file);

	return operations;
}


/**
 * @brief	Armazenar lista de opera��es em ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeOperations_Binary(char fileName[], Operation* head)
{
	if (head == NULL)
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
		currentInFile.operationID = current->operationID;
		currentInFile.jobID = current->jobID;
		currentInFile.position = current->position;
		strncpy(currentInFile.name, current->name, NAME_SIZE);

		fwrite(&currentInFile, sizeof(FileOperation), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Armazenar lista de opera��es em ficheiro de texto
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeOperations_Text(char fileName[], Operation* head)
{
	if (head == NULL)
	{
		return false;
	}

	FILE* file = NULL;
	if ((file = fopen(fileName, "w")) == NULL) // erro ao abrir o ficheiro
	{
		return false;
	}

	Operation* current = head;

	fprintf(file, "ID da Opera��o;ID do Trabalho;Posi��o;Nome\n"); // escreve o cabe�alho do .csv

	while (current != NULL)
	{
		// usa aspas ao redor do nome para garantir que n�o haja problemas com caracteres especiais
		fprintf(file, "%d;%d;%d;%s\n", current->operationID, current->jobID, current->position, current->name);
		current = current->next;
	}

	fclose(file);

	return true;
}



/**
 * @brief	Mostrar a lista de opera��es na consola
 * @param	head	Lista de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayOperations(Operation* head)
{
	if (head == NULL)
	{
		return false;
	}

	Operation* current = head;

	while (current != NULL)
	{
		printf("ID da opera��o: %d, ID do Trabalho: %d, Posi��o: %d, Nome: %s;\n", current->operationID, current->jobID, current->position, current->name);
		current = current->next;
	}

	return true;
}


/**
 * @brief	Procurar por uma opera��o na lista de opera��es
 * @param	head			Lista de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchOperation(Operation* head, int operationID)
{
	if (head == NULL)
	{
		return false;
	}

	Operation* current = head;

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


/**
 * @brief	Procurar por uma opera��o atrav�s do identificador do trabalho, na lista de opera��es
 * @param	head	Lista de opera��es
 * @param	jobID	Identificador do trabalho
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchOperation_ByJob(Operation* head, int jobID)
{
	if (head == NULL)
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
 * @param	head			Lista de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Opera��o encontrada (ou NULL se n�o encontrou)
*/
Operation* getOperation(Operation* head, int operationID)
{
	if (head == NULL)
	{
		return NULL;
	}

	Operation* current = head;

	while (current != NULL)
	{
		if (current->operationID == operationID)
		{
			Operation* operation = newOperation(current->operationID, current->jobID, current->position, current->name); // criar c�pia da opera��o
			return operation;
		}
		current = current->next;
	}

	return NULL;
}


/**
 * @brief	Obter o m�nimo de tempo necess�rio para completo um trabalho e as respetivas execu��es
 * @param	operations		Lista de opera��es
 * @param	executions		Lista de execu��es de opera��es
 * @param	jobID			Identificador do trabalho
 * @param	minExecutions	Apontador para a lista de execu��es de opera��es a ser devolvida, relativamente ao tempo m�nimo
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
			while (currentExecution != NULL) // percorrer lista de execu��es de opera��es
			{
				if (currentExecution->operationID == currentOperation->operationID) // se encontrar a execu��o de opera��o relativa � opera��o
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

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while das execu��es de opera��es de novo
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
 * @param	executions		Lista de execu��es de opera��es
 * @param	jobID			Identificador do trabalho
 * @param	maxExecutions	Apontador para a lista de execu��es de opera��es a ser devolvida, relativamente ao tempo m�ximo
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
			while (currentExecution != NULL) // percorrer lista de execu��es de opera��es
			{
				if (currentExecution->operationID == currentOperation->operationID) // se encontrar a execu��o de opera��o relativa � opera��o
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

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��es de opera��es de novo
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
 * @param	head			Lista de execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Valor da m�dia de tempo
*/
float getAverageTime_ToCompleteOperation(Execution* head, int operationID)
{
	if (head == NULL)
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


/**
 * @brief	Limpar a lista de opera��es da mem�ria
 * @param	head	Lista de opera��es
*/
bool cleanOperations(Operation** head)
{
	if (head != NULL && *head != NULL)
	{
		Operation* current;

		while (*head)
		{
			current = *head;
			*head = (*head)->next;
			free(current);
		}

		return true;
	}

	return false;
}