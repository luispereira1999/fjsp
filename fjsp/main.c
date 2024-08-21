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
	Machine* machines = NULL;
	Operation* operations = NULL;

	// tabela hash das execu��es
	// { NULL } - todos os elementos (ponteiros) da tabela s�o NULL
	ExecutionNode* executionsTable[HASH_TABLE_SIZE] = { NULL };
	
	// matriz do plano de produ��o
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
		printf("   6 -> Inserir uma m�quina\n");
		printf("   7 -> Atualizar nome de uma m�quina\n");
		printf("   8 -> Remover uma m�quina\n");
		printf("   9 -> Inserir um trabalho\n");
		printf("   10 -> Atualizar nome de um trabalho\n");
		printf("   11 -> Remover um trabalho\n");
		printf("   12 -> Inserir uma opera��o\n");
		printf("   13 -> Atualizar nome de uma opera��o\n");
		printf("   14 -> Trocar posi��o de 2 opera��es\n");
		printf("   15 -> Remover uma opera��o\n");
		printf("   16 -> Guardar dados\n");
		printf("   17 -> Sobre\n\n");
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
#pragma region op��o 1: carregar dados de exemplo
				printf("-> Op��o 1. Carregar dados de exemplo\n");

				// definir listas como NULL para limpar os dados
				cleanJobs(&jobs);
				cleanMachines(&machines);
				cleanOperations(&operations);
				cleanExecutions_Table(&executionsTable);
				// FALTA WORK PLANS ?

				// carregar listas em mem�ria a partir de dados em c�digo
				jobs = readJobs_Example();
				machines = readMachines_Example();
				operations = readOperations_Example();

				// carregar tabela hash em mem�ria a partir de dados em c�digo
				*executionsTable = readExecutions_AtTable_Example(executionsTable);

				printf("Dados carregados em mem�ria com sucesso!\n");
#pragma endregion
				break;

			case 2:
#pragma region op��o 2: carregar dados
				printf("-> Op��o 2. Carregar dados\n");

				// definir listas como NULL para limpar os dados
				cleanJobs(&jobs);
				cleanMachines(&machines);
				cleanOperations(&operations);
				cleanExecutions_Table(&executionsTable);
				// FALTA WORK PLANS ?

				// carregar listas em mem�ria a partir de ficheiros .csv
				jobs = readJobs_Text(JOBS_FILENAME_TEXT);
				machines = readMachines_Text(MACHINES_FILENAME_TEXT);
				operations = readOperations_Text(OPERATIONS_FILENAME_TEXT);

				// carregar tabela hash em mem�ria a partir de um ficheiro .csv
				*executionsTable = readExecutions_AtTable_Text(EXECUTIONS_FILENAME_TEXT, executionsTable);

				// carregar listas em mem�ria a partir de ficheiros bin�rios
				//jobs = readJobs_Binary(JOBS_FILENAME_BINARY);
				//machines = readMachines_Binary(MACHINES_FILENAME_BINARY);
				//operations = readOperations_Binary(OPERATIONS_FILENAME_BINARY);

				// carregar tabela hash em mem�ria a partir de um ficheiro bin�rio
				//*executionsTable = readExecutions_AtTable_Binary(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados carregados com sucesso!\n");
#pragma endregion
				break;

			case 3:
#pragma region op��o 3: Mostrar todos os dados
				printf("-> Op��o 3. Mostrar todos os dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				if (!displayJobs(jobs))
				{
					printf("N�o existem trabalhos.\n");
				}

				printf("M�quinas:\n");
				if (!displayMachines(machines))
				{
					printf("N�o existem m�quinas.\n");
				}

				printf("Opera��es:\n");
				if (!displayOperations(operations))
				{
					printf("N�o existem execu��es de opera��es.\n");
				}

				printf("Execu��es de Opera��es:\n");
				if (!displayExecutions_AtTable(executionsTable))
				{
					printf("N�o existem execu��es de opera��es.\n");
				}

				printf("Plano de escalonamento:\n");
				if (!displayPlan(plan))
				{
					printf("N�o existe um plano de escalonamento.\n");
				}
#pragma endregion
				break;

			case 4:
#pragma region op��o 4: Remover todos os dados
				printf("-> Op��o 4. Remover todos os dados\n");

				// definir listas como NULL para limpar os dados
				cleanJobs(&jobs);
				cleanMachines(&machines);
				cleanOperations(&operations);
				cleanExecutions_Table(&executionsTable);
				// FALTA WORK PLANS ?

				printf("Dados removidos com sucesso!\n");
#pragma endregion
				break;

			case 5:
#pragma region op��o 5: proposta de escalonamento
				printf("-> Op��o 5. Proposta de escalonamento\n");

				// carregar todos os dados das execu��es para uma lista
				Execution* executions = readExecutions_AtList_Binary(EXECUTIONS_FILENAME_TEXT);

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

			case 6:
#pragma region op��o 6: inserir uma m�quina
				printf("-> Op��o 6. Inserir uma m�quina\n");

				Machine* machine = NULL;
				machine = newMachine(machines, "Trabalho 5");
				machines = insertMachine_AtStart(machines, machine);

				printf("M�quina adicionada com sucesso!\n");
#pragma endregion
				break;

			case 7:
#pragma region op��o 7: atualizar nome de uma m�quina
				printf("-> Op��o 7. Atualizar nome de uma m�quina\n");

				if (!updateMachine(machines, 1, "M�quina A"))
				{
					printf("N�o foi poss�vel atualizar a m�quina.");
				}

				printf("M�quina atualizada com sucesso!\n");
#pragma endregion
				break;

			case 8:
#pragma region op��o 8: remover uma m�quina
				printf("-> Op��o 8. Remover uma m�quina\n");

				int machineToDelete = 3;

				// remover m�quina
				if (deleteMachine(&machines, machineToDelete))
				{
					printf("M�quina removida com sucesso!\n");

					// remover todas as execu��es de opera��es associadas � m�quina
					deleteExecutions_ByMachine_AtTable(executionsTable, machineToDelete);
					printf("Execu��es de opera��es associadas � m�quina removidas com sucesso!\n");
				}
				else {
					printf("N�o foi poss�vel remover a m�quina.\n");
				}
#pragma endregion
				break;

			case 9:
#pragma region op��o 9: inserir um trabalho
				printf("-> Op��o 9. Inserir um trabalho\n");

				Job* job = NULL;
				job = newJob(jobs, "Trabalho 5");
				jobs = insertJob_AtStart(jobs, job);

				printf("Trabalho adicionado com sucesso!\n");
#pragma endregion
				break;

			case 10:
#pragma region op��o 10: atualizar nome de um trabalho
				printf("-> Op��o 10. Atualizar nome de um trabalho\n");

				if (!updateJob(jobs, 2, "Trabalho A"))
				{
					printf("N�o foi poss�vel atualizar o trabalho.");
				}

				printf("Trabalho atualizado com sucesso!\n");
#pragma endregion
				break;

			case 11:
#pragma region op��o 11: remover um trabalho
				printf("-> Op��o 11. Remover um trabalho\n");

				int jobToDelete = 3;

				// remover trabalho
				if (deleteJob(&jobs, jobToDelete))
				{
					printf("Trabalho removido com sucesso!\n");

					int operationDeletedID = 0;

					do {
						// remover as opera��es associadas ao trabalho
						operationDeletedID = deleteOperation_ByJob(&operations, 3);
						printf("Opera��es associadas ao trabalho removida com sucesso!\n");

						// remover as execu��es de opera��es associadas a cada opera��o
						deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeletedID);
						printf("Execu��es de Opera��es associadas � opera��o removidas com sucesso!\n");
					} while (operationDeletedID != -1);
				}
				else {
					printf("N�o foi poss�vel remover o trabalho.\n");
				}
