/*
Descri��o:           Ficheiro principal da aplica��o, com menu e chamada de fun��es
Desenvolvedor(es):   Lu�s Pereira (18446)
�ltima atualiza��o:  25/03/2022
Cria��o:             14/03/2022
*/

#include <stdio.h>
#include <locale.h>
#include "header.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;
	OperationExecution* operationsExecution = NULL;

	int menuOption = 0;

	do
	{
		// menu 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Fase 1.\n");
		printf("   2 -> Criar dados (tabela).\n");
		printf("   3 -> Testes.\n\n");
		printf("   � Lu�s Pereira | 2022\n\n");
		printf("---------------------------------\n");

		printf("Escolha uma das op��es acima: ");
		scanf("%d", &menuOption);
		printf("\n");

		switch (menuOption)
		{
		case 1: // Fase 1

			// Carregar dados (tabela) para as listas
			loadData(&jobs, &machines, &operations, &operationsExecution);
			// Guardar os dados em ficheiros
			writeJobs("jobs.data", jobs);
			writeOperations("operations.data", operations);
			writeMachines("machines.data", machines);
			writeOperationsExecution("operations-execution.data", operationsExecution);

			// Libertar mem�ria das listas anteriores, para serem lidas dos ficheiros
			freeJobs(jobs);
			freeMachines(machines);
			freeOperations(operations);
			freeOperationsExecution(operationsExecution);
			// Depois de libertar mem�ria, definir listas como NULL para evitar poss�veis erros
			jobs = NULL;
			operations = NULL;
			machines = NULL;
			operationsExecution = NULL;
			// Ler dados de ficheiros
			jobs = readJobs("jobs.data");
			machines = readMachines("machines.data");
			operations = readOperations("operations.data");
			operationsExecution = readOperationsExecution("operations-execution.data");

			// Remover opera��o
			deleteOperation(&operations, 33);
			printf("Opera��o (%d) removida com sucesso!\n", 33);
			bool allFound = false;
			while (allFound == false) // enquanto que encontrar opera��es, remover execu��o de opera��es associadas
			{
				if (searchOperationExecution(operationsExecution, 33))
				{
					deleteOperationExecution(&operationsExecution, 33);
					printf("Execu��o de opera��o associada � opera��o (%d) removida com sucesso!\n", 33);
				}
				else
				{
					allFound = true;
				}
			}
			// Atualizar a posi��o da opera��o num determinado job
			displayOperations(operations);
			bool a = changeOperationPosition(&operations, 1, 4, 2);
			printf("|%s|\n\n", a ? "Sim" : "N�o");
			displayOperations(operations);

			//updateJobInOperation(&operations, 1, 8);
			//printf("Opera��o (%d) atualizada com sucesso! O ID do trabalho foi alterado para %d.\n", 1, 8);
			// Atualizar execu��o de opera��o

			// Inserir novo trabalho
			Job* job = NULL;
			job = newJob(9);
			jobs = insertJobAtStart(jobs, job);
			// Inserir nova m�quina
			Machine* machine = NULL;
			machine = newMachine(9, false);
			machines = insertMachineAtStart(machines, machine);
			// Inserir nova opera��o
			Operation* operation = NULL;
			operation = newOperation(39, 2, 8);
			operations = insertOperationAtStart(operations, operation);
			// Inserir nova execu��o de uma opera��o
			OperationExecution* operationExecution = NULL;
			operationExecution = newOperationExecution(39, 5, 22);
			operationsExecution = insertOperationAtStart(operationsExecution, operationExecution);
			// Guardar as novas inser��es em ficheiros
			writeJobs("jobs.data", jobs);
			writeMachines("machines.data", machines);
			writeOperations("operations.data", operations);
			writeOperationsExecution("operations-execution.data", operationsExecution);

			printf("\n----------------\n\n");

			// Obter o tempo m�nimo para completar um job e as respetivas opera��es
			OperationExecution* minOperationsExecution = NULL;
			int minTime = getMinTimeToCompleteJob(operations, operationsExecution, 1, &minOperationsExecution);
			printf("Menor tempo necess�rio para completar o trabalho (%d): %d\n", 1, minTime);
			displayOperationsExecution(minOperationsExecution);
			// Obter o tempo m�ximo para completar um job
			OperationExecution* maxOperationsExecution = NULL;
			int maxTime = getMaxTimeToCompleteJob(operations, operationsExecution, 1, &maxOperationsExecution);
			printf("Maior tempo necess�rio para completar o trabalho (%d): %d\n", 1, maxTime);
			displayOperationsExecution(maxOperationsExecution);
			// Obter o tempo m�dio para completar uma opera��o
			float average = getAverageTimeToCompleteOperation(operationsExecution, 1);
			printf("M�dia de tempo necess�rio para completar a opera��o (%d): %.2f\n", 1, average);

			printf("\n----------------\n\n");

			// Mostrar dados na consola
			displayJobs(jobs);
			displayMachines(machines);
			displayOperations(operations);
			displayOperationsExecution(operationsExecution);
			// Libertar mem�ria
			freeJobs(jobs);
			freeMachines(machines);
			freeOperations(operations);
			freeOperationsExecution(operationsExecution);
			// Depois de libertar mem�ria, definir listas como NULL para evitar erros
			jobs = NULL;
			operations = NULL;
			machines = NULL;
			operationsExecution = NULL;
			break;

		case 2: // criar dados (tabela) e guardar em ficheiros

			// Carregar dados da tabela para listas
			loadData(&jobs, &machines, &operations, &operationsExecution);
			// Guardar os dados em ficheiros
			writeJobs("jobs.data", jobs);
			writeOperations("operations.data", operations);
			writeMachines("machines.data", machines);
			writeOperationsExecution("operations-execution.data", operationsExecution);
			break;

		case 3: // testes
			break;

		default:
			printf("Op��o inv�lida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}