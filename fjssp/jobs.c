/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos aos jobs
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	if (head == NULL)
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
	Job* current = *head;
	Job* previous = NULL;

	// If head node itself holds the key to be deleted
	if (current != NULL && current->id == id) {
		*head = current->next; // Changed head
		free(current); // free old head
		return true;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (current != NULL && current->id != id)
	{
		previous = current;
		current = current->next;
	}

	// If key was not present in linked list
	if (current == NULL)
	{
		return false;
	}

	// Unlink the node from linked list
	previous->next = current->next;

	free(current); // Free memory
	return true;
}

bool searchJob(Job* head, int id)
{
	if (head == NULL)
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
	if (head == NULL)
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

bool printJobs(Job* head)
{
	if (head == NULL)
	{
		return false;
	}

	Job* current = head;

	while (current != NULL)
	{
		printf("Código do trabalho: %d\n", current->id);
		current = current->next;
	}

	return true;
}

bool freeJobsList(Job* head)
{
	Job* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

bool saveJobToFile(Job* job)
{
	if (job == NULL)
	{
		return false;
	}

	char fileName[SIZE_FILENAME_JOBS] = "jobs.txt";
	FILE* file = fopen(fileName, "a");

	if (file == NULL)
	{
		return false;
	}

	fprintf(file, "%d\n", job->id);
	fclose(file);

	return true;
}

bool saveAllJobsToFile(Job* head)
{
	if (head == NULL)
	{
		return false;
	}

	char fileName[SIZE_FILENAME_JOBS] = "jobs.txt";
	FILE* file = fopen(fileName, "w");
	Job* current = head;

	if (file == NULL)
	{
		return false;
	}

	while (current != NULL)
	{
		fprintf(file, "%d\n", current->id);
		current = current->next;
	}

	fclose(file);

	return true;
}

Job* readJobsFromFile(Job* head) {
	Job* current = NULL;

	char fileName[SIZE_FILENAME_JOBS] = "jobs.txt";
	FILE* file = fopen(fileName, "r");
	char line[30];

	if (file == NULL)
	{
		return NULL;
	}

	int id = 0;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		// remover breakline que a string da linha do ficheiro possui
		line[strcspn(line, "\n")] = 0;

		//fscanf(file, "%d", &id);
		int x = atoi(line);

		current = (Job*)malloc(sizeof(Job));
		fscanf(file, "%d", current->id);

		//current->id = x;
		current->next = NULL;

		if (head == NULL)
		{
			head = current;
		}
		else
		{
			current->next = head;
			head = current;
		}
	}

	fclose(file);

	return head;
}