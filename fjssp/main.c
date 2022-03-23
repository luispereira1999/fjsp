/*
Descrição:           Ficheiro principal da aplicação, com menu e chamada de funções
Desenvolvedor(es):   Luís Pereira (18446)
Última atualização:  25/03/2022
Criação:             14/03/2022
*/

#include <stdio.h>
#include <locale.h>
#include "header.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");

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
		printf("   2 -> Criar dados (tabela).\n");
		printf("   3 -> Testes.\n\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("---------------------------------\n");

		printf("Escolha uma das opções acima: ");
		scanf("%d", &menuOption);
		printf("\n");

		switch (menuOption)
		{
		case 1: // Fase 1

			// Carregar dados (tabela) para as listas
			loadData(&jobs, &machines, &operations, &operationsExecution);
			// Guardar os dados em ficheiros
			writeJobs("jobs.data", jobs);
			writeOperations("operations.data", operations);
			writeMachines("machines.data", machines);
			writeOperationsExecution("operations-execution.data", operationsExecution);

			// Libertar memória das listas anteriores, para serem lidas dos ficheiros
			freeJobs(jobs);
			freeMachines(machines);
			freeOperations(operations);
			freeOperationsExecution(operationsExecution);
			// Depois de libertar memória, definir listas como NULL para evitar possíveis erros
			jobs = NULL;
			operations = NULL;
			machines = NULL;
			operationsExecution = NULL;
			// Ler dados de ficheiros
			jobs = readJobs("jobs.data");
			machines = readMachines("machines.data");
			operations = readOperations("operations.data");
			operationsExecution = readOperationsExecution("operations-execution.data");

			// Remover operação
			deleteOperation(&operations, 33);
			printf("Operação (%d) removida com sucesso!\n", 33);
			bool allFound = false;
			while (allFound == false) // enquanto que encontrar operações, remover execução de operações associadas
			{
				if (searchOperationExecution(operationsExecution, 33))
				{
					deleteOperationExecution(&operationsExecution, 33);
					printf("Execução de operação associada à operação (%d) removida com sucesso!\n", 33);
				}
				else
				{
					allFound = true;
				}
			}
			// Atualizar a posição da operação num determinado job
			displayOperations(operations);
			bool a = changeOperationPosition(&operations, 1, 4, 2);
			printf("|%s|\n\n", a ? "Sim" : "Não");
			displayOperations(operations);

			//updateJobInOperation(&operations, 1, 8);
			//printf("Operação (%d) atualizada com sucesso! O ID do trabalho foi alterado para %d.\n", 1, 8);
			// Atualizar execução de operação

			// Inserir novo trabalho
			Job* job = NULL;
			job = newJob(9);
			jobs = insertJobAtStart(jobs, job);
			// Inserir nova máquina
			Machine* machine = NULL;
			machine = newMachine(9, false);
			machines = insertMachineAtStart(machines, machine);
			// Inserir nova operação
			Operation* operation = NULL;
			operation = newOperation(39, 2, 8);
			operations = insertOperationAtStart(operations, operation);
			// Inserir nova execução de uma operação
			OperationExecution* operationExecution = NULL;
			operationExecution = newOperationExecution(39, 5, 22);
			operationsExecution = insertOperationAtStart(operationsExecution, operationExecution);
			// Guardar as novas inserções em ficheiros
			writeJobs("jobs.data", jobs);
			writeMachines("machines.data", machines);
			writeOperations("operations.data", operations);
			writeOperationsExecution("operations-execution.data", operationsExecution);

			printf("\n----------------\n\n");

			// Obter o tempo mínimo para completar um job e as respetivas operações
			OperationExecution* minOperationsExecution = NULL;
			int minTime = getMinTimeToCompleteJob(operations, operationsExecution, 1, &minOperationsExecution);
			printf("Menor tempo necessário para completar o trabalho (%d): %d\n", 1, minTime);
			displayOperationsExecution(minOperationsExecution);
			// Obter o tempo máximo para completar um job
			OperationExecution* maxOperationsExecution = NULL;
			int maxTime = getMaxTimeToCompleteJob(operations, operationsExecution, 1, &maxOperationsExecution);
			printf("Maior tempo necessário para completar o trabalho (%d): %d\n", 1, maxTime);
			displayOperationsExecution(maxOperationsExecution);
			// Obter o tempo médio para completar uma operação
			float average = getAverageTimeToCompleteOperation(operationsExecution, 1);
			printf("Média de tempo necessário para completar a operação (%d): %.2f\n", 1, average);

			printf("\n----------------\n\n");

			// Mostrar dados na consola
			displayJobs(jobs);
			displayMachines(machines);
			displayOperations(operations);
			displayOperationsExecution(operationsExecution);
			// Libertar memória
			freeJobs(jobs);
			freeMachines(machines);
			freeOperations(operations);
			freeOperationsExecution(operationsExecution);
			// Depois de libertar memória, definir listas como NULL para evitar erros
			jobs = NULL;
			operations = NULL;
			machines = NULL;
			operationsExecution = NULL;
			break;

		case 2: // criar dados (tabela) e guardar em ficheiros

			// Carregar dados da tabela para listas
			loadData(&jobs, &machines, &operations, &operationsExecution);
			// Guardar os dados em ficheiros
			writeJobs("jobs.data", jobs);
			writeOperations("operations.data", operations);
			writeMachines("machines.data", machines);
			writeOperationsExecution("operations-execution.data", operationsExecution);
			break;

		case 3: // testes
			break;

		default:
			printf("Opção inválida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}