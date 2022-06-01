/**
 * @brief	Ficheiro com todas as fun��es relativas aos trabalhos para produ��o
 * @file	work-plans.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	1/6/2022
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