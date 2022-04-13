// Contém todo o algoritmo da parte dos cavalos
#ifndef __CAVALOS_H
#define __CAVALOS_H

#include "desenhos.h"
#include "marca.h"

// Posiçao do nome dos cavalos
#define POS_N_CAVALO_X 15
#define POS_N_CAVALO_Y 12

// Posição inicial dos cavalos
#define POSICAO_INICIAL_CAVALOS_COLUNA 10
#define POSICAO_INICIAL_CAVALOS_LINHA 11

// Posição da linha de chegada
#define LINHA_DE_CHEGADA 70

// Número de cavalos
#define N_DE_CAVALOS 4

void _pista();
short int escolher_cavalo();
short int houve_vencedor(short int cavalos[]);
void apostar_em_cavalos(short int aposta, double valor);
void iniciar_posicao_dos_cavalos(short int pista[], short int cavalo[]);
void atualizar_posicao(short int cavalo[], short int k[]);
void corrida(short int k[], short int cor_cavalo[], short int cavalo[], short int pista[]);
void corrigir_posicao(short int cavalo[]);
void empatou_cavalo(short int pista[], short int cavalo[]);
void ganhou(short int pista[], char nome_cavalos[N_DE_CAVALOS][15], short int temp);
void print_nome_cavalos();

/*
Nome: print_nome_cavalos
Parâmetros: -
Retorno: -
Funcionalidade: Mostra o saldo e o menu de seleção de cavalos na tela
*/

void print_nome_cavalos()
{
    // int y é usada para armazenar o valor da MACRO e poder alterar, ela vai ser usada para o gotoxy
    short int y = POS_N_CAVALO_Y;

    // Imprime o saldo na tela
    gotoxy(POS_SALDO_X, POS_SALDO_Y);
    printf("SALDO: £ %.2lf", getSaldo());

    gotoxy(POS_N_CAVALO_X, y++);
    textcolor(RED);
    printf("  PEGASUS - VERMELHO");
    gotoxy(POS_N_CAVALO_X, y++);
    textcolor(BLUE);
    printf("  JU MENTOS - AZUL");
    gotoxy(POS_N_CAVALO_X, y++);
    textcolor(GREEN);
    printf("  MUSTANG - VERDE");
    gotoxy(POS_N_CAVALO_X, y++);
    textcolor(3);
    printf("  PÉ DE PANO - CIANO");
    gotoxy(POS_N_CAVALO_X, y++);
    textcolor(7);
    printf("  VOLTAR");
    gotoxy(POS_N_CAVALO_X, ++y);
}

/*
Nome: escolher_cavalo
Parâmetros: -
Retorno: Retorna 1 ou 0. Caso deseje voltar para main, ele retorna 0, caso a função finalize com sucesso, retorna 1
Funcionalidade: escolhe o cavalo e faz a aposta
observação: Caso essa função estivesse em um arquivo só, ela seria a main
*/
short int escolher_cavalo()
{
    // Limpa a tela e desenha quadrado
    desenhar_quadrado(TAMANHO_COLUNAS, TAMANHO_LINHAS, 1, 1);
    copyright(COPY_RIGHT_X, COPY_RIGHT_Y);

    logo(POS_LOGO_X, POS_LOGO_Y);

    // Menu de seleçao de cavalo
    print_nome_cavalos();

    //Opcao vai receber o retorno de selecionar opcao, que nesse caso, é o cavalo escolhido, ou o número 5
    short int opcao = selecionar_opcao(POS_N_CAVALO_X, POS_N_CAVALO_Y, 5);

    //5 é voltar, então ele encerra a função 
    if (opcao == 5)
    {
        return 0;
    }


    double valor_aposta;
    //y armazena a linha que ocorrerá os printf()
    short int y = 19;
    gotoxy(POS_N_CAVALO_X, y);
    printf("Digite o valor da aposta {O valor deve ser maior que £ 5.00}: ");
    //Faça isso enquanto não validar a aposta
    do
    {
        gotoxy(POS_N_CAVALO_X, y + 1);
        printf("      ");
        gotoxy(POS_N_CAVALO_X, y + 1);
        printf(">>>");
        scanf("%lf", &valor_aposta);
    
    } while (!validar_aposta_cavalos(valor_aposta));

    //Remove a aposta do saldo
    remover_dinheiro(valor_aposta);


    gotoxy(TAMANHO_COLUNAS / 2 - 10, TAMANHO_LINHAS - 2);
    pausa();

    textcolor(BROWN);
    // Vai para a telinha de corrida
    apostar_em_cavalos(opcao - 1, valor_aposta);
    return 1;
}

