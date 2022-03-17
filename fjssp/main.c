/*
Descrição:           Ficheiro principal da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/20221
*/

#include <stdio.h>
#include "header.h"

int main()
{
    Job* jobs = NULL;
    Operation* operations = NULL;

    Machine* machine1 = NULL;
    Machine* machine2 = NULL;
    Operation* operation1 = newOperation(4, machine1);
    Operation* operation2 = newOperation(5, machine2);
    operations = insertOperationAtStart(operations, operation1);
    operations = insertOperationAtStart(operations, operation2);

    Job* job1 = newJob(1, operations);
    Job* job2 = newJob(2, operations);
    Job* job3 = newJob(3, operations);

    jobs = insertJobAtStart(jobs, job1);
    jobs = insertJobAtStart(jobs, job2);
    jobs = insertJobAtStart(jobs, job3);

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
        Job* jobObtained2 = getJob(jobs, 2);
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
        Job* jobObtained2 = getJob(jobs, 2);
        printf("Obtido o job: %d\n", jobObtained2->id);
    }
    else
    {
        printf("Não foi obtido nenhum job.\n");
    }

    printJobs(jobs);

    int numberOfJobs = getListCount(jobs);
    printf("Numero de jobs: %d\n", numberOfJobs);

    printJobs(jobs);

    return true;
}