

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tecla.h"
#include "telag.h"

char jogodavelha[3][3];
char jogadorX[50], jogadorO[50];


void inicioMat(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            jogodavelha[i][j] = ' ';
        }
    }
}

int valido(char letra){
    if(letra == 'X' || letra == 'O')
        return 1;
    else
        return 0;
}

int lugarEvalido(int x, int y){
    if(x >= 0 && x < 3){
        if(y >= 0 && y < 3)
            return 1;
    }
    return 0;
}

int posicaoValida(int x, int y){
    if(jogodavelha[x][y] != 'X' && jogodavelha[x][y] != 'O')
        return 1;
    return 0;
}

int ganhouLinhas(){
    int igual = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            if(valido(jogodavelha[i][j]) && jogodavelha[i][j] == jogodavelha[i][j+1])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
        return 0;    
}    

int ganhouColunas(){
    int igual = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            if(valido(jogodavelha[j][i]) && jogodavelha[j][i] == jogodavelha[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
        return 0;
}

int ganhouDiagPrincipal(){
    int igual = 1;
    for(int i = 0; i < 2; i++){
        if(valido(jogodavelha[i][i]) && jogodavelha[i][i] == jogodavelha[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int ganhouDiagSecundaria(){
    int igual = 1;
    for(int i = 0; i < 2; i++){
        if(valido(jogodavelha[i][3-i-1]) && jogodavelha[i][3-i-1] == jogodavelha[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

void desenha_jogo(){

    int l = 14;
    int c = 22;
    
    
    printf("┏━━━┳━━━┳━━━┓\n");
    for(int i= 0; i <= 3; i++){
        
        //printf("      %d", i);
        printf("┃");
        for( int j= 0; j < 3; j++){
            if(valido(jogodavelha[i][j])){
                tela_tecla();
                printf("\n %c ┃", jogodavelha[i][j]);
            }else
                printf("   ┃");
        
        }
        printf("\n");

        if(i < 2){
            
            printf("┣━━━╋━━━╋━━━┫\n");
            l += 2;
        }
    }
    
    printf("┗━━━┻━━━┻━━━┛\n");
}

void jogar(){
    int x, y, valida, ordem = 1, jogadas = 0, ganhou = 0;
    int pontosX = 0, pontosO = 0;
    char * jogadorAtual = jogadorX;
    

    bool fim = false;
    int lin_jogador = 1;
    int col_jogador = 5;

    do{
        do{
            desenha_jogo();
            printf("Jogador %s onde você deseja jogar?\n ", jogadorAtual); 
            //scanf("%d%d", &x, &y);

            tecla_ini();
            

            while(!fim){   // NAO FUNCIONA!!
                char move = tecla_le_char();
                if(move == 's') lin_jogador++;
                if(move == 'w') lin_jogador--;
                if(move == 'a') lin_jogador--;
                if(move == 'd') lin_jogador++;
                if(move == '\n') fim = true;
            }




            valida = lugarEvalido(x, y);
            if(valida == 1)
                valida += posicaoValida(x, y);
        }while(valida != 2);
        if(ordem == 1){
            jogodavelha[x][y] = 'X';
        }else 
            jogodavelha[x][y] = 'O';
        jogadas++;
        ordem++;

        if(jogadas % 2 == 0) //alternar jogadores
            jogadorAtual = jogadorX;
        else
            jogadorAtual = jogadorO; //*/

       
            if(ordem == 3)
                ordem = 1;
            ganhou += ganhouLinhas(); 
            ganhou += ganhouColunas(); 
            ganhou += ganhouDiagPrincipal(); 
            ganhou += ganhouDiagSecundaria();
        
        }while(ganhou == 0 && jogadas < 9);
        desenha_jogo();  // desenha o jogo após ter um vencedor  

        if(ganhou != 0){
            if(ordem - 1 == 1){
                printf("\n    Parabens, Jogador %s foi o ganhador da vez.\n", jogadorX);
                
                printf(" jogador vencedor está com %d pontos! \n", pontosX);               
            }
            else{
                printf("\n Parabens, Jogador %s foi o ganhador da vez.\n", jogadorO);
            }
        }
        else {
            printf("\nO jogo empatou, inicie outra rodada!\n\n");
        }

        tecla_fim();  
}  
  



int main(){

    int op;

    //tela_ini();
    //desenha_tela();
    //tela_mostra_cursor(false);
    //tela_atualiza();   
    
    
     tela_inicio(1000, 1000, "Jogo");

    // desenha um retangulo
// x1, y1 são as coordenadas do canto superior esquerdo, 
// x2, y2 as do inferior direito
// l é a largura da linha, corl a cor da linha e corint é a cor
// do interior do retangulo

    tela_retangulo(200,150,750,800, 3, branco, transparente);

// desenha uma linha reta
// x1, y1 e x2, y2 são as coordenadas das pontas, l a largura e corl a cor

    tela_linha(370,150,370,800, 3, branco);

    tela_linha(580,150,580,800, 3, branco);

    tela_linha(580,150,580,800, 3, branco);

    tela_linha(580,150,580,800, 3, branco);
    

    tela_atualiza();

    



    
    printf("Jogador X, digite seu nome:\n "); 
    fgets(jogadorX, 50, stdin);

    
    printf("Jogador Y, digite seu nome:\n "); 
    fgets(jogadorO, 50, stdin);
     
    do{
    inicioMat();
    jogar();
    printf("\n Deseja jogar outra vez?\n1 - Sim\n2 - Nao\n");
    scanf("%d", &op);
    
    }while(op == 1);

    
    return 0;


    tela_fim();


}
