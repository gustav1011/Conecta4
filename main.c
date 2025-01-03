#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Declaração das funções
void jogada(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela,SDL_Texture* ficha_transparente, SDL_Rect quad1);
//void renderizarTabuleiro(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela, SDL_Rect quad1);
//int jogadaMaquina(int tabuleiroAux[6][7], SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela,SDL_Texture* ficha_transparente, SDL_Rect quad1);
void escolheColuna(int col, int tabuleiroAux[6][7], SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_amarela, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_transparente, SDL_Rect quad1);
void reiniciarTabuleiro(); 
void iniciartabuleiroaux();
void escolhaColuna(int coluna);
int getColunaDisponivel(int coluna);
int getColunaDisponivelMquina(int coluna);
void PrintarTabelaux();
bool VerificacaoHorizontal(int tabuleiroAux[6][7]);
bool VerificacaoVertical(int tabuleiroAux[6][7]);
bool VerificacaoDiagonalAscendente(int tabuleiroAux[6][7]);
bool VerificacaoDiagonalDescendente(int tabuleiroAux[6][7]);


// Variáveis globais para o tabuleiro e o controle de posição
int jogadorAtual = 1; 
int tabuleiroAux[6][7] = {0}; // Tabuleiro auxiliar para registrar posições ocupadas
int seleciona_ficha ; // Armazena qual ficha (vermelha ou amarela) está selecionada
int posicaoX; // Posição X da peça selecionada
int escolhacol; // Coluna escolhida pelo jogador
int numeroJogadas = 0; // Contador de jogadas
float posicaoY = 0;
float pos_antY = 0;
int valor_maximo;
int vencedor;
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
    SDL_Texture* tabuleiro = IMG_LoadTexture(renderer, "jogo_tabuleiro-fundo-removido.png"); // Carrega a textura do tabuleiro
    SDL_Texture* ficha_vermelha = IMG_LoadTexture(renderer, "ficha_vermelha.png"); // Carrega a textura da ficha vermelha
    SDL_Texture* ficha_amarela = IMG_LoadTexture(renderer, "ficha_amarela.png"); // Carrega a textura da ficha amarela
    SDL_Texture* ficha_transparente = IMG_LoadTexture(renderer, "ficha_transparente.png"); // Carrega a textura da ficha amarela


    SDL_Rect quad1 = { 200, 20, 1108, 750 }; // Define as dimensões do tabuleiro na tela

   // SDL_RenderClear(renderer); // Limpa a tela
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Define a cor de fundo, pode personalizar sabendo dos valores RGB
   SDL_RenderClear(renderer); // Limpa a tela

    int reiniciar = 1;

    while(reiniciar==1){
    printf("Bem Vindo ao Conecta 4 \n");
    printf("Escolha um Modo de Jogo:\n");
    printf("Digite:\n1 para jogador x jogador\n2 para jogador x máquina:\n "); // implementar essa parte ainda
    int escolhaModo;
    scanf("%d", &escolhaModo); 

 /////////////////////////////MODO DE JOGO JOGADOR X JOGADOR/////////////////////////////////   
if(escolhaModo == 1){
    iniciartabuleiroaux(); // inicia o tabuleiro aux com todos valores setados para 0
    PrintarTabelaux();
    //////////////////////////////////////////////// JOGADA ////////////////////////////////////////////////////
while (numeroJogadas < 42) { // Permite até 42 jogadas (número máximo de peças no tabuleiro)
    
    printf("Escolha a coluna que você quer jogar (0 a 6):\n");
    scanf("%d", &escolhacol); // Usuário escolhe uma coluna

    if (escolhacol >= 0 && escolhacol < 7) {
        escolhaColuna(escolhacol); // Define a posição X com base na coluna
        jogada(renderer, tabuleiro, ficha_vermelha, ficha_amarela,ficha_transparente, quad1);

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
            // Verifica a condição de vitória Diagonal descendente!!!!!
            else if(VerificacaoDiagonalDescendente(tabuleiroAux)){
                printf("Jogador %d venceu com uma sequência Diagonal Descendente!\n", jogadorAtual);
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

      if (vencedor != 0) {
        break; // Sai do loop se houver um vencedor
    }
}

// Se o número de jogadas atingiu 42 e não houve vencedor, o jogo é empate
if (numeroJogadas == 42 && vencedor == 0) {
    printf("Jogo acabou em empate!\n");
}

printf("Jogo terminado! Total de jogadas: %d\n", numeroJogadas);

//////////////////////////MODO DE JOGO X MÁQUINA//////////////////////////////////////////////////////////////

} else if(escolhaModo == 2) {// Modo de jogo contra máquina...
     jogadorAtual = 1; // Jogador 1 (Humano)
    iniciartabuleiroaux(); // inicia o tabuleiro aux com todos valores setados para 0
    PrintarTabelaux();// printa a tabela pela primera vez com ela zerada ainda!
    //////////////////////////////////////////////// JOGADA ////////////////////////////////////////////////////

while (numeroJogadas < 42) { // Permite até 42 jogadas (número máximo de peças no tabuleiro)

printf("Escolha a coluna que você quer jogar (0 a 6):\n");
    scanf("%d", &escolhacol); // Usuário escolhe uma coluna

    if (escolhacol >= 0 && escolhacol < 7) {
        escolhaColuna(escolhacol); // Define a posição X com base na coluna
        jogada(renderer, tabuleiro, ficha_vermelha, ficha_amarela,ficha_transparente, quad1);

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
            // Verifica a condição de vitória Diagonal descendente!!!!!
            else if(VerificacaoDiagonalDescendente(tabuleiroAux)){
                printf("Jogador %d venceu com uma sequência Diagonal Descendente!\n", jogadorAtual);
                break; // Encerra o loop se houver uma vitória    
            }

            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
                    } else {
                        printf("Coluna cheia, tente novamente!\n");
                    }
                } else {
                    printf("Coluna inválida. Escolha uma coluna entre 0 e 6.\n");
                }

/////////////////////////////////////JOGADA DA MÁQUINA/////////////////////////////////////////////////////
//- resolver
 printf("VEZ DA MÁQUINA!\n");

int colunaMaquina = -1; // Coluna escolhida pela máquina
int linhaDisponivel = -1;

// 1. Verificação horizontal para bloquear duas peças consecutivas (1)
for (int i = 0; i < 6; i++) { // Percorre cada linha
    for (int j = 0; j < 4; j++) { // Limita para garantir espaço para 3 colunas consecutivas
        if (tabuleiroAux[i][j] == 1 &&
            tabuleiroAux[i][j + 1] == 1 &&
            tabuleiroAux[i][j + 2] == 0) { // Bloqueia na terceira posição
            colunaMaquina = j + 2;
            linhaDisponivel = getColunaDisponivelMquina(colunaMaquina);
            if (linhaDisponivel != -1) break;
        } else if (tabuleiroAux[i][j] == 1 &&
                   tabuleiroAux[i][j + 2] == 1 &&
                   tabuleiroAux[i][j + 1] == 0) { // Bloqueia no meio
            colunaMaquina = j + 1;
            linhaDisponivel = getColunaDisponivelMquina(colunaMaquina);
            if (linhaDisponivel != -1) break;
        }
    }
    if (linhaDisponivel != -1) break;
}

// 2. Verificação vertical para bloquear duas peças consecutivas (1)
if (linhaDisponivel == -1) {
    for (int j = 0; j < 7; j++) { // Percorre cada coluna
        for (int i = 0; i < 4; i++) { // Limita para evitar overflow vertical
            if (tabuleiroAux[i][j] == 1 &&
                tabuleiroAux[i + 1][j] == 1 &&
                tabuleiroAux[i + 2][j] == 0) { // Bloqueia na terceira posição
                colunaMaquina = j;
                linhaDisponivel = i + 2;
                break;
            }
        }
        if (linhaDisponivel != -1) break;
    }
}

// 3. Escolha de coluna aleatória se nenhuma condição for atendida
if (linhaDisponivel == -1) {
    while (1) {
        colunaMaquina = rand() % 7; // Coluna aleatória entre 0 e 6
        linhaDisponivel = getColunaDisponivelMquina(colunaMaquina);
        if (linhaDisponivel != -1) break; // Garante que a coluna escolhida é válida
    }
}

// 4. Finaliza a jogada da máquina
tabuleiroAux[linhaDisponivel][colunaMaquina] = 2; // Máquina joga (representada por 2)
printf("Máquina jogou na coluna %d, linha %d\n", colunaMaquina, linhaDisponivel);
numeroJogadas++;
PrintarTabelaux();

// Verifica vitória após a jogada
if (VerificacaoHorizontal(tabuleiroAux)) {
    printf("A máquina venceu com uma sequência horizontal!\n");
    break;
} else if (VerificacaoVertical(tabuleiroAux)) {
    printf("A máquina venceu com uma sequência vertical!\n");
    break;
} else if (VerificacaoDiagonalAscendente(tabuleiroAux)) {
    printf("A máquina venceu com uma sequência diagonal ascendente!\n");
    break;
} else if (VerificacaoDiagonalDescendente(tabuleiroAux)) {
    printf("A máquina venceu com uma sequência diagonal descendente!\n");
    break;
}

// Alterna o jogador
jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
   }
}

printf("Jogo terminado! Total de jogadas: %d\n", numeroJogadas);
    

    // Limpeza dos recursos, liberando memória para o final do programa
    SDL_DestroyTexture(tabuleiro);
    SDL_DestroyTexture(ficha_vermelha);
    SDL_DestroyTexture(ficha_amarela);
    SDL_DestroyTexture(ficha_transparente);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Finaliza a SDL
    return 0;
}


////////////////////////////////////////////////////// FIM DO MAIN ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*int jogadaMaquina(int tabuleiroAux[6][7], SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela,SDL_Texture* ficha_transparente, SDL_Rect quad1) {
    // Bloqueio Horizontal (estratégia de jogada)
    for (int i = 0; i < 6; i++) { // Percorre todas as linhas
        for (int j = 0; j < 7 - 4; j++) { // Garante que há espaço para uma sequência de 4
            if (tabuleiroAux[i][j] == 1 &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 2]) {
                // Verifica se a posição seguinte está disponível
                if (j + 3 < 7 && tabuleiroAux[i][j + 3] == 0) {
                    return j + 3; // Retorna a coluna para o bloqueio
                }
            }
        }
    }

    // Caso nenhuma jogada estratégica seja encontrada, escolhe uma coluna aleatória
    int col = -1;
    while (1) {
        col = rand() % 7; // Coluna aleatória entre 0 e 6
        if (getColunaDisponivel(col) != -1) {
            break; // Retorna uma coluna válida
        }
    }

    // Simula a peça da máquina caindo na coluna selecionada
    int valor_maximo = 600; // Posição máxima onde a peça pode cair (começa a partir da última linha)
    for (int i = 0; i < 6; i++) {
        if (tabuleiroAux[i][col] == 0) {
            valor_maximo -= 110 * i; // Define a posição de queda baseada na linha vazia
            break;
        }
    }

    // Animação da peça da máquina caindo na tela
    double posicaoY = 50; // Posição inicial da peça
    while (posicaoY < valor_maximo) {
        posicaoY += 3.5; // Move a peça para baixo

       // SDL_Rect posicao_anterior_maquina = {};
        SDL_Rect posicao_maquina = { posicaoX, (int)posicaoY, 132, 132 }; // Ajuste conforme necessário
        //SDL_RenderCopy(renderer, ficha_transparente,NULL,& )
        SDL_RenderCopy(renderer, ficha_amarela, NULL, &posicao_maquina); // Desenha a peça da máquina
        SDL_RenderPresent(renderer); // Atualiza a tela
        SDL_Delay(10); // Delay para controlar a velocidade da animação
    }

    // Atualiza o tabuleiro com a jogada da máquina
    if (valor_maximo == 600) tabuleiroAux[5][col] = 2; // A máquina usa ficha amarela
    else if (valor_maximo == 490) tabuleiroAux[4][col] = 2;
    else if (valor_maximo == 380) tabuleiroAux[3][col] = 2;
    else if (valor_maximo == 270) tabuleiroAux[2][col] = 2;
    else if (valor_maximo == 160) tabuleiroAux[1][col] = 2;
    else if (valor_maximo == 50) tabuleiroAux[0][col] = 2;

    return col; // Retorna a coluna onde a máquina jogou
}
*/



