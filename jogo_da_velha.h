#ifndef _JOGO_DA_VELHA_H
#define _JOGO_DA_VELHA_H

#include "desenhos.h"
#include "saldo.h"
#include <stdlib.h>

#define POS_PERGUNTAS 23

// Posicao da linha 1 e 2 do #
#define POS_L_1 7
#define POS_L_2 14

// Posicao da coluna 1 e 2 do #
#define POS_C_1 21
#define POS_C_2 43

// Posicao da mensagem de resultado
#define POS_R_L 5
#define POS_R_C 15

void print_tabuleiro(int casas[3][3]);

void x(int pos_x, int pos_y);
void o(int pos_x, int pos_y);

void jogada_x(int casas[3][3]);
void jogada_o(int casas[3][3]);

int vitoria_x(int casas[3][3]);
int vitoria_o(int casas[3][3]);

void print_x_ganhou();
void print_o_ganhou();

void empatou();

void jogo_da_velha();

int x_vai_ganhar(int casas[3][3]);

int cantos_ocupados(int casas[3][3]);
int meios_ocupados(int casas[3][3]);

// Variável global pra controlar o número de jogadas do bot
// Global para não precisar usar ponteiros
int cont;

/*
Nome: jogo_da_velha
Parâmetros:
Retorno: -
Funcionalidade: É a função main do jogo da velha
*/
void jogo_da_velha()
{

    int vencedor = 0;
    preencher_com_espacos(TAMANHO_COLUNAS, TAMANHO_LINHAS, 1, 1);

    // Tabuleiro
    // 1 é X, -1 é O e 0 é null
    int casas[3][3] = {0};

    cont = 0;
    // Ocorrem 9 jogadas durante o jogo. Em cada volta, o X e o O jogam, mas o for é quebrado quando for 4
    for (int i = 0; i < 5; i++)
    {
        /*
            Depois de casa jogada, ocorre a verificação de vitória
        */
        print_tabuleiro(casas);

        // X joga
        jogada_x(casas);

        if (vitoria_x(casas))
        {
            print_tabuleiro(casas);
            // Caso X vença, o saldo volta para ter outra chance
            adicionar_dinheiro(5);
            vencedor = 1;
            break;
        }

        if (i == 4)
        {
            print_tabuleiro(casas);
            break;
        }

        print_tabuleiro(casas);

        // Vez do bot
        jogada_o(casas);

        // Limpa a parte de baixo da tela e dá uma pausa de um pouco mais de 1 segundo
        gotoxy(1, POS_PERGUNTAS);
        printf("                                                  ");
        gotoxy(1, POS_PERGUNTAS + 1);
        printf("                                                      ");
        gotoxy(1, POS_PERGUNTAS);
        printf("   ANALISANDO JOGADA...");

        fflush(stdout);

        delay(1250);

        if (vitoria_o(casas))
        {
            print_tabuleiro(casas);
            vencedor = -1;
            break;
        }
    }

    // Ultima atualização do tabuleiro
    clrscr();
    print_tabuleiro(casas);
    gotoxy(20, TAMANHO_LINHAS - 1);
    pausa();

    desenhar_quadrado(TAMANHO_COLUNAS, TAMANHO_LINHAS, 1, 1);

    if (vencedor == 1)
    {
        print_x_ganhou();
    }
    else if (vencedor == -1)
    {
        print_o_ganhou();
    }
    else // vencedor == 0
    {
        empatou();
    }

    gotoxy(20, 20);
    pausa();
}

