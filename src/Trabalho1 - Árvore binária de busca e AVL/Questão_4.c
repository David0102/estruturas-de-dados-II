#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Lista{//Lista das palavras traduzidas para ingles 
    	char info[100];
    	struct Lista *Prox;
};

struct Arvavl{//Arvore das palavras em portuques
    	int alt;
	char info[100];
    	struct Lista *lista;
	struct Arvavl *Dir;
	struct Arvavl *Esq;
};

struct unidade{//Estruturas para guardar as unidades e o endereco para sua arvore
    	char uni[100];
    	struct Arvavl *Avr;
};

//Prototipos das funcoes
typedef struct Arvavl Arvavl;
typedef struct Lista Lista;
typedef struct unidade unidade;
int maior(int a, int b);
int alturaNo(Arvavl *raiz);
int balanceamento(Arvavl *raiz);
Arvavl *balancear(Arvavl *raiz);
Arvavl *rotacao_dir(Arvavl *raiz);
Arvavl *rotacao_esq(Arvavl *raiz);
Arvavl *rotacao_dir_esq(Arvavl *raiz);
Arvavl *rotacao_esq_dir(Arvavl *raiz);
unidade inserir(unidade unidade, char caractere[100]);
Arvavl *cria_no_arv(char pal_port[100], char pal_ing[100]);
Lista *cria_no_list(char str[100]);
void inseri_lista(Lista **lista, Lista *NO);
int inserir_arv(Arvavl **raiz, Arvavl *no);
int ordena(char str1[100], char str2[100]);
void imprimir_palavras_uni(Arvavl *raiz);
void imprimir_lista(Lista *lista);
void ocorrencia(Lista *raiz, Arvavl *no, int *oc);
Arvavl *busca(Arvavl *raiz, char palavra[100]);
int remover1(Arvavl **raiz, char palavra[100]);
void libera_lista(Lista *lista);
void libera_arv(Arvavl *raiz);

