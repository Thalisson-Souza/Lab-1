<p align="center">
  <img src="https://github.com/user-attachments/assets/b1a43e93-ac86-43b6-898a-a4cb6c4e6ba1" alt="Atual-ezgif com-resize">
</p>

#   Jogo da Velha com Allegro 5

Este projeto é uma implementação simples de um Jogo da Velha utilizando a biblioteca gráfica Allegro 5. O objetivo principal foi desenvolver uma interface gráfica interativa para um jogo clássico, explorando as funcionalidades da Allegro para criar um ambiente amigável e responsivo.

## Funcionalidades

- Interface gráfica com suporte a mouse para interação;
- Verificação automática de vitória ou empate;
- Reinicialização do jogo após o término da partida;
- Layout intuitivo com destaque para o jogador da vez.

## Tecnologias Utilizadas
- Linguagem: C/C++
- Biblioteca gráfica: Allegro 5


## Pré requisitos
- Sistema Operacional:

Linux: qualquer distribuição compatível.

Windows: deve ter o WSL (Windows Subsystem for Linux) instalado. [Guia de instalação do WSL.](https://learn.microsoft.com/pt-br/windows/wsl/install)

- Biblioteca Allegro 5:

A versão 5.2.9.1 ou superior é necessária para rodar este projeto.
Certifique-se de que essa versão está instalada, seguindo as instruções descritas na seção de [Instalação Allegro 5.](https://github.com/Thalisson-Souza/Jogo-da-Velha-com-Allegro-5/blob/main/Instala%C3%A7%C3%A3o-Allegro5.md)


## Como Executar
1 - Clone o repositório:
```bash
git clone https://github.com/Thalisson-Souza/Jogo-da-Velha-com-Allegro-5
```

2 - Acesse o diretório do projeto:
```bash
cd seu-repositorio
```

3 - Compile o código:
```bash
gcc -Wall -o jogodavelha jogodavelha.c telag.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro
```

4 - Execute o jogo:
```bash
./jogodavelha
```