/*
Nome: jogada_o
Parâmetros: tabuleiro
Retorno: -
Funcionalidade: BOT para impedir o X
Observação: Cada if tem um return, Logo, não é necessário usar o else
*/
void jogada_o(int casas[3][3])
{
    // Se for a jogada 2 e o meio estiver desocupado, ele vai jogar lá, pois sempre é a melhor opção
    if (cont == 1)
    {
        if (casas[1][1] == 0)
        {
            casas[1][1] = -1;
            cont++;
            return;
        }
    }

    // Se for a primeira jogada e o meio for X, a melhor jogada é o canto
    if (casas[1][1] == 1 && cont == 0)
    {
        casas[0][0] = -1;
        cont++;
        return;
    }

    // Se o x jogar em alguma casas da linha 2 ou coluna 2 na primeira jogada, ele vai jogar no canto, pois é a melhor jogada
    if (meios_ocupados(casas) && cont == 0)
    {
        if (casas[1][2] == 1 || casas[0][1] == 1)
        {
            casas[0][2] = -1;
        }
        else
        {
            casas[2][0] = -1;
        }
        cont++;
        return;
    }

    // Caso a primeira jogada de X seja no canto, o O vai jogar no meio
    if (casas[1][1] == 0 && cont == 0)
    {
        casas[1][1] = -1;
        cont++;
        return;
    }

    // Se o canto for ocupado por X e for a segunda jogada, o O vai jogar no "meio superior"
    if (cantos_ocupados(casas) == 1 && cont == 1)
    {
        if (casas[0][2] == 0)
        {
            casas[0][2] = -1;
            cont++;
            return;
        }
    }

    // Se 2 cantos forem ocupados por X e for a segunda jogada, o O vai jogar no "meio superior"
    if (cantos_ocupados(casas) > 1 && cont == 1)
    {
        if (casas[0][1] == 0)
        {
            casas[0][1] = -1;
            cont++;
            return;
        }
    }

    // Percorre toda a matriz e testa possíveis valores para O, caso vença, esse é o escolhido
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (casas[i][j] == 0)
            {
                casas[i][j] = -1;
                if (vitoria_o(casas))
                {
                    cont++;
                    return;
                }
                casas[i][j] = 0;
            }
        }
    }

    // Percorre toda a matriz e testa possíveis valores para X, caso X vença, o O joga nessa posição

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (casas[i][j] == 0)
            {
                casas[i][j] = 1;
                if (vitoria_x(casas))
                {
                    casas[i][j] = -1;
                    cont++;
                    return;
                }
                casas[i][j] = 0;
            }
        }
    }

    // Caso nada seja atendido (condições muito específicas), ele vai jogar no primeiro que achar
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (casas[i][j] == 0)
            {
                casas[i][j] = -1;
                return;
            }
        }
    }
}

/*
Nome: meios_ocupados
Parâmetros: tabuleiro
Retorno: um falso bool
Funcionalidade: Vê se as posições da linha ou coluna 2 estão ocupadas por X
*/
int meios_ocupados(int casas[3][3])
{
    if (casas[1][0] == 1 || casas[0][1] == 1 || casas[2][1] == 1 || casas[1][2] == 1)
    {
        return 1;
    }
    return 0;
}

/*
Nome: meios_ocupados
Parâmetros: tabuleiro
Retorno: a quantidade de cantos ocupados
Funcionalidade: Vê se os cantos estão ocupador por X
*/
int cantos_ocupados(int casas[3][3])
{
    int num = 0;
    if (casas[0][0] == 1)
    {
        num++;
    }
    if (casas[0][2] == 1)
    {
        num++;
    }
    if (casas[2][0] == 1)
    {
        num++;
    }
    if (casas[2][2] == 1)
    {
        num++;
    }
    return num;
}

/*
Nome: jogada_x
Parâmetros: tabuleiro
Retorno: -
Funcionalidade: jogada de X
*/
void jogada_x(int casas[3][3])
{
    gotoxy(3, POS_PERGUNTAS - 1);
    printf("                   ");
    gotoxy(3, POS_PERGUNTAS - 1);
    printf("Vez de x");
    // Linha e coluna para jogar
    int l, c;

    // Prende o usuário até digitar 1, 2 ou 3
    do
    {

        gotoxy(3, POS_PERGUNTAS);
        printf("                                                             ");
        gotoxy(3, POS_PERGUNTAS);
        printf("Digite a linha que deseja jogar [1 , 2 , 3]:");
        scanf("%d", &l);

    } while (l < 0 || l > 3);

    do
    {
        gotoxy(3, POS_PERGUNTAS);
        printf("                                                             ");
        gotoxy(3, POS_PERGUNTAS);
        printf("Digite a coluna que deseja jogar [1 , 2 , 3]: ");
        scanf("%d", &c);
    } while (c < 0 || c > 3);

    // Diminue o valor de C e L para ser compativel com a matriz
    c--;
    l--;

    // Se a casa estiver desocupada, ele joga
    if (casas[l][c] == 0)
    {
        casas[l][c] = 1;
    }
    // Se nao, ele chama a propria funcao
    else
    {
        gotoxy(3, POS_PERGUNTAS);
        printf("Casa já ocupada");
        getch();
        jogada_x(casas);
    }
}

