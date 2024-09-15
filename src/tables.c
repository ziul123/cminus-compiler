#include <stdio.h>
#include <stdlib.h>
#include "tables.h"

// tac_address make_tmp(tac_cell *addr) {
// 	return (tac_address){.temporary = addr, .addr_type = TEMP};
// }

tac_address make_tmp(int tac_counter) {
	return (tac_address){.temporary = tac_counter, .addr_type = TEMP};
}

tac_cell *make_tac_cell(tac_address s1, tac_address s2, enum INST inst) {
	tac_cell *new_cell = malloc(sizeof(tac_cell));
	if (!new_cell)
		printf("Erro alocando memoria para nova operacao 3 enderecos\n");
	new_cell->source1 = s1;
	new_cell->source2 = s2;
	new_cell->inst = inst;
	return new_cell;
}

