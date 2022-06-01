/**
 * @brief	Ficheiro com todas as fun��es relativas aos planos de produ��o
 * @file	plan.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	29/05/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data-types.h"
#include "lists.h"


#pragma region planos de produ��o para exportar para ficheiro

/**
* @brief	Iniciar um novo plano com todos as c�lulas vazias
* @param	plan			Plano a ser iniciado
* @param	jobID			Identificador do trabalho
* @param	operationID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool startPlan(Cell plan[][MAX_TIME], int jobID, int operationID)
{
	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			plan[i][j].jobID = jobID;
			plan[i][j].operationID = operationID;
			plan[i][j].currentTime = 0;
		}
	}
}


/**
* @brief	Preencher c�lulas do plano em um intervalo de tempo
* @param	plan			Plano atual
* @param	machineID		Identificador da m�quina
* @param	jobID			Identificador do trabalho
* @param	operationID		Identificador da opera��o
* @param	initialTime		Tempo inicial do intervalo
* @param	finalTime		Tempo final do intervalo
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool fillCells(Cell plan[][MAX_TIME], int machineID, int jobID, int operationID, int initialTime, int finalTime)
{
	// n�o permite ativar c�lulas que j� est�o ativas
	if (searchActiveCells(plan, machineID, initialTime, finalTime))
	{
		return false;
	}

	// preenche o intervalo de c�lulas dispon�veis para este escalonamento
	for (int i = initialTime; i < initialTime + finalTime; i++)
	{
		// mid - 1 porque os IDs das m�quinas come�am em 1 e a matriz do plano come�a em 0
		plan[machineID - 1][i].jobID = jobID;
		plan[machineID - 1][i].operationID = operationID;
		plan[machineID - 1][i].currentTime = initialTime + finalTime;
	}

	return true;
}


/**
* @brief	Obter �ltima c�lula preenchida de uma m�quina
* @param	plan		Plano atual
* @param	machineID	Identificador da m�quina
* @return	C�lula obtida
*/
Cell getLastCellFilled_InMachine(Cell plan[][MAX_TIME], int machineID)
{
	Cell last;
	last.jobID = -1;
	last.currentTime = -1;
	last.operationID = -1;

	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			if (plan[i][j].jobID != -1)
			{
				// -1 porque o �ndice na matriz � -1 do que o identificador
				if (machineID - 1 == i)
				{
					last = plan[i][j];
				}
			}
		}
	}

	return last;
}


/**
* @brief	Obter �ltima c�lula preenchida em rela��o a um trabalho
* @param	plan		Plano atual
* @param	machineID	Identificador do trabalho
* @return	C�lula obtida
*/
Cell getLastCellFilled_OfJob(Cell plan[][MAX_TIME], int jobID)
{
	Cell last;
	last.jobID = -1;
	last.currentTime = -1;
	last.operationID = -1;

	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			if (plan[i][j].jobID != -1)
			{
				if (jobID == plan[i][j].jobID)
				{
					last = plan[i][j];
				}
			}
		}
	}

	return last;
}


/**
* @brief	Preencher todas as c�lulas do plano relativamente a uma lista de planos de trabalhos
* @param	plan			Plano atual
* @param	workPlans		Lista de planos de trabalhos
* @param	numberOfCells	Quantidade de c�lulas a preencher
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool fillAllPlan(Cell plan[][MAX_TIME], WorkPlan* workPlans, int numberOfCells)
{
	WorkPlan* currentWorkPlan = workPlans;

	int i = 0;
	while (currentWorkPlan && i < numberOfCells)
	{
		Cell lastCellInMachine = getLastCellFilled_InMachine(plan, currentWorkPlan->machineID);
		Cell lastCellOfJob = getLastCellFilled_OfJob(plan, currentWorkPlan->jobID);

		if (lastCellInMachine.currentTime == -1)
		{
			if (lastCellOfJob.currentTime != -1)
			{
				lastCellInMachine.currentTime = lastCellOfJob.currentTime;
			}
		}

		if (lastCellInMachine.currentTime == -1)
		{
			lastCellInMachine.currentTime = 0;
		}

		fillCells(plan, currentWorkPlan->machineID, currentWorkPlan->jobID, currentWorkPlan->operationID,
			lastCellInMachine.currentTime, currentWorkPlan->runtime);

		currentWorkPlan = currentWorkPlan->next;
		i++;
	}
}


/**
* @brief	Procurar num intervalo de c�lulas do plano, se existem c�lulas ativas
* @param	plan			Plano atual
* @param	machineID		Identificador da m�quina
* @param	initialTime		Tempo inicial desta c�lula
* @param	finalTime		Tempo final desta c�lula
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchActiveCells(Cell plan[][MAX_TIME], int machineID, int initialTime, int finalTime)
{
	for (int i = initialTime; i < finalTime; i++)
	{
		if (plan[machineID - 1][i].jobID > -1 || plan[machineID - 1][i].operationID > -1)
		{
			return true;
		}
	}

	return false;
}


/**
* @brief	Mostrar plano de escalonamento na consola
* @param	plan	Plano a ser mostrado
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayPlan(Cell plan[][MAX_TIME])
{
	printf("\n");
	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			if (plan[i][j].jobID > -1 && plan[i][j].operationID > -1)
			{
				printf("|j%d o%d", plan[i][j].jobID, plan[i][j].operationID);
			}
			else
			{
				printf("|     ");
			}
		}
		printf("|\n");
	}
	printf("\n");
}

#pragma endregion


#pragma region planos de produ��o para exportar para ficheiro

/**
* @brief	Criar nova c�lula do plano que ser� exportada para um ficheiro
* @param	machineID		Identificador da m�quina
* @param	jobID			Identificador do job
* @param	operationID		Identificador da opera��o
* @param	initialTime		Tempo inicial no plano de produ��o relativamente a esta opera��o
* @param	finalTime		Tempo final no plano de produ��o relativamente a esta opera��o
* @return	Nova c�lula
*/
FileCell* newFileCell(int machineID, int jobID, int operationID, int initialTime, int finalTime)
{
	FileCell* new = (FileCell*)malloc(sizeof(FileCell));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->machineID = machineID;
	new->jobID = jobID;
	new->operationID = operationID;
	new->initialTime = initialTime;
	new->finalTime = finalTime;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir c�lula do plano no in�cio da lista de c�lulas
* @param	head	Lista de c�lulas do plano
* @param	new		Nova c�lula do plano
* @return	Lista de c�lulas do plano
*/
FileCell* insertFileCell_AtStart(FileCell* head, FileCell* new)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = new;
	}
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}


