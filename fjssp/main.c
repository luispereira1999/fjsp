/*
Descrição:           Ficheiro principal da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/20221
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "header.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Job* jobs = NULL;
	Operation* operations = NULL;
	int menuOption = 0;

	do
	{
		// menu da aplicação 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Criar job.\n");
		printf("   2 -> Mostrar jobs.\n");
		printf("   3 -> Apagar job.\n");
		printf("   4 -> Testes.\n");
		printf("   5 -> Sair.\n\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("---------------------------------\n");

		printf("Escolha uma das opções acima: ");
		scanf("%d", &menuOption);

		switch (menuOption)
		{

		case 1: // criar e inserir job na lista e guardar no ficheiro

			printf("\nCRIAR JOB\n");

			char id[SIZE_ID];
			printf("Introduza um código: ");
			scanf("%s", &id);

			Job* job = newJob(id);

			if (searchJob(jobs, job->id))
			{
				printf("Job já existe!\n");
			}
			else
			{
				if (!saveJobToFile(job)) {
					printf("Erro ao criar job.\n");
				}
				else {
					jobs = insertJobAtStart(jobs, job);
					printf("Job criado com sucesso!\n");
				}
			}

			break;

		case 2: // ler do ficheiro, guardar na lista e mostrar jobs na consola

			jobs = readJobsFromFile(jobs);
			printJobs(jobs);
			break;

		case 3: // remover job da lista, guardar todos os jobs no ficheiro e voltar a ler

			if (deleteJob(&jobs, "pr3"))
			{
				printf("Removido com sucesso.\n");
				saveAllJobsToFile(jobs);
			}
			else {
				printf("Não foi possível remover o job pretendido.\n");
			}
			break;

		case 4: // executar várias operações

			Job* jobTest = newJob("prTest");
			jobs = insertJobAtStart(jobs, jobTest);

			Machine* machine1 = NULL;
			Machine* machine2 = NULL;
			Operation* operation1 = newOperation(4, machine1);
			Operation* operation2 = newOperation(5, machine2);
			operations = insertOperationAtStart(operations, operation1);
			operations = insertOperationAtStart(operations, operation2);

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
				printf("NÃo foi obtido nenhum job.\n");
			}

			strcpy(jobTest->id, "PRT");
			jobs = updateJob(jobs, jobTest, 2);
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

			int numberOfJobs = getListCount(jobs);
			printf("Número de jobs: %d\n", numberOfJobs);

			printJobs(jobs);

			break;

		case 5:
			exit(true);
			break;
		default:
			printf("Opção inválida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}