int main(){
    int op, i = -1, j, k, cont = 0, ret;//Declaracao das variaveis
    char caractere[100], aux[100], N[100];
    FILE *file;
    unidade unidades[10];
    Arvavl *raiz;
    clock_t ini, fim;
    double t_insercao, t_busca;

    file = fopen("Entrada.txt", "r");//abre o arquivo

    if(file == NULL){
        printf("\nErro ao abrir o arquivo!\n\n");
    }else{
        do{ //Menu
            printf("\n1 - Preencher as arvores\n2 - Imprimir todas as palavras de uma unidade\n3 - Imprimir as palavras inglesas equivalentes a uma portuguesa\n4 - Remover Palavra De Uma Unidade\n0 - Sair\n");
            scanf("%d", &op);
            printf("\n");
            switch (op){
                case 0:
                    printf("Saindo!!!\n\n");
                    break;
                case 1:
                    ini = clock();//inicio da contagem do tempo
                    while(fgets(caractere, 100, file) != NULL){//Vai ate o final do arquivo linha por linha e pega até 100
                        if(caractere[0] == '%'){               //caracteres por linha e armazena na variavel caractere ou seja,
                            k = 0;                             //caractere sera uma string com todo o conteudo de uma linha.
                            for(j = 1;caractere[j] != '\0';j++){
                                aux[k] = caractere[j];//armazena a unidade sem o %
                                k++;
                            }
                            aux[k-1] = '\0';

                            i++;
                            strcpy(unidades[i].uni, aux);//Pega a unidade sem o % e armazena na estrutura das unidades
                            unidades[i].Avr = NULL;//inicializa a arvore da unidade
                        }else{
                            unidades[i] = inserir(unidades[i], caractere);//se nao for uma unidade preenche a arvore daquela unidade.
                        }
                    }
                    fim = clock();//fim da contagem

                    t_insercao = (double)(fim - ini) / CLOCKS_PER_SEC;

                    printf("\nTEMPO DE INSERCAO: %lf Segundos\n", t_insercao);
                    break;
                case 2:
                    printf("Informe a Unidade: ");
                    scanf(" %99[^\n]", N);
                    
                    cont = 0;
                    for(j = 0;j <= i;j++){//percorre todas as unidades 
                        if(strcmp(N, unidades[j].uni) == 0){//verifica se a unidade dada existe
                            cont = 1;
                            printf("\nArvore de palavras da unidade %s\n\n", unidades[j].uni);
                            imprimir_palavras_uni(unidades[j].Avr);//imprime todas as palavras da arvore passada por parametro
                        }
                    }
                    if(cont == 0){
                        printf("\nUnidade nao cadastrada!\n");
                    }
                    break;
                case 3:
                    printf("Informe a palavra em portuques: ");
                    scanf("%s", N);

                    ini = clock();//inicio da contagem do tempo
                    cont = 0;
                    for(j = 0;j <= i;j++){
                        raiz = busca(unidades[j].Avr, N);//busca a palavra se encontrar retorna o endereco da arvore
                        if(raiz != NULL){
                            cont = 1;
                            printf("\nTraducao em ingles encontrada na unidade %s: ", unidades[j].uni);
                            imprimir_lista(raiz->lista);//passa o endereco da lista que esta armazenado na arvore que foi encontrada na busca
                        }
                    }
                    if(cont == 0){
                        printf("\nPalavra nao encontrada em nenhuma unidade cadastrada!");
                    }
                    printf("\n");
                    fim = clock();//fim da contagem

                    t_busca = (double)(fim - ini) / CLOCKS_PER_SEC;

                    printf("\nTEMPO DE BUSCA: %lf Segundos\n", t_busca);
                    break;
                case 4:
                    //setbuf(stdin, NULL);
                    printf("Informe uma palavra em portuques que deseja remover: ");
                    scanf("%s", N);
                    //setbuf(stdin, NULL);
                    printf("\n");
                    cont = 0;
                    for(j = 0;j <= i;j++){
                        ret = remover1(&(unidades[j].Avr), N);//funcao para remover uma palavra em portugues e suas equivalencias em ingles
                        if(ret == 1){
                            cont = 1;
                            printf("Palavra '%s' removida da unidade %s\n", N, unidades[j].uni);
                        }

                    }
                    if(cont == 0){
                        printf("Nao foi encontrada essa palavra em nenhuma unidade!\n");
                    }
                    break;
                default:
                    printf("Digite uma opcao valida!\n");
                    break;
            }
        }while(op != 0);
    }
    for(j = 0;j <= i;j++){
        libera_arv(unidades[j].Avr);
    }
    fclose(file);
    return 0;
}

int maior(int a, int b){
    if(a > b){
        b = a;
    }
    return b;
}

int alturaNo(Arvavl *raiz){
    int alt;
    if(raiz == NULL){
        alt = -1;
    }else{
        alt = raiz->alt;
    }
    return alt;
}

int balanceamento(Arvavl *raiz){
    int retorno;
    if(raiz == NULL){
        retorno = 0;
    }else{
        retorno = alturaNo(raiz->Esq) - alturaNo(raiz->Dir);
    }
    return retorno;
}

Arvavl *balancear(Arvavl *raiz){
    int fb;
    fb = balanceamento(raiz);
    //rotação esquerda
    if(fb < -1 && balanceamento(raiz->Dir) <= 0){
        raiz = rotacao_esq(raiz);
    }
    //rotação a direita
    else if(fb > 1 && balanceamento(raiz->Esq) >= 0){
        raiz = rotacao_dir(raiz);
    }
    //rotação esquerda direita
    else if(fb > 1 && balanceamento(raiz->Esq) < 0){
        raiz = rotacao_esq_dir(raiz);
    }
    //rotação direita esquerda
    else if(fb < -1 && balanceamento(raiz->Dir) > 0){
        raiz = rotacao_dir_esq(raiz);
    }
    return raiz;
}

