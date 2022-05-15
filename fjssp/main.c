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

	// listas
	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;
	//Execution* executions = NULL;

	// criar tabela hash das execuções vazia
	ExecutionNode* executionsTable[HASH_TABLE_SIZE];
	*executionsTable = createExecutionsTable(executionsTable);

	int menuOption = 0;

	do
	{
		// menu 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Fase 2\n");
		printf("   2 -> Sobre\n");
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

				// carregar dados em memória
				jobs = loadJobs(jobs);
				machines = loadMachines(machines);
				operations = loadOperations(operations);
				*executionsTable = loadExecutionsTable(executionsTable);
				printf("Dados carregados em memória com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiro
				printf("\n\n-  2. Armazenar e ler as estruturas em ficheiro\n");

				// guardar os dados em ficheiros
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				writeMachines(MACHINES_FILENAME_BINARY, machines);
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				//writeExecutions(EXECUTIONS_FILENAME_BINARY, executions);
				//writeExecutionsTable(EXECUTIONS_FILENAME_BINARY, executionsTable);
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
				//executions = NULL;

				// ler dados de ficheiros
				jobs = readJobs(JOBS_FILENAME_BINARY);
				machines = readMachines(MACHINES_FILENAME_BINARY);
				operations = readOperations(OPERATIONS_FILENAME_BINARY);
				//executions = readExecutions(EXECUTIONS_FILENAME_BINARY);
				printf("Dados importados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: remover um trabalho
				printf("\n\n-  3. remover um trabalho\n");

				// remover trabalho
				deleteJob(&jobs, 3);
				printf("trabalho removido com sucesso!\n");

				bool operationsallfound = false;
				bool executionsallfound = false;
				while (!operationsallfound) // enquanto que encontrar trabalhos, remover as operações associadas
				{
					if (searchOperation_ByJob(operations, 3))
					{
						// remover operação
						int operationdeleted = deleteOperation_ByJob(&operations, 3);
						printf("operação associada ao trabalho removida com sucesso!\n");

						//while (!executionsallfound) // enquanto que encontrar a respetiva operação, remover as execuções de operações associadas
						//{
						//	if (searchExecutionByOperation(executions, operationdeleted))
						//	{
						//		// remover execução
						//		deleteExecution_ByOperation(&executions, operationdeleted);
						//		printf("execução associada à operação removida com sucesso!\n");
						//	}
						//	else
						//	{
						//		executionsallfound = true;
						//	}
						//}
						//executionsallfound = false; // necessário para voltar a percorrer o while acima, numva nova operação
					}
					else
					{
						operationsallfound = true;
					}
				}
#pragma endregion

#pragma region funcionalidade 4: inserir um trabalho
				printf("\n\n-  4. Inserir um trabalho\n");

				// inserir novo trabalho
				Job* job = NULL;
				job = newJob(9);
				jobs = insertJob_AtStart(jobs, job);

				// guardar a nova inserção em ficheiro
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 5: remover uma operação
				printf("\n\n-  5. Remover uma operação\n");

				// remover operação
				deleteOperation(&operations, 35);
				printf("Operação removida com sucesso!\n");

				// remover execuções associadas à operação
				deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
				printf("Execuções associadas à operação removidas com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 6: atualizar uma operação
				printf("\n\n-  6. Atualizar uma operação\n");

				// atualizar a posição de uma operação X pela posição de uma operação Y, e vice-versa
				updatePosition(&operations, 2, 4);
				printf("As posições das operações foram trocadas com sucesso!\n");

				// atualizar o tempo de uma execução de operação
		/*		executions = searchExecutionAtTable(executionsTable, 13, 8);
				updateRuntime();*/
#pragma endregion

#pragma region funcionalidade 7: inserir uma operação
				printf("\n\n-  7. Inserir uma operação\n");

				// inserir nova operação
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperation_AtStart(operations, operation);

				// inserir nova execução de uma operação
			/*	Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecution_AtTable(executionsTable, execution);*/

				// guardar as novas inserções em ficheiros
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				//writeExecutions(EXECUTIONS_FILENAME_BINARY, executions);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region mostrar dados
				printf("\n\n-  Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				//displayJobs(jobs);

				printf("Máquinas:\n");
				//displayMachines(machines);

				printf("Operações:\n");
				//displayOperations(operations);

				printf("Execuções de Operações:\n");
				displayExecutionsTable(executionsTable);

				printf("Dados mostrados com sucesso!\n");
#pragma endregion

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