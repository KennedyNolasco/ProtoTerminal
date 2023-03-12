#include <stdio.h>

#include <unistd.h>

#include <dirent.h>

#include <string.h>

#include <sys/wait.h>

#include <ctype.h>

#include <stdlib.h>

#include <stdbool.h>

#include <fcntl.h>
// AUTORES: GABRIEL STONE, KENNEDY NOLASCO, ROBERT GARCIA
// PS: O pipe  funciona quando o segundo programa nao tem ./ EX: ./a | b funciona, a | b funciona, ./a | ./b nao funciona, a | ./b nao funciona 
void escreve_saida(char
  var [256]) {
  char var_buffer[256];
  strcpy(var_buffer,
    var);
  int i = 0;
  int j = 0;
  while (var_buffer[i] != '>') {
    i++;
  }
  while (j < i) {
    int k = 0;
    while (k < strlen(var_buffer)) {
      var_buffer[k] = var_buffer[k + 1];
      k++;
    }
    var_buffer[k] = '\0';
    j++;
  }

  var_buffer[0] = '.';
  var_buffer[1] = '/';
  char aux[34];
  const char * buffer = var_buffer;
  int g = 0;
  while ( * buffer) {
    if (!isspace( * buffer))
      aux[g++] = * buffer;

    buffer++;
  }

  aux[g] = 0;
  close(STDOUT_FILENO);
  open(aux, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
}

void escreve_entrada(char
  var [256], char aux[34]) {
  int i = 0;
  int j = 0;
  while (var [i] != '<') {
    i++;
  }
  while (j < i) {
    int k = 0;
    while (k < strlen(var)) {
      var [k] =
      var [k + 1];
      k++;
    }
    var [k] = '\0';
    j++;
  }
  var [0] = ' ';
  const char * buffer =
    var;
  int g = 0;
  while ( * buffer) {
    if (!isspace( * buffer))
      aux[g++] = * buffer;

    buffer++;
  }

  aux[g] = 0;

}

void divisao_saida(char * myargs[24], char
  var [256]) {
  int arg_exe = 1;
  int arg_input = 0;
  //strcpy(&aux[0], arg[0]);
  //printf("%d\n", arg_exe);
  if (strlen(var) <= 1) {
    myargs[arg_exe] = NULL;
  }
  while (var [arg_input] != '>') {
    int i = 0;
    while (var [arg_input] != ' ') {
      char aux[30];
      aux[i] =
        var [arg_input];
      //printf("%c", aux[i]);
      if (var [arg_input + 1] == ' ') {
        for (int j = 0; j < strlen(aux); j++) {
          if ( & aux[j] == NULL) {
            aux[j] = ' ';
          }
        }
        myargs[arg_exe] = strdup(aux);
        arg_exe++;

      }
      arg_input++;
      i++;
    }
    if (var [arg_input] == ' ') {
      arg_input++;
      //printf("vezes do myargs: %d", arg_exe);
      //arg_exe++;
    }
  }
  myargs[arg_exe] = NULL;
  printf("%d", arg_exe);
  //printf("%d", arg_input++);

}

void sem_operadores(char * myargs[24], char
  var [256]) {
  int arg_exe = 1;
  int arg_input = 0;
  if (strlen(var) <= 1) {
    myargs[arg_exe] = NULL;
  }
  while (arg_input < strlen(var)) {
    char aux[32];
    sscanf(var, "%s", aux);
    myargs[arg_exe] = strdup(aux);
    arg_exe++;
    //printf("%s\n", aux);

    int j = 0;
    while (j < strlen(aux) + 1) {
      int k = 0;
      while (k < strlen(var)) {
        var [k] =
        var [k + 1];
        k++;

      }
      var [k] = '\0';
      j++;
    }
    arg_input++;
  }
  myargs[arg_exe] = NULL;
  //printf("%d",arg_exe);
  //printf("%d", arg_input++);

}

bool is_saida(char
  var [256]) {
  for (int i = 0; i < strlen(var); i++) {
    if (var [i] == '<') {
      return true; // possui caractere especial ou numero  
    }
  }
  return false;
}

int main() {
  char operacao[256]; //guarda a operacao que vai ser feita, se é cd, ls, pwd ou abrir programa
  char pwd[256]; //nome completo do diretorio atual
  int i = 0;
  printf("%s\n", getcwd(pwd, 256)); //printa onde voce atualmente esta no computador
  printf("-> ");
  scanf("%s", operacao); //leio a operação a ser feita 
  //printf("%s\n",operacao);
  while (strcmp(operacao, "exit") != 0) {
    if (strcmp(operacao, "cd") == 0) {
      //essa parte descreve um pouco do comando de shell cd 
      char caminho[256]; //vetor de char que representa o caminho que o programa vai andar a partir do diretorio atual
      scanf("%s", caminho); //le o caminho que vai entrar
      chdir(caminho); //muda diretorio imediato, exemplo: vai de Disco local C, para Disco local C/games
    } else if (strcmp(operacao, "pwd") == 0) {
      //essa parte descreve o comando pwd do linux shell
      //vetor que representa o caminho total do programa
      printf("home%s\n", getcwd(pwd, 256)); //recebe o caminho total da função getcwd e joga no vetor pwd
    } else if (strcmp(operacao, "ls") == 0) {
      //essa parte descreve um pouco o comando ls
      struct dirent * de; // ponteiro que representa o diretorio atual
      DIR * dr = opendir("./"); //DIR é um tipo de dado presente no dirent.h, opendir abre uma stream de diretorio
      while ((de = readdir(dr)) != NULL) // readdir retorna um ponteiro para a posição atual na stream de diretorio, so vai parar quando esse ponteiro for nulo, ou seja quando nao tiver mais arquivos para printar
        printf("%s\n", de -> d_name); //quando nao for nulo, ele printa o componente d_name que contem o nome do arquivo
      closedir(dr); //fecha a stream
    } else { //se não é nenhuma dessas operações acima, então com certeza o usuario vai abrir um programa, chamando seu nome
      char
      var [256]; //variavel pra guardar os argumentos e modificadores que o programa vai executar
      fgets(var, 256, stdin); //vai ler tudo que vem depois do nome do programa, ex: ./prog1 > prog2, nessa variavel vai estar apenas "> prog2"
      i = 0; //reinicializo o i
      while (var [i + 1] != '\n' &&
        var [i + 1] != '\0') { //começa em i+1 pois na posição 0 sempre será um espaço entao eu pulo logo esse espaço
        i++; //conto quantos caracteres tem em var,   espaço conta como um caractere entao a string "meu nome" teria 8 caracteres
      }
      char nome[256]; // variavel vai guardar o nome final do programa a ser executado, ex: se o usuario digitar "prog1" nessa variavel depois das operações vai ter "./prog1" que é nome certo pra executar no execvp
      for (i = 0; i < 256; i++) {
        nome[i] = '\0'; //eu limpo o vetor nome completamente, para não dar erro quando o usuario for tentar abrir um programa
      }
      if (operacao[0] != '.' && operacao[1] != '/') { //caso o usuario não tenha digitado ./prog1 eu tenho que botar um "./" no começo da variavel nome e depois concateno "./" com o nome do programa na variavel operação
        nome[0] = '.';
        nome[1] = '/';
        strcat(nome, operacao);
      } else {
        strcpy(nome, operacao); //se o usuario digitou "./prog1" entao o nome nao precisa ser modificado e so copio pra variavel nome
      }

      int rc = fork(); //eu dou fork no processo
      if (rc < 0) {
        printf("Erro ao executar fork\n"); //printa apenas se o fork tiver dado erro
      } else if (rc == 0) { //esse bloco descreve o que sera feito no processo filho
        //if(i==0 || (i==1 && strstr(var,"&")!=NULL) ){ //caso seja so um programa ou so um programa com o "&" ele executa esse bloco, é executado caso var seja vazio ou possua 1 caractere e esse caractere é '&'
        //char *myargs[24]; //myargs é o vetor que sera usado no execvp
        //	myargs[0] = strdup(nome); //na primeira posicao desse vetor ficará o nome do programa a ser executado
        //divisao_argumentos(myargs, var);
        //myargs[1] =NULL; //a casa depois de todos os argumentos é sempre nula,caso esse programa tenha argumentos os argumentos ficariam nas posições seguintes do vetor
        //	execvp(myargs[0],myargs); //executo o programa, o nome é o primeiro argumento, e o vetor falado anteriormente é o segundo argumento
        //	printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
        //}
        char * myargs[24];
        if ((strstr(var, ">") != NULL) && !((strstr(var, "<") != NULL) | (strstr(var, "|") != NULL))) {
          escreve_saida(var);
          myargs[0] = strdup(nome);
          divisao_saida(myargs,
            var);
          execvp(myargs[0], myargs);
          printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n");
        }
        if ((strstr(var, "<") != NULL) && !((strstr(var, ">") != NULL) | (strstr(var, "|") != NULL))) {
          int fd2; /* descritor de arquivo associado ao arquivo agenda */
          char arg_arquivo[256];
          char aux2[34];
          close(fd2);
          escreve_entrada(var, aux2);
          if ((fd2 = open(aux2, O_RDONLY, S_IRWXU)) == -1) {
            printf("Erro em abrir o arquivo");
            exit(-1);
          }
          if (read(fd2, & arg_arquivo, 256) == -1) {
            printf("Erro em ler o arquivo");
            exit(-1);
          }
          myargs[0] = strdup(nome);
          sem_operadores(myargs, arg_arquivo);
          execvp(myargs[0], myargs);
          printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n");
        }
        if (((strstr(var, "|") != NULL) && !((strstr(var, ">") != NULL) | (strstr(var, "<") != NULL)))) {
          myargs[0] = strdup(nome); //na primeira posicao desse vetor ficará o nome do programa a ser executado
          if (strstr(var, "|") != NULL) { //verifico se tem pipe
            int fd[2];
            if (pipe(fd) == -1) {
              perror("pipe");
              exit(1);
            }
            if (var [1] == '|') { //verifico se o primeiro programa vai precisar de argumentos, nesse bloco ele nao tem argumentos
	      var[strlen(var)-1]='\0';
              i = 3;
              char prog2[256];
              for (i = 0; i < 256; i++) {
                prog2[i] = '\0';
              }
              prog2[0] = '.';
              prog2[1] = '/';
              char * pth = strtok(var, " ");
              pth = strtok(NULL, " ");
              strcat(prog2, pth);
              if (i < strlen(var) - 1) { //caso o segundo programa tenha argumento
                int rc1 = fork();
                if (rc1 > 0) { //to no primeiro processo e envio tudo que sai dele pro filho
                  myargs[1] = NULL; //nao tem nenhum argumento
                  dup2(fd[1], STDOUT_FILENO); //sobreescrevo  a saida padrao com o pipe
                  close(fd[0]); //fecho a conexao dos pipes de entrada e saida
                  close(fd[1]);
                  execvp(myargs[0], myargs); // o que deveria sair na saida padrao agora ta indo pro pipe ao executar
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);
                }
                if (rc1 == 0) { //se isso for verdade to no filho do filho, o processo 2 que recebera as informações
                  myargs[0] = strdup(prog2); //boto o nome do programa 
                  char * pch; //tokenizo a string 
                  pch = strtok(var, " ");
                  pch = strtok(NULL, " ");
                  pch = strtok(NULL, " ");
                  i = 1; //pego apenas o que vem depois do nome do segundo programa, ou seja os argumentos e boto em myargs
                  while (pch != NULL) {
                    myargs[i] = pch;
                    i++;
                    pch = strtok(NULL, " ");
                  }
                  myargs[i] = NULL;
                  dup2(fd[0], STDIN_FILENO); //sobreescrevo a entrada padrao com o pipe
                  close(fd[0]); //fecho as conexoes
                  close(fd[1]);
                  execvp(myargs[0], myargs); //e executo o programa que recebeu as entradas pelo pipe do programa pai
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);
                }
              } else { //caso o segundo programa nao precise de argumentos
                int rc1 = fork();
                if (rc1 > 0) { //to no primeiro processo e envio tudo que sai dele pro filho
                  myargs[1] = NULL;
                  dup2(fd[1], STDOUT_FILENO);
                  close(fd[0]);
                  close(fd[1]);
                  execvp(myargs[0], myargs);
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);
                }
                if (rc1 == 0) { //se isso for verdade to no filho do filho, o processo 2 que recebera as informações
                  myargs[0] = strdup(prog2);
                  myargs[1] = NULL;
                  dup2(fd[0], STDIN_FILENO);
                  close(fd[0]);
                  close(fd[1]);
                  execvp(myargs[0], myargs);
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);

                }
              }
            } else { //caso o primeiro programa precise de argumentos
	      var[strlen(var)-1]='\0';
              char * pch; //pego os argumentos do primeiro programa e boto em myargs
              pch = strtok(var, " ");
              i = 1;
              while (strcmp(pch, "|") != 0) {
                myargs[i] = pch;
                i++;
                pch = strtok(NULL, " ");
              }
              pch = strtok(NULL, " ");
              myargs[i] = NULL;
              char prog2[256];
              for (i = 0; i < 256; i++) {
                prog2[i] = '\0';
              }
              prog2[0] = '.';
              prog2[1] = '/';
              strcat(prog2, pch); //pego o nome do segundo programa
              if (i < strlen(var) - 1) { //caso o segundo programa tenha argumento
                int rc1 = fork();
                if (rc1 > 0) { //to no primeiro processo e envio tudo que sai dele pro filho
                  dup2(fd[1], STDOUT_FILENO); //sobreescrevo  a saida padrao com o pipe
                  close(fd[0]); //fecho a conexao dos pipes de entrada e saida
                  close(fd[1]);
                  execvp(myargs[0], myargs); // o que deveria sair na saida padrao agora ta indo pro pipe ao executar
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);
                }
                if (rc1 == 0) { //se isso for verdade to no filho do filho, o processo 2 que recebera as informações
                  myargs[0] = strdup(prog2); //boto o nome do programa 
                  pch = strtok(NULL, " ");
                  i = 1; //pego apenas o que vem depois do nome do segundo programa, ou seja os argumentos e boto em myargs
                  while (pch != NULL) {
                    myargs[i] = pch;
                    i++;
                    pch = strtok(NULL, " ");
                  }
                  myargs[i] = NULL;
                  dup2(fd[0], STDIN_FILENO); //sobreescrevo a entrada padrao com o pipe
                  close(fd[0]); //fecho as conexoes
                  close(fd[1]);
                  execvp(myargs[0], myargs); //e executo o programa que recebeu as entradas pelo pipe do programa pai
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);

                }
              } else { //caso o segundo programa nao precise de argumentos
                int rc1 = fork();
                if (rc1 > 0) { //to no primeiro processo e envio tudo que sai dele pro filho
                  dup2(fd[1], STDOUT_FILENO);
                  close(fd[0]);
                  close(fd[1]);
                  execvp(myargs[0], myargs);
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);
                }
                if (rc1 == 0) { //se isso for verdade to no filho do filho, o processo 2 que recebera as informações
                  myargs[0] = strdup(prog2);
                  myargs[1] = NULL;
                  dup2(fd[0], STDIN_FILENO);
                  close(fd[0]);
                  close(fd[1]);
                  execvp(myargs[0], myargs);
                  printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n"); //essa linha so vai ser printada se o execvp nao for executado
                  exit(1);

                }
              }

            }

          }
        } else {
          if ((strstr(var, "|") != NULL) | (strstr(var, ">") != NULL) | (strstr(var, "<") != NULL))
            exit(1);
          myargs[0] = strdup(nome);
          sem_operadores(myargs,
            var);
          execvp(myargs[0], myargs);
          printf("Erro no execvp!, verifique se o nome do programa esta certo ou que o comando existe\n");
        }
        exit(1); //fecha o processo filho que foi mal executado
      } else { //esse bloco descreve o que sera feito no processo pai
        if (strstr(var, "&") == NULL) { //verifico se tem algum "&" em var, que significa que o processo ficara livre enquanto o filho é executado, caso não tenha, a linha seguinte é executada
          wait(NULL); //simplesmente espera o processo filho terminar de executar para resumir atividade
        }

      }
      for (i = 0; i < 256; i++) {
        nome[i] = '\0'; //eu limpo o vetor nome completamente, para não dar erro na proxima vez que o usuario for tentar abrir um programa
      }

    }
    printf("%s\n", getcwd(pwd, 256));
    printf("-> ");
    scanf("%s", operacao);
  }
  return 0;

}