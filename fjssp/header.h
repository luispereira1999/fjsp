/*
Descrição:           Ficheiro com todas as declarações necessárias para a fase 1 da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Última atualização:  25/03/2022
Criação:             14/03/2022
*/

#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

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
extern Job* jobs;

typedef struct Machine
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
	struct Machine* next;
} Machine;
extern Machine* machines;

typedef struct Execution // corresponde a cada execução de uma operação em uma máquina
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessária para a execução da operação
	struct Execution* next;
} Execution;
extern Execution* executions;

typedef struct Operation
{
	int id;
	int jobID;
	int position; // posição da operação (se é a 1º, 2º, 3º... a ser executada)
	struct Operation* next;
} Operation;
extern Operation* operations;

#pragma endregion

#pragma region funções e procedimentos

// sobre trabalhos
Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* new);
Job* updateJob(Job* head, Job* jobToUpdate, int id);
bool deleteJob(Job** head, int id);
bool writeJobs(char fileName[], Job* head);
Job* readJobs(char fileName[]);
bool freeJobs(Job* head);
bool displayJobs(Job* head);
bool searchJob(Job* head, int id);

// sobre máquinas
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* new);
bool writeMachines(char fileName[], Machine* head);
Machine* readMachines(char fileName[]);
bool freeMachines(Machine* head);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);

// sobre operações
Operation* newOperation(int id, int jobID, int position);
Operation* insertOperationAtStart(Operation* head, Operation* new);
bool updateOperationPosition(Operation** operations, Job* jobs, int jobID, int oldPosition, int newPosition);
bool deleteOperation(Operation** head, int id);
bool writeOperations(char fileName[], Operation* head);
Operation* readOperations(char fileName[]);
bool freeOperations(Operation* head);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int id);
int getMinTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minexecutions);
int getMaxTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxexecutions);
float getAverageTimeToCompleteOperation(Execution* head, int operationID);

// sobre execuções
Execution* newExecution(int operationID, int machineID, int runtime);
Execution* insertExecutionAtStart(Execution* head, Execution* new);
Execution* insertExecutionByOperation(Execution* head, Execution* new);
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime);
bool deleteExecutionByOperation(Execution** head, int operationID);
bool writeExecutions(char fileName[], Execution* head);
Execution* readExecutions(char fileName[]);
bool freeExecutions(Execution* head);
bool displayExecutions(Execution* head);
bool searchExecution(Execution* head, int operationID, int machineID);
bool searchExecutionByOperation(Execution* head, int operationID);
Execution* SortExecutionsByOperation(Execution* head);

// carregar dados para listas
void loadData(Job** jobs, Machine** machines, Operation** operations, Execution** executions);

#pragma endregion

#endif