/**
 * @brief	Ficheiro com todas as fun��es relativas aos trabalhos.
 * @file	jobs.c
 * @author	Lu�s Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief	Criar novo trabalho
 * @param	id		Identificador do trabalho
 * @param	name	Nome da trabalho
 * @return	Novo trabalho
*/
Job* newJob(int id, const char* name)
{
	Job* new = (Job*)malloc(sizeof(Job));
	if (new == NULL) // se n�o houver mem�ria para alocar
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
 * @brief	Inserir novo trabalho no in�cio da lista de trabalhos
 * @param	head	Lista de trabalhos
 * @param	new		Novo trabalho
 * @return	Lista de trabalhos atualizada
*/
Job* insertJob_AtStart(Job* head, Job* new)
{
	if (searchJob(head, new->id)) // n�o permitir inserir um novo com o mesmo ID
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
 * @brief	Atualizar a posi��o de um trabalho X pela posi��o de um trabalho Y, e vice-versa
 * @param	head			Apontador para a lista de execu��es de opera��es
 * @param	xOperationID	Identificador de uma opera��o qualquer X
 * @param	yOperationID	Identificador de uma opera��o qualquer Y
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
//bool updateJob(Job** head, int xJobID, int yJobID)
//{
//	if (*head == NULL)
//	{
//		return false;
//	}
//
//	if (xJobID == yJobID) // se forem iguais
//	{
//		return false;
//	}
//
//	Job* xJob = NULL;
//	Job* yJob = NULL;
//
//	xJob = getOperation(*head, xJobID);
//	yJob = getOperation(*head, yJobID);
//
//	if (xJob == NULL || yJob == NULL) // se os trabalhos n�o foram encontrados
//	{
//		return false;
//	}
//
//	Job* current = *head;
//
//	while (current != NULL)
//	{
//		if (current->id == xOperation->id) // trocar a posi��o da opera��o X pela posi��o da opera��o Y
//		{
//			current->position = yOperation->position;
//		}
//		if (current->id == yOperation->id) // trocar a posi��o da opera��o Y pela posi��o da opera��o X
//		{
//			current->position = xOperation->position;
//		}
//
//		current = current->next;
//	}
//
//	return true;
//}


/**
 * @brief	Remover um trabalho da lista de trabalhos
 * @param	head	Apontador para a lista de trabalhos
 * @param	id		Identificador do trabalho
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteJob(Job** head, int id)
{
	if (*head == NULL)
	{
		return false;
	}

	Job* current = *head;
	Job* previous = NULL;

	if (current != NULL && current->id == id) { // se o elemento que ser� apagado � o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->id != id) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL) // se o elemento n�o foi encontrado
	{
		return false;
	}

	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return true;
}


/**
 * @brief	Ler lista de trabalhos a partir do c�digo
 * @return	A lista de trabalhos
*/
Job* readJobs_Example()
{
	Job* jobs = NULL;
	Job* job = NULL;

	job = newJob(1, "Trabalho 1");
	jobs = insertJob_AtStart(jobs, job);
	job = newJob(2, "Trabalh�o 2");
	jobs = insertJob_AtStart(jobs, job);
	job = newJob(3, "Trabalh�o 3");
	jobs = insertJob_AtStart(jobs, job);
	job = newJob(4, "Trabalh�o 4");
	jobs = insertJob_AtStart(jobs, job);

	return jobs;
}


/**
 * @brief	Ler lista de trabalhos de ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	Lista de trabalhos
*/
Job* readJobs_Binary(char fileName[])
{
	FILE* file = NULL;
	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Job* head = NULL;
	Job* current = NULL;
	FileJob currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileJob), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newJob(currentInFile.id, currentInFile.name);
		head = insertJob_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief	Carrega dados dos trabalhos de um ficheiro .csv para uma lista em mem�ria
 * @param	fileName	Nome do ficheiro
 * @return	A lista de trabalhos do ficheiro .csv
*/
Job* readJobs_Text(char fileName[])
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return NULL;
	}

	char line[FILE_LINE_SIZE];
	int id = 0;
	char name[NAME_SIZE];

	Job* job = NULL;
	Job* jobs = NULL;

	while (fgets(line, FILE_LINE_SIZE, file) != NULL)
	{
		if (sscanf(line, "%d;%99[^\n]", &id, name) == 2) // ignora o cabe�alho do .csv
		{
			job = (Job*)malloc(sizeof(Job));
			if (job == NULL)
			{
				fclose(file);
				return NULL;
			}

			job->id = id;
			strncpy(job->name, name, NAME_SIZE - 1);
			job->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
			job->next = jobs;
		
			jobs = job;
		}
	}

	fclose(file);

	return jobs;
}


/**
 * @brief	Armazenar lista de trabalhos em ficheiro bin�rio
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de trabalhos
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeJobs_Binary(char fileName[], Job* head)
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

	Job* current = head;
	FileJob currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.id = current->id;
		strncpy(currentInFile.name, current->name, NAME_SIZE);

		fwrite(&currentInFile, sizeof(FileJob), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Armazenar lista de trabalhos em ficheiro de texto
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de trabalhos
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeJobs_Text(char fileName[], Job* head)
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

	Job* current = head;

	fprintf(file, "ID;Nome\n"); // escreve o cabe�alho do .csv

	while (current != NULL)
	{
		// usa aspas ao redor do nome para garantir que n�o haja problemas com caracteres especiais
		fprintf(file, "%d;%s\n", current->id, current->name);
		current = current->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief	Mostrar a lista de trabalhos na consola
 * @param	head	Lista de trabalhos
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayJobs(Job* head)
{
	if (head == NULL)
	{
		return false;
	}

	Job* current = head;

	while (current != NULL)
	{
		printf("ID: %d, Nome: %s;\n", current->id, current->name);
		current = current->next;
	}

	return true;
}


/**
 * @brief	Procurar por um trabalho na lista de trabalhos
 * @param	head	Lista de trabalhos
 * @param	id		Identificador do trabalho
 * @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
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


/**
 * @brief	Obter a quantidade de trabalhos totais
 * @param	head	Lista de trabalhos
 * @return	N�mero de trabalhos
*/
int countJobs(Job* head)
{
	if (head == NULL)
	{
		return -1;
	}

	Job* current = head;
	int counter = 0;

	while (current != NULL)
	{
		counter++;
		current = current->next;
	}

	return counter;
}


/**
 * @brief	Limpar a lista de trabalhos da mem�ria
 * @param	head	Lista de trabalhos
*/
bool cleanJobs(Job** head)
{
	if (head != NULL && *head != NULL)
	{
		Job* current;

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