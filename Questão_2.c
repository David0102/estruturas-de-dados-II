#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Tam 20000 // quantidade de numeros a serem inseridos na arvore

struct Arvavl
{
	int info;
	struct Arvavl *Dir;
	struct Arvavl *Esq;
	int alt;
};

typedef struct Arvavl Arvavl;

struct Dados
{ // estrutura para guardar os dados de cada arvore
	int f_max, f_min, diferenca;
	double t_inser, t_busca;
};

typedef struct Dados Dados;

/*Protótipos das Funções.*/
int maior(int a, int b);
int alturaNo(Arvavl *raiz);
int balanceamento(Arvavl *raiz);
Arvavl *balancear(Arvavl *raiz);
Arvavl *rotacao_dir(Arvavl *raiz);
Arvavl *rotacao_esq(Arvavl *raiz);
Arvavl *rotacao_dir_esq(Arvavl *raiz);
Arvavl *rotacao_esq_dir(Arvavl *raiz);
void gerar(int vet[], int limite);
void embaralhar(int *vet);
Arvavl *criar_no(int valor);
int inserir(Arvavl **raiz, int valor);
void imprimir(Arvavl *raiz);
void liberar(Arvavl *raiz);
int buscar(Arvavl *raiz, int valor);
int proMax(Arvavl *raiz);
int proMin(Arvavl *raiz);

int main()
{
	int i, vet[Tam], j, folha_max, folha_min, dif, aux, cont;
	double t_insercao, t_m_insercao = 0, t_busca, t_m_busca = 0;
	clock_t ini, fim;
	Arvavl *raiz = NULL;
	Dados dados[30];

	// gerando os numeros aleatorios não repetidos e guardando em um vetor
	gerar(vet, 30000);

	for (j = 0; j < 30; j++)
	{
		system("cls"); // limpa a tela
		cont = 0;
		// inserindo na árvore e calculando o tempo de inserção dos elementos
		ini = clock(); // inicio da contagem do tempo
		for (i = 0; i < Tam; i++)
		{
			aux = inserir(&raiz, vet[i]);
			if (aux == 1)
			{
				cont++;
			}
		}
		fim = clock(); // fim da contagem
		t_insercao = (double)(fim - ini) / CLOCKS_PER_SEC;
		t_m_insercao += t_insercao; // somando o tempo de insercao de todas as arvores para calcular a media
		printf("---- %d Arvore preenchida ----\n\n", j + 1);
		printf("- %d valores inseridos\n", cont);
		// Buscando 10 elementos na árvore
		ini = clock();
		for (int i = 1; i <= 10; i++)
		{
			aux = buscar(raiz, 500 * i);
			if (aux == 1)
			{
				printf(" - Valor %d encontrado\n", 500 * i);
			}
			else
			{
				printf(" - Valor %d nao encontrado\n", 500 * i);
			}
		}
		fim = clock();
		// calculando o tempo de busca na arvore
		t_busca = (double)(fim - ini) / CLOCKS_PER_SEC;
		t_m_busca += t_busca; // somando o tempo de busca de todas as arvores para calcular a media

		folha_max = proMax(raiz);	 // buscando folha de maior profundidade
		folha_min = proMin(raiz);	 // buscando folha de menor profundidade
		dif = folha_max - folha_min; // diferenca entre a folha de maior profundidade e a de menor

		printf("- Tempo de execucao da insercao: %lf segundos\n", t_insercao);
		printf("- Tempo de execucao da busca: %lf segundos\n", t_busca);
		printf("- Folha de maior profundidade: %d\n", folha_max);
		printf("- Folha de menor profundidade: %d\n", folha_min);
		printf("- Diferenca entre as folhas: %d\n", dif);
		printf("\n");

		liberar(raiz); // libera a memoria de toda a arvore
		raiz = NULL;
		embaralhar(vet); // embaralhar o vetor para uma nova insercao

		// guarda os dados de todas as arvores em uma estrutura
		dados[j].t_inser = t_insercao;
		dados[j].t_busca = t_busca;
		dados[j].f_max = folha_max;
		dados[j].f_min = folha_min;
		dados[j].diferenca = dif;
		system("pause"); // pausa a tela
		system("cls");	 // limpa a tela
	}

	system("cls");
	for (i = 0; i < 30; i++)
	{ // imprime os dados de todas as arvores
		printf("\t %d Arvore\n", i + 1);
		printf("- Tempo de insersao: %lf\n", dados[i].t_inser);
		printf("- Tempo de de busca: %lf\n", dados[i].t_busca);
		printf("- Folha de maior profundidade: %d\n", dados[i].f_max);
		printf("- Folha de menor profundidade: %d\n", dados[i].f_min);
		printf("- Diferenca entre as folhas: %d\n", dados[i].diferenca);
		printf("\n");
	}

	// tempo medio de insercao e busca
	printf("Tempo medio de insercao: %lf segundos\n", t_m_insercao / 30);
	printf("Tempo medio de busca: %lf segundos\n", t_m_busca / 30);
	printf("\n");
	return 0;
}