////////////////////////// MÉTODO DA JOGADA ////////////////////////////////////////////
void jogada(SDL_Renderer* renderer, SDL_Texture* tabuleiro, SDL_Texture* ficha_vermelha, SDL_Texture* ficha_amarela,SDL_Texture* ficha_transparente, SDL_Rect quad1) {
    SDL_Event event; // Armazena os eventos SDL
    int running = 1; // Variável para controle do loop
    seleciona_ficha = 0; // Zera a seleção da ficha
    int fichaCaiu = 0; // Flag para verificar se a ficha caiu

    const int posicaoY_inicial = 50; // Defina a posição inicial de Y para reiniciar a cada rodada
    posicaoY = posicaoY_inicial; // Inicializa a posição Y com o valor inicial

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
    if (tabuleiroAux[5][escolhacol] == 0) valor_maximo = 600;
    else if (tabuleiroAux[4][escolhacol] == 0) valor_maximo = 490;
    else if (tabuleiroAux[3][escolhacol] == 0) valor_maximo = 380;
    else if (tabuleiroAux[2][escolhacol] == 0) valor_maximo = 270;
    else if (tabuleiroAux[1][escolhacol] == 0) valor_maximo = 160;
    else if (tabuleiroAux[0][escolhacol] == 0) valor_maximo = 50;
    else {
        // Se a coluna estiver cheia, impede a peça de descer mais
        fichaCaiu = 1;
        //return;
    }

    // Move a peça para baixo até atingir `valor_maximo`
    if (posicaoY < valor_maximo) {
        pos_antY = posicaoY;
        posicaoY += 5; // Incrementa a posição Y para simular a descida, deixar 3.5 quando programa estiver
    } else {
        fichaCaiu = 1; // A peça atingiu a posição máxima e "caiu"

        // Atualiza o tabuleiro com base na posição máxima alcançada
        if (valor_maximo == 600) tabuleiroAux[5][escolhacol] = seleciona_ficha;
        else if (valor_maximo == 490) tabuleiroAux[4][escolhacol] = seleciona_ficha;
        else if (valor_maximo == 380) tabuleiroAux[3][escolhacol] = seleciona_ficha;
        else if (valor_maximo == 270) tabuleiroAux[2][escolhacol] = seleciona_ficha;
        else if (valor_maximo == 160) tabuleiroAux[1][escolhacol] = seleciona_ficha;
        else if (valor_maximo == 50) tabuleiroAux[0][escolhacol] = seleciona_ficha;
    }
}


    // Renderiza as fichas disponíveis
    SDL_Rect local_vermelha = { 100, 200, 132, 132 };
    SDL_RenderCopy(renderer, ficha_vermelha, NULL, &local_vermelha);

    SDL_Rect local_amarela = { 100, 400, 132, 132 };
    SDL_RenderCopy(renderer, ficha_amarela, NULL, &local_amarela);

    // Renderiza a ficha que está caindo
    SDL_Rect posicao_anterior = { posicaoX, pos_antY, 132, 132 };
    SDL_Rect posicao_inicial = { posicaoX, posicaoY, 132, 132 };


    if (seleciona_ficha == 1) {
           SDL_Rect posicao_anterior = { posicaoX, pos_antY, 132, 132};   // Ajuste a largura e altura conforme necessário
            SDL_RenderCopy(renderer, ficha_transparente, NULL, &posicao_anterior);

            SDL_Rect posicao_inicial = { posicaoX, posicaoY, 132, 132};   // Ajuste a largura e altura conforme necessário
            SDL_RenderCopy(renderer, ficha_vermelha, NULL, &posicao_inicial);
    } else if (seleciona_ficha == 2) {
           SDL_Rect posicao_anterior = { posicaoX, pos_antY, 132, 132};   // Ajuste a largura e altura conforme necessário
            SDL_RenderCopy(renderer, ficha_transparente, NULL, &posicao_anterior);

            SDL_Rect posicao_inicial = { posicaoX, posicaoY, 132, 132};   // Ajuste a largura e altura conforme necessário
            SDL_RenderCopy(renderer, ficha_amarela, NULL, &posicao_inicial);
    }
    SDL_RenderCopy(renderer, tabuleiro, NULL, &quad1);
    // Atualiza a tela com o novo conteúdo renderizado
    SDL_RenderPresent(renderer);
    SDL_Delay(10); // Delay para controlar a velocidade da animação
 }
}


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
    for (int linha = 6; linha >= 0; linha--) { // Começa da última linha (parte inferior)
        if (tabuleiroAux[linha][coluna] != 1 || tabuleiroAux[linha][coluna] != 2) { // Verifica se a posição está vazia
            return linha; // Retorna a primeira linha disponível
        }
    }
    return -1; // Retorna -1 se a coluna estiver cheia
}

