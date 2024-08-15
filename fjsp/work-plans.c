/**
 * @brief	Ficheiro com todas as fun��es relativas aos trabalhos para produ��o.
 * @file	work-plans.c
 * @author	Lu�s Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "lists.h"


/**
* @brief	Criar novo plano de trabalho
* @param	jobID			Identificador do job
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @param	runtime			Tempo de execu��o da opera��o
* @param	position		Posi��o da opera��o a ser executada relativamente ao trabalho
* @return	Nova plano de trabalho
*/
WorkPlan* newWorkPlan(int jobID, int operationID, int machineID, int runtime, int position)
{
	WorkPlan* new = (WorkPlan*)malloc(sizeof(WorkPlan));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->jobID = jobID;
	new->machineID = machineID;
	new->operationID = operationID;
	new->runtime = runtime;
	new->position = position;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir no plano de trabalho no in�cio da lista de opera��es
* @param	head	Lista de planos de trabalhos
* @param	new		Nova plano de trabalho
* @return	Lista de planos de trabalhos
*/
WorkPlan* insertWorkPlan_AtStart(WorkPlan* head, WorkPlan* new)
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
* @brief	Inserir plano de trabalho ordenado pelo posi��o das opera��es num job na lista de planos de trabalhos
* @param	head	Lista de planos de trabalhos
* @param	new		Novo plano de trabalho
* @return	Lista de planos de trabalhos atualizada
*/
WorkPlan* insertWorkPlan_ByJob_AtList(WorkPlan* head, WorkPlan* new)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = new; // inserir no in�cio
	}
	else
	{
		WorkPlan* current = head;
		WorkPlan* previous = NULL;

		// enquanto que o atual tem a posi��o da opera��o menor que o novo
		while (current != NULL && current->position < new->position)
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
* @brief	Mostrar a lista de planos de trabalhos na consola
* @param	head	Lista de planos de trabalhos
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayWorkPlans(WorkPlan* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	WorkPlan* current = head;

	while (current != NULL)
	{
		printf("ID Trabalho: %d, ID Opera��o: %d, ID M�quina: %d, Tempo de Execu��o: %d, Posi��o: %d;\n", current->jobID, current->operationID, current->machineID, current->runtime, current->position);
		current = current->next;
	}

	return true;
}


/**
* @brief	Ordenar planos de trabalhos por ordem crescente da posi��o das opera��es num job
* @param	head			Lista de planos de trabalhos
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
WorkPlan* sortWorkPlans_ByJob(WorkPlan* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	WorkPlan* current = head;
	WorkPlan* sorted = NULL;
	WorkPlan* new = NULL;

	while (current != NULL)
	{
		new = newWorkPlan(current->jobID, current->operationID, current->machineID, current->runtime, current->position);
		sorted = insertWorkPlan_ByJob_AtList(sorted, new);
		current = current->next;
	}

	return sorted;
}


/**
* @brief	Obter todos os planos de trabalhos para um realizar um plano de produ��o
* @param	head			Lista de planos de trabalhos
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
WorkPlan* getAllWorkPlans(Job* jobs, Operation* operations, Execution* executions)
{
	WorkPlan* workPlans = NULL, * workPlan = NULL;
	Execution* minExecutions = NULL;
	int minTime = 0;

	while (jobs)
	{
		// obter o tempo m�nimo para completar um job e as respetivas opera��es
		minTime = getMinTime_ToCompleteJob(operations, executions, jobs->id, &minExecutions);

		while (minExecutions)
		{
			Operation* currOper = getOperation(operations, minExecutions->operationID);

			workPlan = newWorkPlan(jobs->id, minExecutions->operationID, minExecutions->machineID, minExecutions->runtime, currOper->position);
			workPlans = insertWorkPlan_AtStart(workPlans, workPlan);

			minExecutions = minExecutions->next;
		}

		freeExecutions_List(&minExecutions);
		jobs = jobs->next;
	}

	return workPlans;
}


/**
* @brief	Obter o tempo total do plano
* @param	head			Lista de planos de trabalhos
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
int getFullTimeOfPlan(WorkPlan* head)
{
	if (head == NULL)
	{
		return -1;
	}

	int fullTime = 0;
	WorkPlan* current = head;

	while (current)
	{
		fullTime += current->runtime;
		current = current->next;
	}

	return fullTime;
}