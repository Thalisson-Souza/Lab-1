#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
    tela_retangulo(0,0,800,800, 3, transparente,blue); 
    tela_retangulo(10,10,790,790, 3, amarelo,transparente);
    tela_texto_esq(80,20,16,branco,"ESC");  //ESC NO JOGO
        
    //Desenhar as colunas do tabuleiro 
    tela_linha(330,250,330,550,5,azul);
    tela_linha(466,250,466,550,5,azul);

    //Desenhar as linhas do tabuleiro
    tela_linha(250,340,550,340,5,azul);
    tela_linha(250,460,550,460,5,azul);
   
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (jogodavelha[i][j] != ' ') {
                int pos_x = 280 + j * 120;
                int pos_y = 285 + i * 120;
                if (jogodavelha[i][j] == 'X') {
                    tela_texto(pos_x, pos_y, 65, amarelo, "X");
                } else {
                    tela_texto(pos_x, pos_y, 65, vermelho, "O");
                }
            }
        }
    }
}
void desenha_cursor(int x, int y){  
    int tamanho = 65;
    tela_linha(x - tamanho / 2, y - tamanho / 2, x + tamanho / 2, y - tamanho / 2, 2, branco); // Cima
    tela_linha(x + tamanho / 2, y - tamanho / 2, x + tamanho / 2, y + tamanho / 2, 2, branco); // Direita
    tela_linha(x + tamanho / 2, y + tamanho / 2, x - tamanho / 2, y + tamanho / 2, 2, branco); // Fundo
    tela_linha(x - tamanho / 2, y + tamanho / 2, x - tamanho / 2, y - tamanho / 2, 2, branco); // Esquerda
}

void voltarMenu(){
    void desenha_tela();
        desenha_tela();
        return;
}

void jogar(){
    int x = 1, y = 1, valida, ordem = 1, jogadas = 0, ganhou = 0;

    int pos_x[3] = {280, 400, 520}; // Coordenadas X das casas do tabuleiro
    int pos_y[3] = {285, 400, 515}; // Coordenadas Y das casas do tabuleiro
    char move;
    char *alteraJogador;
    char cor_Jogador;

    do{ 
        do{
            desenha_jogo();
            desenha_cursor(pos_x[y], pos_y[x]);
            if (ordem == 1) {
            alteraJogador = "Jogador X, sua vez!";
            cor_Jogador = amarelo;
            } else {
            alteraJogador = "Jogador O, sua vez!";
            cor_Jogador = vermelho;
            }
            tela_texto(400,720,22,cor_Jogador, alteraJogador);   //Altera cor da letra conforme o jogador da vez.
            if(ordem == 1){
            tela_retangulo(10,10,790,790, 3, amarelo,transparente);
            tela_atualiza();
            }else {
              tela_retangulo(10,10,790,790, 3, vermelho,transparente);
                tela_atualiza();  
            }
            move = tela_tecla();
            if(move == 'W' || move == 'w'){
                if(x > 0) //Não deixa sair do tamanho do tabuleiro
                x--;
            }else if(move == 'S' || move == 's'){
                if(x < 2)
                x++;
            }else if(move == 'A' || move == 'a'){
                if(y > 0)
                y--;        
            }else if(move == 'D' || move == 'd'){
                if(y < 2)
                y++;
            }else if(move == '\n'){  //TROCAR  reverrr
                valida = lugarEvalido(x,y);
            if(valida == 1){
                valida += posicaoValida(x, y);
            }
            }else if(move == '\033'){    //Volta menu inicial durante o jogo
                voltarMenu();
                return;
            }else {
                valida = 0;
            }

        }while(valida != 2);
        if(ordem == 1){  //Quem joga primeiro
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
        
        } while(ganhou == 0 && jogadas < 9);
        desenha_jogo();  // DESENHA O JOGO APOS TER UM VENCEDOR OU DER EMPATE.  
        tela_atualiza();
        if(ganhou != 0){
            if(ordem - 1 == 1){
                desenha_jogo();
                tela_texto(400,720,17,amarelo, "Parabens, Jogador X foi o ganhador da vez!");
                tela_retangulo(10,10,790,790, 3, amarelo,transparente);  
                tela_atualiza();
            }
            else{
                desenha_jogo();
                tela_texto(400,720,15,vermelho, "Parabens, Jogador O foi o ganhador da vez!"); //ARRUMAR
                tela_retangulo(10,10,790,790, 3, vermelho,transparente);
                tela_atualiza();
            }
        }
        else {    // colocar para piscar a barra envolta...
            desenha_jogo();
            tela_texto(400,720,14,branco,"Deu empate, aperte ENTER e inicie outra rodada!");
            tela_retangulo(10,10,790,790, 3, vermelho,transparente);
            tela_atualiza();
        }        
}  

  
void desenha_tela(){
    
    //tela_inicio(800, 800, " "); // DESENHA TELA INICIAL

    tela_retangulo(0,0,800,800, 3, transparente, blue);    // FUNCIONA, USEI PRA MUDAR FUNDO DO JOGO PRA AZUL
    tela_retangulo(10,10,790,790, 3, royal,transparente);


    tela_texto(400,100,28,branco, "BEM VINDO AO JOGO DA VELHA");

    tela_texto(400,580,17,branco, "aperte       para iniciar");  // TEXTO INICIAL E CORES
    tela_texto(340,580,20,verde, " ENTER");

    tela_texto(400,640,15,branco, "aperte   para sair");   // TEXTO INICIAL E CORES
    tela_texto(378,640,20,vermelho, "Q");

    tela_atualiza();

}

int main(){
    tela_inicio(800, 800, " ");  //Cria a tela
    desenha_tela(); //Desenha o Menu

    while (true) {
    char n = tela_tecla();
        if (n == '\n'){  //Inicia o Jogo
        inicioMat();
        jogar();
        }else if(n == 'q' || n == 'Q'){   //Sai do jogo
        tela_fim();
        }
    }
    printf("Jogador X, digite seu nome:\n ");   // TIRAR
    fgets(jogadorX, 50, stdin);

    printf("Jogador Y, digite seu nome:\n "); //TIRAR
    fgets(jogadorO, 50, stdin);
     
/*   do{
    inicioMat();
    jogar();
    tela_texto(400,720,15,branco,"aperte ENTER para iniciar outra rodada ou X para sair"); // REFAZER
    tela_atualiza();
    scanf("%d", &op);
    
    }while(op == 1);
    */
    return 0;
}
