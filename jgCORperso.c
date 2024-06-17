#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    tela_retangulo(0,0,800,800, 3, transparente,blue);  //Cor fundo do jogo
    tela_texto_esq(80,28,16,branco,"ESC");  //Desenha ESC no jogo
        
    //Desenhar as colunas do tabuleiro 
    tela_linha(330,230,330,570,5,azul);
    tela_linha(466,230,466,570,5,azul);

    //Desenhar as linhas do tabuleiro
    tela_linha(230,340,570,340,5,azul);
    tela_linha(230,460,570,460,5,azul);

    //Desenha X ou O no tabueiro
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (jogodavelha[i][j] != ' ') {
                int pos_x = 284 + j * 120;
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
    int tamanho = 80;
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

void desenhaContorno_Amarelo(){
    tela_retangulo(10,10,790,790, 3, amarelo,transparente); 
    tela_retangulo(26,24,84,46, 3, amarelo,transparente);
    tela_atualiza();
}

void desenhaContorno_Vermelho(){
    tela_retangulo(10,10,790,790, 3, vermelho,transparente); 
    tela_retangulo(26,24,84,46, 3, vermelho,transparente); // Desenha uma linha envolta da escrita ESC
    tela_atualiza();
}

void desenhoVencedor_X(){
    tela_retangulo(10,10,790,790, 3, amarelo,transparente);
    tela_retangulo(26,24,84,46, 3, amarelo,transparente);
    tela_retangulo(245,745,555,775,3, amarelo, transparente);
    tela_texto(400,760,15,branco,"ENTER para reiniciar");
    tela_atualiza();
}

void desenhoVencedor_O(){
    tela_retangulo(10,10,790,790, 3, vermelho,transparente);
    tela_retangulo(26,24,84,46, 3, vermelho,transparente);
    tela_retangulo(245,745,555,775,3, vermelho, transparente);
    tela_texto(400,760,15,branco,"ENTER para reiniciar");
    tela_atualiza();
}

void desenho_EMPATE(){
        //Faz um contorno de uma escrita na tela, com cores diferentes.
    tela_linha(25.5,24,52,24,3,amarelo); //Cima
    tela_linha(26,46,26,24,3,amarelo); // Esquerda reto
    tela_linha(25.5,46,52,46,3,amarelo);   //Baixo

    tela_linha(56,24,85,24,3,vermelho); //Cima
    tela_linha(84,46,84,24,3,vermelho); // direita reto
    tela_linha(56,46,85,46,3,vermelho);   //Baixo

        //Faz um contorno na tela com cores diferentes.
    tela_linha(10,790,10,10,3,amarelo); // Linha reta esquerda
    tela_linha(398,790,10,790,3,amarelo); // Linha metade baixo
    tela_linha(398,10,10,10,3,amarelo);  // Linha metade cima

    tela_linha(790,10,790,790,3,vermelho); // Linha reta direita
    tela_linha(402,790,790,790,3,vermelho); // Linha metade baixo
    tela_linha(790,10,402,10,3,vermelho); // Linha metade cima
    tela_atualiza();
}
void jogar(){  //Função principal que controla o loop do jogo da velha
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
            if(ordem == 1){ //Desenha uma linha envolta da tela na cor do jogador da vez.
                desenhaContorno_Amarelo();
            }else {
                desenhaContorno_Vermelho();
            }
            //Movimenta as posições pela W A S D.
            move = tela_tecla();   
            if(move == 'W' || move == 'w'){
                if(x > 0) //Não deixa sair do tamanho do tabuleiro.
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
            }else if(move == '\n'){ //Enter para confirmar a jogada, após verifica com as funções se é um lugar valido, se sim executa.
                valida = lugarEvalido(x,y);
            if(valida == 1){
                valida += posicaoValida(x, y);
            }
            }else if(move == '\033'){  //Volta menu inicial durante o jogo.
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
        
        } while(ganhou == 0 && jogadas < 9); // Desenha o jogo quando tem algum vencedor ou termina em empate.
        desenha_jogo();  
        tela_atualiza();
    
        if(ganhou != 0){
            if(ordem - 1 == 1){ //Mensagem informando quem ganhou.
                desenha_jogo();
                tela_texto(400,630,17,amarelo, "Jogador X foi o ganhador da vez!");
                desenhoVencedor_X(); //Função que desenha nas cores quando X ganha.
            }
            else{
                desenha_jogo();
                tela_texto(400,630,17,vermelho, "Jogador O foi o ganhador da vez!"); 
                desenhoVencedor_O(); //Função que desenha nas cores quando O ganha.
            }
        }
        else{   
            desenha_jogo();
            tela_texto(400,720,14,branco,"Deu empate, aperte ENTER e inicie outra rodada!");
            desenho_EMPATE(); //Função que desenha na tela as cores de EMPATE.
        }        
}  

void desenha_tela(){
    tela_retangulo(0,0,800,800, 3, transparente, blue);  //Cor de fundo da tela
    tela_retangulo(10,10,790,790, 3, azul,transparente); //Faz um contorno de linha envolta da tela
    tela_texto(460,130,42,branco, "JOGO DA"); //Textos MENU inicial.
    tela_texto(400,200,85,azul,"VELHA");
    tela_texto(400,580,17,branco, "aperte       para iniciar");  
    tela_texto(340,580,20,azul, " ENTER");
    tela_texto(400,640,15,branco, "aperte   para sair");   
    tela_texto(378,640,20,vermelho, "X");

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
        }else if(n == 'x' || n == 'X'){   //Sai do jogo
            tela_fim();
        }else if(n == '\033'){ //Volta ao menu
            voltarMenu();
        }
    }
    return 0;
}
