//Feito por: Lucas Garcia E Luis Augusto
// Feito por: Lucas Garcia E Luis Augusto
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef char string[101];
typedef clock_t processTime;

#define FATOR_SEGURANCA 100 /**< Define um fator de segurança para a alocação dinâmica (150% do tamanho original) */

/**
 * @brief Estrutura que representa um nó da árvore binária.
 */
typedef struct {
    long long int matricula; /**< Matrícula do aluno. */
    string nome;             /**< Nome do aluno. */
    int ocupado;             /**< Indica se o nó está ocupado (1) ou vazio (0). */
} NoArvore;

/**
 * @brief Estrutura que representa a árvore binária de alunos.
 */
typedef struct {
    NoArvore *elementos; /**< Ponteiro para os nós da árvore. */
    int tamanho;         /**< Número de elementos ocupados na árvore. */
    int capacidade;      /**< Capacidade atual da árvore. */
} ArvoreBinaria;

/**
 * @brief Abre um arquivo com o modo especificado.
 * 
 * @param nomeArq Nome do arquivo.
 * @param modo Modo de abertura do arquivo (ex: "r", "w").
 * @return Ponteiro para o arquivo aberto.
 */
FILE *abrirArquivo(char *nomeArq, char *modo);

/**
 * @brief Calcula e exibe o tempo de processamento.
 * 
 * @param ini Tempo inicial.
 * @param fim Tempo final.
 */
void calcularTempo(double ini, double fim);

/**
 * @brief Salva os dados da árvore binária em um arquivo.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param arquivoLista Ponteiro para o arquivo onde os dados serão salvos.
 */
void salvarDadosNoArquivo(ArvoreBinaria *arvore, FILE *arquivoLista);

/**
 * @brief Inicializa a árvore binária com uma quantidade específica de matrículas.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param quantidadeMatriculas Quantidade inicial de matrículas.
 */
void inicializarArvore(ArvoreBinaria *arvore, int quantidadeMatriculas);

/**
 * @brief Redimensiona a árvore binária quando sua capacidade é atingida.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void redimensionarArvore(ArvoreBinaria *arvore);

/**
 * @brief Imprime os elementos da árvore em ordem.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param indice Índice do nó atual para a impressão.
 */
void imprimirEmOrdem(ArvoreBinaria *arvore, int indice);

/**
 * @brief Libera a memória alocada para a árvore binária.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void liberarArvore(ArvoreBinaria *arvore);

/**
 * @brief Solicita uma opção ao usuário.
 * 
 * @return Retorna a opção escolhida pelo usuário.
 */
long long int pedirOpcao();

/**
 * @brief Solicita ao usuário um número, dado o caminho escolhido.
 * 
 * @param caminhoASerEscolhido Caminho escolhido pelo usuário.
 * @return Número solicitado.
 */
long long int pedirNum(int caminhoASerEscolhido);

/**
 * @brief Exibe o menu principal e lida com a interação do usuário.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void menuPrincipal(ArvoreBinaria *arvore);

/**
 * @brief Conta o número de matrículas presentes no arquivo.
 * 
 * @param arquivoLista Ponteiro para o arquivo que contém as matrículas.
 * @return O número de matrículas no arquivo.
 */
int contarMatriculas(FILE *arquivoLista);

/**
 * @brief Insere um aluno na árvore binária.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param matricula Matrícula do aluno.
 * @param nome Nome do aluno.
 */
void inserirAluno(ArvoreBinaria *arvore, long long int matricula, char *nome);

/**
 * @brief Busca um aluno na árvore binária pela matrícula.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param matricula Matrícula do aluno a ser buscado.
 */
void buscarAluno(ArvoreBinaria *arvore, long long int matricula);

/**
 * @brief Remove um aluno da árvore binária pela matrícula.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param matricula Matrícula do aluno a ser removido.
 */
void removerAluno(ArvoreBinaria *arvore, long long int matricula);

/**
 * @brief Lê e insere matrículas de um arquivo na árvore binária.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param arquivoLista Ponteiro para o arquivo com as matrículas.
 */
void lerEInserirMatriculas(ArvoreBinaria *arvore, FILE *arquivoLista);

/**
 * @brief Imprime os elementos da árvore binária em ordem (função duplicada).
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param indice Índice do nó atual para a impressão.
 */
void imprimirEmOrdem(ArvoreBinaria *arvore, int indice);