/*==============================================================================*/

// Dupla: Gustavo Araujo Ferreira Da Silva; Jose David Rodrigues da Silva Moura*/

/*
Na entrada dos algoritmos de Dijkstra, Bellman-Ford e Floyd, o usuário irá inserir a matriz correspondente ao grafo,
sendo que nos valores onde os vértices não possuem adjacências nos algoritmos de Dijkstra e Bellman-Ford, deverá
ser inserido o valor zero. No algoritmo de Floyd nos valores onde os vértices não possuem adjacências o usuario
devera iserir -1. Para os algoritmos de Dijkstra e Bellman-Ford, o usuário deverá informar o vértice inicial.
*/

/*==============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 99999

int **aloca_matriz(int qtdvert);
void libera_matriz(int **matriz, int qtdVert);
int distanciaMin(int dist[], int visitados[], int qtdVert);
void imprimirCaminho(int caminho[], int j);
void imprimir(int dist[], int caminho[], int src, int qtdVert);
void dijkstra(int **graph, int src, int qtdVert);
void bellmanFord(int **grafo, int src, int qtdVert);
void floyd(int **grafo, int qtdVert);
void imprimirFloyd(int **dist, int qtdVert);

int main()
{
    int op, qtdVert, **grafo, i, j, src;
    do
    {
        printf("\nQual algoritmo deseja usar?\n1 - Dijkstra\n2 - Bellman-Ford\n3 - Floyd\n0 - Sair\n");
        scanf("%d", &op);
        printf("\n");
        switch (op)
        {
        case 0:
            printf("Saindo!!!\n\n");
            break;
        case 1:
            printf("\t--------Dijkstra--------\n");
            printf("Digite a quantidade de vertices do grafo!\n");
            scanf("%d", &qtdVert);

            grafo = aloca_matriz(qtdVert);

            printf("\n");
            for (i = 0; i < qtdVert; i++)
            {
                for (j = 0; j < qtdVert; j++)
                {
                    printf("Digite o valor da linha %d coluna %d: ", i + 1, j + 1);
                    scanf("%d", &grafo[i][j]);
                }
                printf("\n");
            }

            printf("Digite o vertice de partida: ");
            scanf("%d", &src);

            dijkstra(grafo, src - 1, qtdVert);

            libera_matriz(grafo, qtdVert);
            break;
        case 2:
            printf("\t--------Bellman-Ford--------\n");
            printf("Digite a quantidade de vertices do grafo!\n");
            scanf("%d", &qtdVert);

            grafo = aloca_matriz(qtdVert);

            printf("\n");
            for (i = 0; i < qtdVert; i++)
            {
                for (j = 0; j < qtdVert; j++)
                {
                    printf("Digite o valor da linha %d coluna %d: ", i + 1, j + 1);
                    scanf("%d", &grafo[i][j]);
                }
                printf("\n");
            }

            printf("Digite o vertice de partida: ");
            scanf("%d", &src);

            bellmanFord(grafo, src - 1, qtdVert);

            libera_matriz(grafo, qtdVert);

            break;
        case 3:
            printf("\t--------Floyd--------\n");
            printf("Digite a quantidade de vertices do grafo!\n");
            scanf("%d", &qtdVert);

            grafo = aloca_matriz(qtdVert);

            printf("\n");
            for (i = 0; i < qtdVert; i++)
            {
                for (j = 0; j < qtdVert; j++)
                {
                    printf("Digite o valor da linha %d coluna %d: ", i + 1, j + 1);
                    scanf("%d", &grafo[i][j]);
                    if (grafo[i][j] == -1)
                    {
                        grafo[i][j] = INF;
                    }
                }
                printf("\n");
            }

            printf("\nMatriz de adjacencia fornecida:\n");
            for (i = 0; i < qtdVert; i++)
            {
                for (j = 0; j < qtdVert; j++)
                {
                    if (grafo[i][j] == INF)
                    {
                        printf("%7s", "INF");
                    }
                    else
                    {
                        printf("%7d", grafo[i][j]);
                    }
                }
                printf("\n");
            }
            printf("\n");

            floyd(grafo, qtdVert);

            libera_matriz(grafo, qtdVert);

            break;
        default:
            printf("Digite uma opcao valida!\n");
            break;
        }
    } while (op != 0);
    return 0;
}

int **aloca_matriz(int qtdvert)
{
    int i, **matriz;
    matriz = (int **)malloc(qtdvert * sizeof(int *)); // aloca as linhas da matriz
    for (i = 0; i < qtdvert; i++)
    {
        matriz[i] = (int *)malloc(qtdvert * sizeof(int)); // aloca as colunas de cada linha
    }
    return matriz;
}

void libera_matriz(int **matriz, int qtdVert)
{
    int i;
    for (i = 0; i < qtdVert; i++)
    {
        free(matriz[i]); // desaloca as colunas de cada linha
    }
    free(matriz); // desaloca as linhas da matriz
}

void imprimirCaminho(int caminho[], int j)
{
    if (caminho[j] != -1)
    {
        imprimirCaminho(caminho, caminho[j]);
        printf("-> %d", j + 1);
    }
}

void imprimir(int dist[], int caminho[], int src, int qtdVert)
{
    // Imprime a solução, incluindo o caminho para cada vértice
    int i;
    printf("Vertice\t\tDistancia\tCaminho");
    for (i = 0; i < qtdVert; i++)
    {
        printf("\n%d -> %d \t\t%d\t\t%d ", src + 1, i + 1, dist[i], src + 1);
        imprimirCaminho(caminho, i);
    }
    printf("\n");
}

/*==========================================================================*/
/*Codigos do algoritmo de dijkstra*/

