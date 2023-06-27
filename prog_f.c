/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> /*NULL,printf()*/
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time() */ 


#include "conio_v3.2.4.h" /* textbackground(),gotoxy(),putchar(),textColor() */ 
#include "console_v1.5.4.h" /* COORD ,getPosicaoJanela(),MaxDimensaoJanela(),getPosicaoJanela(), setPosicaoJanela() 
setDimensaoJanela() ,setTituloConsole() ,setCursorStatus(),Sleep() */ 
#include "prog_f.h"
#define LINHA 20
#define COLUNA 50




void CriaArea(AMBIENTE *ambiente)
{
    int i,j;



    clrscr();

    for(j=0;j<=ambiente->contador;j++)
    {
        if(j == ambiente->principal)
        {
            textbackground(ambiente->areas[j].cor);            
        }
        else
        {
            textbackground(LIGHTGRAY);   
        }
      

        

        for(i=ambiente->areas[j].ponto1.X; i<=ambiente->areas[j].ponto2.X;i++)
        {

            gotoxy(i,ambiente->areas[j].ponto1.Y);
         
            putchar(32);

            gotoxy(i,ambiente->areas[j].ponto2.Y);
         
            putchar(32);
            
        }

        for(i = ambiente->areas[j].ponto1.Y;i<=ambiente->areas[j].ponto2.Y;i++)
        {
            gotoxy(ambiente->areas[j].ponto1.X,i);
            putchar(32);

            gotoxy(ambiente->areas[j].ponto2.X,i);
            putchar(32);        
        }
        
    }
   textbackground(0);

   ComandaDirecoes(ambiente);
}



void ImprimeQuadrado(AREA area,int apagar)
{
    

    
    if(apagar)
    {
		textcolor(BLACK);
        gotoxy(area.quadrado.loc.X,area.quadrado.loc.Y-1);
        printf("***");
        gotoxy(area.quadrado.loc.X,area.quadrado.loc.Y);
        printf("***");
        gotoxy(area.quadrado.loc.X,area.quadrado.loc.Y+1);
        printf("***");
    }
    else
    {
        textcolor(area.quadrado.cor);
        gotoxy(area.quadrado.loc.X,area.quadrado.loc.Y-1);
        printf("***");
        gotoxy(area.quadrado.loc.X,area.quadrado.loc.Y);
        printf("***");
        gotoxy(area.quadrado.loc.X,area.quadrado.loc.Y+1);
        printf("***");
    }

    

}


void ComandaDirecoes(AMBIENTE *ambiente)
{
    EVENTO evento;
    int i,j,posMouseX,posMouseY;

    do
    {
        if (i == 1000) 
        {
            ambiente->tempo = 0;
        } 
        else 
        {
            ambiente->tempo++;
        }
        timeBeginPeriod(1);
        for(i=0;i<=ambiente->contador;i++)
        {
        
            
            if(hit(ALL))
            {
                evento = Evento();
            if(evento.tipo_evento & KEY_EVENT)
            {       
                if(evento.teclado.status_tecla == LIBERADA)
                {   
                    if(evento.teclado.status_teclas_controle & LEFT_ALT_PRESSED || evento.teclado.status_teclas_controle & RIGHT_ALT_PRESSED)
                    {

                        
                        if(ambiente->principal == ambiente->contador)
                        {   
                            
                            ambiente->principal--;
                            
                        }
                        else
                        {
                            
                            ambiente->principal++; 
                            
                        }
                        ambiente->areas[ambiente->principal].cor = BLUE;
                        CriaArea(ambiente);
                    }
                    else
                    {
                        if(evento.teclado.status_teclas_controle & LEFT_CTRL_PRESSED || evento.teclado.status_teclas_controle & RIGHT_CTRL_PRESSED)
                        {
                            getchar();
                        }
                        else
                        {
                            SwitchTeclas(evento.teclado,ambiente);
                        }    
                    }
                       

            
            }

            }
            else
            {
                if(evento.tipo_evento & MOUSE_EVENT)
                {
                    if(evento.mouse.botao_clicou & BOTAO_ESQUERDO_PRESSIONADO)
                    {
                        
                        posMouseX =  evento.mouse.posicao.X;
                        posMouseY =  evento.mouse.posicao.Y;

                        for(j=0;j<=ambiente->contador;j++)
                        {
                            if((posMouseX >= ambiente->areas[j].ponto1.X && posMouseY >=ambiente->areas[j].ponto1.Y) && (posMouseX <= ambiente->areas[j].ponto2.X && posMouseY <= ambiente->areas[j].ponto2.Y))
                            {
                                ambiente->areas[j].cor = BLUE;
                                ambiente->principal = j;                                
                                CriaArea(ambiente);
                            }
                        }
                    }
                }
            }
            }
            
             

            if(ambiente->tempo%ambiente->areas[i].quadrado.velocidade ==0)
            {
              SwitchDirecoes(i,ambiente);  
            }
            ambiente->tempo++;
            


                


 
        }
        timeEndPeriod(1);   
    }while(1);


    
}