int maior(int a, int b)
{
	if (a > b)
	{
		b = a;
	}
	return b;
}

int alturaNo(Arvavl *raiz)
{
	int alt;
	if (raiz == NULL)
	{
		alt = -1;
	}
	else
	{
		alt = raiz->alt;
	}
	return alt;
}

int balanceamento(Arvavl *raiz)
{
	int retorno;
	if (raiz == NULL)
	{
		retorno = 0;
	}
	else
	{
		retorno = alturaNo(raiz->Esq) - alturaNo(raiz->Dir);
	}
	return retorno;
}

Arvavl *balancear(Arvavl *raiz)
{
	int fb;
	fb = balanceamento(raiz);
	// rotação esquerda
	if (fb < -1 && balanceamento(raiz->Dir) <= 0)
	{
		raiz = rotacao_esq(raiz);
	}
	// rotação a direita
	else if (fb > 1 && balanceamento(raiz->Esq) >= 0)
	{
		raiz = rotacao_dir(raiz);
	}
	// rotação esquerda direita
	else if (fb > 1 && balanceamento(raiz->Esq) < 0)
	{
		raiz = rotacao_esq_dir(raiz);
	}
	// rotação direita esquerda
	else if (fb < -1 && balanceamento(raiz->Dir) > 0)
	{
		raiz = rotacao_dir_esq(raiz);
	}
	return raiz;
}

Arvavl *rotacao_dir(Arvavl *raiz)
{
	Arvavl *filho, *temp;
	filho = raiz->Esq;
	temp = filho->Dir;
	filho->Dir = raiz;
	raiz->Esq = temp;

	raiz->alt = maior(alturaNo(raiz->Esq), alturaNo(raiz->Dir)) + 1;
	filho->alt = maior(alturaNo(filho->Esq), alturaNo(filho->Dir)) + 1;
	return filho;
}

Arvavl *rotacao_esq(Arvavl *raiz)
{
	Arvavl *filho, *temp;
	filho = raiz->Dir;
	temp = filho->Esq;
	filho->Esq = raiz;
	raiz->Dir = temp;

	raiz->alt = maior(alturaNo(raiz->Esq), alturaNo(raiz->Dir)) + 1;
	filho->alt = maior(alturaNo(filho->Esq), alturaNo(filho->Dir)) + 1;
	return filho;
}

Arvavl *rotacao_dir_esq(Arvavl *raiz)
{
	raiz->Dir = rotacao_dir(raiz->Dir);
	raiz = rotacao_esq(raiz);
	return raiz;
}

Arvavl *rotacao_esq_dir(Arvavl *raiz)
{
	raiz->Esq = rotacao_esq(raiz->Esq);
	raiz = rotacao_dir(raiz);
	return raiz;
}