/*
Nome: print_tabuleiro
Parâmetros: tabuleiro
Retorno: -
Funcionalidade: Desenha o tabuleiro
*/

void print_tabuleiro(int casas[3][3])
{
    desenhar_quadrado(60, 21, 3, 1);

    // Deixa o cursor na linha 2 e desce desenhando linha
    desenhar_linha_vertical(POS_C_1, 2, 19);
    desenhar_linha_vertical(POS_C_2, 2, 19);

    // Deixa o cursor na coluna 4 e segue desenhando linha
    desenhar_linha_horizontal(4, POS_L_1, 58);
    desenhar_linha_horizontal(4, POS_L_2, 58);

    gotoxy(POS_C_1, POS_L_2);
    printf("┼");
    gotoxy(POS_C_1, POS_L_1);
    printf("┼");
    gotoxy(POS_C_2, POS_L_2);
    printf("┼");
    gotoxy(POS_C_2, POS_L_1);
    printf("┼");

    // Coluna e linha
    int c = 9;
    int l = 2;

    for (int i = 0; i < 3; i++)
    {
        int c = 9;
        for (int j = 0; j < 3; j++)
        {
            if (casas[i][j] == 1)
            {
                x(c, l);
            }
            else if (casas[i][j] == -1)
            {
                o(c, l);
            }
            // Desenha uma letra de C em C colunas
            c += 20;
        }
        // Pula 7 linhas: Distancia das linhas
        l += 7;
    }
}

/*
Nome: x
Parâmetros: pos_x para coluna e pos_y para a linhas
Retorno: -
Funcionalidade: Desenha um X
*/

void x(int pos_x, int pos_y)
{
    gotoxy(pos_x, pos_y++);
    printf("#   #");
    gotoxy(pos_x, pos_y++);
    printf(" # # ");
    gotoxy(pos_x, pos_y++);
    printf("  #  ");
    gotoxy(pos_x, pos_y++);
    printf(" # # ");
    gotoxy(pos_x, pos_y++);
    printf("#   #");
}

/*
Nome: o
Parâmetros: pos_x para coluna e pos_y para a linhas
Retorno: -
Funcionalidade: Desenha uma bola
*/
void o(int pos_x, int pos_y)
{
    gotoxy(pos_x, pos_y++);
    printf("  ___  ");
    gotoxy(pos_x, pos_y++);
    printf(" / _ \\ ");
    gotoxy(pos_x, pos_y++);
    printf("| (_) |");
    gotoxy(pos_x, pos_y++);
    printf(" \\___/ ");
    gotoxy(pos_x, pos_y++);
    printf("     ");
}

/*
Nome: vitoria_o / vitoria_x
Parâmetros: tabuleiro
Retorno: falso bool
Funcionalidade: Verifica se ganhou e retorna 1, caso ganhe
*/
int vitoria_o(int casas[3][3])
{
    if (casas[0][0] == -1 && casas[0][1] == -1 && casas[0][2] == -1 ||
        casas[1][0] == -1 && casas[1][1] == -1 && casas[1][2] == -1 ||
        casas[2][0] == -1 && casas[2][1] == -1 && casas[2][2] == -1 ||

        casas[0][0] == -1 && casas[1][0] == -1 && casas[2][0] == -1 ||
        casas[0][1] == -1 && casas[1][1] == -1 && casas[2][1] == -1 ||
        casas[0][2] == -1 && casas[1][2] == -1 && casas[2][2] == -1 ||

        casas[0][0] == -1 && casas[1][1] == -1 && casas[2][2] == -1 ||
        casas[0][2] == -1 && casas[1][1] == -1 && casas[2][0] == -1)
    {
        return 1;
    }

    return 0;
}

