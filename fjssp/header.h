/*
Descri��o:           Ficheiro com todas as declara��es necess�rias para a fase 1 da aplica��o
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/20221
*/

#ifndef HEADER_H

#pragma region constantes

#define HEADER_H
#define SIZE_ID 8

#pragma endregion

#pragma region representa��es e estruturas

typedef enum bool
{
   false = 0,
   true = 1
} bool;

typedef struct Machine
{
	int id;
	int isActive; // se a m�quina est� ou n�o em uso
	struct Machine* next;
} Machine;

typedef struct PerformOperation
{
	struct Job* job;
	struct Operation* operation;
	struct Machine* machine;
	int usageTime; // unidades de tempo necess�ria para a realiza��o da opera��o
	struct PerformOperation* next;
} PerformOperation;

typedef struct Operation
{
	int id;
	struct Operation* next;
} Operation;

typedef struct Job
{
	char id[SIZE_ID];
	struct Operation* operations;
	struct Job* next;
} Job;

#pragma endregion

#pragma region fun��es e procedimentos

// sobre jobs
Job* newJob(char* id[SIZE_ID]);
Job* insertJobAtStart(Job* head, Job* jobToInsert);
Job* getJob(Job* head, char* id[SIZE_ID]);
Job* updateJob(Job* head, Job* jobToUpdate, char* currentID[SIZE_ID]);
bool deleteJob(Job** head, char* id[SIZE_ID]);
bool searchJob(Job* head, char* id[SIZE_ID]);
bool printJobs(Job* head);
Job* readJobsFromFile(Job* head);
bool saveJobToFile(Job* job);
bool saveAllJobsToFile(Job* head);
bool freeJobsList(Job* head);

// sobre operations
Operation* newOperation(int id, Machine* machines);
Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert);

// outros
int getListCount(Job* head);

#pragma endregion

#endif