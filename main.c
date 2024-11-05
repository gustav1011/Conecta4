#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Declaração das funções
int jogada(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela, SDL_Rect quad1);
//void renderizarTabuleiro(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela, SDL_Rect quad1);
void reiniciarTabuleiro(); 
void iniciartabuleiroaux();
void escolhaColuna(int coluna);
int getColunaDisponivel(int coluna);
void PrintarTabelaux();
bool VerificacaoHorizontal(int tabuleiroAux[6][7]);
bool VerificacaoVertical(int tabuleiroAux[6][7]);
bool VerificacaoDiagonalAscendente(int tabuleiroAux[6][7]);



// Variáveis globais para o tabuleiro e o controle de posição
int jogadorAtual = 1; 
int tabuleiroAux[6][7] = {0}; // Tabuleiro auxiliar para registrar posições ocupadas
int seleciona_ficha ; // Armazena qual ficha (vermelha ou amarela) está selecionada
int posicaoX; // Posição X da peça selecionada
int posicaoY = 50; // Posição Y inicial da peça
int escolhacol; // Coluna escolhida pelo jogador
int numeroJogadas = 0; // Contador de jogadas

////////////////////////////////////////////////////// INICIO DO MAIN ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING); // Inicializa a biblioteca SDL
    SDL_Window* window = SDL_CreateWindow(
        "Conecta 4", // Nome da janela
        100, 100,    // Posição da janela
        1500, 1024,  // Tamanho da janela
        SDL_WINDOW_SHOWN // Define a janela como visível
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); // Cria um renderizador
    SDL_Texture* tabuleiro = IMG_LoadTexture(renderer, "jogo_tabuleiro.png"); // Carrega a textura do tabuleiro
    SDL_Texture* ficha_vermelha = IMG_LoadTexture(renderer, "ficha_vermelha.png"); // Carrega a textura da ficha vermelha
    SDL_Texture* ficha_amarela = IMG_LoadTexture(renderer, "ficha_amarela.png"); // Carrega a textura da ficha amarela

    SDL_Rect quad1 = { 200, 150, 1108, 887 }; // Define as dimensões do tabuleiro na tela

    SDL_RenderClear(renderer); // Limpa a tela
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Define a cor de fundo para branco

    printf("Bem Vindo ao Conecta 4 \n");
    printf("Escolha um Modo de Jogo:\n");
    printf("Digite:\n1 para jogador x jogador\n2 para jogador x máquina:\n "); // implementar essa parte ainda

    iniciartabuleiroaux(); // inicia o tabuleiro aux com todos valores setados para 0
    PrintarTabelaux();


    ///////////////////////////// JOGADA /////////////////////////////
while (numeroJogadas < 42) { // Permite até 42 jogadas (número máximo de peças no tabuleiro)
    printf("Escolha a coluna que você quer jogar (0 a 6):\n");
    scanf("%d", &escolhacol); // Usuário escolhe uma coluna

    if (escolhacol >= 0 && escolhacol < 7) {
        escolhaColuna(escolhacol); // Define a posição X com base na coluna
        jogada(renderer, tabuleiro, ficha_vermelha, ficha_amarela, quad1);

        // Verifica se a jogada foi bem-sucedida
        int linhaDisponivel = getColunaDisponivel(escolhacol);
        if (linhaDisponivel != -1) {
            tabuleiroAux[linhaDisponivel][escolhacol] = seleciona_ficha; // Adiciona a ficha na posição
            numeroJogadas++; // Incrementa o contador de jogadas somente se a jogada for válida
            PrintarTabelaux();

            // Verifica a condição de vitória HORIZONTALMENTE!!!!!
            if (VerificacaoHorizontal(tabuleiroAux)) {
                printf("Jogador %d venceu com uma sequência horizontal!\n", jogadorAtual);
                break; // Encerra o loop se houver uma vitória
            }
             // Verifica a condição de vitória VERTICALMENTE!!!!!
            else if(VerificacaoVertical(tabuleiroAux)){
                printf("Jogador %d venceu com uma sequência vertical!\n", jogadorAtual);
                break; // Encerra o loop se houver uma vitória
            }
            // Verifica a condição de vitória Diagonal Ascendente!!!!!
            else if(VerificacaoDiagonalAscendente(tabuleiroAux)){
                printf("Jogador %d venceu com uma sequência Diagonal Ascendente!\n", jogadorAtual);
                break; // Encerra o loop se houver uma vitória
            }

            // Troca de jogador
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        } else {
            printf("Coluna cheia, tente novamente!\n");
        }
    } else {
        printf("Coluna inválida. Escolha uma coluna entre 0 e 6.\n");
    }
}

