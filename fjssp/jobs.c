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
* @brief	Armazenar lista de trabalhos em ficheiro
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
	file = fopen(fileName, "wb");
	if (file == NULL) // se não foi possível abrir o ficheiro
	{
		return false;
	}

	Job* current = head;
	while (current != NULL) // escrever todos os elementos da lista no ficheiro
	{
		fwrite(current, sizeof(Job), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de trabalhos de ficheiro
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de trabalhos
*/
Job* readJobs(char fileName[])
{
	Job* current = (Job*)malloc(sizeof(Job));
	if (current == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	Job* head = NULL;
	Job* last = NULL;

	FILE* file = NULL;
	file = fopen(fileName, "rb");
	if (file == NULL) // se não foi possível abrir o ficheiro
	{
		return NULL;
	}

	while (fread(current, sizeof(Job), 1, file)) // ler todos os elementos da lista do ficheiro
	{
		if (head == NULL) // ler o primeiro elemento
		{
			head = last = (Job*)malloc(sizeof(Job));
		}
		else // ler os restantes elementos
		{
			last->next = (Job*)malloc(sizeof(Job));
			last = last->next;
		}

		last->id = current->id;
		last->next = NULL; // o próximo elemento da lista não existe, portanto é nulo
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