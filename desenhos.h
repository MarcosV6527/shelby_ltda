
/*Esse pequena biblioteca tem algumas funções para controle de vídeo*/

#ifndef __DESENHOS_H
#define __DESENHOS_H

// Compilação condicional para ter comportamentos diferentes de acordo com o compilador
// Nesse caso, MINGW, Clang e GCC
#ifdef __MINGW32__
#include <windows.h>
#include <conio2.h>

// Na bibliotaca gconio.h, existe a função delay(), ela tem a mesma funcionalidade da Sleep()
// Para unificar, caso a delay seja chamada no compilador MINGW, padrão do codeblocks, ela chamará a Sleep()
void delay(int n)
{
    Sleep(n);
}
#elif __clang__
#include <gconio.h>
#include <stdio_ext.h> //__fpurge

#elif __GNUC__
#include <gconio.h>
#include <stdio_ext.h> //__fpurge

#endif

// Tamanho das dimensões da aplicação
#define TAMANHO_LINHAS 24
#define TAMANHO_COLUNAS 80

// Declaração das funcões
short int selecionar_opcao(short int x, short int y, short int num_de_opcoes);
void preencher_com_espacos(short int largura, short int altura, short int pos_x, short int pos_y);
void desenhar_quadrado(short int largura, short int altura, short int pos_x, short int pos_y);
void desenhar_linha_vertical(short int pos_x, short int pos_y, short int tamanho);
void desenhar_linha_horizontal(short int pos_x, short int pos_y, short int tamanho);
void pausa();

/*
Nome: selecionar_opcao
Parâmetros: short int x -> posição do cursor em relação as colunas
            short int y -> posição do cursor em relação as linhas
            short int num_de_opcoes -> Quantas opções o menu vai ter
Retorno: Retorna um inteiro baseado na opção selecionada
Funcionalidade: Descrita no código
*/
short int selecionar_opcao(short int x, short int y, short int num_de_opcoes)
{

    char up_or_down;
    // Por padrão, já vem selecionada a primeira opção
    int opcao = 1;
    // Variavel para que o valor de y não seja alterado
    int ponteiro = y;

    // Vai para a coluna e a linha passada para a função
    gotoxy(x, ponteiro);
    printf(">");

    do
    {
        /*
        getch para ler variavel sem dar enter
        Essa função só aceita W e S para mover a seta e qualquer outra tecla para retornar
        Na hora de selecionar a sua opção, recomendamos apertar qualquer tecla de letra ou enter
        Algumas teclas, como a setinha, pode ocorrer erros e ficar pendente na stdin, comprometendo outros getch que terão mais tarde
        */
        up_or_down = getch();
        switch (up_or_down)
        {

        case 'w':
            // se a seta estiver em cima, não é possível subir
            if (opcao > 1)
            {
                // Apaga a seta atual e desenha uma nova na posição x , ponteiro - 1
                gotoxy(x, ponteiro);
                printf(" ");
                ponteiro--;
                gotoxy(x, ponteiro);
                printf(">");
                opcao--;
            }
            break;

        case 's':
            // Se a seta estiver embaixo, não é possivel descer
            if (opcao < num_de_opcoes)
            {
                gotoxy(x, ponteiro);
                printf(" ");
                ponteiro++;
                gotoxy(x, ponteiro);
                printf(">");
                opcao++;
            }
            break;
        default:
            // Retorna o valor de opção caso qualquer tecla seja digitada, exceto w e s
            return opcao;
        }
    } while (1);
}

/*
Nome: preencher_com_espaços
Parâmetros: short int largura -> Recebe a largura que será preenchida
            short int altura -> Recebe a altura que será preenchida
            short int pos_x -> posição do cursor em relação as colunas
            short int pos_y -> posição do cursor em relação as linhas
Retorno: void
Funcionalidade: Vai preencher largura colunas e altura linhas com espaços, começando das coordenadas pos_x e pos_y
Resumindo, apaga um pedaço da tela
*/
void preencher_com_espacos(short int largura, short int altura, short int pos_x, short int pos_y)
{
    gotoxy(pos_x, pos_y);
    // linhas
    for (short int k = 0; k < altura; k++)
    {
        // colunas
        for (short int c = 0; c < largura; c++)
        {
            printf(" ");
        }
        // O valor de posição primeiro e incrementado e depois o cursor é posicionado
        gotoxy(pos_x, ++pos_y);
    }
}