printf("Jogo terminado! Total de jogadas: %d\n", numeroJogadas);
    printf("DESEJA REINICIAR O JOGO? (1 para Sim, 0 para Não)\n");
    int reiniciar;
    scanf("%d", &reiniciar);
    if (reiniciar == 1) {
    reiniciarTabuleiro(); // Reinicia o tabuleiro se o jogador escolher
    }

    // Limpeza dos recursos, liberando memória para o final do programa
    SDL_DestroyTexture(tabuleiro);
    SDL_DestroyTexture(ficha_vermelha);
    SDL_DestroyTexture(ficha_amarela);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Finaliza a SDL
    return 0;
}
////////////////////////////////////////////////////// FIM DO MAIN ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////// MÉTODO DA JOGADA ////////////////////////////////////////////
int jogada(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela, SDL_Rect quad1) {
    SDL_Event event; // Armazena os eventos SDL
    int running = 1; // Variável para controle do loop
    posicaoY = 50; // Posição inicial de descida
    seleciona_ficha = 0; // Zera a seleção da ficha
    int fichaCaiu = 0; // Flag para verificar se a ficha caiu

    // Aguarda a seleção da ficha
    while (running && !fichaCaiu) {
        while (SDL_PollEvent(&event)) { // Processa eventos
            if (event.type == SDL_QUIT) { // Evento de saída
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Evento de clique do mouse
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;

                printf("A coord_x é: %d\n", mouse_x); // Mostra a posição X do clique
                printf("A coord_y é: %d\n", mouse_y); // Mostra a posição Y do clique

                // Verifica onde o usuário clicou para selecionar a ficha
                if (mouse_x > 100 && mouse_x < 232 && mouse_y > 200 && mouse_y < 332) {
                    seleciona_ficha = 1; // Seleciona a ficha vermelha
                    printf("ficha vermelha\n");
                } else if (mouse_x > 100 && mouse_x < 232 && mouse_y > 400 && mouse_y < 532) {
                    seleciona_ficha = 2; // Seleciona a ficha amarela
                    printf("ficha amarela\n");
                }
            }
        }

        if (seleciona_ficha != 0) {
            // Continua a animação da descida
            if (posicaoY < 600) {
                posicaoY += 3.5; // Incrementa a posição Y (fazendo a peça descer)
            } else {
                fichaCaiu = 1; // Marca que a ficha caiu
            }
        }
       // renderizarTabuleiro(renderer, tabuleiro, ficha_vermelha, ficha_amarela, quad1); // Renderiza o tabuleiro
        SDL_RenderClear(renderer); // Limpa a tela para novo desenho
        SDL_RenderCopy(renderer, tabuleiro, NULL, &quad1); // Desenha o tabuleiro na tela

        // Exibe as fichas disponíveis
        SDL_Rect local_vermelha = { 100, 200, 132, 132 }; // Define a área para exibir a ficha vermelha
        SDL_RenderCopy(renderer, ficha_vermelha, NULL, &local_vermelha);
        SDL_Rect local_amarela = { 100, 400, 132, 132 }; // Define a área para exibir a ficha amarela
        SDL_RenderCopy(renderer, ficha_amarela, NULL, &local_amarela);

        // Exibe a ficha que está caindo
        if (seleciona_ficha == 1) {
            SDL_Rect fichaCaindo = { posicaoX, posicaoY, 132, 132 }; // Define a posição da ficha vermelha que está caindo
            SDL_RenderCopy(renderer, ficha_vermelha, NULL, &fichaCaindo);
        } else if (seleciona_ficha == 2) {
            int posicao = 600;
            SDL_RenderCopy(renderer, ficha_vermelha, NULL, &local_vermelha);

            SDL_Rect fichaCaindo = { posicaoX, posicaoY, 132, 132 }; // Define a posição da ficha amarela que está caindo
            SDL_RenderCopy(renderer, ficha_amarela, NULL, &fichaCaindo);
        }

        SDL_RenderPresent(renderer); // Atualiza a tela com o novo desenho
        SDL_Delay(10); // Delay para controlar a velocidade da animação
    }

    /*
        renderizarTabuleiro(renderer, tabuleiro, ficha_vermelha, ficha_amarela, quad1); // Renderiza o tabuleiro
        SDL_RenderPresent(renderer); // Apresenta o renderizador
    }
    // Adiciona a ficha no tabuleiro (na posição final)
    if (seleciona_ficha == 1) {
        SDL_Rect fichaRect = {posicaoX, posicaoY, 150, 150}; // Define a posição e o tamanho da ficha vermelha
        SDL_RenderCopy(renderer, ficha_vermelha, NULL, &fichaRect); // Desenha a ficha vermelha
    } else if (seleciona_ficha == 2) {
        SDL_Rect fichaRect = {posicaoX, posicaoY, 150, 150}; // Define a posição e o tamanho da ficha amarela
        SDL_RenderCopy(renderer, ficha_amarela, NULL, &fichaRect); // Desenha a ficha amarela
    }
}*/

    return 0; // Retorna 0 para indicar que a função foi bem-sucedida
}