/**
* @brief	Inserir c�lula ordenada por m�quina, na lista de c�lulas
* @param	head	Lista de c�lulas
* @param	new		Nova c�lula
* @return	Lista de c�lulas atualizada
*/
FileCell* insertFileCell_ByMachine(FileCell* head, FileCell* new)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = new; // inserir no in�cio
	}
	else
	{
		FileCell* current = head;
		FileCell* previous = NULL;

		// enquanto que o atual tem o ID da m�quina menor que o novo
		while (current != NULL && current->machineID < new->machineID)
		{
			previous = current;
			current = current->next;

		}

		if (previous == NULL)
		{
			new->next = head;
			head = new; // inserir no meio
		}
		else
		{
			previous->next = new;
			new->next = current; // inserir no fim
		}
	}

	return head;
}


/**
* @brief	Ordenar c�lulas por ordem crescente das m�quinas
* @param	head			Lista de c�lulas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
FileCell* sortFileCells_ByMachine(FileCell* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	FileCell* current = head;
	FileCell* sorted = NULL;
	FileCell* new = NULL;

	while (current != NULL)
	{
		new = newFileCell(current->machineID, current->jobID, current->operationID, current->initialTime, current->finalTime);
		sorted = insertFileCell_ByMachine(sorted, new);
		current = current->next;
	}

	return sorted;
}


/**
* @brief	Obter c�lulas de um plano, para depois serem exportadas para um ficheiro
* @param	plan		Plano atual
* @return	C�lulas que ser�o exportadas
*/
FileCell* getCellsToExport(Cell plan[][MAX_TIME])
{
	FileCell* cells = NULL;

	int currJobID = -1;
	int currOpID = -1;
	int nextJobID = -1;

	int initialTime = -1;
	int finalTime = -1;
	int tempFinalTime = -1;
	int tempInitialTime = -1;

	int equalCells = 0;

	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			if (plan[i][j].jobID != -1)
			{
				currJobID = plan[i][j].jobID;
				currOpID = plan[i][j].operationID;
				nextJobID = plan[i][j + 1].jobID;
				initialTime = j;
				finalTime = initialTime;

				if (currJobID == nextJobID)
				{
					initialTime = j;

					equalCells++;
					if (equalCells == 1)
					{
						tempInitialTime = initialTime;
					}

					tempFinalTime = finalTime;
					tempFinalTime += 1;
				}
				else
				{
					if (equalCells == 0)
					{
						tempInitialTime = initialTime;
					}

					tempFinalTime += 1;

					FileCell* cell = newFileCell(i + 1, currJobID, currOpID, tempInitialTime, tempFinalTime);
					cells = insertFileCell_AtStart(cells, cell);

					equalCells = 0;
					tempInitialTime == -1;
					tempFinalTime == -1;
				}
			}
		}
	}

	return cells;
}


/**
* @brief	Exportar plano para um ficheiro
* @param	fileName	Nome do ficheiro onde ser� guardado as c�lulas
* @param	head		Lista de c�lulas para exportar
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool exportPlan(char* fileName, FileCell* head)
{
	if (head == NULL)
	{
		return false;
	}

	FILE* file = fopen(fileName, "w");
	if (file == NULL)
	{
		return false;
	}

	FileCell* current = head;
	while (current)
	{
		fprintf(file, "Maquina %d, Trabalho %d - Operacao %d, %d, %d\n", current->machineID, current->jobID, current->operationID, current->initialTime, current->finalTime);
		current = current->next;
	}

	fclose(file);

	return true;
}

#pragma endregion