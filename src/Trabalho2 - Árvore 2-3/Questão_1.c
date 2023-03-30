#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Tam_bloco;

struct Bloco
{
    int Bloco_I, Bloco_F;
    char status;
};

struct Arv23
{
    struct Bloco info1, info2;
    int Ninfos;
    struct Arv23 *Esq, *Cen, *Dir;
};

typedef struct Bloco Bloco;
typedef struct Arv23 Arv23;
Arv23 *criaNo(Bloco valor, Arv23 *filho_esq, Arv23 *filho_cen, Arv23 *filho_dir);
int ehFolha(Arv23 *raiz);
Arv23 *adicionaChave(Arv23 *raiz, Bloco valor, Arv23 *ptr);
Arv23 *quebraNo(Arv23 *raiz, Bloco valor, Bloco *promove, Arv23 *ptr);
Arv23 *insere(Arv23 **raiz, Bloco valor, Bloco *promove, Arv23 **pai);
void imprimir(Arv23 *raiz);
void Cadastra(Arv23 **raiz, int *vet);
void AlocaEspacos(Arv23 **raiz, int Qtd);
Bloco ProcuraEspaco(Arv23 **raiz, int Qtd, Arv23 **pai, Arv23 **RAIZAvr, int *ptr);
int remover(Arv23 **raiz, Arv23 **pai, int valor);
int balancear(Arv23 **raiz, Arv23 **pai, int removeu);
int removeInfo2Folha(Arv23 *raiz);
int removeInfo2ComDirFolha(Arv23 *raiz, Arv23 *pai);
Arv23 *obterMenorNo(Arv23 *raiz);
int numeroInfosArv(Arv23 *raiz);
Arv23 *obterMaiorNo(Arv23 *raiz);
int removeInfo2NaoFolha(Arv23 *raiz);
int removeInfo1Folha(Arv23 *raiz, Arv23 *pai);
int removeInfo1NaoFolha(Arv23 *raiz);
Arv23 *busca1(Arv23 **raiz, int info);
int buscar(Arv23 *raiz, int valor);

