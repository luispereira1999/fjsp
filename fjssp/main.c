/*
Descri��o:           Ficheiro principal da aplica��o
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/20221
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
		// menu da aplica��o 
		printf("---------------------------------\n\n");
		printf("   M E N U                          \n\n");
		printf("   1 -> Criar job.\n");
		printf("   1 -> Teste.\n");
		printf("   3 -> Sair.\n\n");
		printf("   � Lu�s Pereira | 2022                   \n\n");
		printf("---------------------------------\n");

		printf("Escolha uma das op��es acima: ");
		scanf("%d", &menuOption);

		switch (menuOption)
		{
		case 1: // criar job

			printf("\nCRIAR JOB\n");

			char id[SIZE_ID];
			printf("Introduza um c�digo: ");
			scanf("%s", &id);

			Job* job = newJob(id);

			if (searchJob(jobs, job->id))
			{
				printf("Job j� existe!\n");
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

		case 2:
			exit(true);
			break;
		default:
			printf("Op��o inv�lida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}