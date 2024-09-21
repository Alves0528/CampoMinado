#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int valor;
    int estado;

}celula;


typedef struct {
    int linha;
    int coluna;
    celula **celulas;

}tabuleiro;
 
tabuleiro *f_MemoriaTabuleiro(l, c, bombas);

int main(){
    int l, c, bombas, x, y;

    printf("Digite o tamanho do campo minado e qauntidade de bombas. Por exemplo 10x10.\n");
    printf("Linhas: ");
    scanf("%d", &l);
    printf("Colunas: ");
    scanf("%d", &c);
    printf("Bombas: ");
    scanf("%d", &bombas);

    tabuleiro *ptr_Tabuleiro = f_MemoriaTabuleiro(l, c, bombas);
   
    return 0;
}

// Aloca memória de forma dinâmica e cria o tabuleiro.
tabuleiro *f_MemoriaTabuleiro(int l, int c, int bombas){

     // Aloca memória para o tabuleiro
    tabuleiro *ptr_tab = (tabuleiro*) malloc(sizeof(tabuleiro));

    //verica se a memoria foi alocada.
    if (!ptr_tab) {
        fprintf(stderr, "Erro ao alocar memória para o tabuleiro.\n");
        exit(EXIT_FAILURE);
    }
    
    ptr_tab -> linha = l;
    ptr_tab -> coluna = c;

    //verica se a memoria foi alocada.
    if(!ptr_tab->celulas){
        printf(stderr, "Erro ao alocar memória para as celulas.\n");
        // Libera a memória.
        free(ptr_tab); 
        exit(EXIT_FAILURE);
    }

    // Aloca a matriz de células
    ptr_tab -> celulas = (celula**) malloc(l * sizeof(celula*));
    for(int i = 0; i < l; i++){
        ptr_tab->celulas[i] =(celula*) malloc(c * sizeof(celula));
    }

    // Inicializa o tabuleiro e coloca bombas
    iniciarTabuleiro(ptr_tab, bombas);  

    // Return tab permite que o tabuleiro criado seja acessado na main.
    return ptr_tab;
}

void iniciarTabuleiro(tabuleiro *ptr_tab, int bombas){
    

}