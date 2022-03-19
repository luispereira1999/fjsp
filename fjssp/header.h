/*
Descri��o:           Ficheiro com todas as declara��es necess�rias para a fase 1 da aplica��o
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/2022
*/

#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

#define SIZE_FILENAME_JOBS 9
#define SIZE_FILENAME_MACHINES 13

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
	bool isActive; // se a m�quina est� ou n�o em utiliza��o
	struct Machine* next;
} Machine;

typedef struct PerformOperation
{
	int operationID;
	int machineID;
	int usageTime; // unidades de tempo necess�ria para a realiza��o da opera��o
	struct PerformOperation* next;
} PerformOperation;

typedef struct Operation
{
	int id;
	int jobID;
	int position; // ordem da opera��o 
	struct Operation* next;
} Operation;

typedef struct Job
{
	int id;
	struct Job* next;
} Job;

#pragma endregion

#pragma region fun��es e procedimentos

// sobre jobs
Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* jobToInsert);
Job* updateJob(Job* head, Job* jobToUpdate, int id);
bool deleteJob(Job** head, int id);
bool searchJob(Job* head, int id);
Job* getJob(Job* head, int id);
bool printJobs(Job* head);
bool freeJobsList(Job* head);
bool saveJobToFile(Job* job);
bool saveAllJobsToFile(Job* head);
Job* readJobsFromFile(Job* head);

// sobre operations
Operation* newOperation(int id);
Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert);

// sobre machines
Machine* newMachine(int id, bool isActive);
Machine* insertMachineAtStart(Machine* head, Machine* machineToInsert);
bool printMachines(Machine* head);
bool searchMachine(Machine* head, int id);
bool saveMachineToFile(Machine* machine);
Machine* readMachinesFromFile(Machine* head);

// outros
int getListCount(Job* head);

#pragma endregion

#endif