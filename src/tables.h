#pragma once
#include <stdint.h>

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
 	inst(NOP) \

#define GENERATE_ENUM(x) x, 
#define GENERATE_LUT(x) [x] = #x, 

typedef struct st_cell st_cell;
typedef struct tac_address tac_address;
typedef struct tac_cell tac_cell;

struct st_cell {
	// Celula da tabela de simbolos
	const char *name;
	int tac_addr;
	uint32_t mem_addr;
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

tac_address make_tmp(int tac_cell);

tac_cell *make_tac_cell(tac_address s1, tac_address s2, enum INST inst);

