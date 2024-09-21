#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definindo constantes
#define BOMB -1
#define HIDDEN 0
#define REVEALED 1

// Estrutura que representa uma célula do tabuleiro
typedef struct {
    int valor;   // Armazena o valor da célula (-1 para bomba, 0 a 8 para vizinhos)
    int estado;  // Armazena o estado da célula (0 = escondido, 1 = revelado)
} Celula;

// Estrutura que representa o tabuleiro de jogo
typedef struct {
    int linhas;
    int colunas;
    Celula **celulas; // Ponteiro para ponteiro (matriz de células)
} Tabuleiro;

// Funções principais
Tabuleiro* criarTabuleiro(int m, int n, int bombas);
void inicializarTabuleiro(Tabuleiro *tab, int bombas);
void imprimirTabuleiro(Tabuleiro *tab);
void revelarCelula(Tabuleiro *tab, int x, int y);
void revelarVizinhos(Tabuleiro *tab, int x, int y);
int contarBombasVizinhas(Tabuleiro *tab, int x, int y);
void liberarTabuleiro(Tabuleiro *tab);
void menu();

int main() {
    int m = 10, n = 10; // Tamanho do tabuleiro
    int bombas = 10;    // Número de bombas
    int x, y;           // Coordenadas do jogador
    char opcao;         // Opção do menu
    
    // Cria o tabuleiro usando ponteiros e struct
    Tabuleiro *tabuleiro = criarTabuleiro(m, n, bombas);
    menu();

    while (1) {
        // Imprime o tabuleiro
        imprimirTabuleiro(tabuleiro);

        // Recebe coordenadas do jogador
        printf("\nDigite a linha e coluna (ex: 2 b): ");
        scanf("%d %c", &x, &opcao);
        y = opcao - 'a';  // Converte letra para índice da coluna

        // Revela célula
        if (tabuleiro->celulas[x][y].valor == BOMB) {
            printf("\nVocê atingiu uma bomba! Fim de jogo.\n");
            break;
        } else {
            revelarCelula(tabuleiro, x, y);
        }
    }

    // Libera a memória do tabuleiro
    liberarTabuleiro(tabuleiro);

    return 0;
}

// Aloca memória de forma dinâmica e cria o tabuleiro.
Tabuleiro* criarTabuleiro(int m, int n, int bombas) {

     // Aloca memória para o tabuleiro
    Tabuleiro *tab = malloc(sizeof(Tabuleiro)); 
    tab->linhas = m;
    tab->colunas = n;

    // Aloca a matriz de células
    tab->celulas = (Celula**) malloc(m * sizeof(Celula*));
    for (int i = 0; i < m; i++) {
        tab->celulas[i] = (Celula*) malloc(n * sizeof(Celula));
    }

    // Inicializa o tabuleiro e coloca bombas
    inicializarTabuleiro(tab, bombas);
    return tab; // return tab permite que o tabuleiro criado seja acessado na main.
}

// Inicializa o tabuleiro e posiciona as bombas
void inicializarTabuleiro(Tabuleiro *tab, int bombas) {
    srand(time(NULL));

    // Inicializa todas as células como vazias
    for (int i = 0; i < tab->linhas; i++) {
        for (int j = 0; j < tab->colunas; j++) {
            tab->celulas[i][j].valor = 0;
            tab->celulas[i][j].estado = HIDDEN;
        }
    }

    // Posiciona as bombas aleatoriamente
    int colocadas = 0;
    while (colocadas < bombas) {
        int x = rand() % tab->linhas;
        int y = rand() % tab->colunas;

        if (tab->celulas[x][y].valor != BOMB) {
            tab->celulas[x][y].valor = BOMB;
            colocadas++;
        }
    }
}

// Imprime o tabuleiro de acordo com o estado das células
void imprimirTabuleiro(Tabuleiro *tab) {
    printf("  ");
    for (int j = 0; j < tab->colunas; j++) {
        printf("%c ", 'a' + j); // Colunas rotuladas com letras
    }
    printf("\n");

    for (int i = 0; i < tab->linhas; i++) {
        printf("%d ", i); // Linhas rotuladas com números
        for (int j = 0; j < tab->colunas; j++) {
            if (tab->celulas[i][j].estado == HIDDEN) {
                printf(". ");
            } else if (tab->celulas[i][j].valor == BOMB) {
                printf("* "); // Mostra bomba ao fim do jogo
            } else {
                printf("%d ", tab->celulas[i][j].valor);
            }
        }
        printf("\n");
    }
}

// Revela a célula e, se for vazia, revela as vizinhas recursivamente
void revelarCelula(Tabuleiro *tab, int x, int y) {
    if (x < 0 || x >= tab->linhas || y < 0 || y >= tab->colunas) return; // Fora dos limites
    if (tab->celulas[x][y].estado == REVEALED) return; // Já revelada

    int bombasVizinhas = contarBombasVizinhas(tab, x, y);
    tab->celulas[x][y].valor = bombasVizinhas;
    tab->celulas[x][y].estado = REVEALED;

    if (bombasVizinhas == 0) {
        revelarVizinhos(tab, x, y); // Recursão para revelar vizinhos vazios
    }
}

// Revela as células vizinhas de forma recursiva
void revelarVizinhos(Tabuleiro *tab, int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {  // Ignora a própria célula
                revelarCelula(tab, x + i, y + j);
            }
        }
    }
}

// Conta o número de bombas vizinhas a uma célula
int contarBombasVizinhas(Tabuleiro *tab, int x, int y) {
    int cont = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < tab->linhas && y + j >= 0 && y + j < tab->colunas) {
                if (tab->celulas[x + i][y + j].valor == BOMB) {
                    cont++;
                }
            }
        }
    }
    return cont;
}

// Libera a memória alocada para o tabuleiro
void liberarTabuleiro(Tabuleiro *tab) {
    for (int i = 0; i < tab->linhas; i++) {
        free(tab->celulas[i]);
    }
    free(tab->celulas);
    free(tab);
}

// Função para exibir o menu de opções
void menu() {
    printf("\n====== MENU ======\n");
    printf("1. Revelar célula\n");
    printf("2. Dar dica inicial\n");
    printf("3. Pausar jogo\n");
    printf("4. Continuar jogo\n");
    printf("==================\n");
}
