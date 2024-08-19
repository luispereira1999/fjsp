/**
 * @brief	Ficheiro com todas as funções relativas às operações.
 * @file	operations.c
 * @author	Luís Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief	Criar nova operação
 * @param	operationID		Identificador da operação
 * @param	jobID			Identificador do trabalho
 * @param	position		Ordem da operação a ser executada
 * @param	name			Nome da operação
 * @return	Nova operação
*/
Operation* newOperation(int operationID, int jobID, int position, const char* name)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se não houver memória para alocar
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
 * @brief	Inserir nova operação no início da lista de operações
 * @param	head	Lista de operações
 * @param	new		Nova operação
 * @return	Lista de operações atualizada
*/
Operation* insertOperation_AtStart(Operation* head, Operation* new)
{
	if (searchOperation(head, new->operationID)) // não permitir inserir uma nova com o mesmo ID
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
 * @brief	Atualizar a posição de uma operação X pela posição de uma operação Y e, vice-versa
 * @param	head			Apontador para a lista de execuções de operações
 * @param	xOperationID	Identificador de uma operação qualquer X
 * @param	yOperationID	Identificador de uma operação qualquer Y
 * @return	Booleano para o resultado da função (se funcionou ou não)
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

	if (xOperation == NULL || yOperation == NULL) // se as operações não foram encontradas
	{
		return false;
	}

	Operation* current = *head;

	while (current != NULL)
	{
		if (current->operationID == xOperation->operationID) // trocar a posição da operação X pela posição da operação Y
		{
			current->position = yOperation->position;
		}
		if (current->operationID == yOperation->operationID) // trocar a posição da operação Y pela posição da operação X
		{
			current->position = xOperation->position;
		}

		current = current->next;
	}

	return true;
}


/**
 * @brief	Remover uma operação da lista de operações
 * @param	head			Apontador para a lista de operações
 * @param	operationID		Identificador da operação
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteOperation(Operation** head, int operationID)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* current = *head;
	Operation* previous = NULL;

	if (current != NULL && current->operationID == operationID) { // se o elemento que será apagado é o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->operationID != operationID) // procurar o elemento a ser apagado
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


/**
 * @brief	Remover operação pelo identificador do trabalho
 * @param	head			Apontador para a lista de operações
 * @param	jobID			Identificador do trabalho
 * @return	Inteiro com o identificador da operação removida
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

	if (current != NULL && current->jobID == jobID) { // se o elemento que será apagado é o primeiro da lista
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

	if (current == NULL) // se o elemento não foi encontrado
	{
		return -1;
	}

	operationDeleted = current->operationID;
	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return operationDeleted;
}


/**
 * @brief	Ler lista de operações a partir do código
 * @return	A lista de operações
*/
Operation* readOperations_Example()
{
	Operation* operations = NULL;
	Operation* operation = NULL;

	// operações para o trabalho 1
	operation = newOperation(1, 1, 1, "Operação J1-O1");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(2, 1, 2, "Operação J1-O2");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(3, 1, 3, "Operação J1-O3");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(4, 1, 4, "Operação J1-04");
	operations = insertOperation_AtStart(operations, operation);
	
	// operações para o trabalho 2
	operation = newOperation(5, 2, 1, "Operação J2-01");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(6, 2, 2, "Operação J2-02");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(7, 2, 3, "Operação J2-03");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(8, 2, 4, "Operação J2-04");
	operations = insertOperation_AtStart(operations, operation);
	
	// operações para o trabalho 3
	operation = newOperation(12, 3, 1, "Operação J3-01");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(13, 3, 2, "Operação J3-02");
	operations = insertOperation_AtStart(operations, operation);
	
	// operações para o trabalho 4
	operation = newOperation(14, 4, 1, "Operação J4-01");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(15, 4, 2, "Operação J4-02");
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(16, 4, 3, "Operação J4-03");
	operations = insertOperation_AtStart(operations, operation);

	return operations; // 13 operações
}


