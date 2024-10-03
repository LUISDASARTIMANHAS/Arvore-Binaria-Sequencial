//Feito por: Lucas Garcia E Luis Augusto
#include "ArvoreBinariaSequencial.h"

//=================================================
/**
 * @brief Abre um arquivo com o modo especificado.
 * 
 * @param nomeArq Nome do arquivo.
 * @param modo Modo de abertura do arquivo (ex: "r", "w").
 * @return FILE* Ponteiro para o arquivo aberto.
 */
FILE *abrirArquivo(char *nomeArq, char *modo) {
    FILE *arq = fopen(nomeArq, modo);
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo.\n");
        exit(-1);
    }
    printf("INFO: Arquivo Aberto! Bom uso.\n");
    return arq;
}
//=================================================
/**
 * @brief Calcula e exibe o tempo de execução em segundos.
 * 
 * @param ini Tempo inicial.
 * @param fim Tempo final.
 */
void calcularTempo(double ini, double fim) {
    double tempoDecorrido = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", tempoDecorrido);
}
//=================================================
/**
 * @brief Salva os dados da árvore binária no arquivo.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param arquivoLista Ponteiro para o arquivo onde os dados serão salvos.
 */
void salvarDadosNoArquivo(ArvoreBinaria *arvore, FILE *arquivoLista) {
    for (int i = 0; i < arvore->capacidade; i++) {
        if (arvore->elementos[i].ocupado) {
            fprintf(arquivoLista, "%s\n%lld\n", arvore->elementos[i].nome, arvore->elementos[i].matricula);
        }
    }
    printf("INFO: Dados salvos com sucesso no arquivo.\n");
}
//=================================================
/**
 * @brief Inicializa a árvore binária com uma capacidade baseada na quantidade de matrículas.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param quantidadeMatriculas Quantidade inicial de matrículas.
 */
void inicializarArvore(ArvoreBinaria *arvore, int quantidadeMatriculas) {
    arvore->capacidade = (int)(quantidadeMatriculas * FATOR_SEGURANCA);
    arvore->tamanho = 0;
    arvore->elementos = (NoArvore *)malloc(arvore->capacidade * sizeof(NoArvore));

    if (arvore->elementos == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < arvore->capacidade; i++) {
        arvore->elementos[i].ocupado = 0; // Inicializa todos os nós como vazios
    }
}
//=================================================
/**
 * @brief Redimensiona a árvore binária quando sua capacidade é atingida.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void redimensionarArvore(ArvoreBinaria *arvore) {
    int novaCapacidade = arvore->capacidade * FATOR_SEGURANCA;
    NoArvore *novoArray = (NoArvore *)realloc(arvore->elementos, novaCapacidade * sizeof(NoArvore));

    if (novoArray == NULL) {
        printf("Erro ao redimensionar a árvore.\n");
        exit(1);
    }

    // Atualizar ponteiros e capacidade
    arvore->elementos = novoArray;
    arvore->capacidade = novaCapacidade;

    // Inicializa os novos espaços alocados como vazios
    for (int i = arvore->tamanho; i < arvore->capacidade; i++) {
        arvore->elementos[i].ocupado = 0;
    }

    printf("Arvore redimensionada para %d elementos.\n", arvore->capacidade);
}
//=================================================
/**
 * @brief Libera a memória alocada para a árvore binária.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void liberarArvore(ArvoreBinaria *arvore) {
    if (arvore->elementos != NULL) {
        free(arvore->elementos);
        arvore->elementos = NULL;
    }
    arvore->tamanho = 0;
    arvore->capacidade = 0;
}
//=================================================
/**
 * @brief Imprime os elementos da árvore binária em ordem.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param indice Índice do nó atual.
 */
void imprimirEmOrdem(ArvoreBinaria *arvore, int indice) {
    if (indice >= arvore->capacidade || !arvore->elementos[indice].ocupado) {
        return;
    }

    // Percorrer o filho esquerdo
    imprimirEmOrdem(arvore, 2 * indice + 1);

    // Imprimir o nó atual
    printf("Matrícula: %lld, Nome: %s\n", arvore->elementos[indice].matricula, arvore->elementos[indice].nome);

    // Percorrer o filho direito
    imprimirEmOrdem(arvore, 2 * indice + 2);
}
//=================================================
/**
 * @brief Exibe o menu de ações para a árvore binária e retorna a opção escolhida.
 * 
 * @return long long int A opção escolhida pelo usuário.
 */
