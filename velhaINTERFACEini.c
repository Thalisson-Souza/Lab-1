
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
    int x, y, valida, ordem = 1, jogadas = 0, ganhou = 0;
    int pontosX = 0, pontosO = 0;
    char * jogadorAtual = jogadorX; //
    
    do{
        do{
            desenha_jogo();
            printf("Jogador %s onde você deseja jogar?\n", jogadorAtual); //ajeitar o alternar d jogadores... esta alternando na primeira vez.
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

        if(ordem == 1){  //alternar jogadores
            jogadorAtual = jogadorX;
        }else if(jogadas % 2 == 1){
            jogadorAtual = jogadorO; //
        }   
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
}   

    
    void desenha_tela(){

    #define LIN_MAX 35
    #define COL_MAX 90

    tela_cor_normal();
    tela_limpa();
    tela_cor_fundo(102,0,0);
        
    tela_cor_normal();
    tela_lincol(1, 10);
    for (int i = 1; i <= COL_MAX; i++) {
        putchar(' ');
    }

    // Desenhar a borda inferior
    tela_lincol(LIN_MAX, 10);
    for (int i = 1; i <= COL_MAX; i++) {
        putchar(' ');
    }

    // Desenhar as bordas laterais
    for (int i = 1; i <= LIN_MAX; i++) {
        tela_lincol(i, 1);
        putchar(' ');
        tela_lincol(i, COL_MAX);
        putchar(' ');
    }  
    tela_cor_normal();

    //desenho do titulo do jogo

    tela_cor_letra(255,255,255);
    
    tela_lincol(6,24);
    printf("   _                         _                   _ _           ");

    tela_lincol(7,24);
    printf("  (_)                       | |                 | | |          ");


    tela_lincol(8,24);
    printf("   _  ___   __ _  ___     __| | __ _  __   _____| | |__   __ _ ");

    tela_lincol(9,24);
    printf("  | |/ _ \\ / _` |/ _ \\   / _` |/ _` | \\ \\ / / _ \\ | '_ \\ / _` |");

    tela_lincol(9,24);
    printf("  | | (_) | (_| | (_) | | (_| | (_| |  \\ V /  __/ | | | | (_| |");

    tela_lincol(10,24);
    printf("  | |\\___/ \\__, |\\___/   \\__,_|\\__,_|   \\_/ \\___|_|_| |_|\\__,_|");

    tela_lincol(11,24);
    printf(" _/ |       __/ |                                              ");

    tela_lincol(12,24);
    printf("|__/       |___/                                               ");






    //desenho das instruções
    tela_lincol(20,40);
    printf("Pressione ENTER para iniciar o jogo");

    //desenhar opcao p sair
    tela_lincol(22,46);
    printf("Pressione Q para sair");

}
      // SEM OS DESENHOS INICIAIS


int main(){

    int op;
    
    tela_ini();
    desenha_tela();
    tela_mostra_cursor(false);
    tela_atualiza();   

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

    desenha_tela();
    tela_atualiza();


    tela_fim(); 
}