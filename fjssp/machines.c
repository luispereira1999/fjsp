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
Machine* insertMachine_AtStart(Machine* head, Machine* new)
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
* @brief	Armazenar lista de máquinas em ficheiro binário
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

	if ((file = fopen(fileName, "wb")) == NULL) // se não foi possível abrir o ficheiro
	{
		return false;
	}

	Machine* current = head;
	FileMachine currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.id = current->id;
		currentInFile.isBusy = current->isBusy;
		fwrite(&currentInFile, sizeof(FileMachine), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de máquinas de ficheiro binário
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de máquinas
*/
Machine* readMachines(char fileName[])
{
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) // se não foi possível abrir o ficheiro
	{
		return NULL;
	}

	Machine* head = NULL;
	Machine* current = NULL;
	FileMachine currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileMachine), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newMachine(currentInFile.id, currentInFile.isBusy);
		head = insertMachine_AtStart(head, current);
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