#include <stdio.h>
#include <stdlib.h>
#include "tables.h"

void insert_sym(st_cell **sym_table, const char *name, type_t sym_type, int len) {
	st_cell *new_symbol = malloc(sizeof(st_cell));
	if (!new_symbol)
		printf("Erro alocando memoria para tabela de simbolos!\n");

	new_symbol->name = name;
	new_symbol->sym_type = sym_type;
	new_symbol->len = len;

	st_cell *current = *sym_table;
	if (!current) {	//se for o primeiro simbolo a ser adicionado
		*sym_table = new_symbol;
		return;
	}

	while (1) {		//busca o ultimo simbolo definido
		if (!current->next) {
			current->next = new_symbol;
			break;
		}
		current = current->next;
	}
}

st_cell *find_sym(st_cell **sym_table, const char *name) {
	st_cell *current = *sym_table;

	if (!current) {
		//nao tem simbolos
		return NULL;
	}
	while (1) {
		if (strcmp(current->name, name) == 0) {
			//achamos o simbolo
			return current;
		}

		if (!current->next) {
			//esse era o ultimo simbolo, e nao achamos o nosso
			return NULL;
		}

		current = current->next;
	}
}

st_cell *pop_sym(st_cell **sym_table) {
	st_cell *current = *sym_table;
	st_cell *past;

	if (!current)
		return NULL;

	if (!current->next) {
		*sym_table = NULL;
		return current;
	}

	while (current->next) {
		past = current; //salva o antigo
		current = current->next; //pega o proximo
	}

	past->next = NULL;
	return current;
}

void destroy_st(st_cell **symbol_table) {
	st_cell *result;
	while ((result = pop_sym(symbol_table))) {
		free(result);
	}
}

tac_address make_tmp(int tac_counter) {
	return (tac_address){.temporary = tac_counter, .addr_type = TEMP};
}