int getColunaDisponivelMquina(int coluna) {
    for (int i = 6; i >= 0; i--) { // Começa de baixo para cima
        if (tabuleiroAux[i][coluna] == 0 ) return i;
    }
    return -1; // Retorna -1 se a coluna estiver cheia
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
            printf(" %d ", tabuleiroAux[i][j]); // Imprime o valor do tabuleiro auxiliar
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
}

////////////////////////////////////////////////// MÉTODOS DE VERIFICAÇÃO DAS VITÓRIAS/////////////////////////////////////////////////////////
// Verifica se há quatro peças consecutivas na horizontal para um jogador
bool VerificacaoHorizontal(int tabuleiroAux[6][7]) {
    for (int i = 0; i < 6; i++) { // Percorre cada linha
        for (int j = 0; j <= 7 - 4; j++) { // Limita a coluna para evitar overflow
            if (tabuleiroAux[i][j] != 0 &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 2] &&
                tabuleiroAux[i][j] == tabuleiroAux[i][j + 3]) {
                return true; // Encontrou 4 consecutivos na horizontal
            }
        }
    }
    return false; // Nenhuma vitória horizontal encontrada
}

bool VerificacaoVertical(int tabuleiroAux[6][7]) {
    for (int i = 0; i <= 6 - 4; i++) { // Limita a linha para evitar overflow
        for (int j = 0; j < 7; j++) { // Percorre todas as colunas
            if (tabuleiroAux[i][j] != 0 &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 1][j] &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 2][j] &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 3][j]) {
                return true; // Encontrou 4 consecutivos na vertical
            }
        }
    }
    return false; // Nenhuma vitória vertical encontrada
}

