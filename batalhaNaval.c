#include <stdio.h>
#include <string.h>

#define TAM_TAB 10
#define TAM_HAB 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para inicializar uma matriz com 0
void inicializaMatriz(int m[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            m[i][j] = AGUA;
}

// Posiciona navio com base em arrays de linha e coluna
void posicionarNavio(int tab[TAM_TAB][TAM_TAB], int linhas[3], int colunas[3]) {
    for (int i = 0; i < 3; i++) {
        tab[linhas[i]][colunas[i]] = NAVIO;
    }
}

// Gera matriz de habilidade Cone (ponta no topo, base embaixo)
void gerarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade Cruz
void gerarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade Octaedro (losango)
void gerarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Sobrepõe matriz de habilidade no tabuleiro
void aplicarHabilidade(int tab[TAM_TAB][TAM_TAB], int hab[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linha_tab = origem_linha + i - TAM_HAB / 2;
            int coluna_tab = origem_coluna + j - TAM_HAB / 2;
            if (linha_tab >= 0 && linha_tab < TAM_TAB && coluna_tab >= 0 && coluna_tab < TAM_TAB) {
                if (hab[i][j] == 1 && tab[linha_tab][coluna_tab] == AGUA)
                    tab[linha_tab][coluna_tab] = HABILIDADE;
            }
        }
    }
}

// Imprime o tabuleiro com símbolos
void exibirTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            char simbolo;
            switch (tab[i][j]) {
                case AGUA: simbolo = '0'; break;
                case NAVIO: simbolo = '3'; break;
                case HABILIDADE: simbolo = '5'; break;
                default: simbolo = '?';
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    inicializaMatriz(tabuleiro);

    // Posiciona dois navios
    int navio1_linhas[3] = {2, 2, 2};
    int navio1_colunas[3] = {1, 2, 3};
    posicionarNavio(tabuleiro, navio1_linhas, navio1_colunas);

    int navio2_linhas[3] = {6, 7, 8};
    int navio2_colunas[3] = {4, 4, 4};
    posicionarNavio(tabuleiro, navio2_linhas, navio2_colunas);

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplica habilidades no tabuleiro em pontos fixos
    aplicarHabilidade(tabuleiro, cone, 1, 5);
    aplicarHabilidade(tabuleiro, cruz, 7, 2);
    aplicarHabilidade(tabuleiro, octaedro, 4, 7);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
