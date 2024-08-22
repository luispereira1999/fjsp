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
#include "utils.h"


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
		printf("   7 -> Atualizar nome de uma máquina\n");
		printf("   8 -> Remover uma máquina\n");
		printf("   9 -> Inserir uma tarefa\n");
		printf("   10 -> Atualizar nome de uma tarefa\n");
		printf("   11 -> Remover uma tarefa\n");
		printf("   12 -> Inserir uma operação\n");
		printf("   13 -> Atualizar nome de uma operação\n");
		printf("   14 -> Atualizar tempo de uma execução de operação\n");
		printf("   15 -> Trocar ordem de 2 operações\n");
		printf("   16 -> Remover uma operação\n");
		printf("   17 -> Guardar dados\n");
		printf("   18 -> Sobre\n\n");
		printf("   © Luís Pereira | 2022\n\n");
		printf("--------------------------------------\n");
		printf("Escolha uma das opções acima: ");

		if (!scanf("%d", &menuOption)) // se não introduzir um número
		{
			fseek(stdin, 0, SEEK_END); // limpar buffer de entrada para evitar ciclo infinito
			printf("\n");
			printf("Opção inválido, tente novamente.\n");
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
				// FALTA WORK PLANS ?

				// carregar listas em memória a partir de dados em código
				jobs = readJobs_Example();
				machines = readMachines_Example();
				operations = readOperations_Example();

				// carregar tabela hash em memória a partir de dados em código
				*executionsTable = readExecutions_AtTable_Example(executionsTable);

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
				// FALTA WORK PLANS ?

				// carregar listas em memória a partir de ficheiros .csv
				jobs = readJobs_Text(JOBS_FILENAME_TEXT);
				machines = readMachines_Text(MACHINES_FILENAME_TEXT);
				operations = readOperations_Text(OPERATIONS_FILENAME_TEXT);

				// carregar tabela hash em memória a partir de um ficheiro .csv
				*executionsTable = readExecutions_AtTable_Text(EXECUTIONS_FILENAME_TEXT, executionsTable);

				// carregar listas em memória a partir de ficheiros binários
				//jobs = readJobs_Binary(JOBS_FILENAME_BINARY);
				//machines = readMachines_Binary(MACHINES_FILENAME_BINARY);
				//operations = readOperations_Binary(OPERATIONS_FILENAME_BINARY);

				// carregar tabela hash em memória a partir de um ficheiro binário
				//*executionsTable = readExecutions_AtTable_Binary(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados carregados com sucesso!\n");
#pragma endregion
				break;

			case 3:
#pragma region opção 3: Mostrar todos os dados
				printf("-> Opção 3. Mostrar todos os dados\n");

				// mostrar dados na consola
				printf("Máquinas:\n");
				if (!displayMachines(machines))
				{
					printf("Não existem máquinas.\n");
				}

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("Não existem tarefas.\n");
				}

				printf("Operações:\n");
				if (!displayOperations(operations))
				{
					printf("Não existem execuções de operações.\n");
				}

				printf("Execuções de Operações:\n");
				if (!displayExecutions_AtTable(executionsTable))
				{
					printf("Não existem execuções de operações.\n");
				}

				printf("Plano de escalonamento:\n");
				if (!displayPlan(plan))
				{
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
				// FALTA WORK PLANS ?

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

				printf("Máquinas:\n");
				if (!displayMachines(machines))
				{
					printf("Não existem máquinas.\n");
				}

				fseek(stdin, 0, SEEK_END);

				char newMachineName[NAME_SIZE];
				printf("Introduza o nome da nova máquina: ");
				fgets(newMachineName, sizeof(newMachineName), stdin);

				removeNewLine(newMachineName); // remover a nova linha do final da string

				Machine* machine = newMachine(machines, newMachineName);
				if (machine == NULL)
				{
					printf("Não foi possível adicionar a máquina.\n");
					break;
				}

				machines = insertMachine_AtStart(machines, machine);
				printf("Máquina adicionada com sucesso!\n");
#pragma endregion
				break;

			case 7:
#pragma region opção 7: atualizar nome de uma máquina
				printf("-> Opção 7. Atualizar nome de uma máquina\n");

				printf("Máquinas:\n");
				if (!displayMachines(machines))
				{
					printf("Não existem máquinas.\n");
					break;
				}

				int machineIdToUpdate;
				printf("Introduza o ID da máquina a ser atualizada: ");
				scanf("%d", &machineIdToUpdate);

				fseek(stdin, 0, SEEK_END);

				char updatedMachineName[NAME_SIZE];
				printf("Introduza o novo nome da máquina: ");
				fgets(updatedMachineName, sizeof(updatedMachineName), stdin);

				removeNewLine(updatedMachineName);

				if (!updateMachine(machines, machineIdToUpdate, updatedMachineName))
				{
					printf("Não foi possível atualizar a máquina.\n");
					break;
				}

				printf("Máquina atualizada com sucesso!\n");
#pragma endregion
				break;

			case 8:
#pragma region opção 8: remover uma máquina
				printf("-> Opção 8. Remover uma máquina\n");

				printf("Máquinas:\n");
				if (!displayMachines(machines))
				{
					printf("Não existem máquinas.\n");
					break;
				}

				int machineIdToDelete;
				printf("Introduza o ID da máquina a ser removida: ");
				scanf("%d", &machineIdToDelete);

				if (!deleteMachine(&machines, machineIdToDelete))
				{
					printf("Não foi possível remover a máquina.\n");
					break;
				}

				printf("Máquina removida com sucesso!\n");

				// remover todas as execuções de operações associadas à máquina
				deleteExecutions_ByMachine_AtTable(executionsTable, machineIdToDelete);
				printf("Execuções de operações associadas à máquina removidas com sucesso!\n");
#pragma endregion
				break;

			case 9:
#pragma region opção 9: inserir uma tarefa
				printf("-> Opção 9. Inserir uma tarefa\n");

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("Não existem tarefas.\n");
				}

				fseek(stdin, 0, SEEK_END);

				char newJobName[NAME_SIZE];
				printf("Introduza o nome da nova tarefa: ");
				fgets(newJobName, sizeof(newJobName), stdin);

				removeNewLine(newJobName);

				Job* job = newJob(jobs, newJobName);
				if (job == NULL)
				{
					printf("Não foi possível adicionar a tarefa.\n");
					break;
				}

				jobs = insertJob_AtStart(jobs, job);
				printf("Tarefa adicionada com sucesso!\n");
