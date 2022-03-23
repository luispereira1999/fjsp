/*
Descri��o:           Ficheiro com todas as declara��es necess�rias para a fase 1 da aplica��o
Desenvolvedor(es):   Lu�s Pereira (18446)
�ltima atualiza��o:  25/03/2022
Cria��o:             14/03/2022
*/

#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

#pragma endregion

#pragma region representa��es e estruturas

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

typedef struct Machine
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
	struct Machine* next;
} Machine;

typedef struct OperationExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�ria para a execu��o da opera��o
	struct OperationExecution* next;
} OperationExecution;

typedef struct Operation
{
	int id;
	int jobID;
	int position; // posi��o da opera��o (se � a 1�, 2�, 3�... a ser executada)
	struct Operation* next;
} Operation;

#pragma endregion

#pragma region fun��es e procedimentos

// sobre jobs
Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* jobToInsert);
Job* updateJob(Job* head, Job* jobToUpdate, int id);
bool deleteJob(Job** head, int id);
bool writeJobs(char fileName[], Job* head);
Job* readJobs(char fileName[]);
bool freeJobs(Job* head);
bool displayJobs(Job* head);
Job* getJob(Job* head, int id);
bool searchJob(Job* head, int id);

// sobre machines
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* machineToInsert);
bool writeMachines(char fileName[], Machine* head);
Machine* readMachines(char fileName[]);
bool freeMachines(Machine* head);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);

// sobre operations
Operation* newOperation(int id, int jobID, int position);
Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert);
bool updateOperationPosition(Operation** head, Job* jobs, int jobID, int oldPosition, int newPosition);
bool deleteOperation(Operation** head, int id);
bool writeOperations(char fileName[], Operation* head);
Operation* readOperations(char fileName[]);
bool freeOperations(Operation* head);
bool displayOperations(Operation* head);
Operation* getOperation(Operation* head, int id);
int getMinTimeToCompleteJob(Operation* operations, OperationExecution* operationsExecution, int jobID, OperationExecution** minOperationsExecution);
int getMaxTimeToCompleteJob(Operation* operations, OperationExecution* operationsExecution, int jobID, OperationExecution** maxOperationsExecution);
float getAverageTimeToCompleteOperation(OperationExecution* operationsExecution, int operationID);

// sobre operations execution
OperationExecution* newOperationExecution(int operationID, int machineID, int runtime);
OperationExecution* insertOperationExecutionAtStart(OperationExecution* head, OperationExecution* operationExecutionToInsert);
bool updateRuntime(OperationExecution** head, int operationID, int machineID, int runtime);
bool deleteOperationExecution(OperationExecution** head, int operationID);
bool writeOperationsExecution(char fileName[], OperationExecution* head);
OperationExecution* readOperationsExecution(char fileName[]);
bool freeOperationsExecution(OperationExecution* head);
bool displayOperationsExecution(OperationExecution* head);
bool searchOperationExecution(OperationExecution* head, int operationID);

// carregar dados para listas
void loadData(Job** jobs, Machine** machines, Operation** operations, OperationExecution** operationsExecution);

#pragma endregion

#endif