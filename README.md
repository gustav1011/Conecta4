# Conecta4:
Jogo "Conecta 4" em C.
# Objetivo:

O "Conecta 4" é um jogo de estratégia para dois jogadores, cujo objetivo é ser o primeiro a alinhar quatro peças consecutivas da sua cor no tabuleiro. Os jogadores escolhem uma coluna para jogar, e a peça desliza até a última posição disponível nessa coluna.
A linha formada pode ser:
-Horizontal
-Vertical
-Diagonal ascendente
-Diagonal descendente

O jogador que alcançar esse objetivo primeiro vence a partida

# Como Rodar o Código:
-COMPILA O PROGRAMA SEM USAR O gprof:
gcc main.c -I SDL2\i686-w64-mingw32\include -L SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

-COMPILA O PROGRAMA COM SUPORTE PARA O gprof FAZER A ANÁLISE:
gcc -pg main.c -I SDL2\i686-w64-mingw32\include -L SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

-Após a compilação, o programa deve ser executado para que ele gere um arquivo chamado gmon.out:(PROGRAMA VAI RODAR NO TERMINAL POR ESSE COMANDO)

./main

-Após gerar o executável .exe e executar o programa para criar o arquivo gmon.out, você pode usar o gprof para produzir um relatório detalhado de desempenho:

gprof main.exe gmon.out > perfil.txt

# Dependências:
SDL2: Biblioteca para gráficos e interação. Certifique-se de que SDL2 está instalado e configurado corretamente no ambiente de desenvolvimento.

