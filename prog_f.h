#include "console_v1.5.4.h"
#include "conio_v3.2.4.h"
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    COORD loc;
    COLORREF cor;
    int direcao;
    int velocidade;
}QUADRADO;


typedef struct
{

    COLORREF cor;
    /*O PONTO 1 IRÁ ARMAZENAR O VALOR DO LADO DIREITO*/
    COORD ponto1; 
    /*O PONTO 2 IRÁ ARMAZENAR O VALOR DO LADO ESQUERDO*/
    COORD ponto2;
    /*ESSA VARIÁVEL IRÁ ARMAZENAR AS INFORMAÇÕES DO QUADRADO DE ASTERISTICO*/
    QUADRADO quadrado;
 


}AREA;

typedef struct
{
    COORD telaAtual;
    COORD telaInicial;
}TELAS;
typedef struct
{
    TELAS tela;
    AREA areas[9];
    int contador;
    int principal;
    int tempo;
}AMBIENTE;



void SwitchTeclas(TECLADO teclado, AMBIENTE *ambiente);
void CriaArea(AMBIENTE *ambiente);
void ImprimeQuadrado(AREA area,int apagar);
void ComandaDirecoes(AMBIENTE *ambiente);
void SwitchDirecoes(int contador, AMBIENTE *ambiente);
void VerificaParede(int contador, AMBIENTE *ambiente);
void ImprimeInfo(AMBIENTE *ambiente,int contador);
int SortearCor();
int TestarArea(AMBIENTE *ambiente);