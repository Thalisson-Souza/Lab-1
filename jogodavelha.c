#include <stdio.h>
#include "telag.h"
#include <stdbool.h>
#include <stdlib.h>

int pos_x[3] = {280, 400, 520}; // Coordenadas X das casas do tabuleiro
int pos_y[3] = {285, 400, 515}; // Coordenadas Y das casas do tabuleiro

// Definição da struct para armazenar o estado do jogo.
typedef struct {
    char jogodavelha[3][3];
    int ordem;  // 1 para X, 2 para O
    int jogadas;
    bool ganhou;
    bool terminou;
    int x;  // Posição atual do cursor X
    int y;  // Posição atual do cursor Y
} jogo_t;

void inicioMat(jogo_t *jogo){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            jogo->jogodavelha[i][j] = ' ';
        }
    }
    jogo->ordem = 1;  // Jogador X começa
    jogo->jogadas = 0;
    jogo->ganhou = false;
    jogo->terminou = false;
    jogo->x = 1;
    jogo->y = 1;
}

int valido(char letra){
    return (letra == 'X' || letra == 'O');
}
int lugarEvalido(int x, int y){
    return (x >= 0 && x < 3 && y >= 0 && y < 3);
}
int posicaoValida(jogo_t *jogo, int x, int y){
    return (jogo->jogodavelha[x][y] != 'X' && jogo->jogodavelha[x][y] != 'O');
}

bool ganhouLinhasOuColunas(jogo_t *jogo) {
    for (int i = 0; i < 3; i++) {
        // Verifica se todas as células em uma linha são iguais e válidas
        if (valido(jogo->jogodavelha[i][0]) && jogo->jogodavelha[i][0] == jogo->jogodavelha[i][1] && jogo->jogodavelha[i][1] == jogo->jogodavelha[i][2]) {
            return true;
        }
        // Verifica se todas as células em uma coluna são iguais e válidas
        if (valido(jogo->jogodavelha[0][i]) && jogo->jogodavelha[0][i] == jogo->jogodavelha[1][i] && jogo->jogodavelha[1][i] == jogo->jogodavelha[2][i]) {
            return true;
        }
    }
    return false;
}

bool ganhouDiagonais(jogo_t *jogo) {
    // Verifica a diagonal principal
    if (valido(jogo->jogodavelha[0][0]) && jogo->jogodavelha[0][0] == jogo->jogodavelha[1][1] && jogo->jogodavelha[1][1] == jogo->jogodavelha[2][2]) {
        return true; // Diagonal principal ganhou
    }
    // Verifica a diagonal secundária
    if (valido(jogo->jogodavelha[0][2]) && jogo->jogodavelha[0][2] == jogo->jogodavelha[1][1] && jogo->jogodavelha[1][1] == jogo->jogodavelha[2][0]) {
        return true; // Diagonal secundária ganhou
    }
    return false; // Nenhuma diagonal ganhou
}

void desenha_X_ou_o_TABULEIRO(jogo_t *jogo){
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (jogo->jogodavelha[i][j] != ' ') {
                int pos_x = 284 + j * 120;
                int pos_y = 285 + i * 120;
                if (jogo->jogodavelha[i][j] == 'X') {
                    tela_texto(pos_x, pos_y, 65, amarelo, "X");
                } else {
                    tela_texto(pos_x, pos_y, 65, vermelho, "O");
                }
            }
        }
    }
}

void desenha_contornoTABULEIRO(){
    //Desenhar as colunas do tabuleiro 
    tela_linha(330,230,330,570,5,azul);
    tela_linha(466,230,466,570,5,azul);

    //Desenhar as linhas do tabuleiro
    tela_linha(230,340,570,340,5,azul);
    tela_linha(230,460,570,460,5,azul);
}

void desenha_jogo(jogo_t *jogo){
    tela_retangulo(0,0,800,800, 3, transparente,blue);  //Cor de fundo do jogo
    tela_texto_esq(80,28,16,branco,"ESC");  //Desenha ESC no jogo
        
    desenha_contornoTABULEIRO();
    desenha_X_ou_o_TABULEIRO(jogo);
}
void desenha_cursor(int x, int y){  
    int tamanho = 40;
    tela_linha(x - tamanho, y - tamanho, x + tamanho, y - tamanho, 2, branco);
    tela_linha(x + tamanho, y - tamanho, x + tamanho, y + tamanho, 2, branco);
    tela_linha(x + tamanho, y + tamanho, x - tamanho, y + tamanho, 2, branco);
    tela_linha(x - tamanho, y + tamanho, x - tamanho, y - tamanho, 2, branco);
}

