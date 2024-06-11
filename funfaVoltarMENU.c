#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

    tela_retangulo(0,0,800,800, 3, transparente,preto); 

    // x1, y1 e x2, y2 são as coordenadas das pontas, l a largura e corl a cor
    //tela_linha(float x1, float y1, float x2, float y2, float l, int corl)
            //COLUNAS 
    tela_linha(330,250,330,550,5,azul);
    tela_linha(466,250,466,550,5,azul);

            //LINHAS
    tela_linha(250,340,550,340,5,azul);
    tela_linha(250,460,550,460,5,azul);
   
    tela_texto(400,720,15,branco, "aperte ESC para voltar");

    tela_linha(340,350,340,450,1,branco);
    tela_atualiza();

}

void jogar(){
    int x, y, valida, ordem = 1, jogadas = 0, ganhou = 0;
    char * jogadorAtual = jogadorX;
    
    bool fim = false;
    int pos_x = 100;
    int pos_y = 100;
    char move = tela_tecla();
    
    do{
        do{
            desenha_jogo();
            printf("Jogador %s onde você deseja jogar?\n ", jogadorAtual); 
            scanf("%d%d", &x, &y);

               while(!fim)   // NAO FUNCIONA!!
                //char move = tela_tecla();
                if(move == 'w')
                    pos_y -= 10;
                        break;
                if(move == 's')
                    pos_y += 10;
                        break;
                if(move == 'd')
                    pos_x += 10;
                        break;
                if(move == 'a')
                    pos_x -= 10;
                        break;
            
 
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

        if(jogadas % 2 == 0) // ALTERNA ENTRE OS JOGADORES
            jogadorAtual = jogadorX;
        else{
            jogadorAtual = jogadorO; //*/
        }
       
            if(ordem == 3)
                ordem = 1;
            ganhou += ganhouLinhas(); 
            ganhou += ganhouColunas(); 
            ganhou += ganhouDiagPrincipal(); 
            ganhou += ganhouDiagSecundaria();
        
        }while(ganhou == 0 && jogadas < 9);
        desenha_jogo();  // DESENHA O JOGO APOS TER UM VENCEDOR OU DER EMPATE.  

        if(ganhou != 0){
            if(ordem - 1 == 1){
                printf("\n    Parabens, Jogador %s foi o ganhador da vez.\n", jogadorX);
                               
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

  
void desenha_tela(){
    
    tela_inicio(800, 800, " "); // DESENHA TELA INICIAL

    //tela_retangulo(0,0,800,800, 3, transparente, azul);    // FUNCIONA, USEI PRA MUDAR FUNDO DO JOGO PRA AZUL

    tela_texto(400,100,28,branco, "BEM VINDO AO JOGO DA VELHA");

    tela_texto(400,580,19,branco, "aperte ENTER para iniciar");
    
    tela_texto(400,640,15,branco, "aperte Q para sair");

    tela_atualiza();

}

void voltarMmenu(){

    //tela_retangulo(0,0,800,800, 3, transparente, azul);  // FUNCIONA, USEI PRA MUDAR FUNDO DO JOGO PRA AZUL

    tela_texto(400,100,28,branco, "BEM VINDO AO JOGO DA VELHA");

    tela_texto(400,580,19,branco, "aperte ENTER para iniciar");
    
    tela_texto(400,640,15,branco, "aperte Q para sair");

    tela_atualiza();

}

int main(){
    int op;  

    // DESENHA O MENU INICIAL DO JOGO
    desenha_tela();

    while (true) {
    char n = tela_tecla();
        if (n == '\n'){  // VAI PARA TELA DO JG/INICIA O JOGO
        desenha_jogo();
        }else if(n == 'q' || n == 'Q'){   //SAI DO JOGO
        tela_fim();
        }else if(n == '\033'){ // SE APERTAR ESC VOLTA PRA TELA INICIAL DO JOGO...
        voltarMmenu();
        }
    }
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

    tela_atualiza();
    tela_fim();
}