void gerar(int vet[], int limite)
{ // gera numeros aleatorios e preenche o vetor sem numeros repetidos
	int i = 0, j, aux;
	srand(time(NULL));
	do
	{
		vet[i] = 1 + rand() % limite;
		aux = 0;
		for (j = 0; j < i; j++)
		{
			if (vet[j] == vet[i])
			{
				aux = 1;
			}
		}
		if (aux == 0)
		{
			i++;
		}
	} while (i < Tam);
}

void embaralhar(int *vet)
{ // embaralha o vetor
	int aux, aux1, i;
	for (i = 0; i < Tam; i++)
	{
		aux = rand() % Tam; // sorteia posicoes dentro do tamanho do vetor e troca o elemento da posicao
		aux1 = vet[i];		// sorteada com o elemento da posicao atual
		vet[i] = vet[aux];
		vet[aux] = aux1;
	}
}

Arvavl *criar_no(int valor)
{
	Arvavl *no = (Arvavl *)malloc(sizeof(Arvavl));
	if (no != NULL)
	{
		no->info = valor;
		no->Dir = NULL;
		no->Esq = NULL;
		no->alt = 0;
	}
	return no;
}

int inserir(Arvavl **raiz, int valor)
{
	int inseriu = 0;
	if (*raiz == NULL)
	{
		*raiz = criar_no(valor);
		if (*raiz == NULL)
		{
			inseriu = 0;
		}
		else
		{
			inseriu = 1;
		}
	}
	else
	{
		if (valor < (*raiz)->info)
		{
			inseriu = inserir(&((*raiz)->Esq), valor);
		}
		else
		{
			if (valor > (*raiz)->info)
			{
				inseriu = inserir(&((*raiz)->Dir), valor);
			}
			else
			{
				inseriu = 2;
			}
		}
	}

	(*raiz)->alt = maior(alturaNo((*raiz)->Esq), alturaNo((*raiz)->Dir)) + 1;
	*raiz = balancear(*raiz);

	return inseriu;
}

void imprimir(Arvavl *raiz)
{ // imprime os elementos da arvore em pre-ordem
	if (raiz != NULL)
	{
		// printf("%d ", balanceamento(raiz));
		printf("%d\n", raiz->info);
		imprimir(raiz->Esq);
		imprimir(raiz->Dir);
	}
}

void liberar(Arvavl *raiz)
{ // libera a memoria alocada de todos os nos da arvore
	if (raiz != NULL)
	{
		liberar(raiz->Esq);
		liberar(raiz->Dir);
		free(raiz);
	}
}

int buscar(Arvavl *raiz, int valor)
{ // verifica se existe um elemento existe na arvore
	int achou = 0;
	if (raiz != NULL)
	{
		if (raiz->info == valor)
		{
			achou = 1;
		}
		else if (valor < raiz->info)
		{
			achou = buscar(raiz->Esq, valor);
		}
		else
		{
			achou = buscar(raiz->Dir, valor);
		}
	}
	return achou;
}

int proMax(Arvavl *raiz)
{ // procura o no folha mais profundo
	int ret, esq = 0, dir = 0;
	if (raiz == NULL)
	{
		ret = -1;
	}
	else
	{
		esq = proMax(raiz->Esq);
		dir = proMax(raiz->Dir);
		if (esq > dir)
		{
			ret = esq + 1;
		}
		else
		{
			ret = dir + 1;
		}
	}

	return ret;
}

int proMin(Arvavl *raiz)
{ // procura o no folha menos profundo
	int ret;
	if (raiz == NULL)
	{
		ret = -1;
	}
	else if (raiz->Esq == NULL && raiz->Dir == NULL)
	{
		ret = 0;
	}
	else if (!raiz->Esq)
	{
		ret = proMin(raiz->Dir) + 1;
	}
	else if (!raiz->Dir)
	{
		ret = proMin(raiz->Esq) + 1;
	}
	else
	{
		ret = min(proMin(raiz->Esq), proMin(raiz->Dir)) + 1;
	}

	return ret;
}

int min(int a, int b)
{ // função para buscar o menor valor entre dois elementos
	if (a < b)
	{
		b = a;
	}
	return b;
}