void desenhaContorno_Amarelo(){ //Desenhos de cores apenas.
    tela_retangulo(10,10,790,790, 3, amarelo,transparente); 
    tela_retangulo(26,24,84,46, 3, amarelo,transparente);
    tela_atualiza();
}
void desenhaContorno_Vermelho(){ //Desenhos de cores apenas.
    tela_retangulo(10,10,790,790, 3, vermelho,transparente); 
    tela_retangulo(26,24,84,46, 3, vermelho,transparente); 
    tela_atualiza();
}
void desenhoVencedor_X(){ //Desenhos de cores apenas.
    tela_retangulo(10,10,790,790, 3, amarelo,transparente);
    tela_retangulo(26,24,84,46, 3, amarelo,transparente);
    tela_retangulo(245,745,555,775,3, amarelo, transparente);
    tela_texto(400,760,15,branco,"ENTER para reiniciar");
    tela_atualiza();
}
void desenhoVencedor_O(){ //Desenhos de cores apenas.
    tela_retangulo(10,10,790,790, 3, vermelho,transparente);
    tela_retangulo(26,24,84,46, 3, vermelho,transparente);
    tela_retangulo(245,745,555,775,3, vermelho, transparente);
    tela_texto(400,760,15,branco,"ENTER para reiniciar");
    tela_atualiza();
}
void desenho_EMPATE(){ //Desenhos de cores apenas.
    //Faz um contorno de uma escrita na tela, com cores diferentes.
    tela_linha(25.5,24,52,24,3,amarelo); 
    tela_linha(26,46,26,24,3,amarelo); 
    tela_linha(25.5,46,52,46,3,amarelo);   

    tela_linha(56,24,85,24,3,vermelho); 
    tela_linha(84,46,84,24,3,vermelho); 
    tela_linha(56,46,85,46,3,vermelho);   

    //Faz um contorno na tela com cores diferentes.
    tela_linha(10,790,10,10,3,amarelo); 
    tela_linha(399.5,790,10,790,3,amarelo); 
    tela_linha(399.5,10,10,10,3,amarelo);  

    tela_linha(790,10,790,790,3,vermelho); 
    tela_linha(399.5,790,790,790,3,vermelho); 
    tela_linha(790,10,399.5,10,3,vermelho); 

    //Faz um contorno na tela com cores diferentes.
    tela_linha(245,745,398,745,3,amarelo);
    tela_linha(402,745,555,745,3,vermelho);
    
    tela_linha(245,775,398,775,3,amarelo);
    tela_linha(402,775,555,775,3,vermelho);
    
    tela_linha(245,776,245,744,3,amarelo);
    tela_linha(555,776,555,744,3,vermelho);
    tela_texto(400,760,15,branco,"ENTER para reiniciar");

    tela_atualiza();
}

void movimentacao(char move, int *x, int *y) {
    if (move == 'W' || move == 'w') {
        if (*x > 0) // Não deixa sair do tamanho do tabuleiro.
            (*x)--;
    } else if (move == 'S' || move == 's') {
        if (*x < 2)
            (*x)++;
    } else if (move == 'A' || move == 'a') {
        if (*y > 0)
            (*y)--;
    } else if (move == 'D' || move == 'd') {
        if (*y < 2)
            (*y)++;
    }
}

void exibe_jogador_atual(jogo_t *jogo) {
    char *alteraJogador;
    char cor_Jogador;

    if (jogo->ordem == 1) {
        alteraJogador = "Jogador X, sua vez!";
        cor_Jogador = amarelo;
    } else {
        alteraJogador = "Jogador O, sua vez!";
        cor_Jogador = vermelho;
    }

    tela_texto(400, 720, 22, cor_Jogador, alteraJogador);
    if (jogo->ordem == 1) {
        desenhaContorno_Amarelo();
    } else {
        desenhaContorno_Vermelho();
    }
}

