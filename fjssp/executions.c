/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos �s execu��es de opera��es
Desenvolvedor(es):   Lu�s Pereira (18446)
�ltima atualiza��o:  25/03/2022
Cria��o:             23/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

Execution* insertExecutionAtStart(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
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

// inserir execu��o de opera��o ordenada pelo ID da opera��o
Execution* insertExecutionByOperation(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
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

// atualizar as unidades de tempo necess�rias para a execu��o da opera��o
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL) // se lista est� vazia
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

bool deleteExecutionByOperation(Execution** head, int operationID)
{
	if (*head == NULL) // se a lista estiver vazia
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

bool writeExecutions(char fileName[], Execution* head)
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

	Execution* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Execution), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}

Execution* readExecutions(char fileName[])
{
	Execution* current = (Execution*)malloc(sizeof(Execution));
	if (current == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	Execution* head = NULL;
	Execution* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "rb");
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(Execution), 1, file)) // ler todos os elementos da lista do ficheiro
	{
		if (head == NULL) // ler o primeiro elemento
		{
			head = last = (Execution*)malloc(sizeof(Execution));
		}
		else // ler os restantes elementos
		{
			last->next = (Execution*)malloc(sizeof(Execution));
			last = last->next;
		}

		last->operationID = current->operationID;
		last->machineID = current->machineID;
		last->runtime = current->runtime;
		last->next = NULL; // o pr�ximo elemento da lista n�o existe, portanto � nulo
	}

	fclose(file);

	return head;
}

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

bool displayExecutions(Execution* head)
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