/**
 * @brief	Ficheiro com todas as assinaturas globais necess�rios para a aplica��o
 * @file	header.h
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/


#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

/**
 * @brief	Tamanho da tabela hash que armazena as execu��es
 */
#define HASH_TABLE_SIZE 13

 /**
  * @brief	Nomes para os ficheiros onde os dados s�o armazenados.
  */
#define JOBS_FILENAME_BINARY "jobs.bin"
#define MACHINES_FILENAME_BINARY "machines.bin"
#define OPERATIONS_FILENAME_BINARY "operations.bin"
#define EXECUTIONS_FILENAME_BINARY "executions.bin"

#pragma endregion


#pragma region representa��es

  /**
   * @brief	Criar tipo de dados booleano
   */
typedef enum bool
{
   false = 0,
   true = 1
} bool;

#pragma endregion


#pragma region estruturas de dados em mem�ria

/**
 * @brief	Estrutura de dados para representar a lista de trabalhos (em mem�ria)
 */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;

// lista de trabalhos
extern Job* jobs; // extern: informa o compilador que esta vari�vel est� definida algures no c�digo

/**
 * @brief	Estrutura de dados para representar a lista de m�quinas (em mem�ria)
 */
typedef struct Machine
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
	struct Machine* next;
} Machine;

// lista de m�quinas
extern Machine* machines;

/**
 * @brief	Estrutura de dados para representar a lista de opera��es (em mem�ria)
 */
typedef struct Operation
{
	int id;
	int jobID;
	int position; // posi��o da opera��o (se � a 1�, 2�, 3�... a ser executada)
	struct Operation* next;
} Operation;

// lista de opera��es
extern Operation* operations;

/**
 * @brief	Estrutura de dados para representar a lista das execu��es das opera��es em m�quinas (em mem�ria)
 */
typedef struct Execution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�rias para a execu��o da opera��o
	struct Execution* next;
} Execution;

// lista de execu��es
extern Execution* executions;

/**
 * @brief	Estrutura de dados para representar cada n� (posi��o) da tabela hash das execu��es (em mem�ria)
 */
typedef struct {
	Execution* start; // apontador para o primeiro elemento de cada posi��o da tabela
	int numberOfExecutions; // quantidade de execu��es de cada posi��o da tabela
} ExecutionNode;

// tabela hash para armazenar as execu��es e fazer buscas de forma mais eficiente,
// � um array de apontadores para listas de execu��es
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
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de m�quinas
 */
typedef struct FileMachine
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
} FileMachine;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de opera��es
 */
typedef struct FileOperation
{
	int id;
	int jobID;
	int position; // posi��o da opera��o (se � a 1�, 2�, 3�... a ser executada)
} FileOperation;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de execu��es das opera��es em m�quinas
 */
typedef struct FileExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�rias para a execu��o da opera��o
} FileExecution;

#pragma endregion


#pragma region fun��es

/**
 * @brief	Sobre trabalhos
 */
Job* newJob(int id);
Job* insertJob_AtStart(Job* head, Job* new);
bool deleteJob(Job** head, int id);
bool writeJobs(char fileName[], Job* head);
Job* readJobs(char fileName[]);
bool freeJobs(Job* head);
bool displayJobs(Job* head);
bool searchJob(Job* head, int id);

/**
 * @brief	Sobre m�quinas
 */
Machine* newMachine(int id, bool isBusy);
Machine* insertMachine_AtStart(Machine* head, Machine* new);
bool writeMachines(char fileName[], Machine* head);
Machine* readMachines(char fileName[]);
bool freeMachines(Machine* head);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);

/**
 * @brief	Sobre opera��es
 */
Operation* newOperation(int id, int jobID, int position);
Operation* insertOperation_AtStart(Operation* head, Operation* new);
bool updatePosition(Operation** head, int xOperationID, int yOperationID);
bool deleteOperation(Operation** head, int id);
int deleteOperation_ByJob(Operation** head, int jobID);
bool writeOperations(char fileName[], Operation* head);
Operation* readOperations(char fileName[]);
bool freeOperations(Operation* head);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int id);
bool searchOperation_ByJob(Operation* head, int jobID);
Operation* getOperation(Operation* head, int id);
int getMinTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions);
int getMaxTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions);
float getAverageTime_ToCompleteOperation(Execution* head, int operationID);

/**
 * @brief	Sobre execu��es com listas
 */
Execution* newExecution(int operationID, int machineID, int runtime);
Execution* insertExecution_AtStart(Execution* head, Execution* new);
Execution* insertExecution_ByOperation(Execution* head, Execution* new);
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime);
bool deleteExecution_ByOperation(Execution** head, int operationID);
bool writeExecutions(char fileName[], Execution* head);
Execution* readExecutions(char fileName[]);
bool freeExecutions(Execution* head);
bool displayExecutions(Execution* head);
Execution* searchExecution(Execution* head, int operationID, int machineID);
Execution* searchExecution_ByOperation(Execution* head, int operationID);
Execution* sortExecutions_ByOperation(Execution* head);

/**
 * @brief	Sobre execu��es com tabela hash
 */
ExecutionNode** createExecutionsTable(ExecutionNode* table[]);
ExecutionNode* createExecutionNode();
int generateHash(int id);
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new);
bool displayExecutionsTable(ExecutionNode* table[]);
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID);
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID);

/**
 * @brief	Carregar dados para as estruturas em mem�ria
 */
Job* loadJobs(Job* jobs);
Machine* loadMachines(Machine* machines);
Operation* loadOperations(Operation* operations);
ExecutionNode** loadExecutionsTable(ExecutionNode* table[]);

#pragma endregion

#endif