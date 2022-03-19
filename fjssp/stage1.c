/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos à fase 1 da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#pragma region jobs

Job* newJob(char* id[SIZE_ID])
{
	Job* new = (Job*)malloc(sizeof(Job));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	strcpy(new->id, id);
	new->operations = NULL;
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

Job* updateJob(Job* head, Job* jobToUpdate, char* currentID[SIZE_ID])
{
	if (head == NULL)
	{
		return NULL;
	}

	Job* current = head;

	while (current != NULL)
	{
		if (current->id == currentID)
		{
			head = jobToUpdate;
			return current;
		}
		current = current->next;
	}

	return head;
}

bool deleteJob(Job** head, char* id[SIZE_ID])
{
	Job* current = *head;
	Job* previous = NULL;

	// If head node itself holds the key to be deleted
	if (current != NULL && strcmp(current->id, id) == 0) {
		*head = current->next; // Changed head
		free(current); // free old head
		return true;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (current != NULL && strcmp(current->id, id) != 0)
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

bool searchJob(Job* head, char* id[SIZE_ID])
{
	if (head == NULL)
	{
		return false;
	}

	Job* current = head;

	while (current != NULL)
	{
		if (strcmp(current->id, id) == 0)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}

Job* getJob(Job* head, char* id[SIZE_ID])
{
	if (head == NULL)
	{
		return NULL;
	}

	Job* current = head;

	while (current != NULL)
	{
		if (strcmp(current->id, id) == 0)
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

	Job* currentJob = head;

	while (currentJob != NULL)
	{
		printf("Código do trabalho: %s\n", currentJob->id);
		currentJob = currentJob->next;
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

	char fileName[9] = "jobs.txt";
	FILE* file = fopen(fileName, "a");

	if (file == NULL)
	{
		return false;
	}

	fprintf(file, "%s\n", job->id);
	fclose(file);

	return true;
}

bool saveAllJobsToFile(Job* head)
{
	if (head == NULL)
	{
		return false;
	}

	char fileName[9] = "jobs.txt";
	FILE* file = fopen(fileName, "w");
	Job* current = head;

	if (file == NULL)
	{
		return false;
	}

	while (current != NULL)
	{
		fprintf(file, "%s\n", current->id);
		current = current->next;
	}

	fclose(file);

	return true;
}

Job* readJobsFromFile(Job* head) {
	Job* current = NULL;

	char fileName[9] = "jobs.txt";
	FILE* file = fopen(fileName, "r");
	char line[30];

	if (file == NULL)
	{
		return NULL;
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		// remover breakline que a string da linha do ficheiro possui
		line[strcspn(line, "\n")] = 0;

		current = (Job*)malloc(sizeof(Job));

		strcpy(current->id, line);
		current->operations = NULL;
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

#pragma endregion

#pragma region operations

Operation* newOperation(char* id[SIZE_ID], Operation* operations)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	strcpy(new->id,id);
	// new->machines = machines;
	// new->machines->next = NULL;
	new->next = NULL;

	return new;
}

Operation* insertOperationAtStart(Operation* head, Operation* current)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = current;
		current = head->next = NULL;
	}
	else
	{
		current->next = head;
		head = current;
	}

	return head;
}

#pragma endregion

#pragma region machines

Machine* newMachine(char* id[SIZE_ID], bool isActive)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	strcpy(new->id, id);
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

#pragma endregion

#pragma region outros

int getListCount(Job* head)
{
	if (head == NULL)
	{
		return -1;
	}

	int count = 0;
	Job* current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return count;
}

#pragma endregion