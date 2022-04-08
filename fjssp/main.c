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

	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;
	Execution* executions = NULL;

	int menuOption = 0;

	do
	{
		// menu 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Fase 1\n");
		printf("   2 -> Fase 2\n");
		printf("   3 -> Sobre\n");
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
			case 1: // fase 1 do projeto

#pragma region funcionalidade 1: definir estruturas de dados din�micas
				printf("-  1. Definir estruturas de dados din�micas\n");

				// carregar dados (tabela) para as listas
				loadData(&jobs, &machines, &operations, &executions);
				printf("Dados carregados em mem�ria com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiro
				printf("\n\n-  2. Armazenar e ler as estruturas em ficheiro\n");

				// guardar os dados em ficheiros
				writeJobs("jobs.txt", jobs);
				writeMachines("machines.txt", machines);
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
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
				executions = NULL;

				// ler dados de ficheiros
				jobs = readJobs("jobs.txt");
				machines = readMachines("machines.txt");
				operations = readOperations("operations.txt");
				executions = readExecutions("executions.txt");
				printf("Dados importados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: remover uma opera��o
				printf("\n\n-  3. Remover uma opera��o\n");

				// remover opera��o
				deleteOperation(&operations, 35);
				printf("Opera��o removida com sucesso!\n");

				bool allFound = false;
				while (!allFound) // enquanto que encontrar opera��es, remover as execu��es de opera��es associadas
				{
					if (searchExecutionByOperation(executions, 35))
					{
						// remover execu��o
						deleteExecutionByOperation(&executions, 35);
						printf("Execu��o associada � opera��o removida com sucesso!\n");
					}
					else
					{
						allFound = true;
					}
				}
#pragma endregion

#pragma region funcionalidade 4: atualizar uma opera��o
				printf("\n\n-  4. Atualizar uma opera��o\n");

				// atualizar o tempo necess�rio para uma execu��o da opera��o
				updateRuntime(&executions, 2, 2, 10);
				printf("Tempo necess�rio para a execu��o da opera��o atualizada com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 5: inserir uma opera��o
				printf("\n\n-  5. Inserir uma opera��o\n");

				// inserir nova opera��o
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperationAtStart(operations, operation);

				// inserir nova execu��o de uma opera��o
				Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecutionAtStart(executions, execution);

				// guardar as novas inser��es em ficheiros
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 6: determinar tempo m�nimo para completar um trabalho e listagem das respetivas opera��es
				printf("\n\n-  6. Determinar tempo m�nimo para completar um trabalho e listagem das respetivas opera��es\n");

				// obter o tempo m�nimo para completar um job e as respetivas opera��es
				Execution* minExecutions = NULL;
				int minTime = getMinTimeToCompleteJob(operations, executions, 1, &minExecutions);

				// mostrar resultados
				printf("Menor tempo necess�rio para completar o trabalho(ID: %d) � %d!\n", 1, minTime);
				printf("Opera��es com menor tempo:\n");
				minExecutions = SortExecutionsByOperation(minExecutions);
				displayExecutions(minExecutions);
#pragma endregion

#pragma region funcionalidade 7: determinar tempo m�ximo para completar um trabalho e listagem das respetivas opera��es
				printf("\n\n-  7. Determinar tempo m�ximo para completar um trabalho e listagem das respetivas opera��es\n");

				// obter o tempo m�ximo para completar um job
				Execution* maxExecutions = NULL;
				int maxTime = getMaxTimeToCompleteJob(operations, executions, 1, &maxExecutions);

				// mostrar resultados
				printf("Maior tempo necess�rio para completar o trabalho(ID: %d) � %d!\n", 1, maxTime);
				printf("Opera��es com maior tempo:\n");
				maxExecutions = SortExecutionsByOperation(maxExecutions);
				displayExecutions(maxExecutions);
#pragma endregion

#pragma region funcionalidade 8: determinar tempo m�dio para completar uma opera��o, considerando todas as alternativas poss�veis
				printf("\n\n-  8. Determinar tempo m�dio para completar uma opera��o, considerando todas as alternativas poss�veis\n");

				// obter o tempo m�dio para completar uma opera��o
				float average = getAverageTimeToCompleteOperation(executions, 1);

				// mostrar resultado
				printf("M�dia de tempo necess�rio para completar a opera��o(ID: %d) � %.2f!\n", 1, average);
#pragma endregion

#pragma region mostrar dados
				printf("\n\n-  Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);
				printf("M�quinas:\n");
				displayMachines(machines);
				printf("Opera��es:\n");
				displayOperations(operations);
				printf("Execu��es de Opera��es:\n");
				displayExecutions(executions);
				printf("Dados mostrados com sucesso!\n");

				// libertar mem�ria
				//freeJobs(jobs);
				//freeMachines(machines);
				//freeOperations(operations);
				//freeExecutions(executions);

				// depois de libertar mem�ria, definir listas como NULL para evitar poss�veis erros
				jobs = NULL;
				machines = NULL;
				operations = NULL;
				executions = NULL;
#pragma endregion

				break;

			case 2: // fase 2 do projeto

#pragma region funcionalidade 1: definir estruturas de dados din�micas
				printf("-  1. Definir estruturas de dados din�micas\n");

				// carregar dados (tabela) para as listas
				loadData(&jobs, &machines, &operations, &executions);
				printf("Dados carregados em mem�ria com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiro
				printf("\n\n-  2. Armazenar e ler as estruturas em ficheiro\n");

				// guardar os dados em ficheiros
				writeJobs("jobs.txt", jobs);
				writeMachines("machines.txt", machines);
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
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
				executions = NULL;

				// ler dados de ficheiros
				jobs = readJobs("jobs.txt");
				machines = readMachines("machines.txt");
				operations = readOperations("operations.txt");
				executions = readExecutions("executions.txt");
				printf("Dados importados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 5: inserir um trabalho
				printf("\n\n-  5. Inserir um trabalho\n");

				// inserir novo trabalho
				Job* job = NULL;
				job = newJob(9);
				jobs = insertJobAtStart(jobs, job);

				// guardar a nova inser��o em ficheiro
				writeJobs("jobs.txt", jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: remover uma opera��o
				printf("\n\n-  3. Remover uma opera��o\n");

				// remover opera��o
				deleteOperation(&operations, 35);
				printf("Opera��o removida com sucesso!\n");

				allFound = false;
				while (!allFound) // enquanto que encontrar opera��es, remover as execu��es de opera��es associadas
				{
					if (searchExecutionByOperation(executions, 35))
					{
						// remover execu��o
						deleteExecutionByOperation(&executions, 35);
						printf("Execu��o associada � opera��o removida com sucesso!\n");
					}
					else
					{
						allFound = true;
					}
				}
#pragma endregion

#pragma region funcionalidade 5: inserir uma opera��o
				printf("\n\n-  5. Inserir uma opera��o\n");

				// inserir nova opera��o
				operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperationAtStart(operations, operation);

				// inserir nova execu��o de uma opera��o
				execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecutionAtStart(executions, execution);

				// guardar as novas inser��es em ficheiros
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region mostrar dados
				printf("\n\n-  Mostrar dados\n");

				// mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);
				printf("M�quinas:\n");
				displayMachines(machines);
				printf("Opera��es:\n");
				displayOperations(operations);
				printf("Execu��es de Opera��es:\n");
				displayExecutions(executions);
				printf("Dados mostrados com sucesso!\n");

				// libertar mem�ria
				//freeJobs(jobs);
				//freeMachines(machines);
				//freeOperations(operations);
				//freeExecutions(executions);

				// depois de libertar mem�ria, definir listas como NULL para evitar poss�veis erros
				jobs = NULL;
				machines = NULL;
				operations = NULL;
				executions = NULL;
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