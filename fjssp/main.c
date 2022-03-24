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
	Execution* executions = NULL;

	int menuOption = 0;

	do
	{
		// menu 
		printf("---------------------------------\n\n");
		printf("   M E N U\n\n");
		printf("   1 -> Fase 1\n");
		printf("   2 -> Sobre\n");
		printf("   � Lu�s Pereira | 2022\n\n");
		printf("---------------------------------\n");
		printf("Escolha uma das op��es acima: ");

		if (!scanf("%d", &menuOption)) // se n�o introduzir um n�mero
		{
			menuOption = 0;
			fseek(stdin, 0, SEEK_END); // repor buffer de entrada para evitar ciclo infinito
			printf("\n");
			printf("O car�cter introduzido n�o � v�lido. Tente outro.\n");
		}
		else
		{
			printf("\n");

			switch (menuOption)
			{
			case 1: // Fase 1 do projeto

				// Carregar dados (tabela) para as listas
				loadData(&jobs, &machines, &operations, &executions);
				// Guardar os dados em ficheiros
				writeJobs("jobs.data", jobs);
				writeOperations("operations.data", operations);
				writeMachines("machines.data", machines);
				writeExecutions("executions.data", executions);
				printf("Dados exportados com sucesso!\n");

				// Libertar mem�ria das listas anteriores, para serem lidas dos ficheiros
				freeJobs(jobs);
				freeMachines(machines);
				freeOperations(operations);
				freeExecutions(executions);
				// Depois de libertar mem�ria, definir listas como NULL para evitar poss�veis erros
				jobs = NULL;
				operations = NULL;
				machines = NULL;
				executions = NULL;
				// Ler dados de ficheiros
				jobs = readJobs("jobs.data");
				machines = readMachines("machines.data");
				operations = readOperations("operations.data");
				executions = readExecutions("executions.data");
				printf("Dados importados com sucesso!\n");

				// Remover opera��o
				//deleteOperation(&operations, 33);
				//printf("Opera��o removida com sucesso!\n");
				//bool allFound = false;
				//while (allFound == false) // enquanto que encontrar opera��es, remover execu��o de opera��es associadas
				//{
				//	if (searchExecution(executions, 33))
				//	{
				//		// Remover execu��o de opera��o relativa � opera��o
				//		deleteExecution(&executions, 33);
				//		printf("Execu��o associada � opera��o removida com sucesso!\n");
				//	}
				//	else
				//	{
				//		allFound = true;
				//	}
				//}
				// Atualizar a posi��o da opera��o num determinado job
				updateOperationPosition(&operations, jobs, 1, 4, 2);
				printf("Posi��o da opera��o atualizada com sucesso!\n");
				// Atualizar o tempo necess�rio para uma execu��o da opera��o
				updateRuntime(&executions, 2, 2, 10);
				printf("Tempo necess�rio para a execu��o da opera��o atualizada com sucesso!\n");

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
				Execution* execution = NULL;
				execution = newExecution(39, 5, 22);
				executions = insertOperationAtStart(executions, execution);
				// Guardar as novas inser��es em ficheiros
				writeJobs("jobs.data", jobs);
				writeMachines("machines.data", machines);
				writeOperations("operations.data", operations);
				writeExecutions("executions.data", executions);
				printf("Novos dados exportados com sucesso!\n");

				printf("\n----------------\n\n");

				// Obter o tempo m�nimo para completar um job e as respetivas opera��es
				Execution* minExecutions = NULL;
				int minTime = getMinTimeToCompleteJob(operations, executions, 1, &minExecutions);
				printf("Menor tempo necess�rio para completar o trabalho(ID: %d) � %d!\n", 1, minTime);
				printf("Opera��es com menor tempo:\n");
				minExecutions = SortExecutionsByOperation(minExecutions);
				displayExecutions(minExecutions);
				// Obter o tempo m�ximo para completar um job
				Execution* maxExecutions = NULL;
				int maxTime = getMaxTimeToCompleteJob(operations, executions, 1, &maxExecutions);
				printf("Maior tempo necess�rio para completar o trabalho(ID: %d) � %d!\n", 1, maxTime);
				printf("Opera��es com maior tempo:\n");
				maxExecutions = SortExecutionsByOperation(maxExecutions);
				displayExecutions(maxExecutions);
				// Obter o tempo m�dio para completar uma opera��o
				float average = getAverageTimeToCompleteOperation(executions, 1);
				printf("M�dia de tempo necess�rio para completar a opera��o(ID: %d) � %.2f!\n", 1, average);

				printf("\n----------------\n\n");

				// Mostrar dados na consola
				printf("Trabalhos:\n");
				displayJobs(jobs);
				printf("M�quinas:\n");
				displayMachines(machines);
				printf("Opera��es:\n");
				displayOperations(operations);
				printf("Execu��o de Opera��es:\n");
				displayExecutions(executions);
				printf("Dados mostrados com sucesso!\n");
				// Libertar mem�ria
				freeJobs(jobs);
				freeMachines(machines);
				freeOperations(operations);
				freeExecutions(executions);
				break;

			case 2: // sobre aplica��o

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