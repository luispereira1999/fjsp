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
		printf("   1 -> Fase 1\n");
		printf("   2 -> Sobre\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("---------------------------------\n");
		printf("Escolha uma das opções acima: ");

		if (!scanf("%d", &menuOption)) // se não introduzir um número
		{
			menuOption = 0;
			fseek(stdin, 0, SEEK_END); // repor buffer de entrada para evitar ciclo infinito
			printf("\n");
			printf("O carácter introduzido não é válido. Tente outro.\n");
		}
		else
		{
			printf("\n");

			switch (menuOption)
			{
			case 1: // Fase 1 do projeto

				// Carregar dados (tabela) para as listas
				loadData(&jobs, &machines, &operations, &operationsExecution);
				// Guardar os dados em ficheiros
				writeJobs("jobs.data", jobs);
				writeOperations("operations.data", operations);
				writeMachines("machines.data", machines);
				writeOperationsExecution("operations-execution.data", operationsExecution);
				printf("Dados exportados com sucesso!\n");

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
				printf("Dados importados com sucesso!\n");

				// Remover operação
				deleteOperation(&operations, 33);
				printf("Operação removida com sucesso!\n");
				bool allFound = false;
				while (allFound == false) // enquanto que encontrar operações, remover execução de operações associadas
				{
					if (searchOperationExecution(operationsExecution, 33))
					{
						// Remover execução de operação relativa à operação
						deleteOperationExecution(&operationsExecution, 33);
						printf("Execução de operação associada à operação removida com sucesso!\n");
					}
					else
					{
						allFound = true;
					}
				}
				// Atualizar a posição da operação num determinado job
				updateOperationPosition(&operations, jobs, 1, 4, 2);
				printf("Posição da operação atualizada com sucesso!\n");
				// Atualizar o tempo necessário para uma execução da operação
				updateRuntime(&operationsExecution, 2, 2, 10);
				printf("Tempo necessário para a execução da operação atualizada com sucesso!\n");

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
				printf("Novos dados exportados com sucesso!\n");

				printf("\n----------------\n\n");

				// Obter o tempo mínimo para completar um job e as respetivas operações
				OperationExecution* minOperationsExecution = NULL;
				int minTime = getMinTimeToCompleteJob(operations, operationsExecution, 1, &minOperationsExecution);
				printf("Menor tempo necessário para completar o trabalho(ID: %d) é %d!\n", 1, minTime);
				printf("Operações com menor tempo:\n");
				minOperationsExecution = SortOperationsExecutionByOperation(minOperationsExecution);
				displayOperationsExecution(minOperationsExecution);
				// Obter o tempo máximo para completar um job
				OperationExecution* maxOperationsExecution = NULL;
				int maxTime = getMaxTimeToCompleteJob(operations, operationsExecution, 1, &maxOperationsExecution);
				printf("Maior tempo necessário para completar o trabalho(ID: %d) é %d!\n", 1, maxTime);
				printf("Operações com maior tempo:\n");
				maxOperationsExecution = SortOperationsExecutionByOperation(maxOperationsExecution);
				displayOperationsExecution(maxOperationsExecution);
				// Obter o tempo médio para completar uma operação
				float average = getAverageTimeToCompleteOperation(operationsExecution, 1);
				printf("Média de tempo necessário para completar a operação(ID: %d) é %.2f!\n", 1, average);

				printf("\n----------------\n\n");

				// Mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);
				printf("Máquinas:\n");
				displayMachines(machines);
				printf("Operações:\n");
				displayOperations(operations);
				printf("Execução de Operações:\n");
				displayOperationsExecution(operationsExecution);
				printf("Dados mostrados com sucesso!\n");
				// Libertar memória
				freeJobs(jobs);
				freeMachines(machines);
				freeOperations(operations);
				freeOperationsExecution(operationsExecution);
				break;

			case 2: // sobre aplicação

				printf("Flexible Job Shop Problem - Proposta de escalonamento para a produção de um produto que envolve várias operações e a utilização de várias máquinas, para minimizar o tempo necessário na sua produção.\n");
				printf("Projeto desenvolvido na unidade curricular Estruturas de Dados Avançadas, no âmbito do curso Licenciatura em Engenharia em Desenvolvimento de Jogos Digitais. Realizado no Instituto Politécnico do Cávado e do Ave, a 14 até 31 de março de 2022, durante o 2º semestre do 1º ano de curso.\n");
				break;

			default:
				printf("Opção inválida. Tente novamente.\n");
				break;
			}
		}

		printf("\n");
	} while (true);

	return true;
}