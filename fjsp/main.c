/**
 * @brief	Ficheiro principal da aplica��o, com menu e chamada de fun��es.
 * @file	main.c
 * @author	Lu�s Pereira
 * @date	15/08/2024
 *
 * -------------------
 *
 * Flexible Job Shop Problem - Solu��o de escalonamento para minimizar o tempo necess�rio
 * na produ��o de um determinado produto numa f�brica, que envolve v�rias opera��es e
 * a utiliza��o de v�rias m�quinas e seus colaboradores.
 * @see https://github.com/luispereira1999/fjsp
*/

#include <stdio.h>
#include <locale.h>
#include "data-types.h"
#include "lists.h"
#include "hashing.h"


/**
* @brief	Fun��o principal do programa
* @return	Resultado do programa na linha de comandos
*/
int main()
{
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

	// listas
	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;

	// tabela hash das execu��es
	ExecutionNode* executionsTable[HASH_TABLE_SIZE];

	// matriz do plano de produ��o
	Cell plan[NUMBER_MACHINES][MAX_TIME];

	int menuOption = 0;

	do
	{
		// menu 
		printf("--------------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   Flexible Job Shop Problem\n");
		printf("   1 -> Carregar dados em mem�ria\n");
		printf("   2 -> Carregar dados de ficheiros\n");
		printf("   3 -> Guardar dados em ficheiros\n");
		printf("   4 -> Remover um trabalho\n");
		printf("   5 -> Inserir um trabalho\n");
		printf("   6 -> Remover uma opera��o\n");
		printf("   7 -> Atualizar uma opera��o\n");
		printf("   8 -> Inserir uma opera��o\n");
		printf("   9 -> Proposta de escalonamento\n");
		printf("   10 -> Mostrar dados\n");
		printf("   11 -> Sobre\n\n");
		printf("   � Lu�s Pereira | 2022\n\n");
		printf("--------------------------------------\n");
		printf("Escolha uma das op��es acima: ");

		if (!scanf("%d", &menuOption)) // se n�o introduzir um n�mero
		{
			fseek(stdin, 0, SEEK_END); // repor buffer de entrada para evitar ciclo infinito
			printf("\n");
			printf("O car�cter introduzido n�o � v�lido. Tente outro.\n");
		}
		else
		{
			printf("\n");

			switch (menuOption)
			{
			case 1:
#pragma region op��o 1: carregar dados em mem�ria
				printf("-> Op��o 1. Carregar dados em mem�ria\n");

				// carregar listas em mem�ria
				jobs = loadJobs(JOBS_FILENAME_TEXT);
				machines = loadMachines(MACHINES_FILENAME_TEXT);
				operations = loadOperations(OPERATIONS_FILENAME_TEXT);

				// carregar tabela hash em mem�ria
				*executionsTable = loadExecutionsTable(EXECUTIONS_FILENAME_TEXT, executionsTable);

				printf("Dados carregados em mem�ria com sucesso!\n");
#pragma endregion
				break;

			case 2:
#pragma region op��o 2: carregar dados de ficheiros
				printf("-> Op��o 2. Carregar dados de ficheiros\n");

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
#pragma region op��o 3: guardar dados em ficheiros
				printf("-> Op��o 3. Guardar dados em ficheiros\n");

				// guardar os dados em ficheiros
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				writeMachines(MACHINES_FILENAME_BINARY, machines);
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados exportados com sucesso!\n");
#pragma endregion
				break;

			case 4:
#pragma region op��o 4: remover um trabalho
				printf("-> Op��o 4. Remover um trabalho\n");

				// remover trabalho
				deleteJob(&jobs, 3);
				printf("trabalho removido com sucesso!\n");

				int operationDeleted = 0;

				do {
					// remover as opera��es associadas ao jobs
					operationDeleted = deleteOperation_ByJob(&operations, 3);
					printf("Opera��es associadas ao trabalho removida com sucesso!\n");

					// remover as execu��es associadas a cada opera��o
					deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeleted);
					printf("Execu��es associadas � opera��o removidas com sucesso!\n");
				} while (operationDeleted != -1);
#pragma endregion
				break;

			case 5:
#pragma region op��o 5: inserir um trabalho
				printf("-> Op��o 5. Inserir um trabalho\n");

				// inserir novo trabalho
				Job* job = NULL;
				job = newJob(9);
				jobs = insertJob_AtStart(jobs, job);

				// guardar a nova inser��o em ficheiro
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion
				break;

			case 6:
#pragma region op��o 6: remover uma opera��o
				printf("-> Op��o 6. Remover uma opera��o\n");

				// remover opera��o
				deleteOperation(&operations, 35);
				printf("Opera��o removida com sucesso!\n");

				// remover execu��es associadas � opera��o
				deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
				printf("Execu��es associadas � opera��o removidas com sucesso!\n");
#pragma endregion
				break;

			case 7:
#pragma region op��o 7: atualizar uma opera��o
				printf("-> Op��o 7. Atualizar uma opera��o\n");

				// atualizar a posi��o de uma opera��o X pela posi��o de uma opera��o Y, e vice-versa
				updatePosition(&operations, 2, 4);
				printf("As posi��es das opera��es foram trocadas com sucesso!\n");

				// atualizar o tempo de uma execu��o de opera��o
				updateRuntime_ByOperation_AtTable(executionsTable, 4, 4, 10);
#pragma endregion
				break;

			case 8:
#pragma region op��o 8: inserir uma opera��o
				printf("-> Op��o 8. Inserir uma opera��o\n");

				// inserir nova opera��o
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperation_AtStart(operations, operation);

				// inserir nova execu��o de uma opera��o
				Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				*executionsTable = insertExecution_AtTable(executionsTable, execution);

				// guardar as novas inser��es em ficheiros
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion
				break;

			case 9:
#pragma region op��o 9: proposta de escalonamento
				printf("-> Op��o 9. Proposta de escalonamento\n");

				// carregar todos os dados das execu��es para uma lista
				Execution* executions = loadExecutions(EXECUTIONS_FILENAME_TEXT);

				// obter todos os planos de trabalhos necess�rios para realizar um plano de produ��o
				WorkPlan* workPlans = getAllWorkPlans(jobs, operations, executions);

				int fullTime = getFullTimeOfPlan(workPlans);
				printf("Tempo total do plano � %d!\n", fullTime);

				// ordenar planos pela posi��o das opera��es nos jobs
				workPlans = sortWorkPlans_ByJob(workPlans);

				// iniciar um plano de produ��o vazio
				startPlan(plan, -1, -1, -1);

				// preencher todo o plano
				fillAllPlan(plan, workPlans, 24); // teste: 24 = 3 opera��es de cada 8 trabalhos

				// exportar plano para ficheiro .csv
				FileCell* cells = getCellsToExport(plan);

				// ordenar c�lulas que ser�o exportadas por m�quinas
				cells = sortFileCells_ByMachine(cells);

				// exportar plano para ficheiro .csv
				exportPlan(PLAN_FILENAME_TEXT, cells);

				printf("Plano escalonado e exportado com sucesso!\n");
#pragma endregion
				break;

			case 10:
#pragma region op��o 10: mostrar dados
				printf("-> Op��o 10. Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);

				printf("M�quinas:\n");
				displayMachines(machines);

				printf("Opera��es:\n");
				displayOperations(operations);

				printf("Execu��es de Opera��es:\n");
				displayExecutions_AtTable(executionsTable);

				printf("Plano:\n");
				displayPlan(plan);

				printf("Dados mostrados com sucesso!\n");
#pragma endregion
				break;

#pragma region op��o 11: sobre
			case 11:
				printf("-> Op��o 11. Sobre\n");
				printf("Flexible Job Shop Problem - Solu��o de escalonamento para minimizar o tempo necess�rio na produ��o de um determinado produto numa f�brica, que envolve v�rias opera��es e a utiliza��o de v�rias m�quinas e seus colaboradores.\n");
				printf("Neste contexto, um trabalho refere-se a... e uma opera��o a...\n");
				printf("Projeto desenvolvido na unidade curricular Estruturas de Dados Avan�adas, no �mbito do curso Licenciatura em Engenharia em Desenvolvimento de Jogos Digitais. Realizado no Instituto Polit�cnico do C�vado e do Ave, a 14 at� 31 de mar�o de 2022, durante o 2� semestre do 1� ano de curso.\n");
#pragma endregion
				break;

			default:
				printf("Op��o inv�lida. Tente novamente.\n");
				break;
			}
		}

		printf("\n");
	} while (true);

	return true;
}