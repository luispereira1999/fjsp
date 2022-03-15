/*
Descrição:           Ficheiro principal da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/20221
*/

#include <stdio.h>
#include "stage1.h"

int main()
{
   Job *jobs = NULL;
   Operation *operations = NULL;

   Job *job1 = newJob(1, operations);
   Job *job2 = newJob(2, operations);
   Job *job3 = newJob(3, operations);

   jobs = insertJobAtStart(jobs, job1);
   jobs = insertJobAtStart(jobs, job2);

   printJobs(jobs);

   if (searchJob(jobs, 1))
   {
      printf("Job encontrado!\n");
   }
   else
   {
      printf("Não foi encontrado nenhum job.\n");
   }

   if (searchJob(jobs, 2))
   {
      Job *jobObtained2 = getJob(jobs, 2);
      printf("Obtido o job: %d\n", jobObtained2->id);
   }
   else
   {
      printf("Não foi obtido nenhum job.\n");
   }

   job2->id = 6;
   jobs = updateJob(jobs, job2, 2);
   printf("Job atualizado: %d\n", jobs->id);

   if (searchJob(jobs, 2))
   {
      Job *jobObtained2 = getJob(jobs, 2);
      printf("Obtido o job: %d\n", jobObtained2->id);
   }
   else
   {
      printf("Não foi obtido nenhum job.\n");
   }

   printJobs(jobs);

   return true;
}