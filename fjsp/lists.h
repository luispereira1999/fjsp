/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a utilização de listas.
 * @file	lists.h
 * @author	Luís Pereira
 * @date	15/08/2024
*/


#ifndef LISTS
#define LISTS 1

#pragma region trabalhos

Job* newJob(Job* head, const char* name);
Job* insertJob_AtStart(Job* head, Job* new);
bool updateJob(Job* head[], int id, const char* newName);
bool deleteJob(Job* head[], int id);
Job* readJobs_Example();
Job* readJobs_Binary(char fileName[]);
Job* readJobs_Text(char fileName[]);
bool writeJobs_Binary(char fileName[], Job* head);
bool writeJobs_Text(char fileName[], Job* head);
bool displayJobs(Job* head);
bool searchJob(Job* head, int id);
int countJobs(Job* head);
bool cleanJobs(Job* head[]);

#pragma endregion


#pragma region máquinas

Machine* newMachine(Machine* head, const char* name);
Machine* insertMachine_AtStart(Machine* head, Machine* new);
bool updateMachine(Machine* head[], int id, const char* newName);
bool deleteMachine(Machine* head[], int id);
Machine* readMachines_Example();
Machine* readMachines_Binary(char fileName[]);
Machine* readMachines_Text(char fileName[]);
bool writeMachines_Binary(char fileName[], Machine* head);
bool writeMachines_Text(char fileName[], Machine* head);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);
int countMachines(Machine* head);
bool cleanMachines(Machine* head[]);

#pragma endregion


#pragma region operações

Operation* newOperation(Operation* head, int jobID, int position, const char* name);
Operation* insertOperation_AtStart(Operation* head, Operation* new);
bool updateOperation_Name(Operation* head[], int operationID, const char* newName);
bool updateOperation_Position(Operation* head[], int jobID, int xOperationID, int yOperationID);
bool deleteOperation(Operation* head[], int operationID);
int deleteOperation_ByJob(Operation* head[], int jobID);
Operation* readOperations_Example();
Operation* readOperations_Binary(char fileName[]);
Operation* readOperations_Text(char fileName[]);
bool writeOperations_Binary(char fileName[], Operation* head);
bool writeOperations_Text(char fileName[], Operation* head);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int operationID);
bool searchOperation_ByJob(Operation* head, int jobID);
Operation* getOperation(Operation* head, int operationID);
Operation* getOperation_ByJob(Operation* head, int operationID, int jobID);
int getMinTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions);
int getMaxTime_ToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions);
float getAverageTime_ToCompleteOperation(Execution* head, int operationID);
int countOperations(Operation* head);
bool cleanOperations(Operation* head[]);

#pragma endregion


#pragma region execuções de operações

Execution* newExecution(int operationID, int machineID, int runtime);
Execution* insertExecution_AtStart_AtList(Execution* head, Execution* new);
Execution* insertExecution_ByOperation_AtList(Execution* head, Execution* new);
bool updateRuntime_AtList(Execution* head[], int operationID, int machineID, int runtime);
bool deleteExecution_ByOperation_AtList(Execution* head[], int operationID);
bool deleteExecution_ByMachine_AtList(Execution* head[], int machineID);
Execution* readExecutions_AtList_Example();
Execution* readExecutions_AtList_Binary(char fileName[]);
Execution* readExecutions_AtList_Text(char fileName[]);
bool writeExecutions_AtList_Binary(char fileName[], Execution* head);
bool writeExecutions_AtList_Text(char fileName[], Execution* head);
bool displayExecutions_AtList(Execution* head);
bool searchExecution_AtList(Execution* head, int operationID, int machineID);
bool searchExecution_ByOperation_AtList(Execution* head, int operationID);
bool searchExecution_ByMachine_AtList(Execution* head, int machineID);
Execution* sortExecutions_ByOperation_AtList(Execution* head);
Execution* getExecution_AtList(Execution* head, int operationID, int machineID);
Execution* getLastExecution_AtList(Execution* head);
bool cleanExecutions_List(Execution* head[]);

#pragma endregion


#pragma region planos de trabalhos

WorkPlan* newWorkPlan(int jobID, int operationID, int machineID, int runtime, int position);
WorkPlan* insertWorkPlan_AtStart(WorkPlan* head, WorkPlan* new);
WorkPlan* insertWorkPlan_ByJob_AtList(WorkPlan* head, WorkPlan* new);
bool displayWorkPlans(WorkPlan* head);
WorkPlan* sortWorkPlans_ByJob(WorkPlan* head);
WorkPlan* getAllWorkPlans(Job* jobs, Operation* operations, Execution* executions);
int getFullTimeOfPlan(WorkPlan* head);

#pragma endregion


#pragma region planos de produção em memória

Cell newCell(int jobID, int operationID, int currentTime);
bool startPlan(Cell plan[][MAX_TIME], int jobID, int operationID, int currentTime);
bool fillCells(Cell plan[][MAX_TIME], int machineID, int jobID, int operationID, int initialTime, int finalTime);
Cell getLastCellFilled_InMachine(Cell plan[][MAX_TIME], int machineID);
Cell getLastCellFilled_OfJob(Cell plan[][MAX_TIME], int jobID);
bool fillAllPlan(Cell plan[][MAX_TIME], WorkPlan* workPlans, int numberOfCells);
bool displayPlan(Cell plan[][MAX_TIME]);
bool searchActiveCells(Cell plan[][MAX_TIME], int machineID, int initialTime, int finalTime);

#pragma endregion


#pragma region planos de produção para exportar para ficheiro

FileCell* newFileCell(int machineID, int jobID, int operationID, int initialTime, int finalTime);
FileCell* insertFileCell_AtStart(FileCell* head, FileCell* new);
FileCell* insertFileCell_ByMachine(FileCell* head, FileCell* new);
FileCell* sortFileCells_ByMachine(FileCell* head);
FileCell* getCellsToExport(Cell plan[][MAX_TIME]);
bool exportPlan(char fileName[], FileCell* head);

#pragma endregion

#endif