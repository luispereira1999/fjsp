/*
Descri��o:           Ficheiro com todas as fun��es e procedimentos que podem ser utilizadas em v�rios ficheiros do projeto, mas que n�o s�o espec�ficas
Desenvolvedor(es):   Lu�s Pereira (18446)
Cria��o:             14/03/2022
�ltima atualiza��o:  31/03/2022
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