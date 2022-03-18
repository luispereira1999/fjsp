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
	new->next = NULL;

	return new;
}

Job* insertJobAtStart(Job* head, Job* jobToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = jobToInsert;
	}
	else
	{
		jobToInsert->next = head;
		head = jobToInsert;
	}

	return head;
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
		if (strcmp(current->id, id))
		{
			return current;
		}
		current = current->next;
	}

	return NULL;
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

Job* deleteJob(Job* head, char* id[SIZE_ID])
{
	if (head == NULL) {
		return NULL;
	}

	if (!searchJob(head, id)) {
		return head;
	}

	Job* current = head;
	Job* previous = NULL;

	while (current != NULL && strcmp(current->next->id, id) == 0)
	{
		previous = current;
		current = current->next;
	}
	if (previous == NULL) // eliminar o primeiro
	{
		head = head->next;
		free(current);
	}
	else // elimiar no meio
	{
		previous->next = current->next;
		free(current);
	}

	return head;
}

bool searchJob(Job* head, char* id[SIZE_ID])
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
			if (strcmp(current->id, id))
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
			printf("Código do trabalho: %s\n", currentJob->id);

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
		FILE* file = fopen(fileName, "a");

		if (file == NULL)
		{
			return false;
		}

		fprintf(file, "%s\n", job->id);
		fclose(file);

		return true;
	}
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

	while (fgets(line, sizeof(line), file) != NULL) {
		// remover breakline que a string da linha do ficheiro possui
		line[strcspn(line, "\n")] = 0;

		current = (Job*)malloc(sizeof(Job));

		strcpy(current->id, line);
		current->operations = NULL;
		current->next = NULL;

		if (head == NULL) {
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

// Operation *updateOperation(Operation *head, Operation *current)
// {
//    return head;
// }

Operation* deleteOperation(Operation* head, Operation* operationToDelete, int currentID)
{
	// if (h == NULL) return NULL;			//Lista vazia
	// 	if (!ExisteJogo(h, cod)) return h;	//se não existe

	// 	JogoListaPtr aux = h;
	// 	JogoListaPtr auxAnt = NULL;

	// 	//localizar registo a eliminar
	// 	while (aux && aux->jogo.cod != cod) {
	// 		auxAnt = aux;
	// 		aux = aux->next;
	// 	}
	// 	if (auxAnt == NULL) {	//Eliminar à cabeça
	// 		h = h->next;
	// 		free(aux);
	// 	}
	// 	else					//Elimiar no meio
	// 	{
	// 		auxAnt->next = aux->next;
	// 		free(aux);
	// 	}
	// 	return h;
}

void printOperations(Operation* head)
{
	Operation* current = head;

	while (current != NULL)
	{
		printf("id: %d\n", current->id);
		current = current->next;
	}
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