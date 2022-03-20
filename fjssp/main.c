/*
Descrição:           Ficheiro principal da aplicação
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "header.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Job* job = NULL;
	Machine* machine = NULL;
	Operation* operation = NULL;
	OperationExecution* operationExecution = NULL;

	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;
	OperationExecution* operationsExecution = NULL;

	int menuOption = 0;

	do
	{
		// menu 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Fase 1.\n");
		printf("   2 -> Testes.\n");
		printf("   3 -> Criar dados da tabela e guardar em ficheiros.\n\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("---------------------------------\n");

		printf("Escolha uma das opções acima: ");
		scanf("%d", &menuOption);

		switch (menuOption)
		{
		case 1: // Fase 1

			// Inserir job
			job = newJob(1);
			jobs = insertJobAtStart(jobs, job);
			// Inserir máquina
			machine = newMachine(1, false);
			machines = insertMachineAtStart(machines, machine);
			// Inserir operação
			operation = newOperation(1, 1, 1);
			operations = insertOperationAtStart(operations, operation);
			// Inserir execução de uma operação
			operationExecution = newOperationExecution(1, 1, 3);
			operationsExecution = insertOperationAtStart(operationsExecution, operationExecution);
			// Guardar as inserções em ficheiros
			writeJobs("jobs.bin", jobs);
			writeOperations("operations.bin", operations);
			writeMachines("machines.bin", machines);
			writeOperationsExecution("operations-execution.bin", operationsExecution);
			// Ler dados de ficheiros
			jobs = readJobs("jobs.bin");
			operations = readOperations("operations.bin");
			machines = readMachines("machines.bin");
			operationsExecution = readOperationsExecution("operations-execution.bin");
			// Mostrar dados na consola
			displayJobs(jobs);
			displayOperations(operations);
			displayMachines(machines);
			displayOperationsExecution(operationsExecution);
			// Remover operação
			// Atualizar operação
			break;

		case 2: // testes

			//Job * jobTest = newJob("prTest");
			//jobs = insertJobAtStart(jobs, jobTest);

			//Machine* machine1 = NULL;
			//Machine* machine2 = NULL;
			//Operation* operation1 = newOperation(4, machine1);
			//Operation* operation2 = newOperation(5, machine2);
			//operations = insertOperationAtStart(operations, operation1);
			//operations = insertOperationAtStart(operations, operation2); */

			//displayJobs(jobs);

			//if (searchJob(jobs, 1))
			//{
				//printf("Job encontrado!\n");
			//}
			//else
			//{
				//printf("Não foi encontrado nenhum job.\n");
			//}

			//if (searchJob(jobs, 2))
			//{
				//Job* jobObtained2 = getJob(jobs, 2);
				//printf("Obtido o job: %d\n", jobObtained2->id);
			//}
			//else
			//{
				//printf("NÃo foi obtido nenhum job.\n");
			//}

			//strcpy(jobTest->id, "PRT");
			//jobs = updateJob(jobs, jobTest, 2);
			//printf("Job atualizado: %d\n", jobs->id);

			//if (searchJob(jobs, 2))
			//{
				//Job* jobObtained2 = getJob(jobs, 2);
				//printf("Obtido o job: %d\n", jobObtained2->id);
			//}
			//else
			//{
				//printf("Não foi obtido nenhum job.\n");
			//}

			//int numberOfJobs = getListCount(jobs);
			//printf("Número de jobs: %d\n", numberOfJobs);

			//printJobs(jobs);

			break;

		case 3: // criar dados da tabela e guardar em ficheiros


			break;

		case 4:
			exit(true);
			break;
		default:
			printf("Opção inválida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}