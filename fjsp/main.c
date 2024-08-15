/**
 * @brief	Ficheiro principal da aplicação, com menu e chamada de funções.
 * @file	main.c
 * @author	Luís Pereira
 * @date	15/08/2024
 *
 * -------------------
 *
 * Flexible Job Shop Problem - Solução de escalonamento para minimizar o tempo necessário
 * na produção de um determinado produto numa fábrica, que envolve várias operações e
 * a utilização de várias máquinas e seus colaboradores.
 * @see https://github.com/luispereira1999/fjsp
*/

#include <stdio.h>
#include <locale.h>
#include "data-types.h"
#include "lists.h"
#include "hashing.h"


/**
* @brief	Função principal do programa
* @return	Resultado do programa na linha de comandos
*/
int main()
{
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

	// listas
	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;

	// tabela hash das execuções
	ExecutionNode* executionsTable[HASH_TABLE_SIZE];

	// matriz do plano de produção
	Cell plan[NUMBER_MACHINES][MAX_TIME];

	int menuOption = 0;

	do
	{
		// menu 
		printf("--------------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   Flexible Job Shop Problem\n");
		printf("   1 -> Carregar dados em memória\n");
		printf("   2 -> Carregar dados de ficheiros\n");
		printf("   3 -> Guardar dados em ficheiros\n");
		printf("   4 -> Remover um trabalho\n");
		printf("   5 -> Inserir um trabalho\n");
		printf("   6 -> Remover uma operação\n");
		printf("   7 -> Atualizar uma operação\n");
		printf("   8 -> Inserir uma operação\n");
		printf("   9 -> Proposta de escalonamento\n");
		printf("   10 -> Mostrar dados\n");
		printf("   11 -> Sobre\n\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("--------------------------------------\n");
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
			case 1:
#pragma region opção 1: carregar dados em memória
				printf("-> Opção 1. Carregar dados em memória\n");

				// carregar listas em memória
				jobs = loadJobs(JOBS_FILENAME_TEXT);
				machines = loadMachines(MACHINES_FILENAME_TEXT);
				operations = loadOperations(OPERATIONS_FILENAME_TEXT);

				// carregar tabela hash em memória
				*executionsTable = loadExecutionsTable(EXECUTIONS_FILENAME_TEXT, executionsTable);

				printf("Dados carregados em memória com sucesso!\n");
#pragma endregion
				break;

			case 2:
#pragma region opção 2: carregar dados de ficheiros
				printf("-> Opção 2. Carregar dados de ficheiros\n");

				// definir listas como NULL para ficarem vazias para ler os dados de ficheiros
				freeJobs(&jobs);
				freeMachines(&machines);
				freeOperations(&operations);
				freeExecutions_Table(&executionsTable);

				// ler listas dos ficheiros
				jobs = readJobs(JOBS_FILENAME_BINARY);
				machines = readMachines(MACHINES_FILENAME_BINARY);
				operations = readOperations(OPERATIONS_FILENAME_BINARY);

				// ler hash table do ficheiro
				*executionsTable = createExecutionsTable(executionsTable);
				*executionsTable = readExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados importados com sucesso!\n");
#pragma endregion
				break;

			case 3:
#pragma region opção 3: guardar dados em ficheiros
				printf("-> Opção 3. Guardar dados em ficheiros\n");

				// guardar os dados em ficheiros
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				writeMachines(MACHINES_FILENAME_BINARY, machines);
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados exportados com sucesso!\n");
#pragma endregion
				break;

			case 4:
#pragma region opção 4: remover um trabalho
				printf("-> Opção 4. Remover um trabalho\n");

				// remover trabalho
				deleteJob(&jobs, 3);
				printf("trabalho removido com sucesso!\n");

				int operationDeleted = 0;

				do {
					// remover as operações associadas ao jobs
					operationDeleted = deleteOperation_ByJob(&operations, 3);
					printf("Operações associadas ao trabalho removida com sucesso!\n");

					// remover as execuções associadas a cada operação
					deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeleted);
					printf("Execuções associadas à operação removidas com sucesso!\n");
				} while (operationDeleted != -1);
#pragma endregion
				break;

			case 5:
#pragma region opção 5: inserir um trabalho
				printf("-> Opção 5. Inserir um trabalho\n");

				// inserir novo trabalho
				Job* job = NULL;
				job = newJob(9);
				jobs = insertJob_AtStart(jobs, job);

				// guardar a nova inserção em ficheiro
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion
				break;

			case 6:
#pragma region opção 6: remover uma operação
				printf("-> Opção 6. Remover uma operação\n");

				// remover operação
				deleteOperation(&operations, 35);
				printf("Operação removida com sucesso!\n");

				// remover execuções associadas à operação
				deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
				printf("Execuções associadas à operação removidas com sucesso!\n");
#pragma endregion
				break;

			case 7:
#pragma region opção 7: atualizar uma operação
				printf("-> Opção 7. Atualizar uma operação\n");

				// atualizar a posição de uma operação X pela posição de uma operação Y, e vice-versa
				updatePosition(&operations, 2, 4);
				printf("As posições das operações foram trocadas com sucesso!\n");

				// atualizar o tempo de uma execução de operação
				updateRuntime_ByOperation_AtTable(executionsTable, 4, 4, 10);
#pragma endregion
				break;

			case 8:
#pragma region opção 8: inserir uma operação
				printf("-> Opção 8. Inserir uma operação\n");

				// inserir nova operação
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperation_AtStart(operations, operation);

				// inserir nova execução de uma operação
				Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				*executionsTable = insertExecution_AtTable(executionsTable, execution);

				// guardar as novas inserções em ficheiros
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion
				break;

			case 9:
#pragma region opção 9: proposta de escalonamento
				printf("-> Opção 9. Proposta de escalonamento\n");

				// carregar todos os dados das execuções para uma lista
				Execution* executions = loadExecutions(EXECUTIONS_FILENAME_TEXT);

				// obter todos os planos de trabalhos necessários para realizar um plano de produção
				WorkPlan* workPlans = getAllWorkPlans(jobs, operations, executions);

				int fullTime = getFullTimeOfPlan(workPlans);
				printf("Tempo total do plano é %d!\n", fullTime);

				// ordenar planos pela posição das operações nos jobs
				workPlans = sortWorkPlans_ByJob(workPlans);

				// iniciar um plano de produção vazio
				startPlan(plan, -1, -1, -1);

				// preencher todo o plano
				fillAllPlan(plan, workPlans, 24); // teste: 24 = 3 operações de cada 8 trabalhos

				// exportar plano para ficheiro .csv
				FileCell* cells = getCellsToExport(plan);

				// ordenar células que serão exportadas por máquinas
				cells = sortFileCells_ByMachine(cells);

				// exportar plano para ficheiro .csv
				exportPlan(PLAN_FILENAME_TEXT, cells);

				printf("Plano escalonado e exportado com sucesso!\n");
#pragma endregion
				break;

			case 10:
#pragma region opção 10: mostrar dados
				printf("-> Opção 10. Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);

				printf("Máquinas:\n");
				displayMachines(machines);

				printf("Operações:\n");
				displayOperations(operations);

				printf("Execuções de Operações:\n");
				displayExecutions_AtTable(executionsTable);

				printf("Plano:\n");
				displayPlan(plan);

				printf("Dados mostrados com sucesso!\n");
#pragma endregion
				break;

#pragma region opção 11: sobre
			case 11:
				printf("-> Opção 11. Sobre\n");
				printf("Flexible Job Shop Problem - Solução de escalonamento para minimizar o tempo necessário na produção de um determinado produto numa fábrica, que envolve várias operações e a utilização de várias máquinas e seus colaboradores.\n");
				printf("Neste contexto, um trabalho refere-se a... e uma operação a...\n");
				printf("Projeto desenvolvido na unidade curricular Estruturas de Dados Avançadas, no âmbito do curso Licenciatura em Engenharia em Desenvolvimento de Jogos Digitais. Realizado no Instituto Politécnico do Cávado e do Ave, a 14 até 31 de março de 2022, durante o 2º semestre do 1º ano de curso.\n");
#pragma endregion
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