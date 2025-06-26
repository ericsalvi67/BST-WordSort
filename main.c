#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct no{
    char palavra[20];
    int repeticoes;
    struct no* esq;
    struct no* dir;
} No;

// --------------------------------------------------------------------------------
//FUNCOES
No* novoNo(char palavra[20]) {
    No* no = (No*) malloc(sizeof(No));
    strcpy(no->palavra, palavra);
    no->repeticoes = 1;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

No* rotacaoEsquerda(No* arvore) {
    No* aux = arvore->dir;
    arvore->dir = aux->esq;
    aux->esq = arvore;
    return aux;
}
No* rotacaoDireita(No* arvore) {
    No* aux = arvore->esq;
    arvore->esq = aux->dir;
    aux->dir = arvore;
    return aux;
}
No* rotacaoDuplaEsquerda(No* arvore) {
    arvore->dir = rotacaoDireita(arvore->dir);
    arvore = rotacaoEsquerda(arvore);
    return arvore;
}
No* rotacaoDuplaDireita(No* arvore) {
    arvore->esq = rotacaoEsquerda(arvore->esq);
    arvore =  rotacaoDireita(arvore);
    return arvore;
}

int altura(No* arvore) {
    if (arvore == NULL) return 0;
    int he = altura(arvore->esq);
    int hd = altura(arvore->dir);
    return (he > hd ? he : hd) + 1;
}

No* balancearAVL(No* arvore) {
    if (!arvore) return NULL;

    int fb = altura(arvore->esq) - altura(arvore->dir);

    if (fb > 1) {
        int fbe = altura(arvore->esq->esq) - altura(arvore->esq->dir);
        if (fbe >= 0)
            return rotacaoDireita(arvore);
        else
            return rotacaoDuplaDireita(arvore);
    }

    if (fb < -1) {
        int fbd = altura(arvore->dir->esq) - altura(arvore->dir->dir);
        if (fbd <= 0)
            return rotacaoEsquerda(arvore);
        else
            return rotacaoDuplaEsquerda(arvore);
    }

    return arvore;
}

 // --------------------------------------------------------------------------------
 //ESQUERDA
void posOrdemE(No* a){
  if (a!= NULL){
      posOrdemE(a->esq);
      posOrdemE(a->dir);
      printf("%s ",a->palavra);
  }
}

void centralE(No* a){
  if (a!= NULL){
      centralE(a->esq);
      printf("%s ",a->palavra);
      centralE(a->dir);
  }
}

void preOrdemE(No* a){
  if (a!= NULL){
      printf("%s ",a->palavra);
      preOrdemE(a->esq);
      preOrdemE(a->dir);
  }
}
 // --------------------------------------------------------------------------------
 //DIREITA

void posOrdemD(No* a){
  if (a!= NULL){
      posOrdemD(a->dir);
      posOrdemD(a->esq);
      printf("%s ",a->palavra);
  }
}

void centralD(No* a){
  if (a!= NULL){
      centralD(a->dir);
      printf("%s ",a->palavra);
      centralD(a->esq);
  }
}

void preOrdemD(No* a){
  if (a!= NULL){
      printf("%s ",a->palavra);
      preOrdemD(a->dir);
      preOrdemD(a->esq);
  }
}
// --------------------------------------------------------------------------------


// conta quantas palavras existem
int contaPalavrasDistintas(No* a) {
    if (a == NULL)
        return 0;

    return 1 + contaPalavrasDistintas(a->esq) + contaPalavrasDistintas(a->dir);
}

// percorre a arvore e soma o total de palavras
int contaTotalPalavras(No* arvore[26]){
    int total = 0, i;
    for(i=0; i<26; i++){
        total += contaPalavrasDistintas(arvore[i]);
    }
    return total;
}

////////////////////////////////

// soma quantas vezes cada palavra aparece
int contaOcorrencias(No* a){
    if(a == NULL){
        return 0;
    }
    // nó atual + da esquerda + da direita
    return a->repeticoes + contaOcorrencias(a->esq) + contaOcorrencias(a->dir);
}

// percorre a arvore e soma cada ocorrencia de palavra
int contaTotalOcorrencias(No* arvore[26]){
    int total = 0, i;
    for(i=0; i<26; i++){
        total += contaOcorrencias(arvore[i]);
    }
    return total;
}

////////////////////////////////

// encontra palavras com maior numero de ocorrencias
void buscaMaiorOcorrencia(No* a, int* maior, char palavras[][20], int* count){
    if(a == NULL){
        return;
    }

    buscaMaiorOcorrencia(a->esq, maior, palavras, count);  // filho esquerdo

    if(a->repeticoes > *maior){
        // encontrou, zera e começa dnv
        *maior = a->repeticoes;
        *count = 0;
        strcpy(palavras[*count], a->palavra);
        (*count)++;
    }else if(a->repeticoes == *maior){
        // mesma ocorrencia, adiciona palavra a lista
        strcpy(palavras[*count], a->palavra);
        (*count)++;
    }

    buscaMaiorOcorrencia(a->dir, maior, palavras, count);  // filho direito
}


// percorre e imprime as palavras com maior numero de ocorrencias
void maiorOcorrencia(No* arvore[26]){
    int maior = 0, count = 0, i;  // maior qtd de repeticoes - count de palavras
    char palavras[100][20];  // limite de 100 palavras

    for(i=0; i<26; i++){
        buscaMaiorOcorrencia(arvore[i], &maior, palavras, &count);
    }

    if(maior == 0){
        printf("\nNenhuma palavra encontrada.\n");
        return;
    }

    printf("\nMaior numero de ocorrencias: %d\n", maior);
    printf("Palavra(s): ");
    for(i=0; i<count; i++){
        printf("%s ", palavras[i]);
    }
    printf("\n");
}

////////////////////////////////

// percorre e imprime 1 ocorrencia
void exibeUmaOcorrencia(No* a){
    if(a == NULL){
        return;
    }

    exibeUmaOcorrencia(a->esq);  // filho esquerdo

    if(a->repeticoes == 1){
        // se aparece uma vez, imprime
        printf("%s ", a->palavra);
    
    }

    exibeUmaOcorrencia(a->dir);  // filho direito
}


// percorre a arvore e imprime 1 ocorrencia
void umaOcorrencia(No* arvore[26]){
    int encontrou = 0, i;
    printf("\nPalavras com apenas uma ocorrencia:\n");

    for(i=0; i<26; i++){
        if(arvore[i] != NULL){
            exibeUmaOcorrencia(arvore[i]);
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhuma palavra com uma ocorrencia encontrada.\n");
    }

}

// --------------------------------------------------------------------------------

No* insereFolha(No* arvore, char palavra[20]) {

    if (!arvore){
        arvore = novoNo(palavra);
        return arvore;
    }
    
    No* aux = arvore;
    No* pai = NULL;

    while (aux != NULL){
        pai = aux;
        if (strcmp(palavra, aux->palavra) == 0){
            aux->repeticoes++;
            printf("-> '%s' ja existe na arvore.\n", palavra);
            return arvore;
        }
        if (strcmp(palavra, aux->palavra) < 0){
            aux = aux->esq;
        }
        else{
            aux = aux->dir;
        }
    }

    if (strcmp(palavra, pai->palavra) < 0){
        pai->esq = novoNo(palavra);
    }
    else{
        pai->dir = novoNo(palavra);
    }

    printf("Palavra '%s' inserida na arvore.\n", palavra);
    return balancearAVL(arvore);
}

No* removeFolha(No* arvore, char palavra[20]) {
    if (arvore == NULL) return NULL;

    if (strcmp(palavra, arvore->palavra) < 0) {
        arvore->esq = removeFolha(arvore->esq, palavra);
    } 
    else if (strcmp(palavra, arvore->palavra) > 0) {
        arvore->dir = removeFolha(arvore->dir, palavra);
    } 
    
    else {
        if (arvore->repeticoes > 1) {
            arvore->repeticoes--;
            return arvore;
        }
        if (arvore->esq == NULL && arvore->dir == NULL) {
            // Folha
            free(arvore);
            return NULL;
        } 
        else if (arvore->esq == NULL) {
            No* temp = arvore->dir;
            free(arvore);
            return temp;
        } 
        else if (arvore->dir == NULL) {
            No* temp = arvore->esq;
            free(arvore);
            return temp;
        } 
        else {
            // Dois filhos
            No* sucessor = arvore->dir;
            while (sucessor->esq != NULL) {
                sucessor = sucessor->esq;
            }
            strcpy(arvore->palavra, sucessor->palavra);
            arvore->dir = removeFolha(arvore->dir, sucessor->palavra);
        }
    }

    return balancearAVL(arvore);
}

int pesquisaFolha(No* arvore, char palavra[20]) {
    int cmp;

    if (arvore != NULL) {
        cmp = strcmp(arvore->palavra, palavra);
        if(cmp == 0)
            return arvore->repeticoes;
        else if (cmp > 0)
            return pesquisaFolha(arvore->esq, palavra);
        else
            return pesquisaFolha(arvore->dir, palavra);
    }

    return 0;
}
// --------------------------------------------------------------------------------
//GERAIS
char* strToLower(char palavra[20]) {
    for (int i = 0; palavra[i]; i++)
        palavra[i] = tolower((unsigned char)palavra[i]);

    return palavra;
}

void exibePalavra(No* arvore) {
    
    if (arvore != NULL) {
        printf("Palavras iniciadas com '%c': ", arvore->palavra[0]);
        centralE(arvore);
        printf("\n");
    }
}

// --------------------------------------------------------------------------------
//MENUS

void menuOcorrencia(No* arvore[26], int opcao){

    switch(opcao){
        case 1:
            printf("\n--------------------------------");
            maiorOcorrencia(arvore);
            printf("--------------------------------");
            break;
        case 2:
            printf("\n-------------------------");
            umaOcorrencia(arvore);
            printf("\n-------------------------");
            break;
    }

}

void menuContagem(No* arvore[26], int opcao){
    int resultado;

    switch(opcao){
        case 1:
            resultado = contaTotalPalavras(arvore);
            printf("\n--------------------------------");
            printf("\nTotal de palavras distintas: %d\n", resultado);
            printf("--------------------------------");
            break;
        case 2:
            resultado = contaTotalOcorrencias(arvore);
            printf("\n-------------------------");
            printf("\nTotal de ocorrencias: %d\n", resultado);
            printf("-------------------------");
            break;
    }

}

void menuOrd(No* arvore[26], int opcao) {
    int ordem;
    char letra;
    int i;

    if(opcao == 2) {
        printf("\nDigite a letra inicial: ");
        scanf(" %c", &letra);
        letra = tolower(letra);
    }
    do {
        printf("\nOrdem a ser exibida 1-Alfabetica / 2-Alfabetica inversa: ");
        scanf("%d", &ordem);
    } while (ordem < 1 || ordem > 2);

    switch(opcao)
    {
        case 1:
            if(ordem == 1) {
                for(i=0 ; i < 26; i++) {
                    if(arvore[i] != NULL){
                        printf("Palavras iniciadas com '%c': ", 'a' + i);
                        centralE(arvore[i]);
                        printf("\n");
                    }
                }
            } else {
                for(i=25 ; i >= 0; i--) {
                    if(arvore[i] != NULL) {
                        printf("Palavras iniciadas com '%c': ", 'a' + i);
                        centralD(arvore[i]);
                        printf("\n");
                    }
                }
            }
            break;
        case 2:
            if(ordem == 1)
                centralE(arvore[letra - 'a']);
            else
                centralD(arvore[letra - 'a']);
            break;
    }
    
}

void menuCRUD(No* arvore[26], int opcao) {
    char* crud[] = {"inserida", "removida", "pesquisada"};
    char palavra[20];
    int soma;

    printf("\nDigite a palavra a ser %s: ", crud[opcao-1]);
    scanf("%s", palavra);
    strToLower(palavra);
    int index = palavra[0] - 'a';

    switch (opcao) {
        case 1:
            arvore[index] = insereFolha(arvore[index], palavra);
            break;
        case 2:
            arvore[index] = removeFolha(arvore[index], palavra);
            break;
        case 3: 
            soma = 0;
            soma = pesquisaFolha(arvore[index], palavra);
            if(soma != 0) {
                printf("Palavra '%s' encontrado na arvore -> % 2d vezes(s)", palavra, soma);
            } else {
                printf("Palavra '%s' nao encontrada na arvore.", palavra);
            }
            break;
    }

}

void menu(No* arvore[26]) {
    int opcao;

    do {
        printf("Menu de Opcoes:\n");
        printf("1. Insere folha\n");
        printf("2. Remove folha\n");
        printf("3. Pesquisa folha\n");
        printf("4. Conta total de palavras\n"); // retorna o numero total de palavras (distintas); 
        printf("5. Conta total de ocorrencias\n"); // retorna o numero total de ocorrencias de palavras (repetidas tb);
        printf("6. Exibe lista de palavras\n");
        printf("7. Exibe lista de palavras por letra\n");
        printf("8. Exibe maior ocorrencia\n"); // retorna as palavras com maior numero de ocorrencias
        printf("9. Exibe uma ocorrencia\n"); // retorna as paalvras que so tem uma ocorrencia
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuCRUD(arvore, 1);
                break;
            case 2:
                menuCRUD(arvore, 2);
                break;
            case 3:
                menuCRUD(arvore, 3);
                break;
            case 4:
                menuContagem(arvore, 1);
                break;
            case 5:
                menuContagem(arvore, 2);
                break;
            case 6:
                menuOrd(arvore, 1);
                break;
            case 7:
                menuOrd(arvore, 2);
                break;
            case 8:
                menuOcorrencia(arvore, 1);
                break;
            case 9:
                menuOcorrencia(arvore, 2);
                break;
            case 0:
                exit(0);
            default:
                printf("\nOpcao invalida!\n");
        }
        printf("\n\n");
    } while (opcao != 0);
}

// --------------------------------------------------------------------------------
void dBinsert(No* arvore[26]) {

   FILE *file;
   char palavra[20];
   int index;

   file = fopen("..\\input.txt", "r");
   if(!file) {
      printf("Erro ao abrir o arquivo!\n");
      return;
   }

   fseek(file, 0, SEEK_SET);

   while (fscanf(file, "%s", palavra) == 1) {
        strToLower(palavra);
        index = palavra[0] - 'a';
        arvore[index] = insereFolha(arvore[index], palavra);
    }

    printf("Todas as palavras do arquivo foram inseridas.\n\n");
    fclose(file);
}

//--------------------------------------------------------------------------------
int main() {

    No* arvore[26] = {NULL};

    dBinsert(arvore);
    menu(arvore);

    return 0;
}