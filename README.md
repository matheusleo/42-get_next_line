# 42-get_next_line

O objetivo do projeto é criar uma função chamada **get_next_line** que faz a leitura de um arquivo linha a linha e aprender sobre viariáveis estáticas (static) em C.

## Descrição

### Mandatório

A parte mandatória consiste em implementar a função que irá fazer a leitura linha a linha de um arquivo. Caso um outro arquivo seja lido, a função irá continuar a partir da numeração da linha do arquivo anterior.

Ex.: Um arquivo está sendo lido e está na linha 8. Então, outro arquivo foi aberto e a função `get_next_line` foi chamada com o novo `file descriptor`. A função irá retornar a linha 9 do novo arquivo.

### Bônus

A parte mandatória consiste em implementar a função que irá fazer a leitura linha a linha de um arquivo, dessa vez, sendo possível fazer a leitura de mais de um arquivo simultaneamente sem que haja perda de informação.

Ex.: Veja o exemplo anterior, contudo dessa vez com o novo file descriptor, ao invés de iniciar na segunda linha, a função irá retornar a primeira linha como esperado.

## Execução

Para utilizar a função `get_next_line`, basta compilar seu programa incluindo os arquivos `get_next_line.c` e `get_next_line_utils.c`

```
	<COMPILADOR> -Wall -Wextra -Werror <FILE> get_next_line.c get_next_line_utils.c -I includes
```
