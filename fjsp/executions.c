/**
 * @brief	Ficheiro com todas as funções relativas às execuções de operações com listas e hash table.
 * @file	executions.c
 * @author	Luís Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"
#include "hashing.h"


#pragma region listas

/**
 * @brief	Criar nova execução de operação
 * @param	operationID		Identificador da operação
 * @param	machineID		Identificador da máquina
 * @param	runtime			Unidades de tempo necessárias para a execução da operação
 * @return	Nova execução de operação
*/
Execution* newExecution(int operationID, int machineID, int runtime)
{
	Execution* new = (Execution*)malloc(sizeof(Execution));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->runtime = runtime;
	new->next = NULL; // o próximo elemento é associado na função insert

	return new;
}


/**
 * @brief	Inserir nova execução no início da lista de execuções de operações
 * @param	head	Lista de execuções de operações
 * @param	new		Nova execução
 * @return	A lista de execuções de operações atualizada
*/
Execution* insertExecution_AtStart_AtList(Execution* head, Execution* new)
{
	if (searchExecution_AtList(head, new->operationID, new->machineID)) // não permitir inserir uma nova com o mesmo ID de operação e ID de máquina
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
 * @brief	Inserir execução ordenada pelo ID da operação na lista de execuções
 * @param	head	Lista de execuções de operações
 * @param	new		Nova execução
 * @return	A lista de execuções de operações atualizada
*/
Execution* insertExecution_ByOperation_AtList(Execution* head, Execution* new)
{
	if (searchExecution_AtList(head, new->operationID, new->machineID)) // não permitir inserir uma nova com o mesmo ID de operação e ID de máquina
	{
		return NULL;
	}

	if (head == NULL)
	{
		head = new; // inserir no início
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
 * @brief	Atualizar as unidades de tempo necessárias para a execução de uma operação
 * @param	head			Apontador para a lista de execuções de operações
 * @param	operationID		Identificador da operação
 * @param	machineID		Identificador da máquina
 * @param	runtime			Unidades de tempo
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool updateRuntime_AtList(Execution* head[], int operationID, int machineID, int runtime)
{
	if (head == NULL || *head == NULL)
	{
		return false;
	}

	if (!searchExecution_AtList(*head, operationID, machineID)) // se não existir a execução de operação para remover
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
 * @brief	Remover execução de operação pelo identificador da operação
 * @param	head			Apontador para a lista de execuções de operações
 * @param	operationID		Identificador da operação
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteExecution_ByOperation_AtList(Execution* head[], int operationID)
{
	if (head == NULL || *head == NULL)
	{
		return false;
	}

	if (!searchExecution_ByOperation_AtList(*head, operationID)) // se não existir a execução de operação para remover
	{
		return false;
	}

	Execution* current = *head;
	Execution* previous = NULL;

	if (current != NULL && current->operationID == operationID) // se o elemento que será apagado é o primeiro da lista
	{
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
 * @brief	Remover execução de operação pelo identificador da máquina
 * @param	head			Apontador para a lista de execuções de operações
 * @param	machineID		Identificador da máquina
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteExecution_ByMachine_AtList(Execution* head[], int machineID)
{
	if (head == NULL || *head == NULL)
	{
		return false;
	}

	if (!searchExecution_ByMachine_AtList(*head, machineID)) // se não existir a execução de operação para remover
	{
		return false;
	}

	Execution* current = *head;
	Execution* previous = NULL;

	if (current != NULL && current->machineID == machineID) // se o elemento que será apagado é o primeiro da lista
	{
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->machineID != machineID) // procurar o elemento a ser apagado
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
 * @brief	Ler lista de execuções de operações a partir do código
 * @return	A lista de execuções de operações
*/
Execution* readExecutions_AtList_Example()
{
	Execution* executions = NULL;
	Execution* execution = NULL;

	// execuções de operações do trabalho 1
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

	// execuções de operações do trabalho 2
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

	// execuções de operações do trabalho 3
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

	// execuções de operações do trabalho 4
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

	return executions; // 31 execuções de operações
}


/**
 * @brief	Ler lista de execuções de operações de ficheiro binário
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	A lista de execuções de operações
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
	FileExecution currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileExecution), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newExecution(currentInFile.operationID, currentInFile.machineID, currentInFile.runtime);
		head = insertExecution_AtStart_AtList(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief	Carrega dados das execuções de operações de um ficheiro .csv para uma lista em memória
 * @param	fileName		Nome do ficheiro
 * @return	A lista de execuções de operações
*/
Execution* readExecutions_AtList_Text(char fileName[])
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	char line[FILE_LINE_SIZE];
	int operationID = 0;
	int machineID = 0;
	int runtime = 0;

	Execution* execution = NULL;
	Execution* executions = NULL;

	while (fgets(line, FILE_LINE_SIZE, file) != NULL)
	{
		if (sscanf(line, "%d;%d;%d", &operationID, &machineID, &runtime) == 3) // ignora o cabeçalho do .csv
		{
			execution = newExecution(operationID, machineID, runtime);
			if (execution == NULL)
			{
				fclose(file);
				return NULL;
			}

			executions = insertExecution_AtStart_AtList(executions, execution);
		}
	}

	fclose(file);

	return executions;
}


/**
 * @brief	Armazenar lista de execuções de operações em ficheiro binário
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
	FileExecution currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

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
 * @brief	Armazenar lista de execuções de operações em ficheiro de texto
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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

	fprintf(file, "ID da Operação;ID da Máquina;Tempo de Execução\n"); // escreve o cabeçalho do .csv

	while (current != NULL)
	{
		fprintf(file, "%d;%d;%d\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Mostrar a lista de execuções de operações na consola
 * @param	head	Lista de execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
		printf("ID da Operação: %d, ID da Máquina: %d, Tempo de Execução: %d;\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	return true;
}


/**
 * @brief	Procurar por uma execução na lista de execuções de operações
 * @param	head			Lista de execuções de operações
 * @param	operationID		Identificador da operação
 * @param	machineID		Identificador da máquina
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
		//printf("current->operationID: %d, current->machineID: %d\n", current->operationID, current->machineID);
		if (current->operationID == operationID && current->machineID == machineID)
		{
			return true;
		}

		current = current->next;
	}

	return false;
}


/**
 * @brief	Procurar por uma execução através do identificador da operação, na lista de execuções de operações
 * @param	head			Lista de execuções de operações
 * @param	operationID		Identificador da operação
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @brief	Procurar por uma execução através do identificador da máquina, na lista de execuções de operações
 * @param	head			Lista de execuções de operações
 * @param	machineID		Identificador da máquina
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchExecution_ByMachine_AtList(Execution* head, int machineID)
{
	if (head == NULL)
	{
		return false;
	}

	Execution* current = head;

	while (current != NULL)
	{
		if (current->machineID == machineID)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}


/**
 * @brief	Ordenar lista de execuções de operações por ordem crescente do identificador da operação
 * @param	head	Lista de execuções de operações
 * @return	A lista de execuções de operações ordenada
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
 * @brief	Obter uma execução na lista de execuções de operações
 * @param	head			Lista de execuções de operações
 * @param	operationID		Identificador da operação
 * @param	machineID		Identificador da máquina
 * @return	Execução encontrada (ou NULL se não encontrou)
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
 * @brief	Obter a última execução de uma lista de execuções de operações
 * @return	Última execução da lista
*/
Execution* getLastExecution_AtList(Execution* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	Execution* current = head;

	while (current->next != NULL) // enquanto o próximo elemento for nulo
	{
		current = current->next;
	}

	return current;
}


/**
 * @brief	Limpar a lista de execuções de operações da memória
 * @param	head	Lista de execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool cleanExecutions_List(Execution* head[])
{
	if (head == NULL)
	{
		return false;
	}

	Execution* current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
	}

	return true;
}

#pragma endregion


#pragma region hashing

/**
 * @brief	Criar nó vazio para uma posição da tabela hash das execuções de operações
 * @return	Nó vazio da tabela hash das execuções de operações criado
*/
ExecutionNode* newExecutionNode()
{
	ExecutionNode* node = malloc(sizeof(ExecutionNode));
	//if (node == NULL)
	//{
	//	return NULL;
	//}

	node->start = NULL;
	node->numberOfExecutions = 0;

	return node;
}


/**
 * @brief	Criar tabela hash das execuções de operações vazia
 * @param	table	Tabela hash das execuções de operações
 * @return	A tabela hash das execuções de operações criada
*/
ExecutionNode** newExecutionsTable_Empty(ExecutionNode* table[])
{
	// inicializar cada posição da tabela hash com um nó vazio
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		table[i] = newExecutionNode();

		//if (table[i] == NULL) // se falhou ao alocar memória, liberta a memória previamente alocada
		//{
		//	for (int j = 0; j < i; j++)
		//	{
		//		free(table[j]);
		//	}

		//	free(table);
		//	return NULL;
		//}
	}

	return *table;
}


/**
 * @brief	Gerar hash para adicionar cada execução de operação a uma posição da tabela
 * @param	operationID		Identificador da operação
 * @return	Valor calculado pela função hash
*/
int generateHash(int machineID)
{
	return (machineID - 1) % HASH_TABLE_SIZE;
}


/**
 * @brief	Inserir nova execução na tabela hash das execuções de operações, numa determinada posição
 * @param	table	Tabela hash das execuções de operações
 * @return	A tabela hash das execuções de operações atualizada
*/
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new)
{
	int index = generateHash(new->machineID);

	table[index]->start = insertExecution_AtStart_AtList(table[index]->start, new);
	table[index]->numberOfExecutions++;

	return *table;
}


/**
 * @brief	Atualizar as unidades de tempo necessárias para a execução de uma operação na tabela hash
 * @param	table			Tabela hash das execuções de operações
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
 * @brief	Remover todas as execuções de operações pelo identificador da operação na tabela hash
 * @param	table			Tabela hash das execuções de operações
 * @param	operationID		Identificador da operação
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID)
{
	if (table == NULL || *table == NULL)
	{
		return false;
	}

	ExecutionNode** current = table;

	int index = generateHash(operationID);

	bool deleted = false;

	do
	{
		// enquanto que remover, significa que ainda existem operações e portanto continuará a remover, até remover todas
		deleted = deleteExecution_ByOperation_AtList(&current[index]->start, operationID);

		if (deleted)
		{
			current[index]->numberOfExecutions--;
		}
	} while (deleted == true);

	return deleted;
}


/**
 * @brief	Remover todas as execuções de operações pelo identificador da máquina na tabela hash
 * @param	table			Tabela hash das execuções de operações
 * @param	machineID		Identificador da máquina
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteExecutions_ByMachine_AtTable(ExecutionNode** table[], int machineID)
{
	if (table == NULL || *table == NULL)
	{
		return false;
	}

	bool deletedAny = false;

	ExecutionNode** currentTable = table;

	for (int i = 0; i < HASH_TABLE_SIZE; i++) // percorre todas as posições da tabela
	{
		if (currentTable[i] == NULL || currentTable[i]->start == NULL)
		{
			continue; // se a posição da tabela estiver vazia, passa para a próxima
		}

		bool deleted;

		do
		{
			// enquanto que remover, significa que ainda existem operações e portanto continuará a remover, até remover todas
			// apagar execuções de operações associadas à máquina na lista
			deleted = deleteExecution_ByMachine_AtList(&currentTable[i]->start, machineID);

			if (deleted)
			{
				currentTable[i]->numberOfExecutions--;
				deletedAny = true;
			}
		} while (deleted);
	}

	return deletedAny;
}


/**
 * @brief	Ler tabela hash de execuções de operações a partir do código
 * @param	table	Tabela hash das execuções de operações
 * @return	A tabela hash de execuções de operações
*/
ExecutionNode** readExecutions_AtTable_Example(ExecutionNode* table[])
{
	Execution* execution = NULL;

	*table = newExecutionsTable_Empty(table);

	// execuções de operações do trabalho 1
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

	// execuções de operações do trabalho 2
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

	// execuções de operações do trabalho 3
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

	// execuções de operações do trabalho 4
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

	return *table; // 38 execuções de operações
}


/**
 * @brief	Armazenar os registos de todas as listas de execuções de operações na tabela hash, em ficheiro binário
 * @brief	Ler de ficheiro binário, os registos de todas as execuções de operações para a tabela hash
 * @param	fileName	Nome do ficheiro para ler a lista
 * @param	table		Tabela hash de execuções de operações
 * @return	A tabela hash de execuções de operações
*/
ExecutionNode** readExecutions_AtTable_Binary(char fileName[], ExecutionNode* table[])
{
	FILE* file = NULL;
	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Execution* execution = NULL;
	Execution* list = NULL;
	list = readExecutions_AtList_Binary(fileName);

	if (list == NULL) // erro ao ler dados do ficheiro
	{
		return NULL;
	}

	// iniciar tabela hash vazia
	//*table = newExecutionsTable_Empty(table);

	while (list != NULL) // enquanto que houver dados na lista, guarda-os na tabela
	{
		execution = newExecution(list->operationID, list->machineID, list->runtime);
		if (execution == NULL)
		{
			fclose(file);
			return NULL;
		}

		*table = insertExecution_AtTable(table, execution);

		list = list->next;
	}

	return *table;
}


/**
 * @brief Carregar dados das execuções de operações um ficheiro .csv para uma tabela hash em memória
 * @param	fileName	Nome do ficheiro
 * @param	table		Tabela hash de execuções de operações
 * @return	A tabela hash de execuções de operações do ficheiro .csv
*/
ExecutionNode** readExecutions_AtTable_Text(char fileName[], ExecutionNode* table[])
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	char line[FILE_LINE_SIZE];
	int operationID = 0;
	int machineID = 0;
	int runtime = 0;

	Execution* execution = NULL;

	// iniciar tabela hash vazia
	//*table = newExecutionsTable_Empty(table);

	while (fgets(line, FILE_LINE_SIZE, file) != NULL)
	{
		if (sscanf(line, "%d;%d;%d", &operationID, &machineID, &runtime) == 3) // ignora o cabeçalho do .csv
		{
			execution = newExecution(operationID, machineID, runtime);
			if (execution == NULL)
			{
				fclose(file);
				return NULL;
			}

			*table = insertExecution_AtTable(table, execution);
		}
	}

	fclose(file);

	return *table;
}


/**
 * @brief	Armazenar os registos de todas as listas de execuções de operações na tabela hash, em ficheiro binário
 * @param	fileName	Nome do ficheiro para armazenar os registos
 * @param	table		Tabela hash de execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @brief	Armazenar os registos de todas as listas de execuções de operações na tabela hash, em ficheiro .csv
 * @param	fileName	Nome do ficheiro para armazenar os registos
 * @param	table		Tabela hash das execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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

	fprintf(file, "ID da Operação;ID da Máquina;Tempo de Execução\n"); // escreve o cabeçalho do .csv

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
 * @brief	Mostrar a tabela hash com as listas de execuções de operações na consola
 * @param	table	Tabela hash das execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
			printf("Lista %d - Número de elementos: %d\n", i + 1, table[i]->numberOfExecutions);
			displayExecutions_AtList(table[i]->start);
		}
	}

	return hasData;
}


/**
 * @brief	Procurar por uma execução na tabela hash
 * @param	table			Tabela hash das execuções de operações
 * @param	operationID		Identificador da operação
 * @param	machineID		Identificador da máquina
 * @return	Execução encontrada ou retorna nulo se não encontrar
*/
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID)
{
	if (table == NULL /*|| *table == NULL*/)
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
 * @brief	Limpar a tabela hash de execuções de operações da memória
 * @param	table	Lista de execuções de operações
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool cleanExecutions_Table(ExecutionNode** table[])
{
	if (table == NULL || *table == NULL)
	{
		return false;
	}

	//if (table != NULL && *table != NULL)
	//{
	//	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	//	{
	//		ExecutionNode* current = *table[i];
	//		if (current != NULL)
	//		{
	//			//printf("%d", &current->start->machineID);
	//			printf("\n");
	//			cleanExecutions_List(&current->start);

	//			free(current);

	//			*table[i] = NULL;
	//		}
	//	}

	//	free(table);

	//	return true;
	//}

	//ExecutionNode** currentTable = *table;
	//Execution* currentExecution;

	//for (int i = 0; i < HASH_TABLE_SIZE; i++) {
	//	ExecutionNode* currentNode = currentTable[i];

	//	if (currentNode != NULL)
	//	{
	//		//cleanExecutions_List(&current->start);
	//		//currentNode->start = currentTable[i];
	//		free(currentNode);
	//		table[i] = NULL;
	//	}
	//}


	ExecutionNode* currentNode;
	Execution* currentExecution;

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		currentNode = table[i];

		if (currentNode == NULL) {
			continue; // se uma posição da tabela estiver vazia, passa para o próximo
		}

		while (currentNode != NULL) {
			currentExecution = currentNode->start;
			cleanExecutions_List(&currentExecution);

			/*		while (currentExecution != NULL) {
						ExecutionNode* tempExecution = currentExecution;
						currentExecution = currentExecution->next;
						free(tempExecution);
						tempExecution = NULL;*/
						/*	current = *head;
							*head = (*head)->next;
							free(current);*/
							//}

			free(currentNode);

			//ExecutionNode* tempNode = currentNode;
			currentNode = NULL;
			//free(tempNode);
		}

		table[i] = NULL;
	}

	return true;
}

#pragma endregion