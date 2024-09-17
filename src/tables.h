#pragma once
#include <stdint.h>
#include <string.h>

#define FOREACH_INSTS(inst) \
	/* Operacoes binarias */ \
	inst(ADD) \
	inst(SUB) \
	inst(MUL) \
	inst(DIV) \
	inst(SLTE) \
	inst(SLT) \
	inst(SGT) \
	inst(SGTE) \
	inst(SEQ) \
	inst(SNEQ) \
	/* Operacao de copia */ \
	inst(CPY) \
	/* Operacoes de desvio */ \
	inst(JMP) \
	inst(JT) \
	inst(JF) \
	inst(BEQ) \
	inst(BNE) \
	inst(BGT) \
	inst(BGE) \
	inst(BLT) \
	inst(BLE) \
	/* Operacoes de chamada de funcao */ \
	inst(PARAM) \
	inst(CALL) \
	inst(RET) \
	/* Operacoes de array */ \
	inst(ARR_GET) \
	inst(ARR_SET) \
	/* No Operation */ \
	inst(NOP)

#define GENERATE_ENUM(x) x, 
#define GENERATE_LUT(x) [x] = #x, 

typedef struct st_cell st_cell;
typedef struct ft_cell ft_cell;
typedef struct tac_address tac_address;
typedef struct tac_cell tac_cell;

typedef enum TYPE {VOID_T, INT_T, INT_ARR_T} type_t;
static const char * const str_type[] = {
	[VOID_T] = "VOID_T",
	[INT_T] = "INT_T",
	[INT_ARR_T] = "INT_ARR_T"
};

struct st_cell {
	// Celula da tabela de simbolos
	const char *name;
	uint32_t mem_addr;
	type_t sym_type;
	int len;	// Caso for INT_ARR
	int usado;
	st_cell *next;
};

struct ft_cell {
	// Celula da tabela de funcoes
	const char *name;
	type_t ret_type;
	// Limitamos para 8 argumentos, pois é a quantidade 
	// de registradores de argumento no RISC-V
	type_t param_types[8];
	int usado;
};

enum INST {
	FOREACH_INSTS(GENERATE_ENUM)
};

static const char * const str_inst[] = {
	FOREACH_INSTS(GENERATE_LUT)
};

struct tac_address {
	// Endereco para codigo de 3 enderecos
	union {
		int temporary;
		int constant;
		const char *name;
	};
	enum ADDR_TYPE {TEMP, CONST, NAME} addr_type;
};


struct tac_cell {
	// Celula da tabela do codigo de 3 enderecos
	enum INST inst;
	tac_address source1;
	tac_address source2;
	char* line_addr; 	// Endereco da linha
	char* jmp_addr;		// Endereco do pulo
};

void add_param_t(ft_cell *fun, type_t p_type);

void insert_sym(st_cell **sym_table, const char *name, type_t sym_type, int len);

st_cell *find_sym(st_cell **sym_table, const char *name);

st_cell *pop_sym(st_cell **sym_table);

void destroy_st(st_cell **sym_table);

tac_address make_tmp(int tac_cell);


