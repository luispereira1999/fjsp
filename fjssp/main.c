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
		printf("   M E N U                          \n\n");
		printf("   1 -> Criar, inserir e guardar job.\n");
		printf("   2 -> Ler e mostrar jobs.\n");
		printf("   3 -> Apagar job.\n");
		printf("   4 -> mostrar jobs.\n");
		printf("   5 -> Sair.\n\n");
		printf("   © Luís Pereira | 2022                   \n\n");
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
			bool isPrinted = printJobs(jobs);
			printf("isPrinted: %d\n", isPrinted);
			break;

		case 3: // remover job da lista

			jobs = deleteJob(jobs, "pr");
			printJobs(jobs);
			break;

		case 4: // remover job da lista

			printJobs(jobs);
			break;

		case 6:
			exit(true);
			break;
		default:
			printf("Opção inválida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}