#pragma endregion
				break;

			case 10:
#pragma region opção 10: atualizar nome de uma tarefa
				printf("-> Opção 10. Atualizar nome de uma tarefa\n");

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("Não existem tarefas.\n");
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
					printf("Não foi possível atualizar a tarefa.\n");
					break;
				}

				printf("Tarefa atualizada com sucesso!\n");
#pragma endregion
				break;

			case 11:
#pragma region opção 11: remover uma tarefa
				printf("-> Opção 11. Remover uma tarefa\n");

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("Não existem tarefas.\n");
					break;
				}

				int jobIdToDelete;
				printf("Introduza o ID da tarefa a ser removida: ");
				scanf("%d", &jobIdToDelete);

				if (!deleteJob(&jobs, jobIdToDelete))
				{
					printf("Não foi possível remover a tarefa.\n");
					break;
				}

				printf("Tarefa removida com sucesso!\n");

				int operationDeletedID = 0;
				int machineID = 0;

				do
				{
					// remover as operações associadas à tarefa
					operationDeletedID = deleteOperation_ByJob(&operations, jobIdToDelete);
					printf("operationDeletedID:%d\n", operationDeletedID);

					// remover as execuções de operações associadas a cada operação
					deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeletedID);
				} while (operationDeletedID != -1);

				printf("Operações associadas à tarefa removidas com sucesso!\n");
				printf("Execuções de Operações associadas à operação removidas com sucesso!\n");
