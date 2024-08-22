/**
 * @brief	Ficheiro com todas as fun��es que podem ser reutilizaadas em v�rios s�tios do projeto.
 * @file	utils.c
 * @author	Lu�s Pereira
 * @date	15/08/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "data-types.h"
#include "utils.h"


/**
 * @brief	Remover a nova linha do final de uma string, se existir
 * @param	text	Texto
 * @return	Texto com nova linha removida
*/
bool removeNewLine(char* text)
{
	bool removed = false;
	size_t len = strlen(text);

	if (len > 0 && text[len - 1] == '\n')
	{
		text[len - 1] = '\0';
		removed = true;
	}

	return removed;
}