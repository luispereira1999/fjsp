/**
 * @brief	Ficheiro com todas as fun��es relativas �s execu��es de opera��es com listas
 * @file	executions.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
 * @brief Carrega dados das execu��es de um ficheiro CSV para uma lista em mem�ria
 * @param fileName		Nome do ficheiro
 * @return A lista de execu��es do ficheiro CSV
 */
Execution* loadExecutions(char* fileName)
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
			// exemplo: 1;1;1
			sscanf(line, "%d;%d;%d", &a, &b, &c);
			execution = newExecution(a, b, c);
			executions = insertExecution_AtStart_AtList(executions, execution);
		}
	}

	fclose(file);

	return executions;
}


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
* @brief	Inserir nova execu��o no in�cio da lista de execu��es
* @param	head	Lista de execu��es
* @param	new		Nova execu��o
* @return	Lista de execu��es atualizada
*/
Execution* insertExecution_AtStart_AtList(Execution* head, Execution* new)
{
	if (searchExecution_AtList(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
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
* @brief	Inserir execu��o ordenada pelo ID da opera��o na lista de execu��es
* @param	head	Lista de execu��es
* @param	new		Nova execu��o
* @return	Lista de execu��es atualizada
*/
Execution* insertExecution_ByOperation_AtList(Execution* head, Execution* new)
{
	if (searchExecution_AtList(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
	{
		return NULL;
	}

	if (head == NULL) // se a lista estiver vazia
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
* @param	head			Apontador para a lista de execu��es
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updateRuntime_AtList(Execution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL) // se lista est� vazia
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
* @param	head			Apontador para a lista de execu��es
* @param	operationID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteExecution_ByOperation_AtList(Execution** head, int operationID)
{
	if (*head == NULL) // se a lista estiver vazia
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
* @brief	Armazenar lista de execu��es em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions_AtList(char fileName[], Execution* head)
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
* @brief	Ler lista de execu��es de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de execu��ess
*/
Execution* readExecutions_AtList(char fileName[])
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
* @brief	Mostrar a lista de execu��es na consola
* @param	head	Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayExecutions_AtList(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* current = head;

	while (current != NULL)
	{
		printf("ID Opera��o: %d, ID M�quina: %d, Tempo de Execu��o: %d;\n", current->operationID, current->machineID, current->runtime);
		current = current->next;
	}

	return true;
}


/**
* @brief	Procurar por uma execu��o na lista de execu��es
* @param	head			Lista de execu��es
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
Execution* searchExecution_AtList(Execution* head, int operationID, int machineID)
{
	if (head == NULL) // se a lista estiver vazia
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
* @brief	Procurar por uma execu��o atrav�s do identificador da opera��o, na lista de execu��es
* @param	head			Lista de execu��es
* @param	operationID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
Execution* searchExecution_ByOperation_AtList(Execution* head, int operationID)
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
* @brief	Ordenar lista de execu��es por ordem crescente do identificador da opera��o
* @param	head			Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
Execution* sortExecutions_ByOperation_AtList(Execution* head)
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
		sorted = insertExecution_ByOperation_AtList(sorted, new);
		current = current->next;
	}

	return sorted;
}


/**
* @brief	Obter a �ltima execu��o de uma lista de execu��es
* @param	head			Lista de execu��es
* @return	�ltima execu��o da lista
*/
Execution* getLastExecution_AtList(Execution* head)
{
	if (head == NULL) // return NULL is list is empty cf (Captain girafe && learningC)
	{
		return NULL;
	}

	Execution* current = head;

	while (current->next != NULL) // check if next element is null then currentElement = next else return currentElement
	{
		current = current->next;
	}

	return current;
}


/**
* @brief	Libertar a lista de execu��es da mem�ria
* @param	head	Lista de execu��es
* @return	Lista libertada da mem�ria
*/
Execution* free_Execution_List(Execution* head)
{
	if (head)
	{
		return NULL;
	}

	Execution* current = head;

	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return current;
}