bool VerificacaoDiagonalAscendente(int tabuleiroAux[6][7]) {
    for (int i = 0; i < 6; i++) { // Começa na linha 3 para permitir a diagonal ascendente
        for (int j = 0; j <= 7 - 4; j++) { // Limita a coluna para evitar overflow
            if (tabuleiroAux[i][j] != 0 &&
                tabuleiroAux[i][j] == tabuleiroAux[i - 1][j + 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i - 2][j + 2] &&
                tabuleiroAux[i][j] == tabuleiroAux[i - 3][j + 3]) {
                return true; // Encontrou 4 consecutivos na diagonal ascendente
            }
        }
    }
    return false; // Nenhuma vitória diagonal ascendente encontrada
}

bool VerificacaoDiagonalDescendente(int tabuleiroAux[6][7]) {
    for (int i = 0; i <= 6 - 4; i++) { // Limita a linha para permitir a diagonal descendente
        for (int j = 0; j <= 7 - 4; j++) { // Limita a coluna para evitar overflow
            if (tabuleiroAux[i][j] != 0 &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 1][j + 1] &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 2][j + 2] &&
                tabuleiroAux[i][j] == tabuleiroAux[i + 3][j + 3]) {
                return true; // Encontrou 4 consecutivos na diagonal descendente
            }
        }
    }
    return false; // Nenhuma vitória diagonal descendente encontrada
}