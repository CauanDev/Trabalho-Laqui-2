#include <stdio.h>  /* printf() */
#include "console_v1.5.4.h" /* evento() */
#include <stdlib.h> 
#include <time.h> 

#include "conio_v3.2.4.h"

#include  "prog_f.h"


/*
Programa: Quadrado Animado
Descrição: 
    O projeto se trata de um quadrado de asteristicos que fica ao redor de uma area, o programa permite que seja controlado o tamanho e a cor da area.
    É possível também controlar a velocidade e a direção que o quadrado de asteristicos irá se locomover, caso o usuario não interfira na direção, o programa
    de forma aleatoria irá escolher uma direção, e quando o quadrado chega no final da area, ele começa a se locomover para o sentido contrário.
    O programa será encerrado quando for pressionado a tecla ESC.

Programador: Kelvin Cauan da Silva Matos
RGM: 47583
Data da ultima modificacão: 01/05/2023
*/
 
/*
COMO COMPILAR E EXECUTAR O CODIGO:
1. iniciar o CMD
2. selecionar no CMD a pasta em que os arquivos estão
3. escrever no CMD:
   "
   gcc prog.c conio_v3.2.4.c console_v1.5.4.c  prog_f.c -o prog.exe -Wall -Werror -Wextra -pedantic -lgdi32 -lwinmm
    "
4. depois de compilado irá ser gerado um arquivo executável "prog.exe", para executar basta escrever no CMD o nome do executavel:
   "prog.exe"
*/
int main(int argc, char *argv[])
{
    /*
    enum{PARA_CIMA, PARA_BAIXO, PARA_ESQUERDA, PARA_DIREITA} direcao;
	char string_direcao[][15] = { "PARA CIMA", "PARA BAIXO", "PARA_ESQUERDA", "PARA DIREITA"};
    */
    

    AMBIENTE *ambiente, auxambiente;

    /*
        Linhas de código para silenciar o warning
    */
    argc = argc;
    argv = argv;

   




    ambiente = &auxambiente;
    ambiente->tela.telaAtual = MaxDimensaoJanela();
    ambiente->tela.telaInicial = tamanhoJanelaConsole();
    ambiente->contador = 0;
    ambiente->areas[0].ponto1.X = 2;
    ambiente->areas[0].ponto1.Y = 2;
    ambiente->areas[0].ponto2.X = ambiente->tela.telaAtual.X/2;
    ambiente->areas[0].ponto2.Y = ambiente->tela.telaAtual.Y/2;

    ambiente->areas[1].ponto1.X = (ambiente->tela.telaAtual.X/2)+1;
    ambiente->areas[1].ponto1.Y = 1;
    ambiente->areas[1].ponto2.X = ambiente->tela.telaAtual.X;
    ambiente->areas[1].ponto2.Y = ambiente->tela.telaAtual.Y/2;
    

    ambiente->areas[0].quadrado.loc.X = ambiente->areas[0].ponto2.X/2;
    ambiente->areas[0].quadrado.loc.Y = ambiente->areas[0].ponto2.Y/2;
    ambiente->areas[1].quadrado.loc.X = ambiente->areas[1].ponto2.X/2+25;
    ambiente->areas[1].quadrado.loc.Y = ambiente->areas[1].ponto2.Y/2;
    ambiente->contador = 1;
    ambiente->principal = 1;

    ambiente->areas[0].quadrado.cor = LIGHTGRAY ;
    ambiente->areas[1].quadrado.cor = LIGHTGRAY ;
    
    ambiente->areas[0].quadrado.velocidade = 100;


    ambiente->areas[0].quadrado.direcao = 4;
    ambiente->areas[1].quadrado.velocidade = 100;


    ambiente->areas[1].quadrado.direcao = 1;


   _setcursortype( _NORMALCURSOR);

    setDimensaoJanela(ambiente->tela.telaAtual.X, ambiente->tela.telaAtual.Y);
    setPosicaoJanela(0,0);
    clrscr();
    ambiente->areas[ambiente->principal].cor = BLUE;

    CriaArea(ambiente);  
   

	
    return 0;
} 