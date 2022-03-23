/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos �s m�quinas
Desenvolvedor(es):   Lu�s Pereira (18446)
�ltima atualiza��o:  25/03/2022
Cria��o:             17/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Machine* newMachine(int id, bool isBusy)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->id = id;
	new->isBusy = isBusy;
	new->next = NULL;

	return new;
}

Machine* insertMachineAtStart(Machine* head, Machine* machineToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = machineToInsert;
	}
	else // se existir algum elemento na lista
	{
		machineToInsert->next = head;
		head = machineToInsert;
	}

	return head;
}

bool writeMachines(char fileName[], Machine* head)
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

	Machine* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Machine), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}

Machine* readMachines(char fileName[])
{
	Machine* current = (Machine*)malloc(sizeof(Machine));
	Machine* head = NULL;
	Machine* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "rb");
	if (file == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(Machine), 1, file)) // ler todos os elementos da lista do ficheiro
	{
		if (head == NULL) // ler o primeiro elemento
		{
			head = last = (Machine*)malloc(sizeof(Machine));
		}
		else // ler os restantes elementos
		{
			last->next = (Machine*)malloc(sizeof(Machine));
			last = last->next;
		}

		last->id = current->id;
		last->isBusy = current->isBusy;
		last->next = NULL; // o pr�ximo elemento da lista n�o existe, portanto � nulo
	}

	fclose(file);

	return head;
}

bool freeMachines(Machine* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	Machine* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

bool displayMachines(Machine* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	Machine* current = head;

	printf("M�quinas:\n");
	while (current != NULL)
	{
		printf("ID: %d, Ocupada?: %s\n", current->id, current->isBusy ? "Sim" : "N�o");
		current = current->next;
	}

	return true;
}

bool searchMachine(Machine* head, int id)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	Machine* current = head;

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