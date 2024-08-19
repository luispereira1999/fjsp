/**
 * @brief	Ficheiro com todas as funções relativas às máquinas.
 * @file	machines.c
 * @author	Luís Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief	Criar nova máquina
 * @param	id		Identificador da máquina
 * @param	name	Nome da máquina
 * @return	Nova máquina
*/
Machine* newMachine(int id, const char* name)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	strncpy(new->name, name, NAME_SIZE - 1);
	new->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
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
 * @brief	Ler lista de máquinas a partir do código
 * @return	A lista de máquinas
*/
Machine* readMachines_Example()
{
	Machine* machines = NULL;
	Machine* machine = NULL;

	machine = newMachine(1, "Máquina 1");
	machines = insertMachine_AtStart(machines, machine);
	machine = newMachine(2, "Máquina 2");
	machines = insertMachine_AtStart(machines, machine);
	machine = newMachine(3, "Máquina 3");
	machines = insertMachine_AtStart(machines, machine);
	machine = newMachine(4, "Máquina 4");
	machines = insertMachine_AtStart(machines, machine);

	return machines;
}


/**
 * @brief	Ler lista de máquinas de ficheiro binário
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	Lista de máquinas
*/
Machine* readMachines_Binary(char fileName[])
{
	FILE* file = NULL;
	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Machine* head = NULL;
	Machine* current = NULL;
	FileMachine currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileMachine), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newMachine(currentInFile.id, currentInFile.name);
		head = insertMachine_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief	Carrega dados dos máquinas de um ficheiro .csv para uma lista em memória
 * @param	fileName	Nome do ficheiro
 * @return	A lista de máquinas do ficheiro .csv
*/
Machine* readMachines_Text(char fileName[])
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	char line[FILE_LINE_SIZE];
	int id = 0;
	char name[NAME_SIZE];

	Machine* machine = NULL;
	Machine* machines = NULL;

	while (fgets(line, FILE_LINE_SIZE, file) != NULL)
	{
		if (sscanf(line, "%d;%99[^\n]", &id, name) == 2) // ignora o cabeçalho do .csv
		{
			machine = (Machine*)malloc(sizeof(Machine));
			if (machine == NULL)
			{
				fclose(file);
				return NULL;
			}

			machine->id = id;
			strncpy(machine->name, name, NAME_SIZE - 1);
			machine->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
			machine->next = machines;

			machines = machine;
		}
	}

	fclose(file);

	return machines;
}


/**
 * @brief	Armazenar lista de máquinas em ficheiro binário
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de máquinas
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeMachines_Binary(char fileName[], Machine* head)
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

	Machine* current = head;
	FileMachine currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.id = current->id;
		strncpy(currentInFile.name, current->name, NAME_SIZE);

		fwrite(&currentInFile, sizeof(FileMachine), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Armazenar lista de máquinas em ficheiro de texto
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de máquinas
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeMachines_Text(char fileName[], Machine* head)
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

	Machine* current = head;

	fprintf(file, "ID;Nome\n"); // escreve o cabeçalho do .csv

	while (current != NULL)
	{
		// usa aspas ao redor do nome para garantir que não haja problemas com caracteres especiais
		fprintf(file, "%d;%s\n", current->id, current->name);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Mostrar a lista de máquinas na consola
 * @param	head	Lista de máquinas
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayMachines(Machine* head)
{
	if (head == NULL)
	{
		return false;
	}

	Machine* current = head;

	while (current != NULL)
	{
		printf("ID: %d, Nome: %s;\n", current->id, current->name);
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


/**
 * @brief	Limpar a lista de máquinas da memória
 * @param	head	Lista de máquinas
*/
bool cleanMachines(Machine** head)
{
	if (head != NULL && *head != NULL)
	{
		Machine* current;

		while (*head)
		{
			current = *head;
			*head = (*head)->next;
			free(current);
		}

		return true;
	}

	return false;
}