int main()
{
    Arv23 *raiz = NULL;
    int op, Qtd, vet[30], aux;
    clock_t ini, fim;
    double t_busca, t_alterar;

    Cadastra(&raiz, vet);
    printf("\nCadastro Finalizado!\n\n");
    system("pause");
    system("cls");

    do
    {
        printf("\n---- Menu ----\n1 - Alocar Nos\n2 - Remover blocos\n3 - Imprimir\n4 - Buscar nos\n0 - Sair\n");
        scanf("%d", &op);
        printf("\n");
        switch (op)
        {
        case 0:
            printf("Saindo!!!\n\n");
            break;
        case 1:
            // system("cls");
            printf("Alocar Nos\n");
            printf("\nDigite a quantidade de blocos que voce deseja alocar: ");
            scanf("%d", &Qtd);

            while (Qtd <= 0)
            {
                printf("\nDigite uma quantidade de blocos valida, maior que zero: ");
                scanf("%d", &Qtd);
            }

            ini = clock();
            AlocaEspacos(&raiz, Qtd);
            fim = clock();

            t_alterar = (double)(fim - ini) / CLOCKS_PER_SEC;

            printf("Tempo de alocacao dos blocos: %.6f\n", t_alterar);
            break;
        case 2:
            // system("cls");
            printf("Remover blocos\n");
            break;
        case 3:
            // system("cls");
            printf("Imprimindo blocos(Nos)\n");
            imprimir(raiz);
            break;
        case 4:
            ini = clock();
            for (int i = 0; i < 30; i++)
            {
                aux = buscar(raiz, vet[i]);

                if (aux == 1)
                {
                    printf("Bloco com final igual a %d encontrado\n", vet[i]);
                }
                else
                {
                    printf("Bloco com final igual a %d nao foi encontrado\n", vet[i]);
                }
            }
            fim = clock();
            t_busca = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("Tempo medio de busca: %.6f\n", t_busca / 30);
            break;
        default:
            printf("Digite uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    return 0;
}

Arv23 *criaNo(Bloco valor, Arv23 *filho_esq, Arv23 *filho_cen, Arv23 *filho_dir)
{
    Arv23 *no;

    no = (Arv23 *)malloc(sizeof(Arv23)); // Aloca o novo no

    if (no != NULL)
    {
        no->info1 = valor;
        // no->info2 = ;      //Tudo vai depender de onde a funcao esta sendo chamada, se foi chamada a partir de um no folha ou nao
        no->Ninfos = 1;
        no->Esq = filho_esq; // Os ponteiros do novo no, recebem os enderecos dos filhos do no raiz
        no->Cen = filho_cen; // caso o no raiz nao seja folha, ou seja, como o no esta sendo criado no meio da
        no->Dir = filho_dir; // arvore, ele vai receber os enderecos dos nos que estao abaixo dele na arvore
    }                        // seguindo as regras da arvore2-3, ja se ele e folha, os enderecos dos filhos da
                             // raiz sao nulos, entao, os filhos do novo no apontarao para nulo

    return no; // retorna o novo no
}

int ehFolha(Arv23 *raiz)
{ // verifica se o no e folha
    int ehfolha;
    if (raiz->Esq == NULL)
    { // se a esquerda for nula, significa que o no e folha, pois como nao tem esq, nao tera centro, nem direita
        ehfolha = 1;
    }
    else
    {
        ehfolha = 0;
    }
    return ehfolha; // retorna 1 se for folha e 0 se nao for
}

Arv23 *adicionaChave(Arv23 *raiz, Bloco valor, Arv23 *ptr)
{ // adiciona ao no com 1 elemento outo elemento
    if (valor.Bloco_F > raiz->info1.Bloco_F)
    { // se o valor e maior que o primeiro so o adiciona na segunda info
        raiz->info2 = valor;
        raiz->Dir = ptr;  // se for um no folha a direita desse no recebe nulo, se nao, recebe o endereco do no criado quando um filho da raiz fez uma quebra de no
        raiz->Ninfos = 2; // adiciona 2 para saber que o no esta cheio
    }
    else
    { // se nao troca os valores, info1 recebe o valor e info2 recebe info1
        raiz->info2 = raiz->info1;
        raiz->info1 = valor;
        raiz->Dir = raiz->Cen; // se for folha, recebe nulo, se nao, recebe o endereco do filho do centro, pois como os valores do centro eram maiores que a info1 antes da troca, eles devem ir para a dir da raiz pois são maiores que info2 que era a info1
        raiz->Cen = ptr;       // se for um no folha, o centro recebe nulo, se nao, recebe o novo no que foi criado quando o filho da raiz foi quebrado
        raiz->Ninfos = 2;
    }
    return raiz; // retorna a raiz ja com as alteracoes que foram necessarias
}

Arv23 *quebraNo(Arv23 *raiz, Bloco valor, Bloco *promove, Arv23 *ptr)
{ // Quebra o no raiz, e retorna um novo no
    Arv23 *novo;
    // na chamada da funcao criaNo, sempre sera passado NULL para a direita, ja que quando um no e criado a direita dele e sempre nula
    if (raiz->info1.Bloco_F > valor.Bloco_F)
    {
        *promove = raiz->info1;                                 // a info1 esta no meio da info2 e o valor
        novo = criaNo(raiz->info2, raiz->Cen, raiz->Dir, NULL); // sera passado o centro como raiz esq, ja que todos os elementos do centro são menores que info2 e sera passado raiz dir para o centro, ja que todos os elementos da direita sao maiores que a info2
        raiz->info1 = valor;
        raiz->Cen = ptr; // se for um no folha, o centro recebe nulo, se nao, recebe o novo no que foi criado quando o filho da raiz foi quebrado
    }
    else
    {
        if (raiz->info2.Bloco_F > valor.Bloco_F)
        {
            *promove = valor;                                 // a valor esta no meio da info2 e da info1
            novo = criaNo(raiz->info2, ptr, raiz->Dir, NULL); // sera passado o MaiorNo como raiz esq, ja que todos os elementos do MaiorNo são menores que info2 e sera passado raiz dir para o centro, ja que todos os elementos da direita sao maiores que a info2
        }
        else
        {
            *promove = raiz->info2;                     // a info2 esta no meio da info1 e o valor
            novo = criaNo(valor, raiz->Dir, ptr, NULL); // sera passado a raiz dir como raiz esq, ja que todos os elementos da raiz dir são menores que o valor que foi promovido e sera passado o maiorNo para o centro, ja que todos os elementos do MaiorNo sao maiores que o valor que foi promovido
        }
    }
    // como ta quebrando a raiz ela só possuira um no, entao a info2 e ajustada
    // raiz->info2 = aux;
    raiz->Ninfos = 1;
    raiz->Dir = NULL;
    return novo; // retorna o novo no criado
}

Arv23 *insere(Arv23 **raiz, Bloco valor, Bloco *promove, Arv23 **pai)
{ // funcao que insere na arvore e organiza as chamadas das funcoes para saber onde cada elemento vai ser inserido corretamente
    Arv23 *MaiorNo;
    MaiorNo = NULL;
    Bloco promove1;

    if (*raiz == NULL)
    { // insere a raiz da arvore
        *raiz = criaNo(valor, NULL, NULL, NULL);
    }
    else
    {
        if (ehFolha(*raiz))
        { // e folha
            if ((*raiz)->Ninfos == 1)
            {                                              // e folha, tem apenas uma informacao
                *raiz = adicionaChave(*raiz, valor, NULL); // adiciona a informacao ao no
            }
            else
            { // e folha, tem duas informacoes
                MaiorNo = quebraNo(*raiz, valor, promove, NULL);
                if (*pai == NULL)
                { // cria uma nova raiz para a arvore
                    *raiz = criaNo(*promove, *raiz, MaiorNo, NULL);
                    MaiorNo = NULL; // O MaiorNo no recebe null, pois ja foi adicionado na arvore, se isso nao acontecer ela vai inserir o elemento repetidas vezes na arvore
                }
            }
        }
        else
        { // se nao for folha
            if (valor.Bloco_F < (*raiz)->info1.Bloco_F)
            {
                MaiorNo = insere(&((*raiz)->Esq), valor, promove, raiz); // percorre a esquerda da arvore
            }
            else
            {
                if (((*raiz)->Ninfos == 1) || (valor.Bloco_F < (*raiz)->info2.Bloco_F))
                {
                    MaiorNo = insere(&((*raiz)->Cen), valor, promove, raiz); // percorre o centro da arvore
                }
                else
                {
                    MaiorNo = insere(&((*raiz)->Dir), valor, promove, raiz); // percorre a direita da arvore
                }
            }
            if (MaiorNo != NULL)
            { // caso o no tenha pai
                if ((*raiz)->Ninfos == 1)
                { // nao e folha, tem apenas uma informacao
                    *raiz = adicionaChave(*raiz, *promove, MaiorNo);
                    MaiorNo = NULL;
                }
                else
                { // nao e folha, tem duas informacoes
                    MaiorNo = quebraNo(*raiz, *promove, &promove1, MaiorNo);
                    *promove = promove1; // atribui o valor a ser subido na arvore para o ponteiro que guarda esse valor
                    if (*pai == NULL)
                    { // cria uma nova raiz para a arvore
                        *raiz = criaNo(promove1, *raiz, MaiorNo, NULL);
                        MaiorNo = NULL;
                    }
                }
            }
        }
    }
    return MaiorNo; // retorna o novo no, ou seja, o no mais a direita da raiz, ou nullo quando o valor for adicionado
}

void imprimir(Arv23 *raiz)
{ // Imprime todos os elementos da arvore em pre-ordem
    if (raiz != NULL)
    {
        imprimir(raiz->Esq);
        printf("\n---Bloco---\n");
        printf("-Inicio: %d\n-Final: %d\n-Status: %c\n", raiz->info1.Bloco_I, raiz->info1.Bloco_F, raiz->info1.status);
        imprimir(raiz->Cen);
        if (raiz->Ninfos == 2)
        {
            printf("\n-Inicio: %d\n-Final: %d\n-Status: %c\n", raiz->info2.Bloco_I, raiz->info2.Bloco_F, raiz->info2.status);
        }
        // imprimir(raiz->Esq);
        // imprimir(raiz->Cen);
        imprimir(raiz->Dir);
    }
}

void Cadastra(Arv23 **raiz, int *vet)
{
    Arv23 *pai = NULL;
    Bloco info, promove;
    int i = 0;

    system("cls");
    printf("\n\t-------- Cadastro da memoria --------\n");
    printf("\nDigite a quantidade de blocos logicos(Memoria em Mbyte): ");
    scanf("%d", &Tam_bloco);

    while (Tam_bloco <= 0)
    {
        printf("\nDigite uma quantidade de blocos valida, maior que zero: ");
        scanf("%d", &Tam_bloco);
    }

    printf("\nDigite o estado do primeiro bloco(o para ocupado ou l para livre): ");
    scanf(" %c", &info.status);

    while (info.status != 'o' && info.status != 'l')
    {
        printf("\nDigite um estado valido para o primeiro bloco(o para ocupado ou l para livre): ");
        scanf(" %c", &info.status);
    }

    info.Bloco_I = 0;
    info.Bloco_F = 0;

    do
    {
        printf("\nInicio do bloco: %d\n", info.Bloco_I);
        printf("Digite o endereco final para o bloco: ");
        scanf("%d", &info.Bloco_F);

        while (info.Bloco_F >= Tam_bloco || info.Bloco_F < info.Bloco_I)
        {
            printf("Digite um valor valido para o fim do bloco(Fim do bloco: %d): ", Tam_bloco);
            scanf("%d", &info.Bloco_F);
        }

        vet[i] = info.Bloco_F;
        i++;

        insere(raiz, info, &promove, &pai);

        if (info.status == 'l')
        {
            info.status = 'o';
        }
        else
        {
            info.status = 'l';
        }

        info.Bloco_I = info.Bloco_F + 1;

    } while (info.Bloco_I != Tam_bloco);
}

void AlocaEspacos(Arv23 **raiz, int Qtd)
{
    Arv23 *Pai = NULL;
    Bloco aux;
    int ptr = 0, N;
    aux = ProcuraEspaco(&(*raiz), Qtd, &Pai, &(*raiz), &ptr);
    N = aux.Bloco_I;
    if (aux.Bloco_I != -1)
    {
        remover(&(*raiz), &Pai, N);
    }
    else
    {
        printf("\nNao e possivel alocar essa quantidade de blocos, nao ha espaco suficiente em nenhum bloco!\n");
    }
}

Bloco ProcuraEspaco(Arv23 **raiz, int Qtd, Arv23 **pai, Arv23 **RAIZAvr, int *ptr)
{
    Arv23 *aux1 = NULL, *aux2 = NULL;
    Bloco aux3;
    aux3.Bloco_I = -1;
    int espaco, aux = 0;
    if (*raiz != NULL)
    {
        espaco = ((*raiz)->info1.Bloco_F - (*raiz)->info1.Bloco_I) + 1;
        if (espaco >= Qtd && (*raiz)->info1.status == 'l')
        {
            printf("\n---Bloco que foi Ocupado---\n");
            printf("  -Inicio: %d\n  -Final: %d\n  -Status: %c\n", (*raiz)->info1.Bloco_I, (*raiz)->info1.Bloco_F, (*raiz)->info1.status);
            aux = 1;
            if (espaco == Qtd)
            {
                if (ehFolha(*raiz))
                {
                    if (*pai == NULL)
                    {
                        if ((*raiz)->Ninfos == 2)
                        {
                            (*raiz)->info1.Bloco_F = (*raiz)->info2.Bloco_F;
                            (*raiz)->info1.status = 'o';
                            (*raiz)->Ninfos = 1;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            (*raiz)->info1.status = 'o';
                            aux3.Bloco_I = -2;
                        }
                    }
                    else
                    {
                        if ((*raiz)->info1.Bloco_I == 0)
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                            if (aux1->Ninfos == 2)
                            {
                                if (aux1->info2.Bloco_I == (*raiz)->info1.Bloco_F + 1)
                                {
                                    (*raiz)->info1.Bloco_F = aux1->info2.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info2;
                                }
                                else
                                {
                                    (*raiz)->info1.Bloco_F = aux1->info1.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info1;
                                }
                            }
                            else
                            {
                                (*raiz)->info1.Bloco_F = aux1->info1.Bloco_F;
                                (*raiz)->info1.status = 'o';
                                aux3 = aux1->info1;
                            }
                        }
                        else if ((*raiz)->info1.Bloco_F + 1 == Tam_bloco)
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                            if (aux1->Ninfos == 2)
                            {
                                if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                                {
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }
                            }
                            else
                            {
                                aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                aux1->info1.status = 'o';
                                aux3 = (*raiz)->info1;
                            }
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                            if (aux1->Ninfos == 2)
                            {
                                if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                                {
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                }
                            }
                            else
                            {
                                aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                aux1->info1.status = 'o';
                            }

                            if (aux1->Ninfos == 2)
                            {
                                if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_F)
                                {
                                    aux2 = busca1(RAIZAvr, aux1->info2.Bloco_F + 1);
                                    if (aux2->Ninfos == 2)
                                    {
                                        if (aux2->info2.Bloco_I == aux1->info2.Bloco_F + 1)
                                        {
                                            aux1->info2.Bloco_F = aux2->info2.Bloco_F;
                                            aux1->info2.status = 'o';
                                            aux3 = aux2->info2;
                                        }
                                        else
                                        {
                                            aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                            aux1->info2.status = 'o';
                                            aux3 = aux2->info1;
                                        }
                                    }
                                    else
                                    {
                                        aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info2.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                                else
                                {
                                    aux2 = busca1(RAIZAvr, aux1->info1.Bloco_F + 1);
                                    if (aux2->Ninfos == 2)
                                    {
                                        if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                        {
                                            aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                            aux1->info1.status = 'o';
                                            aux3 = aux2->info2;
                                        }
                                        else
                                        {
                                            aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                            aux1->info1.status = 'o';
                                            aux3 = aux2->info1;
                                        }
                                    }
                                    else
                                    {
                                        aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                            }
                            else
                            {
                                aux2 = busca1(RAIZAvr, aux1->info1.Bloco_F + 1);
                                if (aux2->Ninfos == 2)
                                {
                                    if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                    {
                                        aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info2;
                                    }
                                    else
                                    {
                                        aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                            remover(RAIZAvr, NULL, (*raiz)->info1.Bloco_I);
                        }
                    }
                }
                else
                {
                    if (*pai == NULL)
                    {
                        printf("aqui\n");
                        aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                        if (aux1->Ninfos == 1)
                        {
                            aux2 = busca1(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                            if (aux2->Ninfos == 1)
                            {
                                aux1->info1.Bloco_I = aux2->info1.Bloco_I;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info1;
                                remover(RAIZAvr, NULL, aux2->info1.Bloco_I);
                            }
                            else
                            {
                                aux1->info1.Bloco_I = aux2->info2.Bloco_I;
                                aux1->info1.status = 'o';
                                // aux3 = aux2->info2;
                                remover(RAIZAvr, NULL, aux2->info2.Bloco_I);
                            }
                        }
                        else
                        {
                            aux2 = busca1(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                            if (aux2->Ninfos == 1)
                            {
                                aux1->info2.Bloco_I = aux2->info1.Bloco_I;
                                aux1->info2.status = 'o';
                                // aux3 = aux2->info1;
                                remover(RAIZAvr, NULL, aux2->info1.Bloco_I);
                            }
                            else
                            {
                                aux1->info2.Bloco_I = aux2->info2.Bloco_I;
                                aux1->info2.status = 'o';
                                // aux3 = aux2->info2;
                                remover(RAIZAvr, NULL, aux2->info2.Bloco_I);
                            }
                        }
                        // aux3 = (*raiz)->info1;
                    }
                    else
                    {
                        aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                        if (aux1->Ninfos == 2)
                        {
                            if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                            {
                                aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                aux1->info2.status = 'o';
                            }
                            else
                            {
                                aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                aux1->info1.status = 'o';
                            }
                        }
                        else
                        {
                            aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                            aux1->info1.status = 'o';
                        }

                        if (aux1->Ninfos == 2)
                        {
                            if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_F)
                            {
                                aux2 = busca1(RAIZAvr, aux1->info2.Bloco_F + 1);
                                if (aux2->Ninfos == 2)
                                {
                                    if (aux2->info2.Bloco_I == aux1->info2.Bloco_F + 1)
                                    {
                                        aux1->info2.Bloco_F = aux2->info2.Bloco_F;
                                        aux1->info2.status = 'o';
                                        aux3 = aux2->info2;
                                    }
                                    else
                                    {
                                        aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info2.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                                else
                                {
                                    aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                            else
                            {
                                aux2 = busca1(RAIZAvr, aux1->info1.Bloco_F + 1);
                                if (aux2->Ninfos == 2)
                                {
                                    if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                    {
                                        aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info2;
                                    }
                                    else
                                    {
                                        aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                        }
                        else
                        {
                            aux2 = busca1(RAIZAvr, aux1->info1.Bloco_F + 1);
                            if (aux2->Ninfos == 2)
                            {
                                if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                {
                                    aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info2;
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                            else
                            {
                                aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info1;
                            }
                        }
                        remover(RAIZAvr, NULL, (*raiz)->info1.Bloco_I);
                    }
                }
            }
            else
            {
                if (*pai == NULL)
                {
                    if ((*raiz)->Ninfos == 2)
                    {
                        if (ehFolha(*raiz))
                        {
                            (*raiz)->info1.Bloco_F -= Qtd;
                            (*raiz)->info2.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                            (*raiz)->info1.Bloco_F -= Qtd;
                            aux1->info1.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                    }
                    else
                    {
                        if (ehFolha(*raiz))
                        {
                            (*raiz)->info1.Bloco_F -= Qtd;
                            (*raiz)->Ninfos = 2;
                            (*raiz)->info2.Bloco_I = (*raiz)->info1.Bloco_F + 1;
                            (*raiz)->info2.Bloco_F = Tam_bloco - 1;
                            (*raiz)->info2.status = 'o';
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                            (*raiz)->info1.Bloco_F -= Qtd;
                            aux1->info1.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                    }
                }
                else
                {
                    if ((*raiz)->info1.Bloco_F == Tam_bloco - 1)
                    {
                        aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                        if (aux1->Ninfos == 2)
                        {
                            if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                            {
                                aux1->info2.Bloco_F += Qtd;
                                (*raiz)->info1.Bloco_I += Qtd;
                            }
                            else
                            {
                                aux1->info1.Bloco_F += Qtd;
                                (*raiz)->info1.Bloco_I += Qtd;
                            }
                        }
                        else
                        {
                            aux1->info1.Bloco_F += Qtd;
                            (*raiz)->info1.Bloco_I += Qtd;
                        }
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca1(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                        if (aux1->Ninfos == 2)
                        {
                            if (aux1->info2.Bloco_I == (*raiz)->info1.Bloco_F + 1)
                            {
                                aux1->info2.Bloco_I -= Qtd;
                                (*raiz)->info1.Bloco_F -= Qtd;
                            }
                            else
                            {
                                aux1->info1.Bloco_I -= Qtd;
                                (*raiz)->info1.Bloco_F -= Qtd;
                            }
                        }
                        else
                        {
                            aux1->info1.Bloco_I -= Qtd;
                            (*raiz)->info1.Bloco_F -= Qtd;
                        }
                        aux3.Bloco_I = -2;
                    }
                }
            }
        }
        else if ((*raiz)->Ninfos == 2)
        {
            espaco = ((*raiz)->info2.Bloco_F - (*raiz)->info2.Bloco_I) + 1;
            if (espaco >= Qtd && (*raiz)->info2.status == 'l')
            {
                printf("\n---Bloco que foi Ocupado---\n");
                printf("  -Inicio: %d\n  -Final: %d\n  -Status: %c\n", (*raiz)->info2.Bloco_I, (*raiz)->info2.Bloco_F, (*raiz)->info2.status);
                aux = 1;
                if (espaco == Qtd)
                {
                    if (*pai == NULL)
                    {
                        if (ehFolha(*raiz))
                        {
                            (*raiz)->info1.Bloco_F += Qtd;
                            (*raiz)->Ninfos = 1;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                            if (aux1->Ninfos == 1)
                            {
                                aux2 = busca1(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                                if (aux2->Ninfos == 1)
                                {
                                    aux1->info1.Bloco_I = aux2->info1.Bloco_I;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                                else
                                {
                                    aux1->info1.Bloco_I = aux2->info2.Bloco_I;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info2;
                                }
                            }
                            else
                            {
                                aux2 = busca1(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                                if (aux2->Ninfos == 1)
                                {
                                    aux1->info2.Bloco_I = aux2->info1.Bloco_I;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info1;
                                }
                                else
                                {
                                    aux1->info2.Bloco_I = aux2->info2.Bloco_I;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info2;
                                }
                            }
                            remover(RAIZAvr, NULL, (*raiz)->info2.Bloco_I);
                        }
                    }
                    else
                    {
                        if (ehFolha(*raiz))
                        {
                            (*raiz)->info1.Bloco_F += Qtd;
                            (*raiz)->Ninfos = 1;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                            if (aux1->Ninfos == 1)
                            {
                                aux2 = busca1(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                                if (aux2->Ninfos == 1)
                                {
                                    aux1->info1.Bloco_I = aux2->info1.Bloco_I;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                                else
                                {
                                    aux1->info1.Bloco_I = aux2->info2.Bloco_I;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info2;
                                }
                            }
                            else
                            {
                                aux2 = busca1(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                                if (aux2->Ninfos == 1)
                                {
                                    aux1->info2.Bloco_I = aux2->info1.Bloco_I;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info1;
                                }
                                else
                                {
                                    aux1->info2.Bloco_I = aux2->info2.Bloco_I;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info2;
                                }
                            }
                            remover(RAIZAvr, NULL, (*raiz)->info2.Bloco_I);
                        }
                    }
                }
                else
                {
                    if (*pai == NULL)
                    {
                        if (ehFolha(*raiz))
                        {
                            (*raiz)->info1.Bloco_F += Qtd;
                            (*raiz)->info2.Bloco_I += Qtd;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                            if (aux1->Ninfos == 1)
                            {
                                (*raiz)->info2.Bloco_F -= Qtd;
                                aux1->info1.Bloco_I -= Qtd;
                                aux3.Bloco_I = -2;
                            }
                            else
                            {
                                (*raiz)->info2.Bloco_F -= Qtd;
                                aux1->info2.Bloco_I -= Qtd;
                                aux3.Bloco_I = -2;
                            }
                        }
                    }
                    else
                    {
                        if (ehFolha(*raiz))
                        {
                            (*raiz)->info1.Bloco_F += Qtd;
                            (*raiz)->info2.Bloco_I += Qtd;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            aux1 = busca1(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                            if (aux1->Ninfos == 1)
                            {
                                (*raiz)->info2.Bloco_F -= Qtd;
                                aux1->info1.Bloco_I -= Qtd;
                                aux3.Bloco_I = -2;
                            }
                            else
                            {
                                (*raiz)->info2.Bloco_F -= Qtd;
                                aux1->info2.Bloco_I -= Qtd;
                                aux3.Bloco_I = -2;
                            }
                        }
                    }
                }
            }
        }
        if (aux == 0)
        { // percorre a arvore
            aux3 = ProcuraEspaco(&(*raiz)->Esq, Qtd, raiz, RAIZAvr, ptr);
            if (aux3.Bloco_I == -1)
            {
                aux3 = ProcuraEspaco(&(*raiz)->Cen, Qtd, raiz, RAIZAvr, ptr);
            }
            if (aux3.Bloco_I == -1)
            {
                aux3 = ProcuraEspaco(&(*raiz)->Dir, Qtd, raiz, RAIZAvr, ptr);
            }
        }
    }
    return aux3;
}

Arv23 *busca1(Arv23 **raiz, int info)
{
    Arv23 *aux = NULL;
    if (*raiz != NULL)
    {
        if ((info == (*raiz)->info1.Bloco_F || info == (*raiz)->info1.Bloco_I) || (info == (*raiz)->info2.Bloco_F || info == (*raiz)->info2.Bloco_I))
        {
            aux = *raiz;
        }
        else if (info < (*raiz)->info1.Bloco_F)
        {
            aux = busca1(&(*raiz)->Esq, info);
        }
        else if (info < (*raiz)->info2.Bloco_F || (*raiz)->Ninfos == 1)
        {
            aux = busca1(&(*raiz)->Cen, info);
        }
        else if (info > (*raiz)->info2.Bloco_F && (*raiz)->Ninfos == 2)
        {
            aux = busca1(&(*raiz)->Dir, info);
        }
    }
    return aux;
}

int remover(Arv23 **raiz, Arv23 **pai, int valor)
{
    int removeu = 0;
    Arv23 *noMenorInfoDir = NULL;
    if (*raiz != NULL)
    {
        if (valor == (*raiz)->info1.Bloco_I || valor == (*raiz)->info2.Bloco_I)
        {
            if (valor == (*raiz)->info1.Bloco_I)
            {
                if (ehFolha(*raiz))
                {
                    removeu = removeInfo1Folha(*raiz, *pai);
                    if (removeu == 3)
                    {
                        free(*raiz);
                        *raiz = NULL;
                    }
                }
                else
                {
                    removeu = removeInfo1NaoFolha((*raiz));
                }
            }
            else
            {
                if (ehFolha(*raiz))
                { // se for folha, so remove o no
                    removeu = removeInfo2Folha(*raiz);
                }
                else if (ehFolha((*raiz)->Dir))
                {
                    removeu = removeInfo2ComDirFolha((*raiz)->Dir, *raiz);
                }
                else
                {
                    if (numeroInfosArv((*raiz)->Dir) > 3)
                    {
                        noMenorInfoDir = obterMenorNo((*raiz)->Dir);
                        (*raiz)->info2 = noMenorInfoDir->info1;
                        removeu = remover(&((*raiz)->Dir), raiz, noMenorInfoDir->info1.Bloco_I);
                    }
                    else
                    {
                        removeu = removeInfo2NaoFolha(*raiz);
                    }
                }
            }
        }
        else if (valor < (*raiz)->info1.Bloco_I)
        {
            removeu = remover(&((*raiz)->Esq), raiz, valor);
        }
        else if (valor < (*raiz)->info2.Bloco_I || (*raiz)->Ninfos == 1)
        {
            removeu = remover(&((*raiz)->Cen), raiz, valor);
        }
        else if (valor > (*raiz)->info2.Bloco_I && (*raiz)->Ninfos == 2)
        {
            removeu = remover(&((*raiz)->Dir), raiz, valor);
        }
        // balancear;
        if (removeu == 2)
        {
            removeu = balancear(&(*raiz), &(*pai), removeu);
        }
    }
    return removeu;
}

int balancear(Arv23 **raiz, Arv23 **pai, int removeu)
{
    if ((*pai) == NULL)
    {
        (*raiz) = (*raiz)->Esq;
        removeu = 1;
    }
    else
    {
        if ((*pai)->Esq == (*raiz))
        {
            if ((*pai)->Cen->Ninfos == 2)
            {
                (*raiz)->info1 = (*pai)->info1;
                (*raiz)->Cen = (*pai)->Cen->Esq;
                (*pai)->info1 = (*pai)->Cen->info1;
                (*pai)->Cen->info1 = (*pai)->Cen->info2;
                (*pai)->Cen->Ninfos = 1;
                (*pai)->Cen->Esq = (*pai)->Cen->Cen;
                (*pai)->Cen->Cen = (*pai)->Cen->Dir;
                (*pai)->Cen->Dir = NULL;
                removeu = 1;
            }
            else
            {
                if ((*pai)->Ninfos == 2)
                {
                    (*raiz)->info1 = (*pai)->info1;
                    (*raiz)->info2 = (*pai)->Cen->info1;
                    (*raiz)->Ninfos = 2;
                    (*raiz)->Cen = (*pai)->Cen->Esq;
                    (*raiz)->Dir = (*pai)->Cen->Cen;
                    free((*pai)->Cen);
                    (*pai)->info1 = (*pai)->info2;
                    (*pai)->Ninfos = 1;
                    (*pai)->Cen = (*pai)->Dir;
                    (*pai)->Dir = NULL;
                    removeu = 1;
                }
                else
                {
                    (*raiz)->info1 = (*pai)->info1;
                    (*raiz)->info2 = (*pai)->Cen->info1;
                    (*raiz)->Ninfos = 2;
                    (*raiz)->Cen = (*pai)->Cen->Esq;
                    (*raiz)->Dir = (*pai)->Cen->Cen;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                }
            }
        }
        else if ((*pai)->Cen == (*raiz))
        {
            if ((*pai)->Esq->Ninfos == 2)
            {
                (*raiz)->info1 = (*pai)->info1;
                (*pai)->info1 = (*pai)->Esq->info2;
                (*raiz)->Cen = (*raiz)->Esq;
                (*raiz)->Esq = (*pai)->Esq->Dir;
                (*pai)->Esq->Dir = NULL;
                (*pai)->Esq->Ninfos = 1;
                removeu = 1;
            }
            else
            {
                if ((*pai)->Ninfos == 2)
                {
                    (*pai)->Esq->info2 = (*pai)->info1;
                    (*pai)->Esq->Ninfos = 2;
                    (*pai)->Esq->Dir = (*raiz)->Esq;
                    free(*raiz);
                    *raiz = NULL;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                    (*pai)->info1 = (*pai)->info2;
                    (*pai)->Ninfos = 1;
                    (*pai)->Cen = (*pai)->Dir;
                    (*pai)->Dir = NULL;
                    removeu = 1;
                }
                else
                {
                    (*pai)->Esq->info2 = (*pai)->info1;
                    (*pai)->Esq->Ninfos = 2;
                    (*pai)->Esq->Dir = (*pai)->Cen->Esq;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                }
            }
        }
        else
        {
            if ((*pai)->Cen->Ninfos == 2)
            {
                (*raiz)->info1 = (*pai)->info2;
                (*raiz)->Cen = (*raiz)->Esq;
                (*raiz)->Esq = (*pai)->Cen->Dir;
                (*pai)->info2 = (*pai)->Cen->info2;
                (*pai)->Cen->Ninfos = 1;
                (*pai)->Cen->Dir = NULL;
            }
            else
            {
                (*pai)->Cen->info2 = (*pai)->info2;
                (*pai)->Cen->Ninfos = 2;
                (*pai)->Cen->Dir = (*raiz)->Esq;
                free(*raiz);
                *raiz = NULL;
                (*pai)->Ninfos = 1;
                free((*pai)->Dir);
                (*pai)->Dir = NULL;
            }
            removeu = 1;
        }
    }
    return removeu;
}

int removeInfo2Folha(Arv23 *raiz)
{
    raiz->Ninfos = 1;
    return 1;
}

int removeInfo2ComDirFolha(Arv23 *raiz, Arv23 *pai)
{
    int removeu = 0;
    if (raiz->Ninfos == 2)
    {
        pai->info2 = raiz->info1;
        raiz->info1 = raiz->info2;
        raiz->Ninfos = 1;
        removeu = 1;
    }
    else
    {
        if (pai->Cen->Ninfos == 2)
        {
            pai->info2 = pai->Cen->info2;
            pai->Cen->Ninfos = 1;
            removeu = 1;
        }
        else
        {
            pai->Cen->info2 = raiz->info1;
            pai->Cen->Ninfos = 2;
            pai->Ninfos = 1;
            free(raiz);
            pai->Dir = NULL;
            removeu = 1;
        }
    }
    return removeu;
}

Arv23 *obterMenorNo(Arv23 *raiz)
{
    Arv23 *aux = NULL;
    aux = raiz;
    if (raiz->Esq != NULL)
    {
        aux = obterMenorNo(raiz->Esq);
    }
    return aux;
}

int numeroInfosArv(Arv23 *raiz)
{
    int cont = 0;
    if (raiz != NULL)
    {
        cont += 1;
        if (raiz->Ninfos == 2)
        {
            cont += 1;
        }
        cont += numeroInfosArv(raiz->Esq);
        cont += numeroInfosArv(raiz->Cen);
        cont += numeroInfosArv(raiz->Dir);
    }
    return cont;
}

Arv23 *obterMaiorNo(Arv23 *raiz)
{
    Arv23 *aux = NULL;
    aux = raiz;
    if (raiz->Dir != NULL)
    {
        aux = obterMaiorNo(raiz->Dir);
    }
    else
    {
        if (raiz->Cen != NULL)
        {
            aux = obterMaiorNo(raiz->Cen);
        }
    }
    return aux;
}

int removeInfo2NaoFolha(Arv23 *raiz)
{
    int removeu = 0;
    Arv23 *noMaiorInfoCen = NULL;
    noMaiorInfoCen = obterMaiorNo(raiz->Cen);

    if (noMaiorInfoCen->Ninfos == 2)
    {
        raiz->info2 = noMaiorInfoCen->info2;
        removeu = remover(&(raiz->Cen), &raiz, noMaiorInfoCen->info2.Bloco_I);
    }
    else
    {
        raiz->info2 = noMaiorInfoCen->info1;
        removeu = remover(&(raiz->Cen), &raiz, noMaiorInfoCen->info1.Bloco_I);
    }
    return removeu;
}

int removeInfo1Folha(Arv23 *raiz, Arv23 *pai)
{
    int removeu = 0;
    if (raiz->Ninfos == 2)
    {
        raiz->info1 = raiz->info2;
        raiz->Ninfos = 1;
        removeu = 1;
    }
    else if (pai == NULL)
    {
        removeu = 3;
    }
    else
    {
        if (pai->Esq == raiz)
        {
            if (pai->Cen->Ninfos == 2)
            {
                raiz->info1 = pai->info1;
                pai->info1 = pai->Cen->info1;
                pai->Cen->info1 = pai->Cen->info2;
                pai->Cen->Ninfos = 1;
                removeu = 1;
            }
            else if (pai->Ninfos == 2)
            {
                raiz->info1 = pai->info1;
                raiz->info2 = pai->Cen->info1;
                raiz->Ninfos = 2;
                free(pai->Cen);
                pai->info1 = pai->info2;
                pai->Ninfos = 1;
                pai->Cen = pai->Dir;
                pai->Dir = NULL;
                removeu = 1;
            }
            else
            {
                removeu = 2;
            }
        }
        else if (pai->Cen == raiz)
        {
            if (pai->Esq->Ninfos == 2)
            {
                raiz->info1 = pai->info1;
                pai->info1 = pai->Esq->info2;
                pai->Esq->Ninfos = 1;
                removeu = 1;
            }
            else if (pai->Ninfos == 2)
            {
                if (pai->Dir->Ninfos == 2)
                {
                    raiz->info1 = pai->info2;
                    pai->info2 = pai->Dir->info1;
                    pai->Dir->info1 = pai->Dir->info2;
                    pai->Dir->Ninfos = 1;
                    removeu = 1;
                }
                else
                {
                    raiz->info1 = pai->info2;
                    raiz->info2 = pai->Dir->info1;
                    raiz->Ninfos = 2;
                    pai->Ninfos = 1;
                    free(pai->Dir);
                    pai->Dir = NULL;
                    removeu = 1;
                }
            }
            else
            {
                removeu = 2;
            }
        }
        else
        {
            if (pai->Cen->Ninfos == 2)
            {
                raiz->info1 = pai->info2;
                pai->info2 = pai->Cen->info2;
                pai->Cen->Ninfos = 1;
                removeu = 1;
            }
            else
            {
                pai->Cen->info2 = pai->info2;
                pai->Cen->Ninfos = 2;
                pai->Ninfos = 1;
                free(pai->Dir);
                pai->Dir = NULL;
                removeu = 1;
            }
        }
    }
    return removeu;
}

int removeInfo1NaoFolha(Arv23 *raiz)
{
    int removeu = 0;
    Arv23 *noMaiorInfoEsq = NULL;
    noMaiorInfoEsq = obterMaiorNo(raiz->Esq);

    if (noMaiorInfoEsq->Ninfos == 2)
    {
        raiz->info1 = noMaiorInfoEsq->info2;
        removeu = remover(&(raiz->Esq), &raiz, noMaiorInfoEsq->info2.Bloco_I);
    }
    else
    {
        raiz->info1 = noMaiorInfoEsq->info1;
        removeu = remover(&(raiz->Esq), &raiz, noMaiorInfoEsq->info1.Bloco_I);
    }
    return removeu;
}

int buscar(Arv23 *raiz, int valor)
{
    int ret = 0;
    if (raiz != NULL)
    {
        if (raiz->info1.Bloco_F == valor || raiz->info2.Bloco_F == valor)
        {
            ret = 1;
        }
        else
        {
            if (raiz->info1.Bloco_F > valor)
            {
                ret = buscar(raiz->Esq, valor);
            }
            else
            {
                if (raiz->info1.Bloco_F < valor && valor < raiz->info2.Bloco_F)
                {
                    ret = buscar(raiz->Cen, valor);
                }
                else
                {
                    ret = buscar(raiz->Dir, valor);
                }
            }
        }
    }

    return ret;
}
