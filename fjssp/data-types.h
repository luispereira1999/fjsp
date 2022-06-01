/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a utilização dos tipos e estruturas de dados
 * @file	data-types.h
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/


#ifndef DATATYPES
#define DATATYPES 1

#pragma region constantes

// tamanho relativos às estruturas de dados
#define HASH_TABLE_SIZE 13
#define NUMBER_MACHINES 8
#define MAX_TIME 35

// tamanhos e nomes relativos a ficheiros de texto
#define FILE_LINE_SIZE 50
#define JOBS_FILENAME_TEXT "text/jobs.csv"
#define MACHINES_FILENAME_TEXT "text/machines.csv"
#define OPERATIONS_FILENAME_TEXT "text/operations.csv"
#define EXECUTIONS_FILENAME_TEXT "text/executions.csv"
#define PLAN_FILENAME_TEXT "text/plan.csv"

// tamanho da quantidade de operações que são guardadas em cada linha do plano exportado
#define OPEARATIONS_TEXT_SIZE 50

// nomes para os ficheiros binários onde os dados são armazenados durante a execução do programa
#define JOBS_FILENAME_BINARY "binary/jobs.bin"
#define MACHINES_FILENAME_BINARY "binary/machines.bin"
#define OPERATIONS_FILENAME_BINARY "binary/operations.bin"
#define EXECUTIONS_FILENAME_BINARY "binary/executions.bin"

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
 * @brief	Estrutura de dados para representar a lista de trabalhos (em memória)
 */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;

// lista de trabalhos
extern Job* jobs; // extern: informa o compilador que esta variável está definida algures no código


/**
 * @brief	Estrutura de dados para representar a lista de máquinas (em memória)
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
 * @brief	Estrutura de dados para representar a lista de operações (em memória)
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
 * @brief	Estrutura de dados para representar a lista das execuções das operações em máquinas (em memória)
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
 * @brief	Estrutura de dados para representar cada nó (posição) da tabela hash das execuções (em memória)
 */
typedef struct {
	Execution* start; // apontador para o primeiro elemento de cada posição da tabela
	int numberOfExecutions; // quantidade de execuções de cada posição da tabela
} ExecutionNode;

// tabela hash para armazenar as execuções e fazer buscas de forma mais eficiente,
// é um array de apontadores para listas de execuções
extern ExecutionNode* executionsTable[HASH_TABLE_SIZE];


/**
 * @brief	Estrutura de dados para guardar as operações e os restantes dados necessários que serão utilizados num plano de produção
 */
typedef struct WorkPlan
{
	int jobID;
	int operationID;
	int machineID;
	int runtime;
	int position;
	struct WorkPlan* next;
} WorkPlan;


/**
 * @brief	Estrutura de dados para representar um plano de produção
 */
typedef struct Cell
{
	int jobID;
	int operationID;
	int currentTime;
} Cell;

// matriz do plano de produção
extern Cell plan[NUMBER_MACHINES][MAX_TIME];

/**
 * @brief	Estrutura de dados para representar um plano de produção que será exportado da aplicação
 */
typedef struct CellExported
{
	int jobID;
	int operationID;
	int initalTime;
	int finalTime;
	struct CellExported* next;
} CellExported;

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

#endif