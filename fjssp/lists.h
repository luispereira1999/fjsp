/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a utilização de listas
 * @file	lists.h
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include "data-types.h"


#ifndef LISTS
#define LISTS 1

#pragma region trabalhos

Job* loadJobs(char* fileName);
Job* newJob(int id);
Job* insertJob_AtStart(Job* head, Job* new);
bool deleteJob(Job** head, int id);
bool writeJobs(char fileName[], Job* head);
Job* readJobs(char fileName[]);
bool displayJobs(Job* head);
bool searchJob(Job* head, int id);
int countJobs(Job* head);
void freeJobs(Job** head);

#pragma endregion


#pragma region máquinas

Machine* loadMachines(char* fileName);
Machine* newMachine(int id, bool isBusy);
Machine* insertMachine_AtStart(Machine* head, Machine* new);
bool enableMachine(Machine** h, int mid, bool ib);
bool writeMachines(char fileName[], Machine* head);
Machine* readMachines(char fileName[]);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);
void freeMachines(Machine** head);

#pragma endregion


#pragma region operações

Operation* loadOperations(char* fileName);
Operation* newOperation(int id, int jobID, int position);
Operation* insertOperation_AtStart(Operation* head, Operation* new);
bool updatePosition(Operation** head, int xOperationID, int yOperationID);
bool deleteOperation(Operation** head, int id);
int deleteOperation_ByJob(Operation** head, int jobID);
bool writeOperations(char fileName[], Operation* head);
Operation* readOperations(char fileName[]);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int id);
bool searchOperation_ByJob(Operation* head, int jobID);
Operation* getOperation(Operation* head, int id);
int getMinTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions);
int getMaxTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions);
float getAverageTime_ToCompleteOperation(Execution* head, int operationID);
void freeOperations(Operation** head);

Operation* getNextOperation_InJob(Operation* operations, Job* jobs, int jobID);
WorkPlan* newWorkPlan(int jobID, int operationID, int machineID, int runtime, int position, bool isDone);
WorkPlan* insertWorkPlan_AtStart(WorkPlan* head, WorkPlan* new);
WorkPlan* insertWorkPlan_ByJob_AtList(WorkPlan* head, WorkPlan* new);
bool displayWorkPlans(WorkPlan* head);
WorkPlan* sortWorkPlans_ByJob(WorkPlan* head);

#pragma endregion


#pragma region execuções

Execution* loadExecutions(char* fileName);
Execution* newExecution(int operationID, int machineID, int runtime);
Execution* insertExecution_AtStart_AtList(Execution* head, Execution* new);
Execution* insertExecution_ByOperation_AtList(Execution* head, Execution* new);
bool updateRuntime_AtList(Execution** head, int operationID, int machineID, int runtime);
bool deleteExecution_ByOperation_AtList(Execution** head, int operationID);
bool writeExecutions_AtList(char fileName[], Execution* head);
Execution* readExecutions_AtList(char fileName[]);
bool displayExecutions_AtList(Execution* head);
Execution* searchExecution_AtList(Execution* head, int operationID, int machineID);
Execution* searchExecution_ByOperation_AtList(Execution* head, int operationID);
Execution* sortExecutions_ByOperation_AtList(Execution* head);
Execution* getLastExecution_AtList(Execution* head);
void freeExecutions_List(Execution** head);

#pragma endregion


#pragma region planos de produção

bool startPlan(Cell plan[][MAX_TIME], int jobID, int executionID);
bool fillCells(Cell p[][MAX_TIME], int mid, int jid, int oid, int it, int ft);
bool searchActiveCells(Cell p[][MAX_TIME], int mid, int it, int ft);
bool displayPlan(Cell p[][MAX_TIME]);
bool exportPlan(char* fileName, Cell p[][MAX_TIME]);

#pragma endregion

#endif