void SwitchDirecoes(int contador, AMBIENTE *ambiente)
{

    switch(ambiente->areas[contador].quadrado.direcao)
    {
       
        /* Para baixo */
        case 1:
            ImprimeQuadrado(ambiente->areas[contador],1);
            ambiente->areas[contador].quadrado.loc.Y--;      
        break;

        /* Para cima */
        case 2:
            ImprimeQuadrado(ambiente->areas[contador],1); 
            ambiente->areas[contador].quadrado.loc.Y++;         
        break;

        /* Para direita */
        case 3:
            ImprimeQuadrado(ambiente->areas[contador],1);
            ambiente->areas[contador].quadrado.loc.X++;
        break;

        /* Para esquerda */
        case 4:
            ImprimeQuadrado(ambiente->areas[contador],1);
            ambiente->areas[contador].quadrado.loc.X--;
        break;        
    }
    VerificaParede(contador,ambiente);      
    ImprimeQuadrado(ambiente->areas[contador],0);      
    ImprimeInfo(ambiente,contador);
    
    


    
    
}


void VerificaParede(int contador, AMBIENTE *ambiente)
{
    /* VERIFICA SE O LADO DE BAIXO FOI ENCOSTADO */
    if(ambiente->areas[contador].quadrado.loc.Y == ambiente->areas[contador].ponto2.Y-2)
    {        
       ambiente->areas[contador].quadrado.direcao = 1; 
    }
    /* VERIFICA SE O LADO DE CIMA FOI ENCOSTADO */
    if(ambiente->areas[contador].quadrado.loc.Y == ambiente->areas[contador].ponto1.Y+2)
    {
       ambiente->areas[contador].quadrado.direcao = 2; 
    }
    /* VERIFICA SE O LADO ESQUERDO FOI ENCOSTADO */
    if(ambiente->areas[contador].quadrado.loc.X == ambiente->areas[contador].ponto1.X+1)
    {
        ambiente->areas[contador].quadrado.direcao = 3; 
    }
    /* VERIFICA SE O LADO DIREITO FOI ENCOSTADO */
    if(ambiente->areas[contador].quadrado.loc.X == ambiente->areas[contador].ponto2.X-3)
    {
       ambiente->areas[contador].quadrado.direcao = 4; 
    }

}


void SwitchTeclas(TECLADO teclado, AMBIENTE *ambiente)
{
    
    DWORD tecla;
    
    tecla = teclado.codigo_tecla;
    
    switch (tecla)
    {       
        /*
        Mudará a direção do quadrado para baixo.
        */
        case SETA_PARA_BAIXO:
            ambiente->areas[ambiente->principal].quadrado.direcao =  2;
        break;
        /*
        Mudará a direção do quadrado para cima.
        */        
        case SETA_PARA_CIMA:
            ambiente->areas[ambiente->principal].quadrado.direcao = 1;
        break;
        /*
        Mudará a direção do quadrado para direita.
        */
        case SETA_PARA_DIREITA:
            ambiente->areas[ambiente->principal].quadrado.direcao = 3;
        break;
        /*
        Mudará a direção do quadrado para esquerda.
        */
        case SETA_PARA_ESQUERDA: 
            ambiente->areas[ambiente->principal].quadrado.direcao = 4;
        break; 

        case ESC:
            exit(0);
            textbackground(BLACK);
            textcolor(WHITE);
        break;

        case ESPACO:
            ambiente->areas[ambiente->principal].quadrado.cor = SortearCor();
        break;

        case TAB:
            ambiente->areas[ambiente->principal].cor = SortearCor();
            CriaArea(ambiente);                      
        break;
        /*  Diminui a velocidade */
        case F1:    
            if(ambiente->areas[ambiente->principal].quadrado.velocidade > 1)
            {
                ambiente->areas[ambiente->principal].quadrado.velocidade--;                  
            }          
            
        break;
        /*  Aumenta a velocidade */
        case F2:
            if(ambiente->areas[ambiente->principal].quadrado.velocidade < 1000)
            {
                ambiente->areas[ambiente->principal].quadrado.velocidade+=100;  
            }
        break;
        /*
        Aumentar Quadrado para a esquerda.
        */
        case F3:
            ambiente->areas[ambiente->principal].ponto1.X--;
            if(TestarArea(ambiente))
            {
                CriaArea(ambiente);
            }
            else
            {
            ambiente->areas[ambiente->principal].ponto1.X++;                
            }

          
        break;
        /*
        Diminuir Quadrado para a esquerda.
        */
        case F4:
            if(TestarArea(ambiente))
            {
                if(ambiente->areas[ambiente->principal].quadrado.loc.X == ambiente->areas[ambiente->principal].ponto1.X)
                {
                    ambiente->areas[ambiente->principal].quadrado.loc.X--;
                }
                ambiente->areas[ambiente->principal].ponto1.X++;
                CriaArea(ambiente);                   
            }

        break;
        /*
        Aumentar Quadrado para a direita.
        */
        case F5:
            ambiente->areas[ambiente->principal].ponto2.X++;
            if(TestarArea(ambiente))
            {
                CriaArea(ambiente);
            }
            else
            {
                ambiente->areas[ambiente->principal].ponto2.X--;                
            }
 
        break;
        /*
        Diminuir Quadrado para a direita
        */
        case F6:
            if(TestarArea(ambiente))
            {
                if(ambiente->areas[ambiente->principal].quadrado.loc.X == ambiente->areas[ambiente->principal].ponto1.X)
                {
                    ambiente->areas[ambiente->principal].quadrado.loc.X++;
                }
                ambiente->areas[ambiente->principal].ponto2.X--;
                CriaArea(ambiente);                   
            }
        break;
        /* 
        Aumenta Quadrado para cima
        */
        case F7:
            ambiente->areas[ambiente->principal].ponto1.Y--;
            if(TestarArea(ambiente))
            {
                CriaArea(ambiente);                   
            }   
            else
            {
                ambiente->areas[ambiente->principal].ponto1.Y++;
            } 
  
    
        break;
        /* 
        Diminuir Quadrado para cima
        */
        case F8:

            if(TestarArea(ambiente))
            {
                if(ambiente->areas[ambiente->principal].quadrado.loc.Y == ambiente->areas[ambiente->principal].ponto1.Y)
                {
                    ambiente->areas[ambiente->principal].quadrado.loc.Y++;
                }
                ambiente->areas[ambiente->principal].ponto1.Y++;
                CriaArea(ambiente);                   
            }
  
        break;
        /* AUMENTA O QUADRADO PARA BAIXO*/
        case F9:
            ambiente->areas[ambiente->principal].ponto2.Y++;
            if(TestarArea(ambiente))
            {
                CriaArea(ambiente);                   
            }      
            else
            {
                ambiente->areas[ambiente->principal].ponto2.Y--;
            }     


        break;
        /* 
        Diminuir Quadrado para baixo
        */
        case F10:

            if(TestarArea(ambiente))
            {
                if(ambiente->areas[ambiente->principal].quadrado.loc.Y == ambiente->areas[ambiente->principal].ponto1.Y)
                {
                    ambiente->areas[ambiente->principal].quadrado.loc.Y--;
                }
                ambiente->areas[ambiente->principal].ponto2.Y--;
                CriaArea(ambiente);                   
            }
        break;


    }
    
    
            

    ComandaDirecoes(ambiente);
      


}

