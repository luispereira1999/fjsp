/*
Descrição:           Ficheiro com todas as declarações necessárias para a fase 1 da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

#define SIZE_FILENAME_JOBS 9
#define SIZE_FILENAME_MACHINES 13

#pragma endregion

#pragma region representações e estruturas

typedef enum bool
{
   false = 0,
   true = 1
} bool;

typedef struct Job
{
	int id;
	struct Job* next;
} Job;

typedef struct Operation
{
	int id;
	int jobID;
	int position; // posição da operação (se será a 1º, 2º, 3º... a ser executada)
	struct Operation* next;
} Operation;

typedef struct PerformOperation
{
	int operationID;
	int machineID;
	int usageTime; // unidades de tempo necessária para a realização da operação
	struct PerformOperation* next;
} PerformOperation;

typedef struct Machine
{
	int id;
	bool isActive; // se a máquina está ou não em utilização
	struct Machine* next;
} Machine;

#pragma endregion

#pragma region funções e procedimentos

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
Operation* newOperation(int id, int jobID, int position);
Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert);
PerformOperation* newPerformOperation(int operationID, int machineID, int usageTime);

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