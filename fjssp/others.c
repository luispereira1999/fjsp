/*
Descrição:           Ficheiro com todas as funções e procedimentos que podem ser utilizadas em vários ficheiros do projeto, mas que não são específicas
Desenvolvedor(es):   Luís Pereira (18446)
Criação:             14/03/2022
Última atualização:  31/03/2022
*/

#include <stdio.h>
#include "header.h"

int getListCount(Job* head)
{
	if (head == NULL)
	{
		return -1;
	}

	int count = 0;
	Job* current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return count;
}