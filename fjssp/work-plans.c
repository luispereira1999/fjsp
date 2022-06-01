/**
 * @brief	Ficheiro com todas as funções relativas aos trabalhos para produção
 * @file	work-plans.c
 * @author	Luís Pereira
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
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Tempo de execução da operação
* @param	position		Posição da operação a ser executada relativamente ao trabalho
* @return	Nova plano de trabalho
*/
WorkPlan* newWorkPlan(int jobID, int operationID, int machineID, int runtime, int position)
{
	WorkPlan* new = (WorkPlan*)malloc(sizeof(WorkPlan));
	if (new == NULL) // se não houver memória para alocar
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
* @brief	Inserir no plano de trabalho no início da lista de operações
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
* @brief	Inserir plano de trabalho ordenado pelo posição das operações num job na lista de planos de trabalhos
* @param	head	Lista de planos de trabalhos
* @param	new		Novo plano de trabalho
* @return	Lista de planos de trabalhos atualizada
*/
WorkPlan* insertWorkPlan_ByJob_AtList(WorkPlan* head, WorkPlan* new)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = new; // inserir no início
	}
	else
	{
		WorkPlan* current = head;
		WorkPlan* previous = NULL;

		// enquanto que o atual tem a posição da operação menor que o novo
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
* @return	Booleano para o resultado da função (se funcionou ou não)
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
		printf("ID Trabalho: %d, ID Operação: %d, ID Máquina: %d, Tempo de Execução: %d, Posição: %d;\n", current->jobID, current->operationID, current->machineID, current->runtime, current->position);
		current = current->next;
	}

	return true;
}


/**
* @brief	Ordenar planos de trabalhos por ordem crescente da posição das operações num job
* @param	head			Lista de planos de trabalhos
* @return	Booleano para o resultado da função (se funcionou ou não)
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