int vitoria_x(int casas[3][3])
{
    if (casas[0][0] == 1 && casas[0][1] == 1 && casas[0][2] == 1 ||
        casas[1][0] == 1 && casas[1][1] == 1 && casas[1][2] == 1 ||
        casas[2][0] == 1 && casas[2][1] == 1 && casas[2][2] == 1 ||

        casas[0][0] == 1 && casas[1][0] == 1 && casas[2][0] == 1 ||
        casas[0][1] == 1 && casas[1][1] == 1 && casas[2][1] == 1 ||
        casas[0][2] == 1 && casas[1][2] == 1 && casas[2][2] == 1 ||

        casas[0][0] == 1 && casas[1][1] == 1 && casas[2][2] == 1 ||
        casas[0][2] == 1 && casas[1][1] == 1 && casas[2][0] == 1)
    {
        return 1;
    }
    return 0;
}

/*
Nome: print_x_ganhou, print_o_ganhou, empatou
Parâmetros:
Retorno: -
Funcionalidade: Desenha tal vencedor
*/
void print_x_ganhou()
{
    int c = POS_R_C;
    int l = POS_R_L;

    gotoxy(c, l++);
    printf("__   __   _____          _   _ _    _  ____  _    _ ");
    gotoxy(c, l++);
    printf("\\ \\ / /  / ____|   /\\   | \\ | | |  | |/ __ \\| |  | |");
    gotoxy(c, l++);
    printf(" \\ V /  | |  __   /  \\  |  \\| | |__| | |  | | |  | |");
    gotoxy(c, l++);
    printf("  > <   | | |_ | / /\\ \\ | . ` |  __  | |  | | |  | |");
    gotoxy(c, l++);
    printf(" / . \\  | |__| |/ ____ \\| |\\  | |  | | |__| | |__| |");
    gotoxy(c, l++);
    printf("/_/ \\_\\  \\_____/_/    \\_\\_| \\_|_|  |_|\\____/ \\____/ ");
}
void print_o_ganhou()
{
    int c = POS_R_C;
    int l = POS_R_L;

    gotoxy(c, l++);
    printf("  ____     _____          _   _ _    _  ____  _    _ ");
    gotoxy(c, l++);
    printf(" / __ \\   / ____|   /\\   | \\ | | |  | |/ __ \\| |  | |");
    gotoxy(c, l++);
    printf("| |  | | | |  __   /  \\  |  \\| | |__| | |  | | |  | |");
    gotoxy(c, l++);
    printf("| |  | | | | |_ | / /\\ \\ | . ` |  __  | |  | | |  | |");
    gotoxy(c, l++);
    printf("| |__| | | |__| |/ ____ \\| |\\  | |  | | |__| | |__| |");
    gotoxy(c, l++);
    printf(" \\____/   \\_____/_/    \\_\\_| \\_|_|  |_|\\____/ \\____/ ");
}
void empatou()
{
    int c = POS_R_C;
    int l = POS_R_L;

    gotoxy(c, l++);
    printf(" ______ __  __ _____     _______ ____  _    _ ");
    gotoxy(c, l++);
    printf("|  ____|  \\/  |  __ \\ /\\|__   __/ __ \\| |  | |");
    gotoxy(c, l++);
    printf("| |__  | \\  / | |__) /  \\  | | | |  | | |  | |");
    gotoxy(c, l++);
    printf("|  __| | |\\/| |  ___/ /\\ \\ | | | |  | | |  | |");
    gotoxy(c, l++);
    printf("| |____| |  | | |  / ____ \\| | | |__| | |__| |");
    gotoxy(c, l++);
    printf("|______|_|  |_|_| /_/    \\_\\_|  \\____/ \\____/ ");
}

#endif /*_JOGO_DA_VELHA_H*/