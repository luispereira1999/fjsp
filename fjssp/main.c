/**
 * @brief	Ficheiro principal da aplicação, com menu e chamada de funções
 * @file	main.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	26/03/2022
 *
 * -----------------
 *
 * Software desenvolvido para a proposta de escalonamento para a produção de um produto que envolve várias operações
 * e a utilização de várias máquinas, para minimizar o tempo necessário na sua produção.
 * @see https://github.com/luispereira1999/fjssp
*/

#include <stdio.h>
#include <locale.h>
#include "header.h"


/**
* @brief	Função principal do programa
* @return	Resultado do programa na linha de comando
*/
int main()
{
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

	// listas de entidades
	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;
	Execution* executions = NULL;

	// criar tabela hash vazia
	ExecutionNode* executionsTable[HASH_TABLE_SIZE];
	*executionsTable = createExecutionsTable(executionsTable);

	int menuOption = 0;

	do
	{
		// menu 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Fase 2\n");
		printf("   2 -> Testes\n");
		printf("   3 -> Sobre\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("---------------------------------\n");
		printf("Escolha uma das opções acima: ");

		if (!scanf("%d", &menuOption)) // se não introduzir um número
		{
			fseek(stdin, 0, SEEK_END); // repor buffer de entrada para evitar ciclo infinito
			printf("\n");
			printf("O carácter introduzido não é válido. Tente outro.\n");
		}
		else
		{
			printf("\n");

			switch (menuOption)
			{
			case 1: // fase 2 da aplicação

#pragma region funcionalidade 1: definir estruturas de dados dinâmicas
				printf("-  1. Definir estruturas de dados dinâmicas\n");

				// carregar dados (tabela) para as listas
				loadJobs(&jobs);
				loadMachines(&machines);
				loadOperations(&operations);
				loadExecutions(&executions);
				printf("Dados carregados em memória com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiro
				printf("\n\n-  2. Armazenar e ler as estruturas em ficheiro\n");

				// guardar os dados em ficheiros
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				writeMachines(MACHINES_FILENAME_BINARY, machines);
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				writeExecutions(EXECUTIONS_FILENAME_BINARY, executions);
				printf("Dados exportados com sucesso!\n");

				// libertar memória das listas anteriores, para serem lidas dos ficheiros
				//freeJobs(jobs);
				//freeMachines(machines);
				//freeOperations(operations);
				//freeExecutions(executions);

				// depois de libertar memória, definir listas como NULL para evitar possíveis erros
				jobs = NULL;
				machines = NULL;
				operations = NULL;
				executions = NULL;

				// ler dados de ficheiros
				jobs = readJobs(JOBS_FILENAME_BINARY);
				machines = readMachines(MACHINES_FILENAME_BINARY);
				operations = readOperations(OPERATIONS_FILENAME_BINARY);
				executions = readExecutions(EXECUTIONS_FILENAME_BINARY);
				printf("Dados importados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: remover um trabalho
				printf("\n\n-  3. Remover um trabalho\n");

				// remover trabalho
				deleteJob(&jobs, 3);
				printf("Trabalho removido com sucesso!\n");

				bool operationsAllFound = false;
				bool executionsAllFound = false;
				while (!operationsAllFound) // enquanto que encontrar trabalhos, remover as operações associadas
				{
					if (searchOperationByJob(operations, 3))
					{
						// remover operação
						int operationDeleted = deleteOperationByJob(&operations, 3);
						printf("Operação associada ao trabalho removida com sucesso!\n");

						while (!executionsAllFound) // enquanto que encontrar a respetiva operação, remover as execuções de operações associadas
						{
							if (searchExecutionByOperation(executions, operationDeleted))
							{
								// remover execução
								deleteExecutionByOperation(&executions, operationDeleted);
								printf("Execução associada à operação removida com sucesso!\n");
							}
							else
							{
								executionsAllFound = true;
							}
						}
						executionsAllFound = false; // necessário para voltar a percorrer o while acima, numva nova operação
					}
					else
					{
						operationsAllFound = true;
					}
				}
#pragma endregion

#pragma region funcionalidade 4: inserir um trabalho
				printf("\n\n-  4. Inserir um trabalho\n");

				// inserir novo trabalho
				Job* job = NULL;
				job = newJob(9);
				jobs = insertJobAtStart(jobs, job);

				// guardar a nova inserção em ficheiro
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 5: remover uma operação
				printf("\n\n-  5. Remover uma operação\n");

				// remover operação
				deleteOperation(&operations, 35);
				printf("Operação removida com sucesso!\n");

				bool allFound = false;
				while (!allFound) // enquanto que encontrar operações, remover as execuções de operações associadas
				{
					if (searchExecutionByOperation(executions, 35))
					{
						// remover execução
						deleteExecutionByOperation(&executions, 35);
						printf("Execução associada à operação removida com sucesso!\n");
					}
					else
					{
						allFound = true;
					}
				}
#pragma endregion

#pragma region funcionalidade 6: atualizar uma operação
				printf("\n\n-  6. Atualizar uma operação\n");

				// atualizar a posição de uma operação X pela posição de uma operação Y, e vice-versa
				updatePosition(&operations, 2, 4);
				printf("As posições das operações foram trocadas com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 7: inserir uma operação
				printf("\n\n-  7. Inserir uma operação\n");

				// inserir nova operação
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperationAtStart(operations, operation);

				// inserir nova execução de uma operação
				Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecutionAtStart(executions, execution);

				// guardar as novas inserções em ficheiros
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				writeExecutions(EXECUTIONS_FILENAME_BINARY, executions);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region mostrar dados
				printf("\n\n-  Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);
				printf("Máquinas:\n");
				displayMachines(machines);
				printf("Operações:\n");
				displayOperations(operations);
				printf("Execuções de Operações:\n");
				displayExecutions(executions);
				printf("Dados mostrados com sucesso!\n");

				// libertar memória
				//freeJobs(jobs);
				//freeMachines(machines);
				//freeOperations(operations);
				//freeExecutions(executions);

				// depois de libertar memória, definir listas como NULL para evitar possíveis erros
				jobs = NULL;
				machines = NULL;
				operations = NULL;
				executions = NULL;
#pragma endregion

				break;

			case 2:



				break;

			case 3: // sobre aplicação

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