////////////////////////// FUNÇÃO RENDERIZAR TABELA //////////////////////////////
/*
void renderizarTabuleiro(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela, SDL_Rect quad1) {
    SDL_RenderClear(renderer); // Limpa a tela
    SDL_RenderCopy(renderer, tabuleiro, NULL, &quad1); // Desenha o tabuleiro
    // Desenha as fichas existentes no tabuleiro
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (tabuleiroAux[i][j] == 1) { // Se a posição contém ficha vermelha
                SDL_Rect fichaRect = {j * 134 + 275, i * 134 + 150, 150, 150}; // Calcula a posição da ficha
                SDL_RenderCopy(renderer, ficha_vermelha, NULL, &fichaRect); // Desenha a ficha vermelha
            } else if (tabuleiroAux[i][j] == 2) { // Se a posição contém ficha amarela
                SDL_Rect fichaRect = {j * 134 + 275, i * 134 + 150, 150, 150}; // Calcula a posição da ficha
                SDL_RenderCopy(renderer, ficha_amarela, NULL, &fichaRect); // Desenha a ficha amarela
            }
        }
    }
    SDL_RenderPresent(renderer); // Atualiza a tela
}
*/

// Define a posição X com base na coluna selecionada
void escolhaColuna(int coluna) { 
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

// Verifica a coluna disponível na linha especificada
int getColunaDisponivel(int coluna) { 
    for (int linha = 5; linha >= 0; linha--) { // Começa da última linha (parte inferior)
        if (tabuleiroAux[linha][coluna] == 0) { // Verifica se a posição está vazia
            return linha; // Retorna a primeira linha disponível
        }
    } return -1; // Retorna -1 se a coluna estiver cheia
}

// Reinicia o tabuleiro
void reiniciarTabuleiro() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            tabuleiroAux[i][j] = 0; // Reseta o tabuleiro
        }
    }
    numeroJogadas = 0; // Reinicia o contador de jogadas
    printf("Tabuleiro reiniciado!\n");
}

// Inicializa o tabuleiro auxiliar
void iniciartabuleiroaux() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            tabuleiroAux[i][j] = 0; // Define todas as posições como vazias
        }
    }
}

// Função para imprimir o tabuleiro auxiliar
void PrintarTabelaux() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d ", tabuleiroAux[i][j]); // Imprime o valor do tabuleiro auxiliar
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
}

/*
void VerificacaoVertical(){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
    if(tabuleiroAux[i][j]==seleciona_ficha){

    }
        }
    }
}
*/


// Verifica se há quatro peças consecutivas na horizontal para um jogador
bool VerificacaoHorizontal(int tabuleiroAux[6][7]) {
    for (int i = 0; i < 6; i++) { // Percorre cada linha
        for (int j = 0; j < 4; j++) { // Até a coluna 4 para evitar overflow
            if (tabuleiroAux[i][j] != 0 && 
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 2] &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 3]) {
                // Se encontramos quatro peças consecutivas, retorna true para indicar vitória
                return true;
            }
        }
    }
    return false; // Nenhuma vitória encontrada
}

bool VerificacaoVertical(int tabuleiroAux[6][7]){
    for (int i = 0; i < 6; i++) { // Percorre cada linha
        for (int j = 0; j < 4; j++) { // Até a coluna 4 para evitar overflow
     if (tabuleiroAux[i][j] != 0 && 
         tabuleiroAux[i][j] == tabuleiroAux[i-1][j] &&
         tabuleiroAux[i][j] == tabuleiroAux[i-2][j] &&
         tabuleiroAux[i][j] == tabuleiroAux[i-3][j]) {
                // Se encontramos quatro peças consecutivas, retorna true para indicar vitória
                return true;
        }
    }
}
    return false; // Nenhuma vitória encontrada
};

bool VerificacaoDiagonalAscendente(int tabuleiroAux[6][7]) {
    for (int i = 3; i < 6; i++) { // Inicia a partir da linha 3 para permitir a diagonal
        for (int j = 0; j < 4; j++) { // Limita a coluna para permitir 4 peças em sequência
            if (tabuleiroAux[i][j] != 0 &&
                tabuleiroAux[i][j] == tabuleiroAux[i - 1][j + 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i - 2][j + 2] &&
                tabuleiroAux[i][j] == tabuleiroAux[i - 3][j + 3]) {
                return true; // Retorna verdadeiro se houver 4 em sequência na diagonal ascendente
            }
        }
    }
    return false; // Não encontrou sequência de 4
};


bool VerificacaoDiagonalDescendente(int tabuleiroAux[6][7]) {
     for (int i = 3; i < 6; i++) { // Inicia a partir da linha 3 para permitir a diagonal
        for (int j = 0; j < 4; j++) { // Limita a coluna para permitir 4 peças em sequência
            if (tabuleiroAux[i][j] != 0 &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 1][j - 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 2][j - 2] &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 3][j - 3]) {
                return true; // Retorna verdadeiro se houver 4 em sequência na diagonal ascendente
            }
        }
    }
    return false; 
};