#pragma endregion
				break;

			case 12:
#pragma region opção 12: inserir uma operação
				printf("-> Opção 12. Inserir uma operação\n");

				printf("Máquinas:\n");
				if (!displayMachines(machines))
				{
					printf("Não existem máquinas.\n");
				}

				printf("Tarefas:\n");
				if (!displayJobs(jobs))
				{
					printf("Não existem tarefas.\n");
				}

				printf("Operações:\n");
				if (!displayOperations(operations))
				{
					printf("Não existem operações.\n");
				}

				printf("Execuções de Operações:\n");
				if (!displayExecutions_AtTable(executionsTable))
				{
					printf("Não existem execuções de operações.\n");
				}

				int jobIdToInsertOperation;
				printf("Introduza o ID da tarefa à qual deseja adicionar a operação: ");
				scanf("%d", &jobIdToInsertOperation);

				int positionToInsertOperation;
				printf("Introduza a ordem de execução da operação dentro da tarefa: ");
				scanf("%d", &positionToInsertOperation);

				fseek(stdin, 0, SEEK_END);

				char newOperationName[NAME_SIZE];
				printf("Introduza o novo nome da operação: ");
				fgets(newOperationName, sizeof(newOperationName), stdin);

				removeNewLine(newOperationName);

				int machineIdToInsertOperation;
				printf("Introduza o ID da máquina onde a operação será realizada: ");
				scanf("%d", &machineIdToInsertOperation);

				int runtimeToInsertExecution;
				printf("Introduza o tempo de execução associada à execução da operação: ");
				scanf("%d", &runtimeToInsertExecution);

				Operation* operation = newOperation(operations, jobIdToInsertOperation, positionToInsertOperation, newOperationName);
				if (operation == NULL)
				{
					printf("Não foi possível adicionar a operação.\n");
					break;
				}

				// inserir nova operação
				operations = insertOperation_AtStart(operations, operation);
				if (operations == NULL)
				{
					printf("Não foi possível adicionar a operação.\n");
					break;
				}

				printf("Operação adicionada com sucesso!\n");

				Execution* execution = newExecution(operation->operationID, machineIdToInsertOperation, runtimeToInsertExecution);
				if (execution == NULL)
				{
					printf("Não foi possível adicionar a execução de operação.\n");
					break;
				}

				// inserir nova execução de uma operação
				*executionsTable = insertExecution_AtTable(executionsTable, execution);
				printf("Execução de operação adicionada com sucesso!\n");
#pragma endregion
				break;

			case 13:
#pragma region opção 13: atualizar nome de uma opereção
				printf("-> Opção 13. Atualizar nome de uma opereção\n");

				printf("Operações:\n");
				if (!displayOperations(operations))
				{
					printf("Não existem operações.\n");
					break;
				}

				int operationIdToUpdate;
				printf("Introduza o ID da opereção a ser atualizada: ");
				scanf("%d", &operationIdToUpdate);

				fseek(stdin, 0, SEEK_END);

				char updatedOperationName[NAME_SIZE];
				printf("Introduza o novo nome da opereção: ");
				fgets(updatedOperationName, sizeof(updatedOperationName), stdin);

				removeNewLine(updatedOperationName);

				if (!updateOperation_Name(operations, operationIdToUpdate, updatedOperationName))
				{
					printf("Não foi possível atualizar a opereção.\n");
					break;
				}

				printf("Opereção atualizada com sucesso!\n");
#pragma endregion
				break;

			case 14:
