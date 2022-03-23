/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos aos trabalhos
Desenvolvedor(es):   Luís Pereira (18446)
Última atualização:  25/03/2022
Criação:             15/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

Job* insertJobAtStart(Job* head, Job* jobToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = jobToInsert;
	}
	else // se existir algum elemento na lista
	{
		jobToInsert->next = head;
		head = jobToInsert;
	}

	return head;
}

Job* updateJob(Job* head, Job* jobToUpdate, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return NULL;
	}

	Job* current = head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			head = jobToUpdate;
			return current;
		}
		current = current->next;
	}

	return head;
}

bool deleteJob(Job** head, int id)
{
	if (*head == NULL) // se lista está vazia
	{
		return false;
	}

	Job* current = *head;
	Job* previous = NULL;

	if (current != NULL && current->id == id) { // se o elemento que será apagado é o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->id != id) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return true;
}

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

Job* readJobs(char fileName[])
{
	Job* current = (Job*)malloc(sizeof(Job));
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

bool displayJobs(Job* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Job* current = head;

	printf("Trabalhos:\n");
	while (current != NULL)
	{
		printf("ID: %d\n", current->id);
		current = current->next;
	}

	return true;
}

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

Job* getJob(Job* head, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return NULL;
	}

	Job* current = head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			return current;
		}
		current = current->next;
	}

	return NULL;
}