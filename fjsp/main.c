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
	Machine* machines = NULL;
	Operation* operations = NULL;

	// tabela hash das execuções
	// { NULL } - todos os elementos (ponteiros) da tabela são NULL
	ExecutionNode* executionsTable[HASH_TABLE_SIZE] = { NULL };

	// matriz do plano de produção
	Cell plan[NUMBER_MACHINES][MAX_TIME];

	int menuOption = 0;

	do
	{
		// menu 
		printf("--------------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   Flexible Job Shop Problem\n");
		printf("   1 -> Carregar dados de exemplo\n");
		printf("   2 -> Carregar dados\n");
		printf("   3 -> Mostrar todos os dados\n");
		printf("   4 -> Remover todos os dados\n");
		printf("   5 -> Proposta de escalonamento\n");
		printf("   6 -> Inserir uma máquina\n");
		printf("   7 -> Atualizar uma máquina\n");
		printf("   8 -> Remover uma máquina\n");
		printf("   9 -> Inserir um trabalho\n");
		printf("   10 -> Atualizar um trabalho\n");
		printf("   11 -> Remover um trabalho\n");
		printf("   12 -> Inserir uma operação\n");
		printf("   13 -> Atualizar uma operação\n");
		printf("   14 -> Remover uma operação\n");
		printf("   15 -> Guardar dados\n");
		printf("   16 -> Sobre\n\n");
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
#pragma region opção 1: carregar dados de exemplo
				printf("-> Opção 1. Carregar dados de exemplo\n");

				// definir listas como NULL para limpar os dados
				cleanJobs(&jobs);
				cleanMachines(&machines);
				cleanOperations(&operations);
				cleanExecutions_Table(&executionsTable);
				// FALTA WORK PLANS

				// carregar listas em memória a partir de dados em código
				jobs = readJobs_Example();
				machines = readMachines_Example();
				operations = readOperations_Example();

				// carregar tabela hash em memória a partir de dados em código
				*executionsTable = readExecutions_AtTable_Example(executionsTable);

				// carregar listas em memória a partir de ficheiros binários
				// jobs = readJobs_Binary(JOBS_FILENAME_BINARY);
				// machines = readMachines_Binary(MACHINES_FILENAME_BINARY);
				// operations = readOperations_Binary(OPERATIONS_FILENAME_BINARY);

				// carregar tabela hash em memória a partir de um ficheiro binário
				// *executionsTable = readExecutions_AtTable_Binary(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados carregados em memória com sucesso!\n");
#pragma endregion
				break;

			case 2:
#pragma region opção 2: carregar dados
				printf("-> Opção 2. Carregar dados\n");

				// definir listas como NULL para limpar os dados
				cleanJobs(&jobs);
				cleanMachines(&machines);
				cleanOperations(&operations);
				cleanExecutions_Table(&executionsTable);
				// FALTA WORK PLANS

				// carregar listas em memória a partir de ficheiros .csv
				jobs = readJobs_Text(JOBS_FILENAME_TEXT);
				machines = readMachines_Text(MACHINES_FILENAME_TEXT);
				operations = readOperations_Text(OPERATIONS_FILENAME_TEXT);

				// carregar tabela hash em memória a partir de um ficheiro .csv
				*executionsTable = readExecutions_AtTable_Text(EXECUTIONS_FILENAME_TEXT, executionsTable);

				printf("Dados carregados com sucesso!\n");
#pragma endregion
				break;

			case 3:
#pragma region opção 3: Mostrar todos os dados
				printf("-> Opção 3. Mostrar todos os dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				bool hasJobs = displayJobs(jobs);
				if (!hasJobs) {
					printf("Não existem trabalhos.\n");
				}

				printf("Máquinas:\n");
				bool hasMachines = displayMachines(machines);
				if (!hasMachines) {
					printf("Não existem máquinas.\n");
				}

				printf("Operações:\n");
				bool hasOperations = displayOperations(operations);
				if (!hasOperations) {
					printf("Não existem execuções de operações.\n");
				}

				printf("Execuções de Operações:\n");
				bool hasExecutions = displayExecutions_AtTable(executionsTable);
				if (!hasExecutions) {
					printf("Não existem execuções de operações.\n");
				}

				printf("Plano de escalonamento:\n");
				bool hasPlan = displayPlan(plan);
				if (!hasPlan) {
					printf("Não existe um plano de escalonamento.\n");
				}
#pragma endregion
				break;

			case 4:
#pragma region opção 4: Remover todos os dados
				printf("-> Opção 4. Remover todos os dados\n");

				// definir listas como NULL para limpar os dados
				cleanJobs(&jobs);
				cleanMachines(&machines);
				cleanOperations(&operations);
				cleanExecutions_Table(&executionsTable);
				// FALTA WORK PLANS

				printf("Dados removidos com sucesso!\n");
#pragma endregion
				break;

			case 5:
#pragma region opção 5: proposta de escalonamento
				printf("-> Opção 5. Proposta de escalonamento\n");

				// carregar todos os dados das execuções para uma lista
				Execution* executions = readExecutions_AtList_Binary(EXECUTIONS_FILENAME_TEXT);

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

			case 6:
#pragma region opção 6: inserir uma máquina
				printf("-> Opção 6. Inserir uma máquina\n");

				Machine* machine = NULL;
				machine = newMachine(5, "Trabalho 5");
				machines = insertMachine_AtStart(machines, machine);

				printf("Máquina adicionada com sucesso!\n");
#pragma endregion
				break;

			case 7:
#pragma region opção 7: atualizar uma máquina
				printf("-> Opção 7. Atualizar uma máquina\n");
#pragma endregion
				break;

			case 8:
#pragma region opção 8: remover uma máquina
				printf("-> Opção 8. Remover uma máquina\n");
#pragma endregion
				break;

			case 9:
#pragma region opção 9: inserir um trabalho
				printf("-> Opção 9. Inserir um trabalho\n");

				Job* job = NULL;
				job = newJob(5, "Trabalho 5");
				jobs = insertJob_AtStart(jobs, job);

				printf("Trabalho adicionado com sucesso!\n");
#pragma endregion
				break;

			case 10:
#pragma region opção 10: atualizar um trabalho
				printf("-> Opção 10. Atualizar um trabalho\n");
#pragma endregion
				break;

			case 11:
#pragma region opção 11: remover um trabalho
				printf("-> Opção 11. Remover um trabalho\n");

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

			case 12:
#pragma region opção 12: inserir uma operação
				printf("-> Opção 12. Inserir uma operação\n");

				// inserir nova operação
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8, "Operação X");
				operations = insertOperation_AtStart(operations, operation);

				// inserir nova execução de uma operação
				Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				*executionsTable = insertExecution_AtTable(executionsTable, execution);

				printf("Novos dados guardados com sucesso!\n");
#pragma endregion
				break;

			case 13:
#pragma region opção 13: atualizar uma operação
				printf("-> Opção 13. Atualizar uma operação\n");

				// trocar a posição de uma operação pela outra e, vice-versa
				updateOperation_Position(&operations, 2, 4);
				printf("As posições das operações foram trocadas com sucesso!\n");

				// atualizar o tempo de uma execução de operação
				updateRuntime_ByOperation_AtTable(executionsTable, 4, 4, 10);
#pragma endregion
				break;

			case 14:
#pragma region opção 14: remover uma operação
				printf("-> Opção 14. Remover uma operação\n");

				// remover operação
				deleteOperation(&operations, 35);
				printf("Operação removida com sucesso!\n");

				// remover execuções associadas à operação
				deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
				printf("Execuções associadas à operação removidas com sucesso!\n");
#pragma endregion
				break;

			case 15:
#pragma region opção 15: guardar dados
				printf("-> Opção 15. Guardar dados\n");

				// guardar os dados em ficheiros .csv
				writeJobs_Text(JOBS_FILENAME_TEXT, jobs);
				writeMachines_Text(MACHINES_FILENAME_TEXT, machines);
				writeOperations_Text(OPERATIONS_FILENAME_TEXT, operations);
				writeExecutions_AtTable_Text(EXECUTIONS_FILENAME_TEXT, executionsTable);

				// guardar os dados em ficheiros binários
				// writeJobs_Binary(JOBS_FILENAME_BINARY, jobs);
				// writeMachines_Binary(MACHINES_FILENAME_BINARY, machines);
				// writeOperations_Binary(OPERATIONS_FILENAME_BINARY, operations);
				// writeExecutions_AtTable_Binary(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados guardados com sucesso!\n");
#pragma endregion
				break;

			case 16:
#pragma region opção 16: sobre
				printf("-> Opção 16. Sobre\n");

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