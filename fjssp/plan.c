/**
 * @brief	Ficheiro com todas as fun��es relativas aos planos
 * @file	plan.c
 * @author	Lu�s Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	29/05/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
* @brief	Inicia um novo plano, com todos os campos vazios
* @param	jid		Identificador do trabalho
* @param	oid		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool startPlan(Cell plan[][MAX_TIME], int jid, int oid)
{
	for (int i = 0; i < NUMBER_MACHINES; i++)
	{
		for (int j = 0; j < MAX_TIME; j++)
		{
			plan[i][j].jobID = jid;
			plan[i][j].operationID = oid;
			plan[i][j].initialTime = 0;
			plan[i][j].finalTime = 0;
		}
	}
}


/**
* @brief	Preenche uma c�lula do plano
* @param	mid		Identificador da m�quina
* @param	jid		Identificador do trabalho
* @param	oid		Identificador da opera��o
* @param	it		Tempo inicial desta c�lula
* @param	ft		Tempo final desta c�lula
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool fillCells(Cell p[][MAX_TIME], int mid, int jid, int oid, int it, int ft)
{
	// n�o permite ativar c�lulas que j� est�o ativas
	if (searchActiveCells(p, mid, it, ft))
	{
		return false;
	}

	// preenche o intervalo de c�lulas dispon�veis para este escalonamento
	for (int i = it; i < ft; i++)
	{
		// mid - 1 porque os ID's das m�quinas come�am no 1 e a matriz do plano come�a no 0
		p[mid - 1][i].jobID = jid;
		p[mid - 1][i].operationID = oid;
		p[mid - 1][i].initialTime = it;
		p[mid - 1][i].finalTime = ft;
	}

	return true;
}


/**
* @brief	Procurar em um intervalo de c�lulas do plano, se existem c�lulas ativas
* @param	mid		Identificador da m�quina
* @param	it		Tempo inicial desta c�lula
* @param	ft		Tempo final desta c�lula
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchActiveCells(Cell p[][MAX_TIME], int mid, int it, int ft)
{
	for (int i = it; i < ft; i++)
	{
		if (p[mid-1][i].jobID > -1 || p[mid-1][i].operationID > -1)
		{
			return true;
		}
	}

	return false;
}