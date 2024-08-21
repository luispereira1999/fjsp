/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a utilização de hash tables.
 * @file	hashing.h
 * @author	Luís Pereira
 * @date	15/08/2024
*/


#ifndef HASHING
#define HASHING 1

#pragma region execuções

ExecutionNode* newExecutionNode();
ExecutionNode** newExecutionsTable_Empty(ExecutionNode* table[]);
int generateHash(int machineID);
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new);
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime);
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID);
bool deleteExecutions_ByMachine_AtTable(ExecutionNode** table[], int machineID);
ExecutionNode** readExecutions_AtTable_Example(ExecutionNode* table[]);
ExecutionNode** readExecutions_AtTable_Binary(char fileName[], ExecutionNode* table[]);
ExecutionNode** readExecutions_AtTable_Text(char fileName[], ExecutionNode* table[]);
bool writeExecutions_AtTable_Binary(char fileName[], ExecutionNode* table[]);
bool writeExecutions_AtTable_Text(char fileName[], ExecutionNode* table[]);
bool displayExecutions_AtTable(ExecutionNode* table[]);
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID);
bool cleanExecutions_Table(ExecutionNode** table[]);

#pragma endregion

#endif