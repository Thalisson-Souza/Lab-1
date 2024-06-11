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
    if(x >= 0 && x < 3 && y >= 0 && y < 3)
        return 1;
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
    tela_retangulo(0, 0, 800, 800, 3, transparente, preto);

    // Desenhar linhas do tabuleiro
    tela_linha(330, 250, 330, 550, 5, azul);
    tela_linha(466, 250, 466, 550, 5, azul);
    tela_linha(250, 340, 550, 340, 5, azul);
    tela_linha(250, 460, 550, 460, 5, azul);

    // Desenhar jogadas no tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (jogodavelha[i][j] == 'X') {
                tela_texto(290 + j * 136, 290 + i * 120, 36, vermelho, "X");
            } else if (jogodavelha[i][j] == 'O') {
                tela_texto(290 + j * 136, 290 + i * 120, 36, verde, "O");
            }
        }
    }
}

void desenha_cursor(int x, int y){
    tela_circulo(x, y, 10, 3, vermelho, rosa);
}

void jogar(){
    int x = 1, y = 1; // Coordenadas iniciais do cursor no tabuleiro
    int pos_x = 380, pos_y = 295; // Coordenadas iniciais do cursor na tela
    int valida, ordem = 1, jogadas = 0, ganhou = 0;
    char *jogadorAtual = jogadorX;
    char move;
    
    do {
        do {
            desenha_jogo();
            desenha_cursor(pos_x, pos_y);
            tela_texto(400, 720, 15, branco, jogadorAtual);
            tela_atualiza();

            move = tela_tecla();
            if (move == 'w' && y > 0) {
                y--;
                pos_y -= 120;
            } else if (move == 's' && y < 2) {
                y++;
                pos_y += 120;
            } else if (move == 'a' && x > 0) {
                x--;
                pos_x -= 136;
            } else if (move == 'd' && x < 2) {
                x++;
                pos_x += 136;
            } else if (move == '\n') {
                valida = lugarEvalido(x, y);
                if (valida == 1) {
                    valida += posicaoValida(x, y);
                }
            } else {
                valida = 0;
            }

        } while (valida != 2);

        jogodavelha[x][y] = (ordem == 1) ? 'X' : 'O';
        jogadas++;
        ordem = 3 - ordem; // Alterna entre 1 e 2
        jogadorAtual = (ordem == 1) ? jogadorX : jogadorO;

        ganhou += ganhouLinhas();
        ganhou += ganhouColunas();
        ganhou += ganhouDiagPrincipal();
        ganhou += ganhouDiagSecundaria();

    } while (ganhou == 0 && jogadas < 9);

    desenha_jogo(); // Desenha o jogo após ter um vencedor ou dar empate
    tela_atualiza();

    if (ganhou != 0) {
        printf("\nParabéns, Jogador %s foi o ganhador da vez.\n", (ordem == 2) ? jogadorX : jogadorO);
    } else {
        printf("\nO jogo empatou, inicie outra rodada!\n\n");
    }
}

void desenha_tela(){
    tela_inicio(800, 800, " "); // Desenha tela inicial

    tela_texto(400, 100, 28, branco, "BEM VINDO AO JOGO DA VELHA");
    tela_texto(400, 580, 19, branco, "aperte ENTER para iniciar");
    tela_texto(400, 640, 15, branco, "aperte Q para sair");

    tela_atualiza();
}

void voltarMmenu(){
    desenha_tela();
}

int main(){
    printf("Jogador X, digite seu nome:\n");
    fgets(jogadorX, 50, stdin);
    jogadorX[strcspn(jogadorX, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Jogador O, digite seu nome:\n");
    fgets(jogadorO, 50, stdin);
    jogadorO[strcspn(jogadorO, "\n")] = '\0'; // Remove o caractere de nova linha

    desenha_tela();

    while (true) {
        char n = tela_tecla();
        if (n == '\n') { // Vai para tela do jogo/inicia o jogo
            inicioMat();
            jogar();
            desenha_tela();
        } else if (n == 'q' || n == 'Q') { // Sai do jogo
            tela_fim();
            break;
        } else if (n == '\033') { // Se apertar ESC volta para a tela inicial do jogo
            voltarMmenu();
        }
    }

    return 0;
}