Arvavl *rotacao_dir(Arvavl *raiz){
    Arvavl *filho, *temp;
    filho = raiz->Esq;
    temp = filho->Dir;
    filho->Dir = raiz;
    raiz->Esq = temp;

    raiz->alt = maior(alturaNo(raiz->Esq), alturaNo(raiz->Dir)) + 1;
    filho->alt = maior(alturaNo(filho->Esq), alturaNo(filho->Dir)) + 1;
    return filho;
}

Arvavl *rotacao_esq(Arvavl *raiz){
    Arvavl *filho, *temp;
    filho = raiz->Dir;
    temp = filho->Esq;
    filho->Esq = raiz;
    raiz->Dir = temp;

    raiz->alt = maior(alturaNo(raiz->Esq), alturaNo(raiz->Dir)) + 1;
    filho->alt = maior(alturaNo(filho->Esq), alturaNo(filho->Dir)) + 1;
    return filho;
}

Arvavl *rotacao_dir_esq(Arvavl *raiz){
    raiz->Dir = rotacao_dir(raiz->Dir);
    raiz = rotacao_esq(raiz);
    return raiz;
}

Arvavl *rotacao_esq_dir(Arvavl *raiz){
    raiz->Esq = rotacao_esq(raiz->Esq);
    raiz = rotacao_dir(raiz);
    return raiz;
}

unidade inserir(unidade uni, char palavra[100]){//funcao que faz o tratamento das strings e insere os dados na arvore
    Arvavl *no;
    int i, j, retorno;
    char pal_port[100], pal_ing[100];

    j = 0;
    for(i = 0; palavra[i] != ':'; i++){//pega a palavra em ingles
        pal_ing[j] = palavra[i];
        j++;
    }

    pal_ing[j] = '\0';//coloca o terminador na string

    j = 0;
    for(i = i + 1; palavra[i] != '\0'; i++){//pega as traduções em portuques
        pal_port[j] = palavra[i];
        j++;
        if(palavra[i] == ',' || palavra[i] == '.' || palavra[i] == '\0'){//verificacao para saber dividir as traducoes em portuques
            pal_port[j-1] = '\0';
            no = cria_no_arv(pal_port, pal_ing);//criar o no da arvore
            retorno = inserir_arv(&uni.Avr, no);//insere o no criado na arvore da respectiva unidade
            j = 0;//zera o contador para iniciar o tratamento de outra palavra
            if(!retorno){
                printf("Palavra '%s' Nao Inserida, palavra ja foi inserida na unidade %s\n", pal_port, uni.uni);
            }
        }
    }

    return uni;//retorna a unidade ja com a arvore preenchida
}

Arvavl *cria_no_arv(char pal_port[100], char pal_ing[100]){//cria o no da arvore
    Lista *No, *lista;
    lista = NULL;

    Arvavl *no = (Arvavl*)malloc(sizeof(Arvavl));//parte de alocar o no da arvore
    strcpy(no->info, pal_port);
    no->alt = 0;
    no->Dir = NULL;
    no->Esq = NULL;

    No = cria_no_list(pal_ing);//cria o no da lista
    inseri_lista(&lista, No);//funcao para inserir no criado na lista

    no->lista = lista;//o ponteiro da arvore recebe o endereco da lista já criada
    return no;
}

Lista *cria_no_list(char str[100]){//criar no da lista
    Lista *No = (Lista*)malloc(sizeof(Lista));//aloca no da lista
    strcpy(No->info, str);
    No->Prox = NULL;
    return No;//retorna o no
}

void inseri_lista(Lista **lista, Lista *NO){//funcao de inserir na lista
    if(*lista == NULL){
        *lista = NO;//se for nullo insere
    }else{
        inseri_lista(&(*lista)->Prox, NO);//percorre toda a lista e insere no final
    }
}

