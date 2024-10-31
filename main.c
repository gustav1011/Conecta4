#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

////usar uma var global do tipo array bidimensional para referenciar as coordenadas do array que ja estão locadas
// LEEGNDA: (0 = posição livre, 1 = peça vermelha, 2 = peça amarela).
//int legendaDisponivel = 0;
//int legendaVermelha = 1;
//int legendaAmae = 2;
int tabuleiroAux[6][7] = {0}; // Tabuleiro auxiliar para registrar posições ocupadas
int seleciona_ficha = 0; // Inicialmente, nenhuma ficha está selecionada
int posicaoX;
int posicaoY = 50; // Posição inicial da peça, da onde a peça vai cair do eixo Y


void escolhaColuna(int coluna) {// escolha da coluna da onde vai cair a peça
    // Define apenas a posição X com base na coluna selecionada
    switch (coluna) {
        case 0: posicaoX = 275; break;
        case 1: posicaoX = 409; break;
        case 2: posicaoX = 543; break;
        case 3: posicaoX = 677; break;
        case 4: posicaoX = 811; break;
        case 5: posicaoX = 945; break;
        case 6: posicaoX = 1079; break;
        default: printf("Coluna inválida.\n"); break;
    }
}

int getLinhaDisponivel(int coluna) {// verifica apenas no tabu aux
    for (int linha = 5; linha >= 0; linha--) { // Verifica de baixo para cima
        if (tabuleiroAux[linha][coluna] == 0) {
            return linha; // Retorna a linha disponível
        }
    }
    return -1; // Retorna -1 se a coluna estiver cheia
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        "Conect Four",
        100, 100,
        1500, 1024,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* tabuleiro = IMG_LoadTexture(renderer, "jogo_tabuleiro.png");
    SDL_Texture* ficha_vermelha = IMG_LoadTexture(renderer, "ficha_vermelha.png");
    SDL_Texture* ficha_amarela = IMG_LoadTexture(renderer, "ficha_amarela.png");
    SDL_Rect quad1;
    quad1.x = 200;
    quad1.y = 150;
    quad1.w = 1108;
    quad1.h = 887;
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);// RENDERIZAÇÃO DA TABELA!!!!!!!!!!!

    ///////////////////////////////////JOGO EM AÇÃO////////////////////////////////////////////////////////////////////////////////////

    // Parte de interação com o usuário
    printf("Bem Vindo ao Conecta 4 \n");
    printf("Escolha um Modo de Jogo:\n");
    printf("Digite:\n 1 para jogador x jogador\n  2 para jogador x máquina:\n "); // a fazer

    printf("Escolha a coluna que você quer jogar (0 a 6):\n");
    int escolhacol;
    scanf("%d", &escolhacol);
    escolhaColuna(escolhacol); // Atualiza posicaoX e posicaoY

     SDL_Event event;
    int running = 1;
    int numeroJogadas;
    while (running && numeroJogadas >= 41) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;

                printf("A coord_x eh: %d\n", mouse_x);
                printf("A coord_y eh: %d\n", mouse_y);

                // Verifica qual ficha foi selecionada
                if (mouse_x > 100 && mouse_x < 232 && mouse_y > 200 && mouse_y < 332) {
                    seleciona_ficha = 1; // ficha VERMELHA
                    printf("ficha vermelha\n");
                    posicaoY = 50; // Reseta a posição Y para começar a descida
                } else if (mouse_x > 100 && mouse_x < 232 && mouse_y > 400 && mouse_y < 532) {
                    seleciona_ficha = 2; // ficha AMARELA
                    printf("ficha amarela\n");
                    posicaoY = 50; // Reseta a posição Y para começar a descida
                }
            }
        }

        // Move a peça para baixo
        if (posicaoY < 600) {  // Limite inferior para parar a descida
            posicaoY += 3.5;  // Incrementa a velocidade de descida
        } else {
            // Chegou no limite do tabuleiro, então pare a descida
            int linhaDisponivel = getLinhaDisponivel(escolhacol); // Verifica a linha disponível
            if (linhaDisponivel != -1 && seleciona_ficha != 0) {
                tabuleiroAux[linhaDisponivel][escolhacol] = seleciona_ficha; // Armazena no tabuleiro
                //posicaoY = 50;  // Reinicia a posição Y para nova peça
                //seleciona_ficha = 0; // Reseta a seleção de ficha
            }
        }

        // Renderiza o tabuleiro e as fichas
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tabuleiro, NULL, &quad1);

        // Desenha as fichas disponíveis
        SDL_Rect local_vermelha = { 100, 200, 132, 132 };
        SDL_RenderCopy(renderer, ficha_vermelha, NULL, &local_vermelha);

        SDL_Rect local_amarela = { 100, 400, 132, 132 };
        SDL_RenderCopy(renderer, ficha_amarela, NULL, &local_amarela);

        // Renderiza a ficha selecionada se houver
        if (seleciona_ficha == 1) {
            SDL_Rect posicao_inicial = { posicaoX, posicaoY, 132, 132 };
            SDL_RenderCopy(renderer, ficha_vermelha, NULL, &posicao_inicial);
        } else if (seleciona_ficha == 2) {
            SDL_Rect posicao_inicial = { posicaoX, posicaoY, 132, 132 };
            SDL_RenderCopy(renderer, ficha_amarela, NULL, &posicao_inicial);
        }


        SDL_RenderPresent(renderer);
        SDL_Delay(20); // Delay para controlar a taxa de atualização
    
    }

    
    // Libera recursos
    SDL_DestroyTexture(tabuleiro);
    SDL_DestroyTexture(ficha_vermelha);
    SDL_DestroyTexture(ficha_amarela);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
