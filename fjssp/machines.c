/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos às machines
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Machine* newMachine(int id, bool isActive)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->isActive = isActive;
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

bool printMachines(Machine* head)
{
	if (head == NULL)
	{
		return false;
	}

	Machine* current = head;

	while (current != NULL)
	{
		printf("Código da máquina: %d\n", current->id);
		current = current->next;
	}

	return true;
}

bool searchMachine(Machine* head, int id)
{
	if (head == NULL)
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