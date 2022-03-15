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

Job *getJob(Job *head, int id)
{
   if (head == NULL)
   {
      return NULL;
   }
   else
   {
      Job *current = head;

      while (current != NULL)
      {
         if (current->id == id)
         {
            return current;
         }
         current = current->next;
      }

      return NULL;
   }
}

Job *updateJob(Job *head, Job *jobToUpdate, int currentID)
{
   if (head == NULL)
   {
      return NULL;
   }

   Job *current = head;

   while (current != NULL)
   {
      if (current->id == currentID)
      {
         head = jobToUpdate;
         return current;
      }
      current = current->next;
   }

   return head;
}

bool searchJob(Job *head, int id)
{
   if (head == NULL)
   {
      return false;
   }
   else
   {
      Job *current = head;

      while (current != NULL)
      {
         if (current->id == id)
         {
            return true;
         }
         current = current->next;
      }
      return false;
   }
}

void printJobs(Job *list)
{
   Job *current = list;

   while (current != NULL)
   {
      printf("id: %d\n", current->id);
      current = current->next;
   }
}

#pragma endregion