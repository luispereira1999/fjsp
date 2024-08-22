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
#include "utils.h"


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
		printf("   9 -> Inserir uma tarefa\n");
		printf("   10 -> Atualizar nome de uma tarefa\n");
		printf("   11 -> Remover uma tarefa\n");
		printf("   12 -> Inserir uma opera��o\n");
		printf("   13 -> Atualizar nome de uma opera��o\n");
		printf("   14 -> Atualizar tempo de uma execu��o de opera��o\n");
		printf("   15 -> Trocar ordem de 2 opera��es\n");
		printf("   16 -> Remover uma opera��o\n");
		printf("   17 -> Guardar dados\n");
		printf("   18 -> Sobre\n\n");
		printf("   � Lu�s Pereira | 2022\n\n");
		printf("--------------------------------------\n");
		printf("Escolha uma das op��es acima: ");

		if (!scanf("%d", &menuOption)) // se n�o introduzir um n�mero
		{
			fseek(stdin, 0, SEEK_END); // limpar buffer de entrada para evitar ciclo infinito
			printf("\n");
			printf("Op��o inv�lido, tente novamente.\n");
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
				printf("M�quinas:\n");
				if (!displayMachines(machines))
				{
					printf("N�o existem m�quinas.\n");
				}

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("N�o existem tarefas.\n");
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

				printf("M�quinas:\n");
				if (!displayMachines(machines))
				{
					printf("N�o existem m�quinas.\n");
				}

				fseek(stdin, 0, SEEK_END);

				char newMachineName[NAME_SIZE];
				printf("Introduza o nome da nova m�quina: ");
				fgets(newMachineName, sizeof(newMachineName), stdin);

				removeNewLine(newMachineName); // remover a nova linha do final da string

				Machine* machine = newMachine(machines, newMachineName);
				if (machine == NULL)
				{
					printf("N�o foi poss�vel adicionar a m�quina.\n");
					break;
				}

				machines = insertMachine_AtStart(machines, machine);
				printf("M�quina adicionada com sucesso!\n");
#pragma endregion
				break;

			case 7:
#pragma region op��o 7: atualizar nome de uma m�quina
				printf("-> Op��o 7. Atualizar nome de uma m�quina\n");

				printf("M�quinas:\n");
				if (!displayMachines(machines))
				{
					printf("N�o existem m�quinas.\n");
					break;
				}

				int machineIdToUpdate;
				printf("Introduza o ID da m�quina a ser atualizada: ");
				scanf("%d", &machineIdToUpdate);

				fseek(stdin, 0, SEEK_END);

				char updatedMachineName[NAME_SIZE];
				printf("Introduza o novo nome da m�quina: ");
				fgets(updatedMachineName, sizeof(updatedMachineName), stdin);

				removeNewLine(updatedMachineName);

				if (!updateMachine(machines, machineIdToUpdate, updatedMachineName))
				{
					printf("N�o foi poss�vel atualizar a m�quina.\n");
					break;
				}

				printf("M�quina atualizada com sucesso!\n");
#pragma endregion
				break;

			case 8:
#pragma region op��o 8: remover uma m�quina
				printf("-> Op��o 8. Remover uma m�quina\n");

				printf("M�quinas:\n");
				if (!displayMachines(machines))
				{
					printf("N�o existem m�quinas.\n");
					break;
				}

				int machineIdToDelete;
				printf("Introduza o ID da m�quina a ser removida: ");
				scanf("%d", &machineIdToDelete);

				if (!deleteMachine(&machines, machineIdToDelete))
				{
					printf("N�o foi poss�vel remover a m�quina.\n");
					break;
				}

				printf("M�quina removida com sucesso!\n");

				// remover todas as execu��es de opera��es associadas � m�quina
				deleteExecutions_ByMachine_AtTable(executionsTable, machineIdToDelete);
				printf("Execu��es de opera��es associadas � m�quina removidas com sucesso!\n");
#pragma endregion
				break;

			case 9:
#pragma region op��o 9: inserir uma tarefa
				printf("-> Op��o 9. Inserir uma tarefa\n");

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("N�o existem tarefas.\n");
				}

				fseek(stdin, 0, SEEK_END);

				char newJobName[NAME_SIZE];
				printf("Introduza o nome da nova tarefa: ");
				fgets(newJobName, sizeof(newJobName), stdin);

				removeNewLine(newJobName);

				Job* job = newJob(jobs, newJobName);
				if (job == NULL)
				{
					printf("N�o foi poss�vel adicionar a tarefa.\n");
					break;
				}

				jobs = insertJob_AtStart(jobs, job);
				printf("Tarefa adicionada com sucesso!\n");
