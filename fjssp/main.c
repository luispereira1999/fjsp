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
		printf("Nao foi encontrado nenhum job.\n");
	}

	if (searchJob(jobs, 2))
	{
		Job* jobObtained2 = getJob(jobs, 2);
		printf("Obtido o job: %d\n", jobObtained2->id);
	}
	else
	{
		printf("Nao foi obtido nenhum job.\n");
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
		printf("Nao foi obtido nenhum job.\n");
	}

	int numberOfJobs = getListCount(jobs);
	printf("Numero de jobs: %d\n", numberOfJobs);

	printJobs(jobs);

	printf("\nGuardar job no ficheiro\n");
	bool a = saveJobToFile(job1);
	printf("saveJobToFile: %s", a ? "true" : "false");

	int menuOption = 0;

	do
	{
		// menu da aplicação 
		printf("\n                          M E N U                          \n\n");
		printf("   1 -> Criar job.\n");
		printf("   3 -> Sair.\n\n");
		printf("                 \xB8 Lu\xa1s Pereira | 2022                   \n\n");
		
		printf("Escolha uma das op\x87\xE4"
			"es acima: ");
		scanf("%d", &menuOption);

		switch (menuOption)
		{
		case 1:
			printf("\nCRIAR JOB\n");

			break;
		case 2:
			exit(true);
			break;
		default:
			printf("Op\x87\xC6o inv\xA0lida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	//free(players);

	return true;
}