/*Basicamente uma extensão da desenhos.h, mas com implementações da empresa*/
#ifndef MARCA_H
#define MARCA_H

#include "desenhos.h"

// Posição do copyright
#define COPY_RIGHT_X 19
#define COPY_RIGHT_Y 23

// Posicao da logo
#define POS_LOGO_X 13
#define POS_LOGO_Y 3

void logo(short int onde_comecar_linhas, short int onde_comecar_colunas);

void garrafa(short int pos_x, short int pos_y);

void copyright(short int pos_x, short int pos_y);

void descricao();

/*
Nome: logo
Parâmetros: short int pos_x -> posição do cursor em relação as colunas
            short int pod_y -> posição do cursor em relação as linhas
Retorno: -
Funcionalidade: Desenha a logo da empresa com os caracteres da tebela ASCII
*/

void logo(short int pos_x, short int pos_y)
{
    // Variaveis auxiliares para que o valor não seja perdido
    short int x = pos_x;
    short int y = pos_y;
    // Desenha a logo SHELBY ltda com base nos parametros
    gotoxy(pos_x, pos_y++);
    printf("  _____ _    _ ______ _      ______     __ ");
    gotoxy(pos_x, pos_y++);
    printf(" / ____| |  | |  ____| |    |  _ \\ \\   / /");
    gotoxy(pos_x, pos_y++);
    printf("| (___ | |__| | |__  | |    | |_) \\ \\_/ /");
    gotoxy(pos_x, pos_y++);
    printf(" \\___ \\|  __  |  __| | |    |  _ < \\   /");
    gotoxy(pos_x, pos_y++);
    printf(" ____) | |  | | |____| |____| |_) | | |  |  |_  _|  _.");
    gotoxy(pos_x, pos_y++);
    printf("|_____/|_|  |_|______|______|____/  |_|  |_ |_ (_| (_|");

    // Desenha a linha superior que tem na logo
    desenhar_linha_horizontal(x - 5, y - 1, 65);
    // Desenha a linha inferior na logo
    desenhar_linha_horizontal(x - 5, y + 7, 65);

    gotoxy(25, y + 6);
    printf("Sangue, apostas e navalhas");
}

/*
Nome: garrafa
Parâmetros: short int pos_x -> posição do cursor em relação as colunas
            short int pod_y -> posição do cursor em relação as linhas
Retorno: -
Funcionalidade: Desenha a garrafa com os caracteres da tebela ASCII
*/
void garrafa(short int pos_x, short int pos_y)
{
    gotoxy(pos_x, pos_y++);
    printf("      _");
    gotoxy(pos_x, pos_y++);
    printf("     {_}");
    gotoxy(pos_x, pos_y++);
    printf("     |(|");
    gotoxy(pos_x, pos_y++);
    printf("    _|=|_");
    gotoxy(pos_x, pos_y++);
    printf("   / --- \\      ");
    gotoxy(pos_x, pos_y++);
    printf("   ││   ││ .-==-.");
    gotoxy(pos_x, pos_y++);
    printf("   ││   ││ │    │");
    gotoxy(pos_x, pos_y++);
    printf("   │'---'│ │'-- │  ");
    gotoxy(pos_x, pos_y++);
    printf("   '-===-' '-==-'");
}

/*
Nome: logo
Parâmetros: short int pos_x -> posição do cursor em relação as colunas
            short int pod_y -> posição do cursor em relação as linhas
Retorno: -
Funcionalidade: Imprime a marca de copyright da empresa com base na posição selecionada
*/
void copyright(short int pos_x, short int pos_y)
{
    gotoxy(pos_x, pos_y);
    printf("Copyright (c) 2022 SHELBY ltda All Rights Reserved to UFS/DSI");
}

/*
Nome: logo
Parâmetros: -
Retorno: -
Funcionalidade: Mostra uma pequena contextualização da empresa
*/
void descricao()
{
    // Descrição sobre a famíla - BETA
    desenhar_quadrado(TAMANHO_COLUNAS, TAMANHO_LINHAS, 1, 1);
    logo(POS_LOGO_X, POS_LOGO_Y);
    short int c = 11, l = 12;

    gotoxy(c, l++);
    printf("A gangue dos shelby formada inicialmente para");
    gotoxy(c, l++);
    printf("apostas ilegais em corridas de cavalos, ");
    gotoxy(c, l++);
    printf("toma controles de Birmingham na região central da inglatera.");
    gotoxy(c, l++);
    printf("Agora, à fim de expandir seus negócios, a ambiciosa");
    gotoxy(c, l++);
    printf("família fundou a empresa SHELBY.ltda");
    gotoxy(c, l++);
    printf("que buscou novos pontos de apostas e agora,");
    gotoxy(c, l++);
    printf("entra com a novidade das corridas virtuais.");
    gotoxy(c, l++);
    printf("Por apenas 5 libras desfrute uma emocionante corrida.");
    gotoxy(c, l++);
    printf("de cavalos e tenha a chance de quadruplicar seu capital.");
}

#endif
