/**
 * @brief	Ficheiro com função para carregar dados em memória
 * @file	data.c
 * @author	Luís Pereira
 * @email	a18446@alunos.ipca.pt
 * @date	25/03/2022
*/

#include <stdio.h>
#include "header.h"


/**
* @brief	Carregar dados de execuções de operações para a tabela hash em memória
* @param	table	Apontador para a tabela hash das execuções de operações
*/
ExecutionNode** loadExecutionsTable(ExecutionNode* table[])
{
	Execution* execution = NULL;

	// execution - job 1
	execution = newExecution(1, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(1, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(2, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(2, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(3, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(3, 5, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 7, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 8, 9);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 2
	execution = newExecution(5, 1, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(5, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(5, 5, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(6, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(6, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(7, 4, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(7, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 7, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 8, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(9, 4, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(9, 6, 2);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 1, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(11, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 3
	execution = newExecution(12, 2, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(12, 3, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(12, 8, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 8, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(14, 3, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(14, 5, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(14, 7, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(15, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(15, 6, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(16, 1, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(16, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 4
	execution = newExecution(17, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(17, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(17, 5, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(18, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(18, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 7, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(20, 5, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(20, 6, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(20, 8, 5);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 5
	execution = newExecution(21, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(22, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(22, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(23, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(23, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(24, 5, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(24, 6, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(24, 8, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(25, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(25, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 6
	execution = newExecution(26, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(26, 2, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(26, 3, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(27, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(27, 5, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(28, 3, 9);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(28, 6, 8);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 7
	execution = newExecution(29, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(29, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(29, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(30, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(30, 7, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(30, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(32, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(32, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(32, 8, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(33, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(33, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 8
	execution = newExecution(34, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(34, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(34, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(35, 4, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(35, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(35, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(36, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(36, 7, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(37, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(37, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(38, 7, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(38, 8, 2);
	*table = insertExecution_AtTable(table, execution);

	return *table;
}