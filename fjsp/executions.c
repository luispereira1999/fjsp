/**
 * @brief	Ficheiro com todas as fun��es relativas �s execu��es de opera��es com listas e hash table.
 * @file	executions.c
 * @author	Lu�s Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"
#include "hashing.h"


#pragma region listas

/**
 * @brief	Criar nova execu��o
 * @param	operationID		Identificador da opera��o
 * @param	machineID		Identificador da m�quina
 * @param	runtime			Unidades de tempo necess�rias para a execu��o da opera��o
 * @return	Nova execu��o
*/
Execution* newExecution(int operationID, int machineID, int runtime)
{
	Execution* new = (Execution*)malloc(sizeof(Execution));
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


/**
 * @brief	Inserir nova execu��o no in�cio da lista de execu��es de opera��es
 * @param	head	Lista de execu��es de opera��es
 * @param	new		Nova execu��o
 * @return	Lista de execu��es de opera��es atualizada
*/
Execution* insertExecution_AtStart_AtList(Execution* head, Execution* new)
{
	if (searchExecution_AtList(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
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
 * @brief	Inserir execu��o ordenada pelo ID da opera��o na lista de execu��es
 * @param	head	Lista de execu��es de opera��es
 * @param	new		Nova execu��o
 * @return	Lista de execu��es de opera��es atualizada
*/
Execution* insertExecution_ByOperation_AtList(Execution* head, Execution* new)
{
	if (searchExecution_AtList(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
	{
		return NULL;
	}

	if (head == NULL)
	{
		head = new; // inserir no in�cio
	}
	else
	{
		Execution* current = head;
		Execution* previous = NULL;

		// enquanto que atual tem o ID menor que a nova
		while (current != NULL && current->operationID < new->operationID)
		{
			previous = current;
			current = current->next;
		}

		if (previous == NULL)
		{
			new->next = head;
			head = new; // inserir no meio
		}
		else
		{
			previous->next = new;
			new->next = current; // inserir no fim
		}
	}

	return head;
}


/**
 * @brief	Atualizar as unidades de tempo necess�rias para a execu��o de uma opera��o
 * @param	head			Apontador para a lista de execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @param	machineID		Identificador da m�quina
 * @param	runtime			Unidades de tempo
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updateRuntime_AtList(Execution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL)
	{
		return false;
	}

	if (!searchExecution_AtList(*head, operationID, machineID)) // se n�o existir a execu��o para remover
	{
		return false;
	}

	Execution* current = *head;

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


/**
 * @brief	Remover execu��o pelo identificador da opera��o
 * @param	head			Apontador para a lista de execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteExecution_ByOperation_AtList(Execution** head, int operationID)
{
	if (*head == NULL)
	{
		return false;
	}

	if (!searchExecution_ByOperation_AtList(*head, operationID)) // se n�o existir a execu��o para remover
	{
		return false;
	}

	Execution* current = *head;
	Execution* previous = NULL;

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
 * @brief	Ler lista de execu��es de opera��es a partir do c�digo
 * @return	A lista de execu��es de opera��es
*/
Execution* readExecutions_AtList_Example()
{
	Execution* executions = NULL;
	Execution* execution = NULL;

	// execu��es de opera��es do trabalho 1
	execution = newExecution(1, 1, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(1, 3, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(2, 2, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(2, 4, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(3, 3, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(3, 4, 6);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(4, 2, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(4, 3, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(4, 4, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);

	// execu��es de opera��es do trabalho 2
	execution = newExecution(5, 1, 1);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(5, 4, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(6, 2, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(6, 4, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(7, 1, 1);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(7, 2, 6);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(8, 1, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(8, 2, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(8, 3, 7);
	executions = insertExecution_AtStart_AtList(executions, execution);

	// execu��es de opera��es do trabalho 3
	execution = newExecution(9, 2, 7);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(9, 3, 6);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(9, 4, 8);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(10, 1, 7);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(10, 2, 7);
	executions = insertExecution_AtStart_AtList(executions, execution);

	// execu��es de opera��es do trabalho 4
	execution = newExecution(11, 1, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(11, 3, 3);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(11, 4, 7);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(12, 2, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(12, 3, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(13, 1, 4);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(13, 2, 5);
	executions = insertExecution_AtStart_AtList(executions, execution);
	execution = newExecution(13, 3, 6);
	executions = insertExecution_AtStart_AtList(executions, execution);

	return executions; // 31 execu��es de opera��es
}


/**
 * @brief	Ler lista de execu��es de opera��es de ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	Lista de execu��es de opera��es
*/
Execution* readExecutions_AtList_Binary(char fileName[])
{
	FILE* file = NULL;
	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Execution* head = NULL;
	Execution* current = NULL;
	FileExecution currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileExecution), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newExecution(currentInFile.operationID, currentInFile.machineID, currentInFile.runtime);
		head = insertExecution_AtStart_AtList(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief Carrega dados das execu��es de opera��es de um ficheiro .csv para uma lista em mem�ria
 * @param fileName		Nome do ficheiro
 * @return A lista de execu��es de opera��es do ficheiro .csv
*/
Execution* readExecutions_AtList_Text(char fileName[])
{
	char line[FILE_LINE_SIZE];
	int a = 0, b = 0, c = 0;

	Execution* execution = NULL;
	Execution* executions = NULL;

	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	while (!feof(file))
	{
		if (fgets(line, FILE_LINE_SIZE, file) != NULL)
		{
			sscanf(line, "%d;%d;%d", &a, &b, &c);
			execution = newExecution(a, b, c);
			executions = insertExecution_AtStart_AtList(executions, execution);
		}
	}

	fclose(file);

	return executions;
}


/**
 * @brief	Armazenar lista de execu��es de opera��es em ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions_AtList_Binary(char fileName[], Execution* head)
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

	Execution* current = head;
	FileExecution currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.operationID = current->operationID;
		currentInFile.machineID = current->machineID;
		currentInFile.runtime = current->runtime;

		fwrite(&currentInFile, sizeof(FileExecution), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Armazenar lista de execu��es de opera��es em ficheiro de texto
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions_AtList_Text(char fileName[], Execution* head)
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

	Execution* current = head;

	fprintf(file, "ID da Opera��o;ID da M�quina;Tempo de Execu��o\n"); // escreve o cabe�alho do .csv

	while (current != NULL)
	{
		fprintf(file, "%d;%d;%d\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Mostrar a lista de execu��es de opera��es na consola
 * @param	head	Lista de execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayExecutions_AtList(Execution* head)
{
	if (head == NULL)
	{
		return false;
	}

	Execution* current = head;

	while (current != NULL)
	{
		printf("ID da Opera��o: %d, ID da M�quina: %d, Tempo de Execu��o: %d;\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	return true;
}


/**
 * @brief	Procurar por uma execu��o na lista de execu��es de opera��es
 * @param	head			Lista de execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @param	machineID		Identificador da m�quina
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchExecution_AtList(Execution* head, int operationID, int machineID)
{
	if (head == NULL)
	{
		return false;
	}

	Execution* current = head;

	while (current != NULL)
	{
		if (current->operationID == operationID && current->machineID == machineID)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}


/**
 * @brief	Procurar por uma execu��o atrav�s do identificador da opera��o, na lista de execu��es
 * @param	head			Lista de execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchExecution_ByOperation_AtList(Execution* head, int operationID)
{
	if (head == NULL)
	{
		return false;
	}

	Execution* current = head;

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
 * @brief	Ordenar lista de execu��es de opera��es por ordem crescente do identificador da opera��o
 * @param	head			Lista de execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
Execution* sortExecutions_ByOperation_AtList(Execution* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	Execution* current = head;
	Execution* sorted = NULL;
	Execution* new = NULL;

	while (current != NULL)
	{
		new = newExecution(current->operationID, current->machineID, current->runtime);
		sorted = insertExecution_ByOperation_AtList(sorted, new);
		current = current->next;
	}

	return sorted;
}


/**
 * @brief	Obter uma execu��o na lista de execu��es de opera��es
 * @param	head			Lista de execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @param	machineID		Identificador da m�quina
 * @return	Execu��o encontrada (ou NULL se n�o encontrou)
*/
Execution* getExecution_AtList(Execution* head, int operationID, int machineID)
{
	if (head == NULL)
	{
		return NULL;
	}

	Execution* current = head;

	while (current != NULL)
	{
		if (current->operationID == operationID && current->machineID == machineID)
		{
			return current;
		}
		current = current->next;
	}

	return NULL;
}


/**
 * @brief	Obter a �ltima execu��o de uma lista de execu��es de opera��es
 * @param	head			Lista de execu��es de opera��es
 * @return	�ltima execu��o da lista
*/
Execution* getLastExecution_AtList(Execution* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	Execution* current = head;

	while (current->next != NULL) // enquanto o pr�ximo elemento for nulo
	{
		current = current->next;
	}

	return current;
}


/**
 * @brief	Limpar a lista de execu��es de opera��es da mem�ria
 * @param	head	Lista de execu��es de opera��es
*/
bool cleanExecutions_List(Execution** head)
{
	if (head != NULL && *head != NULL)
	{
		Execution* current;

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

#pragma endregion


#pragma region hashing

/**
 * @brief	Criar n� vazio para uma posi��o da tabela hash das execu��es de opera��es
 * @return	N� vazio da tabela hash das execu��es de opera��es criado
*/
ExecutionNode* createExecutionNode()
{
	ExecutionNode* node = malloc(sizeof(ExecutionNode));

	node->start = NULL;
	node->numberOfExecutions = 0;

	return node;
}


/**
 * @brief	Criar tabela hash das execu��es de opera��es vazia
 * @param	table	Tabela hash das execu��es de opera��es
 * @return	Tabela hash das execu��es de opera��es criada
*/
ExecutionNode** createExecutionsTable(ExecutionNode* table[])
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		table[i] = createExecutionNode();
	}

	return *table;
}


/**
 * @brief	Gerar hash atrav�s de uma fun��o.
 *			A fun��o � representada pelo resto da divis�o do identificador da opera��o pelo tamanho da tabela
 * @param	operationID		Identificador da opera��o
 * @return	Valor calculado pela fun��o hash
*/
int generateHash(int operationID)
{
	return operationID % HASH_TABLE_SIZE;
}


/**
 * @brief	Inserir nova execu��o na tabela hash das execu��es de opera��es, numa determinada posi��o
 * @param	table	Tabela hash das execu��es de opera��es
 * @return	Tabela hash das execu��es de opera��es atualizada
*/
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new)
{
	int index = generateHash(new->operationID);
 
	table[index]->start = insertExecution_AtStart_AtList(table[index]->start, new);
	table[index]->numberOfExecutions++;

	return *table;
}


/**
 * @brief	Atualizar as unidades de tempo necess�rias para a execu��o de uma opera��o na tabela hash
 * @param	table			Tabela hash das execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @param	machineID		Identificador da m�quina
 * @param	runtime			Unidades de tempo
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime)
{
	ExecutionNode** current = table;

	int index = generateHash(operationID);
	bool updated = updateRuntime_AtList(&current[index]->start, operationID, machineID, runtime);

	return updated;
}


/**
 * @brief	Remover todas as execu��es de opera��es pelo identificador da opera��o na tabela
 * @param	table			Tabela hash das execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID)
{
	ExecutionNode** current = table;

	int index = generateHash(operationID);
	if (index <= -1)
	{
		return false;
	}

	bool deleted = false;

	do
	{
		// enquanto que remover, significa que ainda existe opera��es e portanto continuar� a remover, at� remover todas
		deleted = deleteExecution_ByOperation_AtList(&current[index]->start, operationID);

		if (deleted)
		{
			current[index]->numberOfExecutions--;
		}
	} while (deleted == true);

	return deleted;
}


/**
 * @brief	Ler tabela hash de execu��es de opera��es a partir do c�digo
 * @param	table	Tabela hash das execu��es de opera��es
 * @return	A tabela hash de execu��es de opera��es
*/
ExecutionNode** readExecutions_AtTable_Example(ExecutionNode* table[])
{
	// iniciar tabela hash vazia
	*table = createExecutionsTable(table);

	Execution* execution = NULL;

	// execu��es de opera��es do trabalho 1
	execution = newExecution(1, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(1, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(2, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(2, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(3, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(3, 4, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 2, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 4, 4);
	*table = insertExecution_AtTable(table, execution);

	// execu��es de opera��es do trabalho 2
	execution = newExecution(5, 1, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(5, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(6, 2, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(6, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(7, 1, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(7, 2, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 3, 7);

	// execu��es de opera��es do trabalho 3
	execution = newExecution(9, 2, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(9, 3, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(9, 4, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 1, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 2, 7);
	*table = insertExecution_AtTable(table, execution);

	// execu��es de opera��es do trabalho 4
	execution = newExecution(11, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(11, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(11, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(12, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(12, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 2, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 3, 6);
	*table = insertExecution_AtTable(table, execution);

	return *table; // 38 execu��es de opera��es
}


/**
 * @brief	Armazenar os registos de todas as listas de execu��es de opera��es na tabela hash, em ficheiro bin�rio
 * @brief	Ler de ficheiro bin�rio, os registos de todas as execu��es de opera��es para a tabela hash
 * @param	fileName	Nome do ficheiro para ler a lista
 * @param	table		Tabela hash de execu��es de opera��es
 * @return	Tabela hash de execu��es de opera��es
*/
ExecutionNode** readExecutions_AtTable_Binary(char fileName[], ExecutionNode* table[])
{
	FILE* file = NULL;
	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	// iniciar tabela hash vazia
	*table = createExecutionsTable(table);

	Execution* execution = NULL;
	Execution* list = NULL;
	list = readExecutions_AtList_Binary(fileName);

	if (list == NULL) // erro ao ler dados do ficheiro
	{
		return NULL;
	}

	while (list != NULL) // enquanto que houver dados na lista, guarda-os na tabela
	{
		execution = newExecution(list->operationID, list->machineID, list->runtime);
		*table = insertExecution_AtTable(table, execution);

		list = list->next;
	}

	return *table;
}


/**
 * @brief Carregar dados das execu��es de opera��es um ficheiro .csv para uma tabela hash em mem�ria
 * @param	fileName	Nome do ficheiro
 * @param	table		Tabela hash de execu��es de opera��es
 * @return A tabela hash de execu��es de opera��es do ficheiro .csv
*/
ExecutionNode** readExecutions_AtTable_Text(char fileName[], ExecutionNode* table[])
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	// iniciar tabela hash vazia
	*table = createExecutionsTable(table);

	char line[FILE_LINE_SIZE];
	int operationID = 0, machineID = 0, runtime = 0;

	Execution* execution = NULL;

	while (!feof(file))
	{
		if (fgets(line, FILE_LINE_SIZE, file) != NULL)
		{
			// exemplo: 1;1;1
			sscanf(line, "%d;%d;%d", &operationID, &machineID, &runtime);

			execution = newExecution(operationID, machineID, runtime);
			*table = insertExecution_AtTable(table, execution);
		}
	}

	fclose(file);

	return *table;
}


/**
 * @brief	Armazenar os registos de todas as listas de execu��es de opera��es na tabela hash, em ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para armazenar os registos
 * @param	table		Tabela hash de execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions_AtTable_Binary(char fileName[], ExecutionNode* table[])
{
	if (table == NULL || *table == NULL)
	{
		return false;
	}

	FILE* file = NULL;
	if ((file = fopen(fileName, "wb")) == NULL) // erro ao abrir o ficheiro
	{
		return false;
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		Execution* current = table[i]->start;
		FileExecution currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

		while (current != NULL)
		{
			currentInFile.operationID = current->operationID;
			currentInFile.machineID = current->machineID;
			currentInFile.runtime = current->runtime;
			fwrite(&currentInFile, sizeof(FileExecution), 1, file); // guarda cada registo da lista no ficheiro

			current = current->next;
		}
	}

	fclose(file);

	return true;
}


/**
 * @brief	Armazenar os registos de todas as listas de execu��es de opera��es na tabela hash, em ficheiro .csv
 * @param	fileName	Nome do ficheiro para armazenar os registos
 * @param	table		Tabela hash das execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions_AtTable_Text(char fileName[], ExecutionNode* table[])
{
	if (table == NULL || *table == NULL)
	{
		return false;
	}

	FILE* file = NULL;
	if ((file = fopen(fileName, "w")) == NULL) // erro ao abrir o ficheiro
	{
		return false;
	}

	fprintf(file, "ID da Opera��o;ID da M�quina;Tempo de Execu��o\n"); // escreve o cabe�alho do .csv

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		Execution* current = table[i]->start;

		while (current != NULL)
		{
			fprintf(file, "%d;%d;%d\n", current->operationID, current->machineID, current->runtime);
			current = current->next;
		}
	}

	fclose(file);

	return true;
}


/**
 * @brief	Mostrar a tabela hash com as listas de execu��es de opera��es na consola
 * @param	table	Tabela hash das execu��es de opera��es
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayExecutions_AtTable(ExecutionNode* table[])
{
	if (table == NULL || *table == NULL)
	{
		return false;
	}

	bool hasData = false;

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (table[i] != NULL && table[i]->start != NULL)
		{
			hasData = true;
			printf("Lista %d - N�mero de elementos: %d\n", i + 1, table[i]->numberOfExecutions);
			displayExecutions_AtList(table[i]->start);
		}
	}

	return hasData;
}


/**
 * @brief	Procurar por uma execu��o na tabela hash
 * @param	table			Tabela hash das execu��es de opera��es
 * @param	operationID		Identificador da opera��o
 * @param	machineID		Identificador da m�quina
 * @return	Execu��o encontrada ou retorna nulo se n�o encontrar
*/
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID)
{
	if (table == NULL)
	{
		return NULL;
	}

	int index = generateHash(operationID);
	Execution* executionFound = getExecution_AtList(table[index]->start, operationID, machineID);

	if (executionFound == NULL)
	{
		return NULL;
	}

	return executionFound;
}


/**
 * @brief	Limpar a tabela hash de execu��es de opera��es da mem�ria
 * @param	table	Lista de execu��es de opera��es
 * @return	Tabela hash libertada da mem�ria
*/
bool cleanExecutions_Table(ExecutionNode** table[])
{
	if (table != NULL && *table != NULL)
	{
		for (int i = 0; i < HASH_TABLE_SIZE; i++)
		{
			ExecutionNode* current = (*table)[i];
			if (current != NULL)
			{
				cleanExecutions_List(&(current->start));

				free(current);

				(*table)[i] = NULL;
			}
		}

		*table = NULL;

		return true;
	}

	return false;
}

#pragma endregion