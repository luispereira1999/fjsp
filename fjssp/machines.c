/**
 * @brief	Ficheiro com todas as funções relativas às máquinas
 * @file	machines.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
* @brief	Criar nova máquina
* @param	id		Identificador da máquina
* @param	isBusy	Booleano para se a máquina está ou não em utilização
* @return	Nova máquina
*/
Machine* newMachine(int id, bool isBusy)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->isBusy = isBusy;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova máquina no início da lista de máquinas
* @param	head	Lista de máquinas
* @param	new		Nova máquina
* @return	Lista de máquinas atualizada
*/
Machine* insertMachineAtStart(Machine* head, Machine* new)
{
	if (searchMachine(head, new->id)) // não permitir inserir uma nova com o mesmo ID
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
* @brief	Armazenar lista de máquinas em ficheiro
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de máquinas
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeMachines(char fileName[], Machine* head)
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

	Machine* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Machine), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de máquinas de ficheiro
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de operações
*/
Machine* readMachines(char fileName[])
{
	Machine* current = (Machine*)malloc(sizeof(Machine));
	if (current == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	Machine* head = NULL;
	Machine* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "rb");
	if (file == NULL) // se não foi possível abrir o ficheiro
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
		last->next = NULL; // o próximo elemento da lista não existe, portanto é nulo
	}

	fclose(file);

	return head;
}


/**
* @brief	Libertar a lista de máquinas da memória
* @param	head	Lista de máquinas
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool freeMachines(Machine* head)
{
	if (head == NULL) // se lista está vazia
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


/**
* @brief	Mostrar a lista de máquinas na consola
* @param	head	Lista de máquinas
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayMachines(Machine* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Machine* current = head;

	while (current != NULL)
	{
		printf("ID: %d, Ocupada?: %s;\n", current->id, current->isBusy ? "Sim" : "Não");
		current = current->next;
	}

	return true;
}


/**
* @brief	Procurar por uma máquina na lista de máquinas
* @param	head	Lista de máquinas
* @param	id		Identificador da máquina
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchMachine(Machine* head, int id)
{
	if (head == NULL) // se lista está vazia
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