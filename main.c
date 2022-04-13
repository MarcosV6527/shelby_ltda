#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jogo_da_velha.h"
#include "desenhos.h"
#include "cavalos.h"
#include "marca.h"
#include "saldo.h"

#define POS_CAIXA_X 10
#define POS_CAIXA_Y 12

#define TAMANHO_LINHAS 24
#define TAMANHO_COLUNAS 80

#define POSICAO_GARRAFA_X 50
#define POSICAO_GARRAFA_Y 12

void tela_inicial();

int main()
{
    system("chcp 65001");
    new_saldo();

    // Cor de texto -> Marrom
    textcolor(BROWN);
    clrscr();
    descricao();
    getch();
    // Geração de números aleatórios diferentes para cada vez que o programa for executado
    srand(time(NULL));
    int opcao;

    adicionar_dinheiro(5);

    do
    {
        clrscr();
        // Desenha a tela inicial toda vez que começa o loop;
        tela_inicial();

        // Caso o saldo seja 0, vai desenhar o menu com o jogo da velha
        if (getSaldo() == 0.00)
        {
            opcao = selecionar_opcao(POS_CAIXA_X + 2, POS_CAIXA_Y + 1, 2);

            switch (opcao)
            {
            case 1:
                jogo_da_velha();
                break;

            case 2:
                return 0;
                break;
            }
        }

        else
        {
            opcao = selecionar_opcao(POS_CAIXA_X + 2, POS_CAIXA_Y + 1, 3);
            switch (opcao)
            {
            case 1:
                // Vai para o menu de seleção de cavalos e aposta
                if (getSaldo() >= 5.0)
                {
                    int i = escolher_cavalo();
                    // Se a corrida ocorreu normalmente, ocorrerá uma pausa após a corrida
                    if (i)
                    {
                        gotoxy(20, TAMANHO_LINHAS - 3);
                        pausa();
                    }
                }
                else
                {

                    gotoxy(10, 21);
                    printf("SALDO INSUFICIENTE PARA ESSE MODO");
                    gotoxy(10, 22);
                    pausa();
                    gotoxy(POS_CAIXA_X, 21);
                    printf("                  ");
                }
                break;
            case 2:

                break;
            case 3:
                return 0;
            default:
                break;
            }

        }

    } while (1);
}

void tela_inicial()
{
    textcolor(BROWN);

    // Desenha todo o background
    desenhar_quadrado(TAMANHO_COLUNAS, TAMANHO_LINHAS, 1, 1);
    // Desenha a logo "SHELBY ltda" nas dimensões especificadas
    logo(POS_LOGO_X, POS_LOGO_Y);

    // Desenha o quadrado do menu de opcoes
    desenhar_quadrado(30, 9, POS_CAIXA_X, POS_CAIXA_Y);

    garrafa(POSICAO_GARRAFA_X, POSICAO_GARRAFA_Y);
    int linha = POS_CAIXA_Y;

    //Escolhe o menu a ser desenhado
    if (getSaldo() == 0.0)
    {
        gotoxy(POS_CAIXA_X + 4, ++linha);
        printf("JOGO DA VELHA");
        gotoxy(POS_CAIXA_X + 4, ++linha);
        printf("SAIR");
    }
    else
    {
        gotoxy(POS_CAIXA_X + 4, ++linha);
        printf("CORRIDA DE CAVALOS");
        gotoxy(POS_CAIXA_X + 4, ++linha);
        printf("JOGO DO BICHO");
        gotoxy(POS_CAIXA_X + 4, ++linha);
        printf("SAIR");
    }

    copyright(COPY_RIGHT_X, COPY_RIGHT_Y);

    gotoxy(POS_SALDO_X, POS_SALDO_Y);
    printf("SALDO: £ %.2lf", getSaldo());
}
