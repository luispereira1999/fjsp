/**
 * @brief	Ficheiro com todas as funções relativas aos trabalhos
 * @file	jobs.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
* @brief	Criar novo trabalho
* @param	id	Identificador do trabalho
* @return	Novo trabalho
*/
Job* newJob(int id)
{
	Job* new = (Job*)malloc(sizeof(Job));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir novo trabalho no início da lista de trabalhos
* @param	head	Lista de trabalhos
* @param	new		Novo trabalho
* @return	Lista de trabalhos atualizada
*/
Job* insertJobAtStart(Job* head, Job* new)
{
	if (searchJob(head, new->id)) // não permitir inserir um novo com o mesmo ID
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
* @brief	Armazenar lista de trabalhos em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de trabalhos
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeJobs(char fileName[], Job* head)
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

	Job* current = head;
	FileJob currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.id = current->id;
		fwrite(&currentInFile, sizeof(FileJob), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de trabalhos de ficheiro binário
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de trabalhos
*/
Job* readJobs(char fileName[])
{
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) // se não foi possível abrir o ficheiro
	{
		return NULL;
	}

	Job* head = NULL;
	Job* current = NULL;
	FileJob currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileJob), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newJob(currentInFile.id);
		head = insertJobAtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Libertar a lista de trabalhos da memória
* @param	head	Lista de trabalhos
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool freeJobs(Job* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Job* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}


/**
* @brief	Mostrar a lista de trabalhos na consola
* @param	head	Lista de trabalhos
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayJobs(Job* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Job* current = head;

	while (current != NULL)
	{
		printf("ID: %d;\n", current->id);
		current = current->next;
	}

	return true;
}


/**
* @brief	Procurar por um trabalho na lista de trabalhos
* @param	head	Lista de trabalhos
* @param	id		Identificador do trabalho
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchJob(Job* head, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Job* current = head;

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