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
* @param	executionID		Identificador da execução
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool startPlan(Plan plan[][MAX_RUNTIME], int jobID, int executionID)
{
	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_RUNTIME; j++)
		{
			plan[i][j].jobID = jobID;
			plan[i][j].executionID = executionID;
		}
	}
}