void ImprimeInfo(AMBIENTE *ambiente,int contador)
{    
    textcolor(WHITE);
    textbackground(ambiente->areas[contador].cor);
    gotoxy(ambiente->areas[contador].ponto1.X + ambiente->areas[contador].ponto1.Y, ambiente->areas[contador].ponto2.Y);
    printf("Velocidade: %d",ambiente->areas[contador].quadrado.velocidade);
    textbackground(BLACK);

}

int SortearCor()
{
    int cor;

    do
    {
        cor = rand() % 14;
        cor++;
    }while(cor==BLACK);

    return cor;
}



int TestarArea(AMBIENTE *ambiente)
{
    
    int aprovado, i, j, k;
    aprovado = 1;

 if((ambiente->areas[ambiente->principal].ponto2.X - ambiente->areas[ambiente->principal].ponto1.X) <=5 || (ambiente->areas[ambiente->principal].ponto2.Y - ambiente->areas[ambiente->principal].ponto1.Y) <=5)
    {
        printf("não passou! ");
        getchar();
	    return 0;
    }
    if (ambiente->areas[ambiente->principal].ponto2.X > ambiente->tela.telaAtual.X || ambiente->areas[ambiente->principal].ponto2.Y > ambiente->tela.telaAtual.Y)
    {
        printf("não passou!1 ");
        getchar();
        aprovado = 0;
    }

    if (ambiente->areas[ambiente->principal].ponto1.X > ambiente->tela.telaAtual.X || ambiente->areas[ambiente->principal].ponto1.Y > ambiente->tela.telaAtual.Y)
    {
        printf("não passou! 2");
        getchar();
        aprovado = 0;
    }


    for (i = 0; i <= ambiente->contador; i++)
    {

        if (i != ambiente->principal)
        {   

            j = 0;
            while (j <= ambiente->areas[ambiente->principal].ponto2.X - ambiente->areas[ambiente->principal].ponto1.X)
            {
                k = 0;

                while (k <= ambiente->areas[ambiente->principal].ponto2.Y - ambiente->areas[ambiente->principal].ponto1.Y)
                {

                        /* VERIFICA F5 E O F9*/
                       
                    if (ambiente->areas[ambiente->principal].ponto2.X + k  >= ambiente->areas[i].ponto1.X
                    && ambiente->areas[ambiente->principal].ponto2.Y + j >= ambiente->areas[i].ponto1.Y)
                    {
                        /* VERIFICA O F3 E O F7 FUNCIONANDO */
                        if (ambiente->areas[ambiente->principal].ponto1.X + k <= ambiente->areas[i].ponto2.X 
                        && ambiente->areas[ambiente->principal].ponto1.Y + j <= ambiente->areas[i].ponto2.Y)
                        {
                            aprovado = 0;
                        }


                    }

                    k++;
                }
                j++;
            }
        }
    }

    
    return aprovado;

}