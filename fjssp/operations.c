/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos relativos �s operations
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Operation* newOperation(int id, int jobID, int position)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->id = id;
	new->jobID = id;
	new->position = position;
	new->next = NULL;

	return new;
}

Operation* insertOperationAtStart(Operation* head, Operation* operationToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = operationToInsert;
	}
	else // se existir algum elemento na lista
	{
		operationToInsert->next = head;
		head = operationToInsert;
	}

	return head;
}

PerformOperation* newPerformOperation(int operationID, int machineID, int usageTime)
{
	PerformOperation* new = (PerformOperation*)malloc(sizeof(PerformOperation));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->usageTime = usageTime;
	new->next = NULL;

	return new;
}

PerformOperation* insertPerformOperationAtStart(PerformOperation* head, PerformOperation* performOperationToInsert)
{
	if (head == NULL) // se a lista estiver vazia
	{
		head = performOperationToInsert;
	}
	else // se existir algum elemento na lista
	{
		performOperationToInsert->next = head;
		head = performOperationToInsert;
	}

	return head;
}