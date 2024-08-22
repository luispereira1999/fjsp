/**
 * @brief	Ficheiro com todas as funções relativas aos trabalhos.
 * @file	jobs.c
 * @author	Luís Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
 * @brief	Criar novo trabalho
 * @param	id		Identificador do trabalho
 * @param	name	Nome do trabalho
 * @return	Novo trabalho
*/
Job* newJob(Job* head, const char* name)
{
	Job* new = (Job*)malloc(sizeof(Job));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	int nextId = countJobs(head) + 1;

	new->id = nextId;
	strncpy(new->name, name, NAME_SIZE - 1);
	new->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
	new->next = NULL; // o próximo elemento é associado na função insert

	return new;
}


/**
 * @brief	Inserir novo trabalho no início da lista de trabalhos
 * @param	head	Lista de trabalhos
 * @param	new		Novo trabalho
 * @return	A lista de trabalhos atualizada
*/
Job* insertJob_AtStart(Job* head, Job* new)
{
	if (searchJob(head, new->id)) // não permitir inserir um novo com o mesmo ID
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
 * @brief	Atualizar o nome de um trabalho existente
 * @param	head		Apontador para a lista de trabalhos
 * @param	id			Identificador do trabalho a ser atualizado
 * @param	newName		Novo nome para o trabalho
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool updateJob(Job* head[], int id, const char* newName)
{
	if (head == NULL || *head == NULL)
	{
		return false;
	}

	if (!searchMachine(head, id)) // se a máquina não existir
	{
		return false;
	}

	Job* current = head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			strncpy(current->name, newName, NAME_SIZE - 1);
			current->name[NAME_SIZE - 1] = '\0'; // assegura que o nome termina com '\0'
		}

		current = current->next;
	}

	return true;
}


/**
 * @brief	Remover um trabalho da lista de trabalhos
 * @param	head	Apontador para a lista de trabalhos
 * @param	id		Identificador do trabalho
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteJob(Job* head[], int id)
{
	if (head == NULL || *head == NULL)
	{
		return false;
	}

	Job* current = *head;
	Job* previous = NULL;

	if (current != NULL && current->id == id) // se o elemento que será apagado é o primeiro da lista
	{
		*head = current->next;
		free(current);
		return true;
	}

	while (current != NULL && current->id != id) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL) // se o elemento não foi encontrado
	{
		return false;
	}

	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return true;
}


/**
 * @brief	Ler lista de trabalhos a partir do código
 * @return	A lista de trabalhos
*/
Job* readJobs_Example()
{
	Job* jobs = NULL;
	Job* job = NULL;

	job = newJob(jobs, "Tarefa 1");
	jobs = insertJob_AtStart(jobs, job);
	job = newJob(jobs, "Tarefa 2");
	jobs = insertJob_AtStart(jobs, job);
	job = newJob(jobs, "Tarefa 3");
	jobs = insertJob_AtStart(jobs, job);
	job = newJob(jobs, "Tarefa 4");
	jobs = insertJob_AtStart(jobs, job);

	return jobs;
}


/**
 * @brief	Ler lista de trabalhos de ficheiro binário
 * @param	fileName	Nome do ficheiro para ler a lista
 * @return	A lista de trabalhos
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
	FileJob currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileJob), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newJob(head, currentInFile.name);
		head = insertJob_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
 * @brief	Carrega dados dos trabalhos de um ficheiro .csv para uma lista em memória
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
		if (sscanf(line, "%d;%99[^\n]", &id, name) == 2) // ignora o cabeçalho do .csv
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
			job->next = NULL;

			jobs = insertJob_AtStart(jobs, job);
		}
	}

	fclose(file);

	return jobs;
}


/**
 * @brief	Armazenar lista de trabalhos em ficheiro binário
 * @param	fileName	Nome do ficheiro para armazenar a lista
 * @param	head		Lista de trabalhos
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
	FileJob currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

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
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @brief	Mostrar a lista de trabalhos na consola
 * @param	head	Lista de trabalhos
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @return	Booleano para o resultado da função (se funcionou ou não)
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
 * @brief	Contar o número de trabalhos existentes na lista de trabalhos
 * @param	head	Lista de trabalhos
 * @return	Quantidade de trabalhos
*/
int countJobs(Job* head)
{
	if (head == NULL)
	{
		return 0;
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
 * @brief	Limpar a lista de trabalhos da memória
 * @param	head	Apontador para a lista de trabalhos
 * @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool cleanJobs(Job* head[])
{
	if (head == NULL || *head == NULL)
	{
		return false;
	}

	Job* current;

	while (*head != NULL)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
	}

	return false;
}