/**
 * @brief	Ler lista de operações de ficheiro binário
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	Lista de operações
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
	FileOperation currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileOperation), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newOperation(currentInFile.operationID, currentInFile.jobID, currentInFile.position, currentInFile.name);
		head = insertOperation_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief	Carrega dados dos operações de um ficheiro .csv para uma lista em memória
 * @param	fileName	Nome do ficheiro
 * @return	A lista de operações do ficheiro .csv
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
		if (sscanf(line, "%d;%d;%d;%99[^\n]", &operationID, &jobID, &position, name) == 4) // ignora o cabeçalho do .csv
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
 * @brief	Armazenar lista de operações em ficheiro binário
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
	FileOperation currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

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
 * @brief	Armazenar lista de operações em ficheiro de texto
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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

	fprintf(file, "ID da Operação;ID do Trabalho;Posição;Nome\n"); // escreve o cabeçalho do .csv

	while (current != NULL)
	{
		// usa aspas ao redor do nome para garantir que não haja problemas com caracteres especiais
		fprintf(file, "%d;%d;%d;%s\n", current->operationID, current->jobID, current->position, current->name);
		current = current->next;
	}

	fclose(file);

	return true;
}



/**
 * @brief	Mostrar a lista de operações na consola
 * @param	head	Lista de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
		printf("ID da operação: %d, ID do Trabalho: %d, Posição: %d, Nome: %s;\n", current->operationID, current->jobID, current->position, current->name);
		current = current->next;
	}

	return true;
}


/**
 * @brief	Procurar por uma operação na lista de operações
 * @param	head			Lista de operações
 * @param	operationID		Identificador da operação
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @brief	Procurar por uma operação através do identificador do trabalho, na lista de operações
 * @param	head	Lista de operações
 * @param	jobID	Identificador do trabalho
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @brief	Obter uma operação da lista de operações
 * @param	head			Lista de operações
 * @param	operationID		Identificador da operação
 * @return	Operação encontrada (ou NULL se não encontrou)
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
			Operation* operation = newOperation(current->operationID, current->jobID, current->position, current->name); // criar cópia da operação
			return operation;
		}
		current = current->next;
	}

	return NULL;
}


/**
 * @brief	Obter o mínimo de tempo necessário para completo um trabalho e as respetivas execuções
 * @param	operations		Lista de operações
 * @param	executions		Lista de execuções de operações
 * @param	jobID			Identificador do trabalho
 * @param	minExecutions	Apontador para a lista de execuções de operações a ser devolvida, relativamente ao tempo mínimo
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

	while (currentOperation != NULL) // percorrer lista de operações
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (currentExecution != NULL) // percorrer lista de execuções de operações
			{
				if (currentExecution->operationID == currentOperation->operationID) // se encontrar a execução de operação relativa à operação
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

			*minExecutions = insertExecution_AtStart_AtList(*minExecutions, minExecution);

			// repor lista percorrida (currentExecution), para que se for necessário voltar a percorrer o while das execuções de operações de novo
			currentExecution = NULL;
			currentExecution = executions;

			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 999; // resetar tempo para a próxima iteração
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}


/**
 * @brief	Obter o máximo de tempo necessário para completo um trabalho e as respetivas execuções
 * @param	operations		Lista de operações
 * @param	executions		Lista de execuções de operações
 * @param	jobID			Identificador do trabalho
 * @param	maxExecutions	Apontador para a lista de execuções de operações a ser devolvida, relativamente ao tempo máximo
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

	while (currentOperation != NULL) // percorrer lista de operações
	{
		if (currentOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (currentExecution != NULL) // percorrer lista de execuções de operações
			{
				if (currentExecution->operationID == currentOperation->operationID) // se encontrar a execução de operação relativa à operação
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

			*maxExecutions = insertExecution_AtStart_AtList(*maxExecutions, maxExecution);

			// repor lista percorrida (currentExecution), para que se for necessário voltar a percorrer o while da execuções de operações de novo
			currentExecution = NULL;
			currentExecution = executions;

			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 0; // resetar tempo de utilização para a próxima iteração
		}

		currentOperation = currentOperation->next;
	}

	return counter;
}


/**
 * @brief	Obter a média de tempo necessário para completar uma operação, considerando todas as alternativas possíveis
 * @param	head			Lista de execuções de operações
 * @param	operationID		Identificador da operação
 * @return	Valor da média de tempo
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
		if (current->operationID == operationID) // se encontrar a execução de operação relativa à operação
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


/**
 * @brief	Limpar a lista de operações da memória
 * @param	head	Lista de operações
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