#pragma endregion
				break;

			case 10:
#pragma region op��o 10: atualizar nome de uma tarefa
				printf("-> Op��o 10. Atualizar nome de uma tarefa\n");

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("N�o existem tarefas.\n");
					break;
				}

				int jobIdToUpdate;
				printf("Introduza o ID da tarefa a ser atualizado: ");
				scanf("%d", &jobIdToUpdate);

				fseek(stdin, 0, SEEK_END);

				char updatedJobName[NAME_SIZE];
				printf("Introduza o novo nome da tarefa: ");
				fgets(updatedJobName, sizeof(updatedJobName), stdin);

				removeNewLine(updatedJobName);

				if (!updateJob(jobs, jobIdToUpdate, updatedJobName))
				{
					printf("N�o foi poss�vel atualizar a tarefa.\n");
					break;
				}

				printf("Tarefa atualizada com sucesso!\n");
#pragma endregion
				break;

			case 11:
#pragma region op��o 11: remover uma tarefa
				printf("-> Op��o 11. Remover uma tarefa\n");

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("N�o existem tarefas.\n");
					break;
				}

				int jobIdToDelete;
				printf("Introduza o ID da tarefa a ser removida: ");
				scanf("%d", &jobIdToDelete);

				if (!deleteJob(&jobs, jobIdToDelete))
				{
					printf("N�o foi poss�vel remover a tarefa.\n");
					break;
				}

				printf("Tarefa removida com sucesso!\n");

				int operationDeletedID = 0;
				int machineID = 0;

				do
				{
					// remover as opera��es associadas � tarefa
					operationDeletedID = deleteOperation_ByJob(&operations, jobIdToDelete);
					printf("operationDeletedID:%d\n", operationDeletedID);

					// remover as execu��es de opera��es associadas a cada opera��o
					deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeletedID);
				} while (operationDeletedID != -1);

				printf("Opera��es associadas � tarefa removidas com sucesso!\n");
				printf("Execu��es de Opera��es associadas � opera��o removidas com sucesso!\n");
#pragma endregion
				break;

			case 12:
#pragma region op��o 12: inserir uma opera��o
				printf("-> Op��o 12. Inserir uma opera��o\n");

				printf("M�quinas:\n");
				if (!displayMachines(machines))
				{
					printf("N�o existem m�quinas.\n");
				}

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("N�o existem tarefas.\n");
				}

				printf("Opera��es:\n");
				if (!displayOperations(operations))
				{
					printf("N�o existem opera��es.\n");
				}

				printf("Execu��es de Opera��es:\n");
				if (!displayExecutions_AtTable(executionsTable))
				{
					printf("N�o existem execu��es de opera��es.\n");
				}

				int jobIdToInsertOperation;
				printf("Introduza o ID da tarefa � qual deseja adicionar a opera��o: ");
				scanf("%d", &jobIdToInsertOperation);

				int positionToInsertOperation;
				printf("Introduza a ordem de execu��o da opera��o dentro da tarefa: ");
				scanf("%d", &positionToInsertOperation);

				fseek(stdin, 0, SEEK_END);

				char newOperationName[NAME_SIZE];
				printf("Introduza o novo nome da opera��o: ");
				fgets(newOperationName, sizeof(newOperationName), stdin);

				removeNewLine(newOperationName);

				int machineIdToInsertOperation;
				printf("Introduza o ID da m�quina onde a opera��o ser� realizada: ");
				scanf("%d", &machineIdToInsertOperation);

				int runtimeToInsertExecution;
				printf("Introduza o tempo de execu��o associada � execu��o da opera��o: ");
				scanf("%d", &runtimeToInsertExecution);

				Operation* operation = newOperation(operations, jobIdToInsertOperation, positionToInsertOperation, newOperationName);
				if (operation == NULL)
				{
					printf("N�o foi poss�vel adicionar a opera��o.\n");
					break;
				}

				// inserir nova opera��o
				operations = insertOperation_AtStart(operations, operation);
				if (operations == NULL)
				{
					printf("N�o foi poss�vel adicionar a opera��o.\n");
					break;
				}

				printf("Opera��o adicionada com sucesso!\n");

				Execution* execution = newExecution(operation->operationID, machineIdToInsertOperation, runtimeToInsertExecution);
				if (execution == NULL)
				{
					printf("N�o foi poss�vel adicionar a execu��o de opera��o.\n");
					break;
				}

				// inserir nova execu��o de uma opera��o
				*executionsTable = insertExecution_AtTable(executionsTable, execution);
				printf("Execu��o de opera��o adicionada com sucesso!\n");
