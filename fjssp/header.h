/*
Descri��o:           Ficheiro com todas as declara��es necess�rias para a fase 1 da aplica��o
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/20221
*/

#ifndef STAGE1_H

#pragma region constantes

#define HEADER_H

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
	int time; // quantidade de unidades de tempo necess�ria para a realiza��o da opera��o
	struct Machine* next;
} Machine;

typedef struct Operation
{
	int id;
	struct Machine* machines;
	struct Operation* next;
} Operation;

typedef struct Job
{
	int id;
	struct Operation* operations;
	struct Job* next;
} Job;

#pragma endregion

#pragma region fun��es e procedimentos

// sobre jobs
Job* newJob(int id, Operation* operations);
Job* insertJobAtStart(Job* head, Job* jobToInsert);
Job* getJob(Job* head, int id);
Job* updateJob(Job* head, Job* jobToUpdate, int currentID);
bool searchJob(Job* head, int id);
bool printJobs(Job* head);

// sobre operations
Operation* newOperation(int id, Machine* machines);
Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert);

// outros
int getListCount(Job* head);

#pragma endregion

#endif