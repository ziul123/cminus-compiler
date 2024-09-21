# Trabalho da disciplina de Compiladores
## Compilador de C- para RISC-V

### Compilação:
- `./build` ou `make; make cmc`

### Uso:
- `cmc file [-o filename] [-t] [-s] [-f] [-W]`
- `-o <filename>`:	escreve output para arquivo `<filename>` (default é file.asm).
- `-t`:							imprime a tabela de código de três endereços na tela.
- `-s`:							imprime a tabela de símbolos na tela.
- `-f`:							imprime a tabela de funções na tela.
- `-W`:							ignora warnings.

### Execução do código gerado:
O código gerado está na linguagem de RISC-V Assembly, portanto, ainda precisa ser montado, e depois simulado.
Recomendamos a utilização do montador e simulador [FPGRARS](https://github.com/LeoRiether/FPGRARS).
Caso desejado, pode-se usar o script `test` para compilar e executar programas automaticamente. Para isso, simplesmente renomeie o comando que invoca o `FPGRARS` com o nome do executável.

### Alunos:

1. Luiz Carlos da Silva Néto Vartuli
2. Paulo Maurício Costa Lopes
3. Paulo Victor França de Souza
4. Thais Fernanda de Castro Garcia
5. Victor Hugo França Lisboa
