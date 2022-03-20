/*
Descri��o:           Ficheiro principal da aplica��o
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/2022
*/

#include <stdio.h>
#include <locale.h>
#include "header.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Job* job = NULL;
	Machine* machine = NULL;
	Operation* operation = NULL;
	OperationExecution* operationExecution = NULL;

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
			//operationsExecution = NULL;
			// Ler dados de ficheiros
			jobs = readJobs("jobs.data");
			machines = readMachines("machines.data");
			operations = readOperations("operations.data");
			operationsExecution = readOperationsExecution("operations-execution.data");

			// Remover opera��o
			if (deleteOperation(&operations, 33))
			{
				printf("Opera��o removida com sucesso!\n");

				int allFound = false;
				while (allFound == false)
				{
					if (searchOperationExecution(operationsExecution, 33))
					{
						if (deleteOperationExecution(&operationsExecution, 33))
						{
							printf("Execu��o de opera��o removida com sucesso!\n");
						}
					}
					else
					{
						allFound = true;
					}
				}
			}
			// Atualizar opera��o
			Operation* operationToUpdate = getOperation(operations, 31);
			operationToUpdate->position = 17;
			if (updateOperation(&operations, operationToUpdate, operationToUpdate->id))
			{
				printf("Opera��o atualizada com sucesso!\n");
			}

			// Inserir novo trabalho
			job = newJob(9);
			jobs = insertJobAtStart(jobs, job);
			// Inserir nova m�quina
			machine = newMachine(9, false);
			machines = insertMachineAtStart(machines, machine);
			// Inserir nova opera��o
			operation = newOperation(39, 2, 8);
			operations = insertOperationAtStart(operations, operation);
			// Inserir nova execu��o de uma opera��o
			operationExecution = newOperationExecution(39, 5, 22);
			operationsExecution = insertOperationAtStart(operationsExecution, operationExecution);
			// Guardar as novas inser��es em ficheiros
			writeJobs("jobs.data", job);
			writeMachines("machines.data", machines);
			writeOperations("operations.data", operations);
			writeOperationsExecution("operations-execution.data", operationsExecution);

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

		default:
			printf("Op��o inv�lida! Tente novamente.\n\n\n");
			break;
		}
	} while (true);

	return true;
}