/*
Nome: escolher_cavalo
Parâmetros: cavalo escolhido e valor da aposta
Retorno: -
Funcionalidade: Faz a aposta
*/

void apostar_em_cavalos(short int aposta, double valor)
{
    //Vetor para armazenar a cor dos cavalos
    short int cor_cavalo[N_DE_CAVALOS] = {RED, BLUE, GREEN, CYAN};

    //Vetor de string / matriz de char para armazenar nomes
    char nome_cavalos[N_DE_CAVALOS][15] = {"PEGASUS", "JU MENTOS", "MUSTANG", "PÉ DE PANO"};

    desenhar_quadrado(TAMANHO_COLUNAS, TAMANHO_LINHAS, 1, 1);

    // vetor que controla onde os cavalos estão
    //Colunas
    short int cavalo[N_DE_CAVALOS];
    //linhas
    short int pista[N_DE_CAVALOS];

    //Posiciona o cavalos em suas posições iniciais
    iniciar_posicao_dos_cavalos(pista, cavalo);

    // Desenha a pista
    _pista();

    //Valor do premio
    double premio = 0;

    // Vetor que armazena a quantidade de passos de todos os cavalos
    short int k[N_DE_CAVALOS];

    while (1)
    {   
        //Chama a corrida
        corrida(k, cor_cavalo, cavalo, pista);

        // Background reiniciado
        textbackground(0);
        //Atualiza a posiçao de cada cavalo
        atualizar_posicao(cavalo, k);
        //Caso algum cavalo fique na frente da linha de chegada, ele vai pra linha de chegada
        corrigir_posicao(cavalo);

        short int temp = houve_vencedor(cavalo);

        // Empate
        if (temp == -1)
        {
            empatou_cavalo(pista, cavalo);
            break;
        }
        // Alguem ganhou
        else if (temp != -2)
        {
            ganhou(pista, nome_cavalos, temp);
            //Se a aposta foi igual ao cavalo vencedor, o valor é multiplicado pela quanridade de cavalos
            if (aposta == temp)
            {
                premio = valor * N_DE_CAVALOS;
                adicionar_dinheiro(premio);
            }
            break;
        }

    } // While

    // Se o premio for maior que 0, significa que houve um vencedor
    if (premio > 0.0)
    {
        gotoxy(TAMANHO_COLUNAS / 2 - 13, 7);
        printf("PARABÉNS, VOCÊ GANHOU £ %.2f", premio);
    }
    else
    {
        gotoxy(TAMANHO_COLUNAS / 2 - 1, 7);
        printf("):");
    }
}

/*
Nome: Houve vencedor
Parâmetros: vetor com os cavalos
Retorno: Detalhes no código
Funcionalidade: Verifica se os cavalos chegaram no destino
*/

short int houve_vencedor(short int cavalos[])
{
    short int vencedor;
    //Usada para verificação de empate
    short int num_de_vencedores = 0;

    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {
        if (cavalos[i] >= LINHA_DE_CHEGADA)
        {
            vencedor = i;
            num_de_vencedores++;
        }
    }

    //Se o numero de vencedor for maior que 1, retorna -1, que é o empate
    if (num_de_vencedores > 1)
    {
        return -1;
    }
    //Se apenas 1 cavalo chegar no destino, retorna o tal cavalo
    if (num_de_vencedores == 1)
    {
        return vencedor;
    }
    // Ainda não teve vencedor
    return -2;
}

/*
Nome: pista
Parâmetros: -
Retorno: -
Funcionalidade: Desenha a pista
*/
void _pista()
{   
    //Desenha a linha de chegada
    desenhar_linha_vertical(LINHA_DE_CHEGADA, POSICAO_INICIAL_CAVALOS_LINHA, N_DE_CAVALOS * 2 - 1);
    // Desenha a borda
    gotoxy(LINHA_DE_CHEGADA, 10);
    printf("┐");

    // Desenha a pista dos cavalos
    short int j = POSICAO_INICIAL_CAVALOS_COLUNA + (N_DE_CAVALOS * 2);
    for (short int i = POSICAO_INICIAL_CAVALOS_COLUNA; i <= j; i += 2)
    {   
        //Desenha j linhas e a proxima vai ser desenhar 1 linha depois
        desenhar_linha_horizontal(POSICAO_INICIAL_CAVALOS_COLUNA, i, LINHA_DE_CHEGADA - POSICAO_INICIAL_CAVALOS_COLUNA);
    }
    // Desenha a borda
    printf("┘");
}

