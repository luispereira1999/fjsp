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
			case 1: // fase 1 do projeto

#pragma region funcionalidade 1: definir estruturas de dados dinâmicas
				printf("-  1. Definir estruturas de dados dinâmicas\n");

				// carregar dados (tabela) para as listas
				loadData(&jobs, &machines, &operations, &executions);
				printf("Dados carregados em memória com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiro
				printf("\n\n-  2. Armazenar e ler as estruturas em ficheiro\n");

				// guardar os dados em ficheiros
				writeJobs("jobs.txt", jobs);
				writeMachines("machines.txt", machines);
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
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
				jobs = readJobs("jobs.txt");
				machines = readMachines("machines.txt");
				operations = readOperations("operations.txt");
				executions = readExecutions("executions.txt");
				printf("Dados importados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: remover uma operação
				printf("\n\n-  3. Remover uma operação\n");

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

#pragma region funcionalidade 4: atualizar uma operação
				printf("\n\n-  4. Atualizar uma operação\n");

				// atualizar o tempo necessário para uma execução da operação
				updateRuntime(&executions, 2, 2, 10);
				printf("Tempo necessário para a execução da operação atualizada com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 5: inserir uma operação
				printf("\n\n-  5. Inserir uma operação\n");

				// inserir nova operação
				Operation* operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperationAtStart(operations, operation);

				// inserir nova execução de uma operação
				Execution* execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecutionAtStart(executions, execution);

				// guardar as novas inserções em ficheiros
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 6: determinar tempo mínimo para completar um trabalho e listagem das respetivas operações
				printf("\n\n-  6. Determinar tempo mínimo para completar um trabalho e listagem das respetivas operações\n");

				// obter o tempo mínimo para completar um job e as respetivas operações
				Execution* minExecutions = NULL;
				int minTime = getMinTimeToCompleteJob(operations, executions, 1, &minExecutions);

				// mostrar resultados
				printf("Menor tempo necessário para completar o trabalho(ID: %d) é %d!\n", 1, minTime);
				printf("Operações com menor tempo:\n");
				minExecutions = SortExecutionsByOperation(minExecutions);
				displayExecutions(minExecutions);
#pragma endregion

#pragma region funcionalidade 7: determinar tempo máximo para completar um trabalho e listagem das respetivas operações
				printf("\n\n-  7. Determinar tempo máximo para completar um trabalho e listagem das respetivas operações\n");

				// obter o tempo máximo para completar um job
				Execution* maxExecutions = NULL;
				int maxTime = getMaxTimeToCompleteJob(operations, executions, 1, &maxExecutions);

				// mostrar resultados
				printf("Maior tempo necessário para completar o trabalho(ID: %d) é %d!\n", 1, maxTime);
				printf("Operações com maior tempo:\n");
				maxExecutions = SortExecutionsByOperation(maxExecutions);
				displayExecutions(maxExecutions);
#pragma endregion

#pragma region funcionalidade 8: determinar tempo médio para completar uma operação, considerando todas as alternativas possíveis
				printf("\n\n-  8. Determinar tempo médio para completar uma operação, considerando todas as alternativas possíveis\n");

				// obter o tempo médio para completar uma operação
				float average = getAverageTimeToCompleteOperation(executions, 1);

				// mostrar resultado
				printf("Média de tempo necessário para completar a operação(ID: %d) é %.2f!\n", 1, average);
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

			case 2: // fase 2 do projeto

#pragma region funcionalidade 1: definir estruturas de dados dinâmicas
				printf("-  1. Definir estruturas de dados dinâmicas\n");

				// carregar dados (tabela) para as listas
				loadData(&jobs, &machines, &operations, &executions);
				printf("Dados carregados em memória com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiro
				printf("\n\n-  2. Armazenar e ler as estruturas em ficheiro\n");

				// guardar os dados em ficheiros
				writeJobs("jobs.txt", jobs);
				writeMachines("machines.txt", machines);
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
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

				// guardar a nova inserção em ficheiro
				writeJobs("jobs.txt", jobs);
				printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: remover uma operação
				printf("\n\n-  3. Remover uma operação\n");

				// remover operação
				deleteOperation(&operations, 35);
				printf("Operação removida com sucesso!\n");

				allFound = false;
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

#pragma region funcionalidade 5: inserir uma operação
				printf("\n\n-  5. Inserir uma operação\n");

				// inserir nova operação
				operation = NULL;
				operation = newOperation(39, 2, 8);
				operations = insertOperationAtStart(operations, operation);

				// inserir nova execução de uma operação
				execution = NULL;
				execution = newExecution(39, 5, 17);
				executions = insertExecutionAtStart(executions, execution);

				// guardar as novas inserções em ficheiros
				writeOperations("operations.txt", operations);
				writeExecutions("executions.txt", executions);
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