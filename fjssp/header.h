/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a aplicação
 * @file	header.h
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/


#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

/**
 * @brief	Tamanho da tabela hash que armazena as execuções
 */
#define HASH_TABLE_SIZE 10

 /**
  * @brief	Nomes para os ficheiros onde os dados são armazenados.
  */
#define JOBS_FILENAME_BINARY "jobs.bin"
#define MACHINES_FILENAME_BINARY "machines.bin"
#define OPERATIONS_FILENAME_BINARY "operations.bin"
#define EXECUTIONS_FILENAME_BINARY "executions.bin"

#pragma endregion


#pragma region representações

  /**
   * @brief	Criar tipo de dados booleano
   */
typedef enum bool
{
   false = 0,
   true = 1
} bool;

#pragma endregion


#pragma region estruturas de dados em memória

/**
 * @brief	Estrutura de dados para a lista (em memória) de trabalhos
 */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;

// lista de trabalhos
extern Job* jobs; // extern: informar o compilador que esta variável está definida algures no código

/**
 * @brief	Estrutura de dados para a lista (em memória) de máquinas
 */
typedef struct Machine
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
	struct Machine* next;
} Machine;

// lista de máquinas
extern Machine* machines;

/**
 * @brief	Estrutura de dados para a lista (em memória) de operações
 */
typedef struct Operation
{
	int id;
	int jobID;
	int position; // posição da operação (se é a 1º, 2º, 3º... a ser executada)
	struct Operation* next;
} Operation;

// lista de operações
extern Operation* operations;

/**
 * @brief	Estrutura de dados para a lista (em memória) das execuções das operações em máquinas
 */
typedef struct Execution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessárias para a execução da operação
	struct Execution* next;
} Execution;

// lista de execuções
extern Execution* executions;

/**
 * @brief	Estrutura de dados para a lista (em memória) de cada posição da tabela hash de execuções
 */
typedef struct {
	Execution* start; // apontador para o primeiro elemento de cada posição da tabela
	int numberOfExecutions; // quantidade de execuções de cada posição da tabela
} ExecutionNode;

// tabela hash para armazenar as execuções e fazer buscas de forma mais eficiente (um array de apontadores para listas de execuções)
extern ExecutionNode* executionsTable[HASH_TABLE_SIZE];

#pragma endregion


#pragma region estruturas de dados em ficheiros

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de trabalhos
 */
typedef struct FileJob
{
	int id;
} FileJob;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de máquinas
 */
typedef struct FileMachine
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
} FileMachine;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de operações
 */
typedef struct FileOperation
{
	int id;
	int jobID;
	int position; // posição da operação (se é a 1º, 2º, 3º... a ser executada)
} FileOperation;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de execuções das operações em máquinas
 */
typedef struct FileExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessárias para a execução da operação
} FileExecution;

#pragma endregion


#pragma region funções

/**
 * @brief	Sobre trabalhos
 */
Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* new);
bool deleteJob(Job** head, int id);
bool writeJobs(char fileName[], Job* head);
Job* readJobs(char fileName[]);
bool freeJobs(Job* head);
bool displayJobs(Job* head);
bool searchJob(Job* head, int id);

/**
 * @brief	Sobre máquinas
 */
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* new);
bool writeMachines(char fileName[], Machine* head);
Machine* readMachines(char fileName[]);
bool freeMachines(Machine* head);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);

/**
 * @brief	Sobre operações
 */
Operation* newOperation(int id, int jobID, int position);
Operation* insertOperationAtStart(Operation* head, Operation* new);
bool updatePosition(Operation** head, int xOperationID, int yOperationID);
bool deleteOperation(Operation** head, int id);
int deleteOperationByJob(Operation** head, int jobID);
bool writeOperations(char fileName[], Operation* head);
Operation* readOperations(char fileName[]);
bool freeOperations(Operation* head);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int id);
bool searchOperationByJob(Operation* head, int jobID);
Operation* getOperation(Operation* head, int id);
int getMinTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions);
int getMaxTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions);
float getAverageTimeToCompleteOperation(Execution* head, int operationID);

/**
 * @brief	Sobre execuções com listas
 */
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
Execution* sortExecutionsByOperation(Execution* head);

/**
 * @brief	Sobre execuções com tabela hash
 */
ExecutionNode* createExecutionNode();
ExecutionNode** createExecutionsTable(ExecutionNode* table[]);
int generateHash(int id);

/**
 * @brief	Carregar dados para listas em memória
 */
void loadData(Job** jobs, Machine** machines, Operation** operations, Execution** executions);

#pragma endregion

#endif