#pragma endregion
				break;

			case 13:
#pragma region op��o 13: atualizar nome de uma opere��o
				printf("-> Op��o 13. Atualizar nome de uma opere��o\n");

				printf("Opera��es:\n");
				if (!displayOperations(operations))
				{
					printf("N�o existem opera��es.\n");
					break;
				}

				int operationIdToUpdate;
				printf("Introduza o ID da opere��o a ser atualizada: ");
				scanf("%d", &operationIdToUpdate);

				fseek(stdin, 0, SEEK_END);

				char updatedOperationName[NAME_SIZE];
				printf("Introduza o novo nome da opere��o: ");
				fgets(updatedOperationName, sizeof(updatedOperationName), stdin);

				removeNewLine(updatedOperationName);

				if (!updateOperation_Name(operations, operationIdToUpdate, updatedOperationName))
				{
					printf("N�o foi poss�vel atualizar a opere��o.\n");
					break;
				}

				printf("Opere��o atualizada com sucesso!\n");
#pragma endregion
				break;

			case 14:
#pragma region op��o 14: atualizar tempo de uma execu��o de opera��o
				printf("-> Op��o 14. Atualizar tempo de uma execu��o de opera��o\n");

				printf("Execu��es de Opera��es:\n");
				if (!displayExecutions_AtTable(executionsTable))
				{
					printf("N�o existem execu��es de opera��es.\n");
				}

				int operationIdToUpdateRuntime;
				printf("Introduza o ID da opera��o: ");
				scanf("%d", &operationIdToUpdateRuntime);

				int machineIdToUpdateRuntime;
				printf("Introduza o ID da m�quina: ");
				scanf("%d", &machineIdToUpdateRuntime);

				int runtimeToUpdateRuntime;
				printf("Introduza o novo tempo de execu��o: ");
				scanf("%d", &runtimeToUpdateRuntime);

				if (!updateRuntime_ByOperation_AtTable(&executionsTable, operationIdToUpdateRuntime, machineIdToUpdateRuntime, runtimeToUpdateRuntime))
				{
					printf("N�o foi poss�vel atualizar a execu��o de opere��o.\n");
					break;
				}

				printf("Execu��o de opere��o atualizada com sucesso!\n");
#pragma endregion
				break;

			case 15:
#pragma region op��o 15: trocar ordem de 2 opera��es
				printf("-> Op��o 15. Trocar ordem de 2 opera��es\n");

				printf("Opera��es:\n");
				if (!displayOperations(operations))
				{
					printf("N�o existem opera��es.\n");
					break;
				}

				int jobIdToUpdatePositions;
				printf("Introduza o ID da tarefa que as posi��es fazem parte: ");
				scanf("%d", &jobIdToUpdatePositions);

				int operation1IdToUpdate;
				printf("Introduza o ID da 1� opere��o para trocar: ");
				scanf("%d", &operation1IdToUpdate);

				int operation2IdToUpdate;
				printf("Introduza o ID da 2� opere��o para trocar: ");
				scanf("%d", &operation2IdToUpdate);

				if (!updateOperation_Position(&operations, jobIdToUpdatePositions, operation1IdToUpdate, operation2IdToUpdate))
				{
					printf("N�o foi poss�vel atualizar a execu��o de opere��o.\n");
					break;
				}

				printf("Ordem das opera��es trocadas com sucesso!\n");
#pragma endregion
				break;

			case 16:
#pragma region op��o 16: remover uma opera��o
				printf("-> Op��o 16. Remover uma opera��o\n");

				printf("Opera��es:\n");
				if (!displayOperations(operations))
				{
					printf("N�o existem opera��es.\n");
					break;
				}

				int operationIdToDelete;
				printf("Introduza o ID da opera��o a ser removida: ");
				scanf("%d", &operationIdToDelete);

				// remover opera��o
				if (!deleteOperation(&operations, operationIdToDelete))
				{
					printf("N�o foi poss�vel remover a opera��o.\n");
					break;
				}

				printf("Opera��o removida com sucesso!\n");

				// remover execu��es de opera��es associadas � opera��o
				if (!deleteExecutions_ByOperation_AtTable(&executionsTable, operationIdToDelete))
				{
					printf("N�o foi poss�vel remover as execu��es de opera��es associadas � opera��o.\n");
					break;
				}

				printf("Execu��es de opera��es associadas � opera��o removidas com sucesso!\n");
#pragma endregion
				break;

			case 17:
#pragma region op��o 17: guardar dados
				printf("-> Op��o 17. Guardar dados\n");

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

			case 18:
#pragma region op��o 18: sobre
				printf("-> Op��o 18. Sobre\n");

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