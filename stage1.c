/*
Descrição:           Ficheiro com todas as funções e procedimentos relativos à fase 1 da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/20221
*/

#include <stdio.h>
#include <stdlib.h>
#include "stage1.h"

#pragma region jobs

Job *newJob(int id, Operation *operations)
{
   Job *new = (Job *)malloc(sizeof(Job));
   if (new == NULL) // se não houver memória para alocar
   {
      return NULL;
   }

   new->id = id;
   new->operations = operations;
   new->next = NULL;

   return new;
}

Job *insertJobAtStart(Job *head, Job *jobToInsert)
{
   if (head == NULL) // se a lista estiver vazia
   {
      head = jobToInsert;
      jobToInsert = head->next = NULL;
   }
   else
   {
      jobToInsert->next = head;
      head = jobToInsert;
   }

   return head;
}

#pragma endregion