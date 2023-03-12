# ProtoTerminal
 Autores: GABRIEL STONE, KENNEDY NOLASCO, ROBERT GARCIA
 Implementação de um terminal simples em C, ele possui alguns comandos básicos de um terminal
# Comandos básicos
- ls – listar os elementos do diretório atual
- cd – Trocar o diretório atual
- pwd – imprimir o caminho completo do diretório atual
# Modificadores 
Além disso, ele também deve roda um programa cujo nome é digitado pelo usuário, e ficar parado até esse programa terminar.
Ele também possui 4 modificadores para execução de processos, que são: ">", "<", "|" e "&"
# Execução
Cenários para a execução de programas:

./prog1 ou prog1 – roda prog1 normalmente

./prog1 arg1 arg2 – roda prog1 com 2 argumentos (arg1 e arg2)

./prog1 & - roda prog1 e deixa o terminal livre para outros comandos.

./prog1 > saída – roda prog1 e joga o output dele para o arquivo saída

./prog1 < entrada – roda prog1 e recebe como input o arquivo entrada

./prog1 | ./prog2 – faz a saída de prog1 ser a entrada de prog2

E misturas entre eles (não possui entre os <> e o pipe)
