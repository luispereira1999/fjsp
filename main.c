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

   return true;
}