/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a utilização de hash tables
 * @file	hashing.h
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include "data-types.h"


#ifndef HASHING
#define HASHING 1

#pragma region execuções

ExecutionNode** loadExecutionsTable(char* fileName, ExecutionNode* table[]);
ExecutionNode** createExecutionsTable(ExecutionNode* table[]);
ExecutionNode* createExecutionNode();
int generateHash(int id);
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new);
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime);
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID);
bool writeExecutions_AtTable(char fileName[], ExecutionNode* table[]);
ExecutionNode** readExecutions_AtTable(char fileName[], ExecutionNode* tableee[]);
bool displayExecutions_AtTable(ExecutionNode* table[]);
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID);
ExecutionNode** free_Execution_Table(ExecutionNode* table[]);

#pragma endregion

#endif