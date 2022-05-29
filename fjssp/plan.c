/**
 * @brief	Ficheiro com todas as funções relativas aos planos
 * @file	plan.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	29/05/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
* @brief	Inicia um novo plano, com todos os campos vazios
* @param	jobID			Identificador do trabalho
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool startPlan(Cell plan[][MAX_TIME], int jobID, int operationID)
{
	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			plan[i][j].jobID = jobID;
			plan[i][j].operationID = operationID;
			plan[i][j].initialTime = 0;
			plan[i][j].finalTime = 0;
		}
	}
}


/**
* @brief	Preenche uma célula do plano
* @param	mid		Identificador da máquina
* @param	jid		Identificador do trabalho
* @param	oid		Identificador da operação
* @param	it		Tempo inicial desta célula
* @param	ft		Tempo final desta célula
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool fillOneCell(Cell p[][MAX_TIME], int mid, int jid, int oid, int it, int ft)
{
	p[mid][it].jobID = jid;
	p[mid][it].operationID = oid;
	p[mid][it].initialTime = it;
	p[mid][it].finalTime = ft;
}