#pragma endregion
				break;

			case 12:
#pragma region op��o 12: inserir uma opera��o
				printf("-> Op��o 12. Inserir uma opera��o\n");

				// inserir nova opera��o
				Operation* operation = NULL;
				operation = newOperation(17, 2, 8, "Opera��o X");
				operations = insertOperation_AtStart(operations, operation);

				// inserir nova execu��o de uma opera��o
				Execution* execution = NULL;
				execution = newExecution(17, 5, 17);
				*executionsTable = insertExecution_AtTable(executionsTable, execution);

				printf("Novos dados guardados com sucesso!\n");
#pragma endregion
				break;

			case 13:
#pragma region op��o 13: atualizar nome de uma opere��o
				printf("-> Op��o 13. Atualizar nome de uma opere��o\n");

				if (!updateOperation_Name(operations, 2, "Opere��o A"))
				{
					printf("N�o foi poss�vel atualizar a opere��o.");
				}

				printf("Opere��o atualizada com sucesso!\n");
#pragma endregion
				break;

			case 14:
#pragma region op��o 14: trocar posi��o de 2 opera��es
				printf("-> Op��o 14. Trocar posi��o de 2 opera��es\n");

				// trocar a posi��o de uma opera��o pela outra e, vice-versa
				updateOperation_Position(&operations, 2, 4);
				printf("As posi��es das opera��es foram trocadas com sucesso!\n");

				// atualizar o tempo de uma execu��o de opera��o
				updateRuntime_ByOperation_AtTable(executionsTable, 4, 4, 10);
#pragma endregion
				break;

			case 15:
#pragma region op��o 15: remover uma opera��o
				printf("-> Op��o 15. Remover uma opera��o\n");

				// remover opera��o
				deleteOperation(&operations, 35);
				printf("Opera��o removida com sucesso!\n");

				// remover execu��es associadas � opera��o
				deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
				printf("Execu��es associadas � opera��o removidas com sucesso!\n");
#pragma endregion
				break;

			case 16:
#pragma region op��o 16: guardar dados
				printf("-> Op��o 16. Guardar dados\n");

				// guardar os dados em ficheiros .csv
				writeJobs_Text(JOBS_FILENAME_TEXT, jobs);
				writeMachines_Text(MACHINES_FILENAME_TEXT, machines);
				writeOperations_Text(OPERATIONS_FILENAME_TEXT, operations);
				writeExecutions_AtTable_Text(EXECUTIONS_FILENAME_TEXT, executionsTable);

				// guardar os dados em ficheiros bin�rios
				//writeJobs_Binary(JOBS_FILENAME_BINARY, jobs);
				//writeMachines_Binary(MACHINES_FILENAME_BINARY, machines);
				//writeOperations_Binary(OPERATIONS_FILENAME_BINARY, operations);
				//writeExecutions_AtTable_Binary(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados guardados com sucesso!\n");
#pragma endregion
				break;

			case 17:
#pragma region op��o 17: sobre
				printf("-> Op��o 17. Sobre\n");

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

	// libertar mem�ria das estruturas din�micas antes de fechar o programa
	cleanJobs(&jobs);
	cleanMachines(&machines);
	cleanOperations(&operations);
	cleanExecutions_Table(&executionsTable);
	// FALTA WORK PLANS ?

	return true;
}