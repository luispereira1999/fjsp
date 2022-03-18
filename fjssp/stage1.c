/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos à fase 1 da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/20221
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
	// new->operations->next = NULL;
	new->next = NULL;

	return new;
}

Job* insertJobAtStart(Job* head, Job* jobToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = jobToInsert;
		jobToInsert = head->next = NULL;
	}
	else
	{
		jobToInsert->next = head;
		head = jobToInsert;
	}

	return head;
}

Job* getJob(Job* head, int id)
{
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
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
}

Job* updateJob(Job* head, Job* jobToUpdate, int currentID)
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

bool searchJob(Job* head, int id)
{
	if (head == NULL)
	{
		return false;
	}
	else
	{
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
}

bool printJobs(Job* head)
{
	if (head == NULL)
	{
		return false;
	}
	else
	{
		Job* currentJob = head;
		Operation* currentOperation = head->operations;

		while (currentJob != NULL)
		{
			printf("Código da operação: %s\n", currentJob->id);

			while (currentOperation != NULL)
			{
				printf("Código da operação: %d\n", currentOperation->id);
				currentOperation = currentOperation->next;
			}

			currentOperation = currentJob->operations;
			currentJob = currentJob->next;
		}

		return true;
	}
}

bool saveJobToFile(Job* job)
{
	if (job == NULL)
	{
		return false;
	}
	else
	{
		char fileName[9] = "jobs.txt";
		FILE* file = fopen(fileName, "w");

		if (file == NULL)
		{
			return false;
		}

		fprintf(file, "%s\n", job->id);
		fclose(file);

		return true;
	}
}

#pragma endregion

#pragma region operations

Operation* newOperation(int id, Machine* machines)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
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