int inserir_arv(Arvavl **raiz, Arvavl *no){//insere na arvore
    Lista *NO;
    int inseriu = 0, oc;
    if(*raiz == NULL){
        *raiz = no;//insere na arvore quando for nullo, ou seja, em um endereco sem ninguem
        inseriu = 1;
    }else{
        if(ordena(no->info, (*raiz)->info) == -1){//verifica qual palavra ocorre primeiro em ordem alfabetica
            inseriu = inserir_arv(&((*raiz)->Esq), no);//ou seja, qual palavra é maior ou menor
        }else if(ordena(no->info, (*raiz)->info) == 1){//fazendo isso chamando a funcao ordena que faz isso
            inseriu = inserir_arv(&((*raiz)->Dir), no);
        }else{//se a palavra em portugues já existe verifica se a sua tradução é diferente da 
            oc = 0;//que já existe, e adiciona a nova tradução da palavra a lista
            ocorrencia((*raiz)->lista, no, &oc);//funcao para verifica na lista se já existe uma traducao
            if(oc == 0){                        //em ingles 
                NO = cria_no_list(no->lista->info);//cria no da lista
                inseri_lista(&((*raiz)->lista), NO);//funcao para inserir no criado na lista
            }
        }
    }
    (*raiz)->alt = maior(alturaNo((*raiz)->Esq), alturaNo((*raiz)->Dir)) + 1;
    *raiz = balancear(*raiz);
    return inseriu;
}

int ordena(char str1[100], char str2[100]){//função que verifica a ocorrencia de duas palavras
    int r, ret;                             //ou seja qual a que vem primeiro em ordem alfabetica
    r = strcmp(str1, str2);
    if(r == -1){//string 1 e menor que string 2, ou seja, string 1 vem que antes string 2
        ret = -1;
    }else if(r == 1){//string 1 e maior que string 2, ou seja, string 1 vem que depois string 2
        ret = 1;
    }else{//string 1 e igual que string 2
        ret = 0;
    }
    return ret;
}

void imprimir_palavras_uni(Arvavl *raiz){//funcao de imprimir as palavras em portuques e suas traducoes  
    if(raiz != NULL){                    //em ingles
        imprimir_palavras_uni(raiz->Esq);//imprime in-ordem
        printf("- Palavra em Portuques: %s\n", raiz->info);//palavra em portugues
        printf("- Sua traducao para ingles: ");
        imprimir_lista(raiz->lista);//imprime lista de traducoes em ingles
        printf("\n\n");
        imprimir_palavras_uni(raiz->Dir);
    }
}

void imprimir_lista(Lista *lista){//imprime a lista
    if(lista != NULL){//imprime a palavra e vai adiante imprimindo as proximas até o final da lista
        if(lista->Prox == NULL){
            printf("%s", lista->info);//se for a ultima palavra nao imprime a virgula
        }else{
            printf("%s, ", lista->info);//se nao for a ultima palavra imprime a virgula
        }
        imprimir_lista(lista->Prox);//vai até o final da lista
    } 
    //printf("\n");
}

void ocorrencia(Lista *raiz, Arvavl *no, int *oc){
    if(raiz != NULL){
        if(strcmp(raiz->info, no->lista->info) == 0){//verifica se a palavra já existe na lista
            *oc = 1;//controla se a palavra existe ou nao, ou seja, se nao existir o oc continua sendo 0
        }           //o que indica que a palavra nao existe na lista e a insere, caso contrario ela nao e inserida
        ocorrencia(raiz->Prox, no, oc);//percorre a lista ate o final
    }
}