long long int pedirOpcao() {
    int op;
    printf("\n--- Menu Principal ---\n");
    do {
        printf("1 - Inserir na Arvore\n");
        printf("2 - Exibir a Arvore\n");
        printf("3 - Excluir da Arvore\n");
        printf("4 - Pesquisar na Arvore\n");
        printf("5 - Total de Matriculas\n");
        printf("6 - Percorrer toda a Arvore\n");
        printf("7 - Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &op);
    } while ((op < 1) || (op > 7));
    return op;
}
//=================================================
/**
 * @brief Solicita ao usuário um número para inserção ou exclusão na árvore binária.
 * 
 * @param caminhoASerEscolhido Define o caminho escolhido (0 para inserir, 1 para excluir).
 * @return long long int O número solicitado ao usuário.
 */
long long int pedirNum(int caminhoASerEscolhido) {
    long long int num;
    if (caminhoASerEscolhido == 0) {
        printf("Digite um numero para ser inserido: ");
        scanf("%lld", &num);
    } else {
        printf("Digite um numero para ser excluido: ");
        scanf("%lld", &num);
    }
    return num;
}
//=================================================
/**
 * @brief Imprime todos os elementos da árvore binária, incluindo suas relações de parentesco.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void imprimirVetorCompleto(ArvoreBinaria *arvore) {
    printf("\n===| Impressão Completa do Vetor da Árvore |===\n\n");
    for (int i = 0; i < arvore->capacidade; i++) {
        if (arvore->elementos[i].ocupado) {
            if (i == 0) {
                printf("Índice %d: Matrícula: %lld, Nome: %s (Raiz)\n", i, arvore->elementos[i].matricula, arvore->elementos[i].nome);
            } else {
                int parentIndex = (i - 1) / 2;
                if (2 * parentIndex + 1 == i) {
                    printf("Índice %d: Matrícula: %lld, Nome: %s (Filho Esquerdo de %lld)\n", i, arvore->elementos[i].matricula, arvore->elementos[i].nome, arvore->elementos[parentIndex].matricula);
                } else {
                    printf("Índice %d: Matrícula: %lld, Nome: %s (Filho Direito de %lld)\n", i, arvore->elementos[i].matricula, arvore->elementos[i].nome, arvore->elementos[parentIndex].matricula);
                }
            }
        } else {
            printf("Índice %d: (vazio)\n", i);
        }
    }
    printf("\n==============================================\n");
}
//=================================================
/**
 * @brief Menu principal do programa para interagir com a árvore binária.
 * 
 * @param arvore Ponteiro para a árvore binária.
 */
void menuPrincipal(ArvoreBinaria *arvore) {
    long long int op;
    long long int numInseri;
    char nomeInseri[100];
    int repete = 0;
    do {
        op = pedirOpcao();
        switch (op) {
            case 1:
                // Inserir na Árvore Binária
                numInseri = pedirNum(0);
                printf("Digite o nome associado à matrícula: ");
                getchar();  // Para evitar problemas com a leitura do '\n' residual
                fgets(nomeInseri, sizeof(nomeInseri), stdin);
                nomeInseri[strcspn(nomeInseri, "\n")] = 0;  // Remover a quebra de linha
                inserirAluno(arvore, numInseri, nomeInseri);
                break;
            case 2:
                // Exibir a Árvore Binária em Ordem
                printf("\n\n===| Exibição da Árvore Binária (Em Ordem) |===\n\n");
                imprimirEmOrdem(arvore, 0);
                break;
            case 3:
                // Excluir da Árvore Binária
                numInseri = pedirNum(1);
                removerAluno(arvore, numInseri);
                break;
            case 4:
                // Pesquisar uma matrícula na Árvore Binária
                numInseri = pedirNum(0);
                buscarAluno(arvore, numInseri);
                break;
            case 5:
                // Exibir total de matrículas na Árvore Binária
                printf("O total de matrículas na árvore é: %d\n", arvore->tamanho);
                break;
            case 6:
                // Imprimir Vetor completo
                imprimirVetorCompleto(arvore);
                break;
            case 7:
                // Sair
                repete = 1;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (repete == 0);
}
//=================================================
/**
 * @brief Conta o número de matrículas no arquivo.
 * 
 * @param arquivoLista Ponteiro para o arquivo de matrícula.
 * @return int O número de matrículas no arquivo.
 */
int contarMatriculas(FILE *arquivoLista) {
    char linha[100];
    int totalMatriculas = 0;
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        totalMatriculas++;
    }
    return totalMatriculas / 2;  // Cada matrícula ocupa duas linhas (nome e matrícula)
}
//=================================================
/**
 * @brief Insere um aluno na árvore binária.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param matricula Matrícula do aluno.
 * @param nome Nome do aluno.
 */
void inserirAluno(ArvoreBinaria *arvore, long long int matricula, char *nome) {
    if (arvore->tamanho >= arvore->capacidade) {
        redimensionarArvore(arvore);
    }

    int i = 0;
    while (i < arvore->capacidade && arvore->elementos[i].ocupado) {
        if (matricula < arvore->elementos[i].matricula) {
            i = 2 * i + 1; // Vai para o filho esquerdo
        } else if (matricula > arvore->elementos[i].matricula) {
            i = 2 * i + 2; // Vai para o filho direito
        } else {
            printf("Matrícula já existente.\n");
            return;
        }
    }

    if (i < arvore->capacidade) {
        arvore->elementos[i].matricula = matricula;
        strcpy(arvore->elementos[i].nome, nome);
        arvore->elementos[i].ocupado = 1;
        arvore->tamanho++;
        printf("Aluno inserido com sucesso!\n");
    } else {
        printf("Erro ao inserir o aluno. Posição inválida.\n");
    }
}
//=================================================
/**
 * @brief Busca um aluno na árvore binária pela matrícula.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param matricula Matrícula do aluno a ser buscado.
 */
void buscarAluno(ArvoreBinaria *arvore, long long int matricula) {
    int i = 0;
    while (i < arvore->capacidade && arvore->elementos[i].ocupado) {
        if (matricula < arvore->elementos[i].matricula) {
            i = 2 * i + 1; // Filho esquerdo
        } else if (matricula > arvore->elementos[i].matricula) {
            i = 2 * i + 2; // Filho direito
        } else {
            printf("Aluno encontrado: %s (Matrícula: %lld)\n", arvore->elementos[i].nome, arvore->elementos[i].matricula);
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}
//=================================================
/**
 * @brief Remove um aluno da árvore binária pela matrícula.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param matricula Matrícula do aluno a ser removido.
 */
void removerAluno(ArvoreBinaria *arvore, long long int matricula) {
    int i = 0;
    while (i < arvore->capacidade && arvore->elementos[i].ocupado) {
        if (matricula < arvore->elementos[i].matricula) {
            i = 2 * i + 1; // Filho esquerdo
        } else if (matricula > arvore->elementos[i].matricula) {
            i = 2 * i + 2; // Filho direito
        } else {
            // Encontrei o nó para remover
            printf("Removendo aluno: %s (Matrícula: %lld)\n", arvore->elementos[i].nome, arvore->elementos[i].matricula);
            arvore->elementos[i].ocupado = 0;
            arvore->tamanho--;
            return;
        }
    }
    printf("Matrícula não encontrada para remoção.\n");
}
//=================================================
/**
 * @brief Lê e insere matrículas da lista de alunos no arquivo.
 * 
 * @param arvore Ponteiro para a árvore binária.
 * @param arquivoLista Ponteiro para o arquivo com as matrículas.
 */
void lerEInserirMatriculas(ArvoreBinaria *arvore, FILE *arquivoLista) {
    rewind(arquivoLista);  // Reposicionar para o início do arquivo
    long long int matricula;
    char nome[100];

    while (fgets(nome, sizeof(nome), arquivoLista) != NULL) {  // Ler o nome
        nome[strcspn(nome, "\n")] = 0;  // Remover o '\n' do nome
        if (fscanf(arquivoLista, "%lld\n", &matricula) != EOF) {  // Ler a matrícula
            inserirAluno(arvore, matricula, nome);  // Inserir na árvore binária
        }
    }
}
//=================================================
/**
 * @brief Função principal do programa.
 * 
 * @return int Código de retorno do programa.
 */
int main() {
    FILE *arquivoLista = abrirArquivo("nomes_matriculas.txt", "r");
    int totalMatriculas = contarMatriculas(arquivoLista);
    printf("Total de matrículas no arquivo: %d\n", totalMatriculas);
    rewind(arquivoLista); // Volta ao início do arquivo

    ArvoreBinaria arvore;
    inicializarArvore(&arvore, totalMatriculas);
    double inicio = clock();
    // Ler as matrículas e inseri-las na árvore
    lerEInserirMatriculas(&arvore, arquivoLista);
    double fim = clock();
    fclose(arquivoLista);
    calcularTempo(inicio,fim);
    // Menu para interação
    menuPrincipal(&arvore);

    // Salvar os dados antes de encerrar
    arquivoLista = abrirArquivo("nomes_matriculas.txt", "w");
    salvarDadosNoArquivo(&arvore, arquivoLista);
    fclose(arquivoLista);

    // Liberar a memória
    liberarArvore(&arvore);

    return 0;
}