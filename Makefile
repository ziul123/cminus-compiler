CC = gcc
CFLAGS = -g3

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

build: setup scan parse
	@echo Build terminado, agora faça make cmc

cmc: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o cmc

.PHONY: setup
setup:
	mkdir -p $(OBJ_DIR)

scan: flex/cm.l
	flex -o $(SRC_DIR)/$@.c $<

parse: bison/cm.y
	bison -o $(SRC_DIR)/$@.c -d $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

-include $(DEP_FILES)

.PHONY: clean
clean:
		rm -rf $(OBJ_DIR)/* $(SRC_DIR)/parse* $(SRC_DIR)/scan.c cmc