#pragma region opção 14: atualizar tempo de uma execução de operação
				printf("-> Opção 14. Atualizar tempo de uma execução de operação\n");

				printf("Execuções de Operações:\n");
				if (!displayExecutions_AtTable(executionsTable))
				{
					printf("Não existem execuções de operações.\n");
				}

				int operationIdToUpdateRuntime;
				printf("Introduza o ID da operação: ");
				scanf("%d", &operationIdToUpdateRuntime);

				int machineIdToUpdateRuntime;
				printf("Introduza o ID da máquina: ");
				scanf("%d", &machineIdToUpdateRuntime);

				int runtimeToUpdateRuntime;
				printf("Introduza o novo tempo de execução: ");
				scanf("%d", &runtimeToUpdateRuntime);

				if (!updateRuntime_ByOperation_AtTable(&executionsTable, operationIdToUpdateRuntime, machineIdToUpdateRuntime, runtimeToUpdateRuntime))
				{
					printf("Não foi possível atualizar a execução de opereção.\n");
					break;
				}

				printf("Execução de opereção atualizada com sucesso!\n");
#pragma endregion
				break;

			case 15:
#pragma region opção 15: trocar ordem de 2 operações
				printf("-> Opção 15. Trocar ordem de 2 operações\n");

				printf("Operações:\n");
				if (!displayOperations(operations))
				{
					printf("Não existem operações.\n");
					break;
				}

				int jobIdToUpdatePositions;
				printf("Introduza o ID da tarefa que as posições fazem parte: ");
				scanf("%d", &jobIdToUpdatePositions);

				int operation1IdToUpdate;
				printf("Introduza o ID da 1º opereção para trocar: ");
				scanf("%d", &operation1IdToUpdate);

				int operation2IdToUpdate;
				printf("Introduza o ID da 2º opereção para trocar: ");
				scanf("%d", &operation2IdToUpdate);

				if (!updateOperation_Position(&operations, jobIdToUpdatePositions, operation1IdToUpdate, operation2IdToUpdate))
				{
					printf("Não foi possível atualizar a execução de opereção.\n");
					break;
				}

				printf("Ordem das operações trocadas com sucesso!\n");
#pragma endregion
				break;

			case 16:
#pragma region opção 16: remover uma operação
				printf("-> Opção 16. Remover uma operação\n");

				printf("Operações:\n");
				if (!displayOperations(operations))
				{
					printf("Não existem operações.\n");
					break;
				}

				int operationIdToDelete;
				printf("Introduza o ID da operação a ser removida: ");
				scanf("%d", &operationIdToDelete);

				// remover operação
				if (!deleteOperation(&operations, operationIdToDelete))
				{
					printf("Não foi possível remover a operação.\n");
					break;
				}

				printf("Operação removida com sucesso!\n");

				// remover execuções de operações associadas à operação
				if (!deleteExecutions_ByOperation_AtTable(&executionsTable, operationIdToDelete))
				{
					printf("Não foi possível remover as execuções de operações associadas à operação.\n");
					break;
				}

				printf("Execuções de operações associadas à operação removidas com sucesso!\n");
#pragma endregion
				break;

			case 17:
#pragma region opção 17: guardar dados
				printf("-> Opção 17. Guardar dados\n");

				// guardar os dados em ficheiros .csv
				writeJobs_Text(JOBS_FILENAME_TEXT, jobs);
				writeMachines_Text(MACHINES_FILENAME_TEXT, machines);
				writeOperations_Text(OPERATIONS_FILENAME_TEXT, operations);
				writeExecutions_AtTable_Text(EXECUTIONS_FILENAME_TEXT, executionsTable);

				// guardar os dados em ficheiros binários
				//writeJobs_Binary(JOBS_FILENAME_BINARY, jobs);
				//writeMachines_Binary(MACHINES_FILENAME_BINARY, machines);
				//writeOperations_Binary(OPERATIONS_FILENAME_BINARY, operations);
				//writeExecutions_AtTable_Binary(EXECUTIONS_FILENAME_BINARY, executionsTable);

				printf("Dados guardados com sucesso!\n");
#pragma endregion
				break;

			case 18:
#pragma region opção 18: sobre
				printf("-> Opção 18. Sobre\n");

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

	// libertar memória das estruturas dinâmicas antes de fechar o programa
	cleanJobs(&jobs);
	cleanMachines(&machines);
	cleanOperations(&operations);
	cleanExecutions_Table(&executionsTable);
	// FALTA WORK PLANS ?

	return true;
}