/*
    Nome: desenhar_quadrado
    Parâmetros: short int largura -> Recebe a largura que será preenchida
                short int altura -> Recebe a altura que será preenchida
                short int pos_x -> posição do cursor em relação as colunas
                short int pos_y -> posição do cursor em relação as linhas
    Retorno: void
    Funcionalidade: Desenhará bordas na posiçao pos_x e pos_y e vai estender até altura e largura
    Logo depois, esse espaço interno será preenchido
    */
void desenhar_quadrado(short int largura, short int altura, short int pos_x, short int pos_y)
{
    gotoxy(pos_x, pos_y);
    // Desenha a borda e a linha horizontal superior
    printf("┌");
    desenhar_linha_horizontal(pos_x + 1, pos_y, largura - 2);
    printf("┐");
    // Desenha as 2 linhas verticais, uma no começo e outra no final
    desenhar_linha_vertical(pos_x, pos_y + 1, altura - 2);
    desenhar_linha_vertical(largura + pos_x - 1, pos_y + 1, altura - 2);

    // Desenha a borda e a linha horizontal inferior
    gotoxy(pos_x, altura + pos_y - 1);
    printf("└");
    desenhar_linha_horizontal(pos_x + 1, altura + pos_y - 1, largura - 2);
    printf("┘");
    // Preenche a parte interna com espaços
    preencher_com_espacos(largura - 2, altura - 2, pos_x + 1, pos_y + 1);
}

/*
    Nome: desenhar_linha_vertical
    Parâmetros: short int tamanho -> Recebe o tamanho da linha que vai ser desenhada
                short int pos_x -> posição do cursor em relação as colunas
                short int pos_y -> posição do cursor em relação as linhas
    Retorno: void
    Funcionalidade: Desenhará "│" na posiçao pos_x e pos_y e do tamanho que escolhido
*/
void desenhar_linha_vertical(short int pos_x, short int pos_y, short int tamanho)
{
    for (short int i = 0; i < tamanho; i++)
    {
        // Posiciona o cursor e logo depois aumenta a variavel das linhas
        gotoxy(pos_x, pos_y++);
        printf("│");
    }
}

/*
    Nome: desenhar_linha_vertical
    Parâmetros: short int tamanho -> Recebe o tamanho da linha que vai ser desenhada
                short int pos_x -> posição do cursor em relação as colunas
                short int pos_y -> posição do cursor em relação as linhas
    Retorno: void
    Funcionalidade: Desenhará um traço na posiçao pos_x e pos_y e do tamanho que escolhido
*/

void desenhar_linha_horizontal(short int pos_x, short int pos_y, short int tamanho)
{
    for (short int i = 0; i < tamanho; i++)
    {
        // Posiciona o cursor e logo depois aumenta a variavel das colunas
        gotoxy(pos_x++, pos_y);
        printf("─");
    }
}

/*
    Nome: pausa
    Parâmetros: -
    Retorno: void
    Funcionalidade: Caso seja windows, ele chamará a pausa do próprio SO,pois ela é mais consistente
    do que a segunda implementação, que vai ter que limpar tudo que está pendente na entrada padrão
    exemplo: Após digitar o valor de int atravez de um scanf e dar enter, a variável receberá o "nextint", ou seja, o proximo inteiro que achar
    e o enter, '\n', ficará pendente e será consumido pela próxima leitura de char, o que pode acarretar bugs.
    Na implementação para outros SO, a pausa espera por um enter, pois a funcao fgetc espera um enter para acabar
    Não foi usado getch para aumentar a consistência
*/
#ifdef _WIN32

void pausa()
{
    system("pause");
}

#else

void pausa()
{
    printf("Pressione a tecla ENTER para continuar...");
    // Limpa o que está pendente na entrada
    __fpurge(stdin);
    fgetc(stdin);
    // Limpa denovo, pois a teimosia do usuário pode levar ele a digitar uma palavra inteira
    // e como o fgetc só pega um char, o restante fica pendente
    __fpurge(stdin);
}

#endif

#endif /*__DESENHOS_H*/