/*
Nome: iniciar_posicao_dos_cavalos
Parâmetros: vetor com a posicao das linhas e vetor com a posicao das colunas
Retorno: -
Funcionalidade: Coloca os cavalos na linha de partida
*/
void iniciar_posicao_dos_cavalos(short int pista[], short int cavalo[])
{
    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {
        cavalo[i] = POSICAO_INICIAL_CAVALOS_COLUNA;
    }

    short int x = POSICAO_INICIAL_CAVALOS_LINHA;

    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {
        pista[i] = x;
        x += 2;
    }
}

/*
Nome: corrida
Parâmetros: Vetor que vai armazenar o número de passor k[], vetor com a cor dos cavalos, posicao do cavalo nas colunas e nas linhas
Retorno: -
Funcionalidade: Faz a grandiosa corrida
*/
void corrida(short int k[], short int cor_cavalo[], short int cavalo[], short int pista[])
{
    // Cada cavalo vai receber uma quantidade de passos
    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {
        k[i] = rand() % 2 + 1;
    }

    // Controla o cavalo
    for (short int cont = 0; cont < N_DE_CAVALOS; cont++)
    {
        // Controla os passos do cavalo na posição cont
        for (short int i = 0; i < k[cont]; i++)
        {
            // Essa função fflush serve para que a animação ocorra no linux
            fflush(stdout);
            delay(20);

            // Movimenta o cursor para a posição do cavalo
            gotoxy(cavalo[cont] + i, pista[cont]);

            // Cor de texto diferente para cada cavalo
            textbackground(cor_cavalo[cont]);
            printf(" ");
        }
    }
}

/*
Nome: atualizar_posicao
Parâmetros: posição dos cavalos e os passos que ele deu
Retorno: -
Funcionalidade: Altera a posição dos cavalos
Observação: A função corrida faz só a parte visual
*/
void atualizar_posicao(short int cavalo[], short int k[])
{   
    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {
        // Atualiza a posição do cavalo
        //Por ser vetor, está sendo usado um ponteiro para a posição dos cavalos, ou seja
        //esse valor vai mudar nas outras funções
        cavalo[i] += k[i];
    }
}

/*
Nome: corrigir_posicao
Parâmetros: posicao dos cavalos
Retorno: -
Funcionalidade: Caso algum cavalo fique na frente da linha de chegada, ele volta para a linha de chegada
*/
void corrigir_posicao(short int cavalo[])
{
    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {
        if (cavalo[i] > LINHA_DE_CHEGADA)
        {
            cavalo[i] = LINHA_DE_CHEGADA;
        }
    }
}

/*
Nome: empatou_cavalo
Parâmetros: posicao das linhas e das colunas dos cavalos
Retorno: -
Funcionalidade: Mostra a tela de empate
*/
void empatou_cavalo(short int pista[], short int cavalo[])
{
    // Cursor no meio superior
    gotoxy(TAMANHO_COLUNAS / 2 - 7, 6);
    printf("OCORREU UM EMPATE");

    // Coloca os cavalos que ultrapassaram a linha de chagada na linha de chegada
    for (short int i = 0; i < N_DE_CAVALOS; i++)
    {

        gotoxy(LINHA_DE_CHEGADA, pista[i]);
        if (cavalo[i] == LINHA_DE_CHEGADA)
        {
            printf(">   "); // Limpar espaços para caso algum cavalo chegue na posição 71
        }
    }
}

/*
Nome: ganhou
Parâmetros: posicao dos cavalos nas linhas, nome dos cavalos e o campeão
Retorno: -
Funcionalidade: Mostra o nome de quem ganhou
*/

void ganhou(short int pista[], char nome_cavalos[N_DE_CAVALOS][15], short int vencedor)
{
    textcolor(BROWN);
    // Limpar a coluna 71
    gotoxy(LINHA_DE_CHEGADA, pista[vencedor]);
    printf(">   ");

    gotoxy(TAMANHO_COLUNAS / 2 - 7, 6);
    printf("%s GANHOU", nome_cavalos[vencedor]);
}

#endif /*__CAVALOS_H*/