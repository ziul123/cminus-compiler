#pragma once
#include "tables.h"

#define NUM_TMP 7
#define NUM_SAV 11

void allocate_variables(st_cell **symbol_table);
void generate_instruction(tac_cell tac_line, st_cell **symbol_table); 
