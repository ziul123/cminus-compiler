#include "codegen.h"
#include "tables.h"
#include "string.h"

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