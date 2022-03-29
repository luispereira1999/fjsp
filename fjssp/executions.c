/**
 * @brief	Ficheiro com todas as funções relativas às execuções de operações
 * @file	executions.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
* @brief	Criar nova execução
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Unidades de tempo necessárias para a execução da operação
* @return	Nova execução
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
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova execução no início da lista de execuções
* @param	head	Lista de execuções
* @param	new		Nova execução
* @return	Lista de execuções atualizada
*/
Execution* insertExecutionAtStart(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // não permitir inserir uma nova com o mesmo ID de operação e ID de máquina
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
* @brief	Inserir execução ordenada pelo ID da operação na lista de execuções
* @param	head	Lista de execuções
* @param	new		Nova execução
* @return	Lista de execuções atualizada
*/
Execution* insertExecutionByOperation(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // não permitir inserir uma nova com o mesmo ID de operação e ID de máquina
	{
		return NULL;
	}

	if (head == NULL) // se a lista estiver vazia
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
* @param	head			Apontador para a lista de execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL) // se lista está vazia
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
* @brief	Remover execução pelo identificador da operação
* @param	head			Apontador para a lista de execuções
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteExecutionByOperation(Execution** head, int operationID)
{
	if (*head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* current = *head;
	Execution* previous = NULL;

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
* @brief	Armazenar lista de execuções em ficheiro
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeExecutions(char fileName[], Execution* head)
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

	Execution* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Execution), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de execuções de ficheiro
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de execuçõess
*/
Execution* readExecutions(char fileName[])
{
	FILE* file;
	Execution* head = NULL;
	Execution* current = NULL;

	if ((file = fopen(fileName, "rb")) == NULL) // se não foi possível abrir o ficheiro
	{
		return NULL;
	}
	
	// é a mesma estrutura mas sem o campo *next, pelo facto de ao guardar no ficheiro não ser necessário guardá-lo
	FileExecution currentInFile; 

	while (fread(&currentInFile, sizeof(FileExecution), 1, file)) // lê todos os registos do ficheiro 
	{
		current = newExecution(currentInFile.operationID, currentInFile.operationID, currentInFile.runtime);
		head = insertExecutionAtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Libertar a lista de operações da memória
* @param	head	Lista de operações
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool freeExecutions(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}


/**
* @brief	Mostrar a lista de execuções na consola
* @param	head	Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayExecutions(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* current = head;

	while (current != NULL)
	{
		printf("ID Operação: %d, ID Máquina: %d, Tempo de Execução: %d;\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	return true;
}


/**
* @brief	Procurar por uma execução na lista de execuções
* @param	head			Lista de execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchExecution(Execution* head, int operationID, int machineID)
{
	if (head == NULL) // se a lista estiver vazia
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
* @brief	Procurar por uma execução através do identificador da operação, na lista de execuções
* @param	head			Lista de execuções
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchExecutionByOperation(Execution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
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
* @brief	Ordenar lista de execuções por ordem crescente do identificador da operação
* @param	head			Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
Execution* SortExecutionsByOperation(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	Execution* current = head;
	Execution* sorted = NULL;
	Execution* new = NULL;

	while (current != NULL)
	{
		new = newExecution(current->operationID, current->machineID, current->runtime);
		sorted = insertExecutionByOperation(sorted, new);
		current = current->next;
	}

	return sorted;
}