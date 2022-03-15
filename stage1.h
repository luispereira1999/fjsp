/*
Descrição:           Ficheiro com todas as declarações necessárias para a fase 1 da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/20221
*/

#ifndef STAGE1_H

#pragma region constantes

#define HEADER_H

#pragma endregion

#pragma region representações e estruturas

typedef enum bool
{
   false = 0,
   true = 1
} bool;

typedef struct Machine
{
   int id;
   int time; // quantidade de unidades de tempo necessária para a realização da operação
   struct Machine *next;
} Machine;

typedef struct Operation
{
   int id;
   struct Machine *machines;
   struct Operation *next;
} Operation;

typedef struct Job
{
   int id;
   struct Operation *operations;
   struct Job *next;
} Job;

#pragma endregion

#pragma region funções e procedimentos

// sobre jobs
Job *newJob(int id, Operation *operations);

#pragma endregion

#endif