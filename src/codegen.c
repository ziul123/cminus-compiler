#include "codegen.h"

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

