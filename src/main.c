#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include "codegen.h"

extern FILE *yyin;
extern void yyparse(void);
extern st_cell **symbol_table;
extern ft_cell fun_table[4096];
extern tac_cell tac_table[4096];
extern int fun_counter;
extern int tac_counter;
extern int label_counter;
extern char data[0xFFFF];
extern char text[0xFFFF];

void print_st_cell(st_cell symbol) {
	printf("%s: %s", symbol.name, str_type[symbol.sym_type]);
	if (symbol.sym_type == INT_ARR_T)
		printf("[%d]", symbol.len);
	printf(" (usado: %s)\n", symbol.usado?"sim":"nao");
}

void print_ft_cell(ft_cell fun) {
	printf("%s (usado: %s)\n", fun.name, fun.usado?"sim":"nao");
}

void print_tac_address(tac_address addr) {
	switch (addr.addr_type) {
		case TEMP:
			printf("(%d)", addr.temporary);
			break;

		case CONST:
			printf("%d", addr.constant);
			break;

		case NAME:
			printf("%s", addr.name);
			break;
	}
}

void print_tac_cell(tac_cell cell, int lineno) {
	printf("%d\t", lineno);
	if (cell.line_addr)
		printf("%s: ", cell.line_addr);
	printf(" %s ", str_inst[cell.inst]);
	print_tac_address(cell.source1);
	printf(" ");
	print_tac_address(cell.source2);
	if (cell.inst >= JMP && cell.inst <= CALL)
		printf(" %s", cell.jmp_addr);
	printf("\n");
}



int main(int argc, char **argv) {
	char *filename;
	if (argc == 2) {
		filename = argv[1];
		if (!(yyin = fopen(argv[1], "r"))) {
			perror("Error reading file.\n");
			return 1;
		}
	}

	size_t fname_len = strlen(filename);
	char *outfilename = malloc(fname_len + 1);
	strcpy(outfilename, filename);
	memcpy(outfilename + fname_len - 2, "asm", 3);

	symbol_table = malloc(sizeof(st_cell*));

//	yydebug = 1;
	yyparse();

//	st_cell *current = *symbol_table;
//	if (current) {
//		while (current) {
//			//print_st_cell(*current);
//			if (!current->usado)
//				printf("WARNING: Variavel %s declarada mas nao utilizada!\n", current->name);
//			current = current->next;
//		}
//	}
//
//	for (int i=0; i<fun_counter; i++) {
//		if (strcmp(fun_table[i].name, "main") == 0)
//			fun_table[i].usado = 1;
//		//print_ft_cell(fun_table[i]);
//		if (!fun_table[i].usado)
//			printf("WARNING: Funcao %s declarada mas nao utilizada!\n", fun_table[i].name);
//	}
//
	for (int i = 0; i < tac_counter; i++) {
		print_tac_cell(tac_table[i], i);
	}

	allocate_variables(symbol_table);
	allocate_temporaries(tac_table, tac_counter);
	
	generate_insts(tac_table, tac_counter, symbol_table);
	
	FILE *outfile = fopen(outfilename, "w");
	fwrite(data, 1, strlen(data), outfile);
	fwrite(text, 1, strlen(text), outfile);
	fclose(outfile);
}
