#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

/*
 * -o <file>: output to <file>
 * -t: 				print tac
 * -s: 				print symbol table
 * -f: 				print function table
 * -W:				ignore warnings
*/
int main(int argc, char **argv) {
	int oflag = 0;
	char *outname = NULL;
	int tflag = 0;
	int sflag = 0;
	int fflag = 0;
	int Wflag = 0;
	char *filename;
	int c;

	while ((c = getopt(argc, argv, "o:tsfW")) != -1)
		switch (c) {
		case 'o':
			oflag = 1;
			outname = optarg;
			break;
		case 't':
			tflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'f':
			fflag = 1;
			break;
		case 'W':
			Wflag = 1;
			break;
		case '?':
			if (optopt == 'o')
				fprintf(stderr, "Opção -%c requere argumento.\n", optopt);
			else
				fprintf(stderr, "Opção '-%c' não reconhecida.\n", optopt);
	}

	if (!argv[optind])
		fprintf(stderr, "Não especificou o arquivo a ser compilado.\n");
	else
		filename = argv[optind];

	if (!(yyin = fopen(filename, "r"))) {
		perror("Error reading file.\n");
		return 1;
	}

	if (!oflag) {
		size_t fname_len = strlen(filename);
		outname = malloc(fname_len + 2);
		strcpy(outname, filename);
		memcpy(outname + fname_len - 2, "asm", 3);
	}
	symbol_table = malloc(sizeof(st_cell*));

//	yydebug = 1;
	yyparse();

	if (!Wflag) {
		st_cell *current = *symbol_table;
		if (current) {
			while (current) {
				if (!current->usado)
					printf("WARNING: Variavel %s declarada mas nao utilizada!\n", current->name);
				current = current->next;
			}
		}

		for (int i=0; i<fun_counter; i++) {
			if (strcmp(fun_table[i].name, "main") == 0)
				fun_table[i].usado = 1;
			if (!fun_table[i].usado)
				printf("WARNING: Funcao %s declarada mas nao utilizada!\n", fun_table[i].name);
		}
	}

	if (sflag) {
		st_cell *current = *symbol_table;
		if (current) {
			while (current) {
				print_st_cell(*current);
				current = current->next;
			}
		}
	}

	if (fflag) {
		for (int i=0; i<fun_counter; i++) {
			if (strcmp(fun_table[i].name, "main") == 0)
				fun_table[i].usado = 1;
			print_ft_cell(fun_table[i]);
		}
	}

	if (tflag) {
		for (int i = 0; i < tac_counter; i++) {
			print_tac_cell(tac_table[i], i);
		}
	}

	allocate_variables(symbol_table);
	allocate_temporaries(tac_table, tac_counter);
	
	generate_insts(tac_table, tac_counter, symbol_table);
	
	FILE *outfile = fopen(outname, "w");
	fwrite(data, 1, strlen(data), outfile);
	fwrite(text, 1, strlen(text), outfile);
	fclose(outfile);
}
