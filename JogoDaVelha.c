#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tela.h"


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

    printf("\t  0   1   2  \n");
    printf("\t┏━━━┳━━━┳━━━┓\n");
    for(int i= 0; i < 3; i++){
        printf("      %d", i);
        printf("\t┃");
        for( int j= 0; j < 3; j++){
            if(valido(jogodavelha[i][j]))
                printf(" %c ┃", jogodavelha[i][j]);
            else
                printf("   ┃");
        
        }
        printf("\n");

        if(i < 2){
            printf("\t┣━━━╋━━━╋━━━┫\n");
        }
    }
    printf("\t┗━━━┻━━━┻━━━┛\n");
}

void jogar(){
    int x, y, valida, ordem = 1, jogadas = 0, ganhou = 0, pontosX = 0 , pontosO = 0;
    
    do{
        do{
            desenha_jogo(); 
            printf("Jogador da vez, onde você deseja jogar?\n"); 
            scanf("%d%d", &x, &y);
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

            if(ordem == 3)
                ordem = 1;
            ganhou += ganhouLinhas(); 
            ganhou += ganhouColunas(); 
            ganhou += ganhouDiagPrincipal(); 
            ganhou += ganhouDiagSecundaria();
        
        }while(ganhou == 0 && jogadas < 9);
        desenha_jogo();
                
        if(ganhou != 0){
            if(ordem - 1 == 1){
                printf("\n    Parabens, Jogador %sfoi o ganhador da vez.\n", jogadorX);
                
                printf(" jogador vencedor está com %d pontos! \n", pontosX);               
            }
            else{
                printf("\n Parabens, Jogador %sfoi o ganhador da vez.\n", jogadorO);
            }
        }
        else {
            printf("\nO jogo empatou, inicie outra rodada!\n\n");
        }
}   

int main(){

    int op;
    
    tela_atualiza();
    tela_cor_normal();
    tela_cor_letra(153,0,0);
    printf("Jogador X, digite seu nome:\n "); tela_cor_normal();
    fgets(jogadorX, 50, stdin);

    tela_cor_letra(0,255,0);
    printf("Jogador Y, digite seu nome:\n "); tela_cor_normal(); 
    fgets(jogadorO, 50, stdin);
    
    
    do{
    inicioMat();
    jogar();
    printf("\n Deseja jogar outra vez?\n1 - Sim\n2 - Nao\n");
    scanf("%d", &op);
    
    }while(op == 1);

    
    return 0;
}