int distanciaMin(int dist[], int visitados[], int qtdVert)
{
    int i, min = INT_MAX, min_index;
    for (i = 0; i < qtdVert; i++)
    {
        if (visitados[i] == 0 && dist[i] <= min)
        {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int **grafo, int src, int qtdVert)
{
    int *dist, *visitados, i, cont, k, j, *Caminho;
    dist = (int *)malloc(qtdVert * sizeof(int));
    visitados = (int *)malloc(qtdVert * sizeof(int));
    Caminho = (int *)malloc(qtdVert * sizeof(int));

    for (i = 0; i < qtdVert; i++)
    {
        dist[i] = INT_MAX;
        visitados[i] = 0;
        Caminho[i] = -1;
    }

    dist[src] = 0;
    // Caminho[src] = -1;

    for (cont = 0; cont < qtdVert - 1; cont++)
    {
        k = distanciaMin(dist, visitados, qtdVert);

        visitados[k] = 1;

        for (j = 0; j < qtdVert; j++)
        {
            if (!visitados[j] && grafo[k][j] && dist[k] != INT_MAX && dist[k] + grafo[k][j] < dist[j])
            {
                dist[j] = dist[k] + grafo[k][j];
                Caminho[j] = k;
            }
        }
    }

    imprimir(dist, Caminho, src, qtdVert);

    free(dist);
    free(visitados);
    free(Caminho);
    dist = NULL;
    visitados = NULL;
    Caminho = NULL;
}

/*==========================================================================*/

/*==========================================================================*/
/*Codigos do algoritmo de Bellman-Ford*/

void bellmanFord(int **grafo, int src, int qtdVert)
{
    int *dist, *caminho, i, j, k;

    dist = (int *)malloc(qtdVert * sizeof(int));
    caminho = (int *)malloc(qtdVert * sizeof(int));

    for (i = 0; i < qtdVert; i++)
    {
        dist[i] = INT_MAX;
        caminho[i] = -1;
    }

    dist[src] = 0;

    for (k = 0; k < qtdVert - 1; k++)
    {
        for (i = 0; i < qtdVert; i++)
        {
            for (j = 0; j < qtdVert; j++)
            {
                if (grafo[i][j] != 0 && dist[i] != INT_MAX && dist[i] + grafo[i][j] < dist[j])
                {
                    dist[j] = dist[i] + grafo[i][j];
                    caminho[j] = i;
                }
            }
        }
    }
    imprimir(dist, caminho, src, qtdVert);

    free(dist);
    free(caminho);
    dist = NULL;
    caminho = NULL;
}

/*==========================================================================*/

/*==========================================================================*/
/*Codigos do algoritmo de Floyd*/

void imprimirFloyd(int **dist, int qtdVert)
{
    printf("Distancia mais curta entre todos os pares de vertices:\n");
    for (int i = 0; i < qtdVert; i++)
    {
        for (int j = 0; j < qtdVert; j++)
        {
            if (dist[i][j] == INT_MAX)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void floyd(int **grafo, int qtdVert)
{
    int i, j, k;

    for (k = 0; k < qtdVert; k++)
    {
        for (i = 0; i < qtdVert; i++)
        {
            for (j = 0; j < qtdVert; j++)
            {
                if (i == j)
                {
                    grafo[i][j] = 0;
                }
                else if (grafo[i][j] > grafo[i][k] + grafo[k][j])
                {
                    grafo[i][j] = grafo[i][k] + grafo[k][j];
                }
            }
        }
        printf("Matriz M %d:\n", k + 1);
        for (i = 0; i < qtdVert; i++)
        {
            for (j = 0; j < qtdVert; j++)
            {
                if (grafo[i][j] == INF)
                {
                    printf("%7s", "INF");
                }
                else
                {
                    printf("%7d", grafo[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    imprimirFloyd(grafo, qtdVert);
}

/*==========================================================================*/