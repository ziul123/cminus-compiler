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
	"li a7, 11\n"
	"li a0, 10\n"
	"ecall\n"
	"ret\n";

char data[0xFFFF] = ".data\n";
char text[0xFFFF] = ".text\ncall main\nli a7, 10\necall\n";

char *load_addr(tac_address addr, char *cur_text, int reg, type_t var_type) {
	int offset;
	const char *name = addr.name;
	int tmp = addr.temporary;
	int c = addr.constant;
	switch (addr.addr_type) {
		case TEMP:
			offset = sprintf(cur_text, "la t%1$d, T%2$d\nlw t%1$d, 0(t%1$d)\n", reg, tmp);
			break;

		case NAME:
			if (var_type == INT_T) {
				offset = sprintf(cur_text, "la t%1$d, %2$s\nlw t%1$d, 0(t%1$d)\n", reg, name);
			} else {
				offset = sprintf(cur_text, "la t%d, %s\n", reg, name);
			}
			break;

		case CONST:
			offset = sprintf(cur_text, "li t%d, %d\n", reg, c);
			break;
	}
	return cur_text + offset;
}

char *store_tmp(int num, char *cur_text) {
	cur_text += sprintf(cur_text, "la t1, T%d\n", num);
	return memccpy(cur_text, "sw t0, 0(t1)\n", 0, 50) - 1;
}

void generate_insts(tac_cell tac_table[], int tac_c, st_cell **symbol_table) {
	char *cur_text = text + strlen(text);
	cur_text = memccpy(cur_text, write_proc, 0, 100) - 1;
	cur_text = memccpy(cur_text, read_proc, 0, 100) - 1;
	for (int i=0; i<tac_c; i++) {
		tac_address s1 = tac_table[i].source1;
		tac_address s2 = tac_table[i].source2;
		enum INST inst = tac_table[i].inst;
		char *line_addr = tac_table[i].line_addr;
		char *jmp_addr = tac_table[i].jmp_addr;
		char instr[10];
		char *rd, *rs1, *rs2;
		type_t s1t = VOID_T;
		type_t s2t = VOID_T;

		if (s1.addr_type == NAME) {
			st_cell *symbol = find_sym(symbol_table, s1.name);
			s1t = symbol->sym_type;
		}

		if (s2.addr_type == NAME) {
			st_cell *symbol = find_sym(symbol_table, s2.name);
			s2t = symbol->sym_type;
		}
		
		if (line_addr) {
			cur_text = memccpy(cur_text, line_addr, 0, 50) - 1;
			*(cur_text++) = ':';
			*(cur_text++) = '\n';
		}
		
		switch (inst) {
			case ADD:
				strcpy(instr, "add");
				goto tipo_r;

			case SUB:
				strcpy(instr, "sub");
				goto tipo_r;

			case MUL:
				strcpy(instr, "mul");
				goto tipo_r;

			case DIV:
				strcpy(instr, "div");
				goto tipo_r;

			case SLT:
				strcpy(instr, "slt");
				goto tipo_r;

			case SLTE: //TODO
				strcpy(instr, "add");
				goto tipo_r;

			case SGT: //TODO
				strcpy(instr, "add");
				goto tipo_r;

			case SGTE: //TODO
				strcpy(instr, "add");
				goto tipo_r;

			case SEQ: //TODO
				strcpy(instr, "add");
				goto tipo_r;

			case SNEQ: //TODO
				strcpy(instr, "add");
				goto tipo_r;

			case CPY:
				cur_text = load_addr(s2, cur_text, 0, s2t);
				cur_text += sprintf(cur_text, "la t1, %s\n", s1.name);
				cur_text = memccpy(cur_text, "sw t0, 0(t1)\n", 0, 50) - 1;
				break;

			case JMP:
				cur_text += sprintf(cur_text, "j %s\n", jmp_addr);
				break;

			case JF:
				cur_text = load_addr(s1, cur_text, 0, s1t);
				cur_text += sprintf(cur_text, "beqz t0, %s\n", jmp_addr);
				break;

			case CALL:
				cur_text += sprintf(cur_text, "call %s\n", jmp_addr);
				break;

			case ENTER:
				cur_text = memccpy(cur_text, "addi sp, sp, -4\nsw ra, 0(sp)\n", 0, 50) - 1;
				break;

			case RET:
				cur_text = memccpy(cur_text, "lw ra, 0(sp)\naddi sp, sp, 4\nret\n", 0, 100) - 1;
				break;

			case PTR_GET:
				cur_text += sprintf(cur_text, "la t0, %s\n", s1.name);
				cur_text = load_addr(s2, cur_text, 1, s2t);
				cur_text = memccpy(cur_text, "add t0, t0, t1\nlw t0, 0(t0)\n", 0, 50) - 1;
				cur_text = store_tmp(i, cur_text);
				break;

			case PTR_SET:
				cur_text = load_addr(s1, cur_text, 0, s1t);
				cur_text = load_addr(s2, cur_text, 1, s2t);
				cur_text = memccpy(cur_text, "sw t1, 0(t0)\n", 0, 50) - 1;
				break;

			case NOP:
				cur_text = memccpy(cur_text, "nop\n", 0, 10) - 1;
				break;

			case READ_INST:
				cur_text = memccpy(cur_text, "call read\n", 0, 50) - 1;
				cur_text += sprintf(cur_text, "la t1, %s\n", s1.name);
				cur_text = memccpy(cur_text, "sw a0, 0(t1)\n", 0, 50) - 1;
				break;

			case WRITE_INST:
				cur_text = load_addr(s1, cur_text, 0, s1t);
				cur_text = memccpy(cur_text, "mv a0, t0\ncall write\n", 0, 50) - 1;
				break;


			tipo_r:
				cur_text = load_addr(s1, cur_text, 0, s1t);
				cur_text = load_addr(s2, cur_text, 1, s2t);
				cur_text += sprintf(cur_text, "%s t0, t0, t1\n", instr);
				cur_text = store_tmp(i, cur_text);
				break;
		}
	}
}

void allocate_temporaries(tac_cell tac_table[], int tac_c) {
	/* Popula .data com variaveis temporarias */
	char *dest = data + strlen(data);
	for (int i=0; i<tac_c; i++) {
		char tmp[40]; 
		sprintf(tmp, "T%d: .space 4\n", i);
		dest = memccpy(dest, tmp, 0, 50) - 1;
	}
}

void allocate_variables(st_cell **symbol_table) {
	/* Popula .data com variáveis */
	st_cell *current = *symbol_table;
	char space_num[5];
	
	while(current) {
		type_t type = current->sym_type;
		if(type == VOID_T) {
			current = current->next;
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
		const char *id = current->name;
		sprintf(line, "%s: .space %s\n", id, space_num); // line = id + : + .space: + space_num
		
		strcat(data, line);
		current = current->next;
	}
}
