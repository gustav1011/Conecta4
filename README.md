# Conecta4:
Jogo "Conecta 4" em C.
# Objetivo:
O objetivo do "Conecta 4" é formar quatro peças em linha. Quando o primeiro jogador a formar uma linha de quatro peças consecutivas da sua cor, será o vencendor. Essa linha pode ser horizontal, vertical ou diagonal.
# Como Rodar o Código:
-COMPILA O PROGRAMA SEM USAR O gprof:
gcc main.c -I SDL2\i686-w64-mingw32\include -L SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

-COMPILA O PROGRAMA COM SUPORTE PARA O gprof FAZER A ANÁLISE:
gcc -pg main.c -I SDL2\i686-w64-mingw32\include -L SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

-Após a compilação, o programa deve ser executado para que ele gere um arquivo chamado gmon.out:(PROGRAMA VAI RODAR NO TERMINAL POR ESSE COMANDO)
./main

-Após gerar o executável .exe e executar o programa para criar o arquivo gmon.out, você pode usar o gprof para produzir um relatório detalhado de desempenho:
gprof main.exe gmon.out > perfil.txt

