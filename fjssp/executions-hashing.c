/**
 * @brief	Ficheiro com todas as funções relativas às execuções de operações com hash table
 * @file	executions.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"
#include "hashing.h"


/**
 * @brief Carrega dados das execuções de um ficheiro CSV para uma tabela hash em memória
 * @param fileName		Nome do ficheiro
 * @return A tabela hash de execuções do ficheiro CSV
 */
ExecutionNode** loadExecutionsTable(char* fileName, ExecutionNode* table[])
{
	char line[FILE_LINE_SIZE];
	int a = 0, b = 0, c = 0;

	Execution* execution = NULL;

	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	// iniciar tabela hash vazia
	*table = createExecutionsTable(table);

	while (!feof(file))
	{
		if (fgets(line, FILE_LINE_SIZE, file) != NULL)
		{
			// exemplo: 1;1;1
			sscanf(line, "%d;%d;%d", &a, &b, &c);

			execution = newExecution(a, b, c);
			*table = insertExecution_AtTable(table, execution);
		}
	}
	fclose(file);

	return *table;
}


/**
* @brief	Criar tabela hash das execuções vazia
* @param	table	Tabela hash das execuções
* @return	Tabela hash das execuções criada
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
* @brief	Criar nó vazio para uma posição da tabela hash das execuções
* @return	Nó vazio da tabela hash das execuções criado
*/
ExecutionNode* createExecutionNode()
{
	ExecutionNode* node = malloc(sizeof(ExecutionNode));

	node->start = NULL;
	node->numberOfExecutions = 0;

	return node;
}


/**
* @brief	Gerar hash através de uma função.
*			A função é representada pelo resto da divisão do identificador da operação pelo tamanho da tabela
* @param	operationID		Identificador da operação
* @return	Valor calculado pela função hash
*/
int generateHash(int operationID)
{
	return operationID % HASH_TABLE_SIZE;
}


/**
* @brief	Inserir nova execução na tabela hash das execuções, numa determinada posição
* @param	table	Tabela hash das execuções
* @return	Tabela hash das execuções atualizada
*/
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new)
{
	int index = generateHash(new->operationID);

	table[index]->start = insertExecution_AtStart_AtList(table[index]->start, new);
	table[index]->numberOfExecutions++;

	return *table;
}


/**
* @brief	Atualizar as unidades de tempo necessárias para a execução de uma operação na tabela hash
* @param	table			Tabela hash das execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime)
{
	ExecutionNode** current = table;

	int index = generateHash(operationID);
	bool updated = updateRuntime_AtList(&current[index]->start, operationID, machineID, runtime);

	return updated;
}


/**
* @brief	Remover todas as execuções pelo identificador da operação na tabela
* @param	table			Tabela hash das execuções
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
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
		// enquanto que remover, significa que ainda existe operações e portanto continuará a remover, até remover todas
		deleted = deleteExecution_ByOperation_AtList(&current[index]->start, operationID);

		if (deleted)
		{
			current[index]->numberOfExecutions--;
		}
	} while (deleted == true);

	return deleted;
}


/**
* @brief	Armazenar os registos de todas as listas de execuções na tabela hash, em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar os registos
* @param	head		Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeExecutions_AtTable(char fileName[], ExecutionNode* table[])
{
	if (table == NULL) // se tabela está vazia
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
		FileExecution currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

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
* @brief	Armazenar os registos de todas as listas de execuções na tabela hash, em ficheiro binário
* @brief	Ler de ficheiro binário, os registos de todas as execuções para a tabela hash
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Tabela hash de execuçõess
*/
ExecutionNode** readExecutions_AtTable(char fileName[], ExecutionNode* table[])
{
	FILE* file = NULL;

	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Execution* execution = NULL;
	Execution* list = NULL;
	list = readExecutions_AtList(fileName);

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
* @brief	Mostrar a tabela hash com as listas de execuções na consola
* @param	table	Tabela hash das execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayExecutions_AtTable(ExecutionNode* table[])
{
	if (table == NULL)
	{
		return false;
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		printf("Lista %d - Número de elementos: %d\n", i + 1, table[i]->numberOfExecutions);
		displayExecutions_AtList(table[i]->start);
	}

	return true;
}


/**
* @brief	Procurar por uma execução na tabela hash
* @param	table			Tabela hash das execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @return	Execução encontrada ou retorna nulo se não encontrar
*/
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID)
{
	if (table == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	int index = generateHash(operationID);
	Execution* search = searchExecution_AtList(table[index]->start, operationID, machineID);

	if (search == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	return search;
}


/**
* @brief	Libertar a tabela hash de execuções da memória
* @param	head	Lista de execuções
* @return	Tabela hash libertada da memória
*/
void freeExecutions_Table(ExecutionNode** table[])
{
	if (table != NULL)
	{
		ExecutionNode** table2 = *table;
		ExecutionNode* current;
		Execution* current2;

		for (int i = 0; i < HASH_TABLE_SIZE; i++)
		{
			current = table[i];

			//current = *head;
			//*head = (*head)->start;
			free(current);
			//freeExecutionsNode(&current);
		}
	}
}