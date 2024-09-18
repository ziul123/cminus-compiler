#include "codegen.h"
#include "tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char *read_proc = \
	"read: li a7, 5\n"
	"ecall\n"
	"ret\n";

const char *write_proc = \
	"write: li a7, 1\n"
	"ecall\n"
	"ret\n";

char data[0xFFFF];
char text[0xFFFF] = "call main\nli a7, 10\necall\n";
size_t text_counter = 26; //contador de caracteres em text

const char *sav_regs[NUM_SAV];
int tmp_reg = 0;
int sav_reg = 0;

int last_tmp() {
	return (tmp_reg - 1) % NUM_TMP;
}

char *last_tmp_str() {
	char *reg = malloc(10);
	sprintf(reg, "t%d", last_tmp());
	return reg;
}

int get_tmp() {
	int reg = tmp_reg;
	tmp_reg = (tmp_reg + 1) % NUM_TMP;
	return reg;
}

char *get_tmp_str() {
	char *reg = malloc(10);
	sprintf(reg, "t%d", get_tmp());
	return reg;
}

int get_reg_num(tac_address addr, type_t var_type) {
	//returns t register if temporary, s register if var
	// and number if constant
	int reg;
	switch (addr.addr_type) {
		case TEMP:
			reg = get_tmp();
			break;
		case NAME:
			for (int i=0; i<=NUM_SAV; i++) {
				if (!sav_regs[i])
					break;
				if (strcmp(sav_regs[i], addr.name) == 0) {
					return i;
				}
			}
			sav_regs[sav_reg] = addr.name;
			switch (var_type) {
				case INT_T:
					printf("la s%1$d, %2$s\nlw, s%1$d, 0(s%1$d)\n", sav_reg, addr.name);
					break;
				case INT_ARR_T:
					printf("la s%d, %s", sav_reg, addr.name);
					break;
			}
			reg = sav_reg;
			sav_reg = (sav_reg + 1) % NUM_SAV;
			break;
		case CONST:
			return addr.constant;
	}
	return reg;
}

char *get_reg_str(tac_address addr, type_t addr_type) {
	char *reg = malloc(10);
	switch (addr.addr_type) {
		case TEMP:
			sprintf(reg, "t%d", last_tmp(addr, VOID_T));
			break;
		case NAME:
			sprintf(reg, "s%d", get_reg_num(addr, addr_type));
			break;
		case CONST:
			sprintf(reg, "%d", addr.constant);
			break;
	}
	return reg;
}

void generate_instruction(tac_cell tac_line, st_cell **symbol_table) {
	tac_address s1 = tac_line.source1;
	tac_address s2 = tac_line.source2;
	enum INST inst = tac_line.inst;
	char *line_addr = tac_line.line_addr;
	char *jmp_addr = tac_line.jmp_addr;
	char instr[10];
	char *rd, *rs1, *rs2;
	type_t s1t = VOID_T;
	type_t s2t = VOID_T;
	int imm = 0;

	if (s1.addr_type == NAME) {
		st_cell *symbol = find_sym(symbol_table, s1.name);
		s1t = symbol->sym_type;
	}

	if (s2.addr_type == NAME) {
		st_cell *symbol = find_sym(symbol_table, s2.name);
		s2t = symbol->sym_type;
	}

	//caso as duas fontes forem constante, uma precisa ser
	//carregada em registrador previamente
	if ((s1.addr_type == CONST) && (s2.addr_type == CONST)) { 
		printf("li, t%d, %d\n", get_tmp(), s1.constant);
		imm = 1;
	} else if ((s1.addr_type == CONST) || (s2.addr_type == CONST)) {
		imm = 1;
	}

	switch (inst) {
		case ADD:
			if (imm) {
				strcpy(instr, "addi");
				goto tipo_i;
			} else {
				strcpy(instr, "add");
				goto tipo_r;
			}

		case NOP:
			if (line_addr)
				printf("%s ", line_addr);
			printf("nop\n");
			break;

		tipo_r:
			rs1 = get_reg_str(s1, s1t);
			rs2 = get_reg_str(s2, s2t);
			rd = get_tmp_str();
			if (line_addr)
				printf("%s ", line_addr);
			printf("%s, %s, %s, %s\n", instr, rd, rs1, rs2); 
			break;

		tipo_i:
			break;
	}
}

void allocate_variables(st_cell **symbol_table) {
	/* Popula .data com variáveis */
	st_cell *ptr = *symbol_table;
	char space_num[5];
	
	while(!ptr->next) {
		st_cell *current = ptr->next;
		type_t type = current->sym_type;
		if(type == VOID_T) {
			continue;
		}
		if(type == INT_T) {
			strcpy(space_num, "4");
 		}
		else {
			int len = current->len;
			sprintf(space_num, "%d", len*4);
		}

		char line[40];
		char id[20] = current->name;
		sprintf(line, "%s: .space %s\n", id, space_num); // line = id + : + .space: + space_num
		
		strcat(data, line);
	}
}
