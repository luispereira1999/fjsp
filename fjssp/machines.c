/**
 * @brief	Ficheiro com todas as fun��es relativas �s m�quinas
 * @file	machines.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief Carrega dados das m�quinas de um ficheiro CSV para uma lista em mem�ria
 * @param fileName		Nome do ficheiro
 * @return A lista de m�quinas do ficheiro CSV
 */
Machine* loadMachines(char* fileName)
{
	char line[FILE_LINE_SIZE];
	int a = 0, b = 0;

	Machine* machine = NULL;
	Machine* machines = NULL;

	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	while (!feof(file))
	{
		if (fgets(line, FILE_LINE_SIZE, file) != NULL)
		{
			// exemplo: 1;0
			sscanf(line, "%d;%d", &a, &b);
			machine = newMachine(a, b);
			machines = insertMachine_AtStart(machines, machine);
		}
	}

	fclose(file);

	return machines;
}


/**
* @brief	Criar nova m�quina
* @param	id		Identificador da m�quina
* @param	isBusy	Booleano para se a m�quina est� ou n�o em utiliza��o
* @return	Nova m�quina
*/
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


/**
* @brief	Inserir nova m�quina no in�cio da lista de m�quinas
* @param	head	Lista de m�quinas
* @param	new		Nova m�quina
* @return	Lista de m�quinas atualizada
*/
Machine* insertMachine_AtStart(Machine* head, Machine* new)
{
	if (searchMachine(head, new->id)) // n�o permitir inserir uma nova com o mesmo ID
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
* @brief	Ocupa uma m�quina, diz que no memento est� ocupada
* @param	h		Apontador para a lista de m�quinas
* @param	mid		Identificador da m�quina
* @param	ib		Booleano para da m�quina
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool enableMachine(Machine** h, int mid, bool ib)
{
	if (*h == NULL) // se lista est� vazia
	{
		return false;
	}

	if (!searchMachine(*h, mid))
	{
		return false;
	}

	Machine* current = *h;

	while (current != NULL)
	{
		if (current->id == mid)
		{
			current->isBusy = ib;
			return true;
		}
		current = current->next;
	}

	return false;
}


/**
* @brief	Armazenar lista de m�quinas em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeMachines(char fileName[], Machine* head)
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

	Machine* current = head;
	FileMachine currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

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
* @brief	Ler lista de m�quinas de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de m�quinas
*/
Machine* readMachines(char fileName[])
{
	FILE* file = NULL;

	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Machine* head = NULL;
	Machine* current = NULL;
	FileMachine currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileMachine), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newMachine(currentInFile.id, currentInFile.isBusy);
		head = insertMachine_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Mostrar a lista de m�quinas na consola
* @param	head	Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayMachines(Machine* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	Machine* current = head;

	while (current != NULL)
	{
		printf("ID: %d, Ocupada?: %s;\n", current->id, current->isBusy ? "Sim" : "N�o");
		current = current->next;
	}

	return true;
}


/**
* @brief	Procurar por uma m�quina na lista de m�quinas
* @param	head	Lista de m�quinas
* @param	id		Identificador da m�quina
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
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