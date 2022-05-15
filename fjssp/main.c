/**
 * @brief	Ficheiro principal da aplica��o, com menu e chamada de fun��es
 * @file	main.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	26/03/2022
 *
 * -----------------
 *
 * Software desenvolvido para a proposta de escalonamento para a produ��o de um produto que envolve v�rias opera��es
 * e a utiliza��o de v�rias m�quinas, para minimizar o tempo necess�rio na sua produ��o.
 * @see https://github.com/luispereira1999/fjssp
*/

#include <stdio.h>
#include <locale.h>
#include "header.h"


/**
* @brief	Fun��o principal do programa
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

	// criar tabela hash das execu��es vazia
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
		printf("   � Lu�s Pereira | 2022\n\n");
		printf("---------------------------------\n");
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
			case 1: // fase 2 da aplica��o

#pragma region funcionalidade 1: definir estruturas de dados din�micas
				printf("-  1. Definir estruturas de dados din�micas\n");

				// carregar dados em mem�ria
				jobs = loadJobs(jobs);
				machines = loadMachines(machines);
				operations = loadOperations(operations);
				*executionsTable = loadExecutionsTable(executionsTable);
				printf("Dados carregados em mem�ria com sucesso!\n");
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

				// libertar mem�ria das listas anteriores, para serem lidas dos ficheiros
				//freeJobs(jobs);
				//freeMachines(machines);
				//freeOperations(operations);
				//freeExecutions(executions);

				// depois de libertar mem�ria, definir listas como NULL para evitar poss�veis erros
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
				while (!operationsallfound) // enquanto que encontrar trabalhos, remover as opera��es associadas
				{
					if (searchOperation_ByJob(operations, 3))
					{
						// remover opera��o
						int operationdeleted = deleteOperation_ByJob(&operations, 3);
						printf("opera��o associada ao trabalho removida com sucesso!\n");

						//while (!executionsallfound) // enquanto que encontrar a respetiva opera��o, remover as execu��es de opera��es associadas
						//{
						//	if (searchExecutionByOperation(executions, operationdeleted))
						//	{
						//		// remover execu��o
						//		deleteExecution_ByOperation(&executions, operationdeleted);
						//		printf("execu��o associada � opera��o removida com sucesso!\n");
						//	}
						//	else
						//	{
						//		executionsallfound = true;
						//	}
						//}
						//executionsallfound = false; // necess�rio para voltar a percorrer o while acima, numva nova opera��o
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

				// guardar a nova inser��o em ficheiro
				writeJobs(JOBS_FILENAME_BINARY, jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 5: remover uma opera��o
				printf("\n\n-  5. Remover uma opera��o\n");

				// remover opera��o
				deleteOperation(&operations, 35);
				printf("Opera��o removida com sucesso!\n");

				// remover execu��es associadas � opera��o
				deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
				printf("Execu��es associadas � opera��o removidas com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 6: atualizar uma opera��o
				printf("\n\n-  6. Atualizar uma opera��o\n");

				// atualizar a posi��o de uma opera��o X pela posi��o de uma opera��o Y, e vice-versa
				updatePosition(&operations, 2, 4);
				printf("As posi��es das opera��es foram trocadas com sucesso!\n");

				// atualizar o tempo de uma execu��o de opera��o
		/*		executions = searchExecutionAtTable(executionsTable, 13, 8);
				updateRuntime();*/
#pragma endregion

#pragma region funcionalidade 7: inserir uma opera��o
				printf("\n\n-  7. Inserir uma opera��o\n");

				// inserir nova opera��o
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperation_AtStart(operations, operation);

				// inserir nova execu��o de uma opera��o
			/*	Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecution_AtTable(executionsTable, execution);*/

				// guardar as novas inser��es em ficheiros
				writeOperations(OPERATIONS_FILENAME_BINARY, operations);
				//writeExecutions(EXECUTIONS_FILENAME_BINARY, executions);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region mostrar dados
				printf("\n\n-  Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				//displayJobs(jobs);

				printf("M�quinas:\n");
				//displayMachines(machines);

				printf("Opera��es:\n");
				//displayOperations(operations);

				printf("Execu��es de Opera��es:\n");
				displayExecutionsTable(executionsTable);

				printf("Dados mostrados com sucesso!\n");
#pragma endregion

				break;

			case 3: // sobre aplica��o

				printf("Flexible Job Shop Problem - Proposta de escalonamento para a produ��o de um produto que envolve v�rias opera��es e a utiliza��o de v�rias m�quinas, para minimizar o tempo necess�rio na sua produ��o.\n");
				printf("Projeto desenvolvido na unidade curricular Estruturas de Dados Avan�adas, no �mbito do curso Licenciatura em Engenharia em Desenvolvimento de Jogos Digitais. Realizado no Instituto Polit�cnico do C�vado e do Ave, a 14 at� 31 de mar�o de 2022, durante o 2� semestre do 1� ano de curso.\n");
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