void desenha_tela();
void atualiza_movimentacao(jogo_t *jogo, char move, int *valida) {
    if (move == '\n') { // Enter para confirmar a jogada
        *valida = lugarEvalido(jogo->x, jogo->y);
        if (*valida == 1) {
            *valida += posicaoValida(jogo, jogo->x, jogo->y);
        }
    } else if (move == '\033') { // Volta ao menu inicial
        desenha_tela();
    } else {
        movimentacao(move, &jogo->x, &jogo->y); // Atualiza a posição do cursor
        *valida = 0;
    }
}

void atualiza_tabuleiro(jogo_t *jogo) {
    if (jogo->jogodavelha[jogo->x][jogo->y] == ' ' && !jogo->terminou){
        if (jogo->ordem == 1) {
            jogo->jogodavelha[jogo->x][jogo->y] = 'X';
        } else {
            jogo->jogodavelha[jogo->x][jogo->y] = 'O';
        }
        jogo->jogadas++;

    // Verifica se alguém ganhou
        if (ganhouLinhasOuColunas(jogo) || ganhouDiagonais(jogo)) {
            jogo->ganhou = true;
            jogo->terminou = true; // Marca o jogo como terminado
        } else if (jogo->jogadas >= 9) {
            jogo->ganhou = false;
            jogo->terminou = true; // Marca o jogo como terminado
        } else {
            jogo->ordem = (jogo->ordem == 1) ? 2 : 1; // Alterna a ordem dos jogadores
        }
    }
}

void desenha_tela(jogo_t *jogo){ 

    while (true) {
        tela_retangulo(0,0,800,800, 3, transparente, blue);  //Cor de fundo da tela
        tela_retangulo(10,10,790,790, 3, azul,transparente); //Faz um contorno com linha envolta da tela
        tela_texto(460,130,42,branco, "JOGO DA"); //Textos do MENU inicial.
        tela_texto(400,200,85,azul,"VELHA");
        tela_texto(400,580,17,branco, "aperte       para iniciar");  
        tela_texto(340,580,20,azul, " ENTER");
        tela_texto(400,640,15,branco, "aperte   para sair");   
        tela_texto(378,640,20,vermelho, "X");
        tela_atualiza();
    
    char tecla = tela_tecla();
        if (tecla == '\n'){  //Inicia o Jogo
            inicioMat(jogo);
            return;
            //jogar(jogo);
        }else if(tecla == 'x' || tecla == 'X'){  //Sai do jogo
            tela_fim();
            exit(0);
        }
    }
}

void tela_finalQUEMGANHOU(jogo_t *jogo) {
    desenha_jogo(jogo);
    if (jogo->ganhou) {
        if (jogo->ordem == 1) { // Jogador X ganhou
            tela_texto(400, 650, 20, amarelo, "Jogador X foi o ganhador da vez!");
            desenhoVencedor_X(); // Função para exibir cores quando X ganha
        } else { // Jogador O ganhou
            tela_texto(400, 650, 20, vermelho, "Jogador O foi o ganhador da vez!");
            desenhoVencedor_O(); // Função para exibir cores quando O ganha
        }
    }else { // Empate
        tela_texto(400, 650, 20, branco, "Empate!");
        desenho_EMPATE(); // Função para exibir cores de empate
    }
    while(true){
        if(tela_tecla() == '\n'){
            jogo->terminou = false;
            inicioMat(jogo);
            return;
        }if(tela_tecla() == '\033'){
            desenha_tela(jogo);
            return;
        }
    }
}

int main(){
    int valida;
    jogo_t jogo;
    tela_inicio(800, 800, "GAME");  //Cria a tela
    desenha_tela(&jogo); //Desenha o Menu

    while(!jogo.terminou){
        while(!jogo.terminou){
            desenha_jogo(&jogo);
            desenha_cursor(pos_x[jogo.y], pos_y[jogo.x]);
            exibe_jogador_atual(&jogo);
            atualiza_movimentacao(&jogo, tela_tecla(), &valida);
            if (valida == 2) {
                atualiza_tabuleiro(&jogo);
            }
        }
        tela_finalQUEMGANHOU(&jogo); // Exibe a tela final com o resultado
    }
    tela_fim();
    return 0;
}