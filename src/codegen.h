#pragma once
#include "tables.h"

#define NUM_TMP 7
#define NUM_SAV 11

void allocate_temporaries(tac_cell tac_table[], int tac_c);
void allocate_variables(st_cell **symbol_table);
void generate_insts(tac_cell tac_table[], int tac_c, st_cell **symbol_table); 