Arvavl *busca(Arvavl *raiz, char palavra[100]){//funcao de buscar uma palavra na arvore
    Arvavl *ret;
    if(raiz == NULL){
        ret = NULL;//se for nullo nao existe essa palavra na arvore e retorna nullo
    }else{
        if(ordena(palavra, raiz->info) == -1){//verifica se a palavra e menor que a raiz, se for percorre a esquerda da arvore
            ret = busca(raiz->Esq, palavra);//percorre esquerda da arvore
        }else if(ordena(palavra, raiz->info) == 1){//verifica se a palavra e maior que a raiz, se for percorre a direita da arvore
            ret = busca(raiz->Dir, palavra);//percorre direita da arvore
        }else{//se não e porque e igual entao retorna o endereco do no onde a palavra esta
            ret = raiz;
        }
    }
    return ret;
}

int remover1(Arvavl **raiz, char palavra[100]){//funcao para remover uma palavra a suas equivalencias em ingles
    int removeu = 0;
    if(*raiz == NULL){
        removeu = 2;//se for nullo não existe na arvore
    }else{
        if(ordena(palavra, (*raiz)->info) == -1){//verifica se a palavra e menor que a raiz, se for percorre a esquerda da arvore
            removeu = remover1(&((*raiz)->Esq), palavra);//percorre a esquerda da arvore
        }else if(ordena(palavra, (*raiz)->info) == 1){//verifica se a palavra e maior que a raiz, se for percorre a direita da arvore
            removeu = remover1(&((*raiz)->Dir), palavra);//percorre a direita da arvore
        }else{//se não é por que é igual entao o no da palavra foi encontrado
            if((*raiz)->Esq == NULL && (*raiz)->Dir == NULL){//remove no folha
                Arvavl *aux;
                aux = *raiz;
				*raiz = NULL;
                libera_lista(aux->lista);//chama a funcao de liberar a memoria da lista antes de liberar o no
                free(aux);//liberar o no onde a palavra esta
				removeu = 1;
			}else{
				/*Remover no com dois filhos*/
				if((*raiz)->Esq != NULL && (*raiz)->Dir != NULL){
					Arvavl *aux = (*raiz)->Esq;//recebe a esquerda, entao procurado o maior no da direita da esquerda
                    Lista *aux1;
					while(aux->Dir != NULL){//procura o maior no para ser trocado com o no atual
						aux = aux->Dir;
					}

        //troca as palavras e o endereco das lista do no a ser removido com o no que vai subistituir seu lugar
                    strcpy((*raiz)->info, aux->info);
                    aux1 = (*raiz)->lista;
                    (*raiz)->lista = aux->lista;
                    strcpy(aux->info, palavra);
                    aux->lista = aux1;
    //chama a funcao passando a esquerda(onde o no a ser removido estara) para ser procurado e removido
					removeu = remover1(&((*raiz)->Esq), palavra);
				}else{
					/*Remover no com um filho*/
					Arvavl *aux = *raiz;
					if((*raiz)->Esq != NULL){
						*raiz = (*raiz)->Esq;
					}else{
						*raiz = (*raiz)->Dir;
					}
                    libera_lista(aux->lista);
					free(aux);
					removeu = 1;
				}
			}
        }
    }
    if(*raiz != NULL){
        //recalcula a altura de todos os nos da arvore
        (*raiz)->alt = maior(alturaNo((*raiz)->Esq), alturaNo((*raiz)->Dir)) + 1;
        
        //função responsavel por verificar a necessidade de balancear a arvore
        *raiz = balancear(*raiz);
    }
    return removeu;
}

void libera_lista(Lista *lista){//funcao para liberar a memoria da lista
    if(lista != NULL){
        libera_lista(lista->Prox);//vai ate o final da lista e depois volta liberando a memoria
        free(lista);//libera a memoria
    }
}

void libera_arv(Arvavl *raiz){//funcao para liberar a memoria alocada de de uma arvore
    if(raiz != NULL){//percorre toda a arvore e libera a memoria quando achar um o folha
        libera_arv(raiz->Esq);
        libera_arv(raiz->Dir);
        libera_lista(raiz->lista);//libera a memoria da lista que a arvore armazena
        free(raiz);//libera o no
    }
}

