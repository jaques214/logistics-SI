/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "../API_Leitura/API_Leitura.h"
#include "gestao_utilizadores.h"

/**
 * Devolve a posição em que ocorre o cliente com o nif dado
 * @param ap_clientes array de clientes
 * @param nElementos nº de clientes no array
 * @param nif identificador do cliente a pesquisar
 * @return índice do cliente, se existir, ou -1 caso contrário
 */
int pesquisa (struct Cliente *ap_clientes, int nElementos, int nif) {
    int i = 0;
    
    while (i < nElementos && ap_clientes[i].nif != nif) {
        i++;
    }
    
    if(i == nElementos) {
        //Não existe esse identificador
        return -1;
    }
    else {
        return i;
    }
}

/**
 * Lê os dados do cliente e guarda numa determinada posição da lista
 * 
 * @param ap_clientes array/apontador de clientes
 * @param pos a posição em que o novo elemento vai ser inserido
 * @param nif identificador do cliente
 */
void dadosCliente(struct Cliente *ap_clientes, int *pos, int nif) {
    ap_clientes[*pos].nif = nif;
    readString(ap_clientes[*pos].nome, (TAM_STR - 1) , "Nome: ");
    readInt(&ap_clientes[*pos].cc , 0, 99999999 , "Número Cartão de Cidadão: ");
    printf("Morada Pré-Definida");
    readString(ap_clientes[*pos].mpredef.rua, (TAM_STR - 1) , "Rua: ");
    readInt(&ap_clientes[*pos].mpredef.num, 0, 9999, "Número: ");
    readString(ap_clientes[*pos].mpredef.localidade, (TAM_STR - 1), "Localidade: ");
    readString(ap_clientes[*pos].mpredef.codPostal, (TAM_STR - 1), "Código-Postal (XXXX-XXX): ");
    readString(ap_clientes[*pos].mpredef.pais, (TAM_STR - 1), "País: ");
    enum Status estado = Ativo;
    ap_clientes[*pos].status = estado;
    (*pos)++;
}

/**
 * Adiciona um cliente à lista de clientes, se possível
 * 
 * @param ap_clientes apontador duplo para o endereço do primeiro cliente da lista
 * @param nElementos apontador para o número de clientes que existem atualmente no array
 * @param tam_max_cli apontador para o tamanho do array clientes
 * @param nif identificador do cliente
 */
void adicionarCliente(struct Cliente **ap_clientes, int *nElementos, int *tam_max_cli, int nif) {
    struct Cliente *novo;
    int pos, tam;
    
    pos = pesquisa(*ap_clientes, *nElementos, nif);
    
    if(pos == -1) {
        //Se o array estiver cheio
        if(*nElementos == *tam_max_cli) {
            tam = ((*nElementos) + TAM_INCREMENTO); 
            novo = realloc(*ap_clientes, tam
                    * sizeof(struct Cliente));
            
            if(novo == NULL) {
                printf("Realocação de memória falhou, cliente não adicionado");
            }
            else {
                printf("Realocou memória. Novo Tamanho %d bytes", 
                        ((*nElementos) + TAM_INCREMENTO) * sizeof(struct Cliente));
                *ap_clientes = novo;
                (*tam_max_cli) += TAM_INCREMENTO;
                dadosCliente(*ap_clientes, nElementos, nif);
            }
        }
        else {
            dadosCliente(*ap_clientes, nElementos, nif);
        }
        printf("A sua conta foi criada com sucesso\n");
    }
    else {
        printf("Esse nif já foi utilizado!\n");
    }
}

/**
 * Devolve um apontador para o cliente com o nif dado, se existir
 * 
 * @param ap_clientes array/apontador de clientes
 * @param nElementos nº elementos no array clientes
 * @param nif identificador do cliente a obter
 * @return um apontador para o cliente, ou NULL se não existir
 * 
 * @pre precisa de ter a função pesquisa declarada antes
 */
struct Cliente* getCliente(struct Cliente *ap_clientes, int nElementos, int nif) {
    int pos;
    
    pos = pesquisa(ap_clientes, nElementos, nif);
    
    if(pos == -1) {
        return NULL;
    }
    else {
        return &ap_clientes[pos];
    }
}

/**
 * Edita a informação do um cliente, se existir
 * 
 * @param ap_clientes array/apontador de clientes
 * @param nElementos nº de clientes no array
 * @param nif identificador do cliente a editar
 */
void editarCliente(struct Cliente *ap_clientes, int nElementos, int nif) {
    struct Cliente *cliente = getCliente(ap_clientes, nElementos, nif);
    
    if(cliente != NULL) {
        readString(cliente->nome, (TAM_STR - 1) , "Nome: ");
        readInt(&cliente->cc , 0, 99999999 , "Número Cartão de Cidadão: ");
        printf("Morada Pré-Definida");
        readString(cliente->mpredef.rua, (TAM_STR - 1) , "Rua: ");
        readInt(&cliente->mpredef.num, 0, 9999, "Número: ");
        readString(cliente->mpredef.localidade, (TAM_STR - 1), "Localidade: ");
        readString(cliente->mpredef.codPostal, (TAM_STR - 1), "Código-Postal (XXXX-XXX): ");
        readString(cliente->mpredef.pais, (TAM_STR - 1), "País: ");
    }
    else {
        printf("Cliente não existe!\n");
    }
}

/**
 * Remove o cliente, mudando o seu estado para desativo, se estiver ativo
 * 
 * @param ap_clientes array/apontador de clientes
 * @param nElementos nº de clientes no array
 * @param nif identificador do cliente a remover/desativar
 */
void removeCliente(struct Cliente *ap_clientes, int nElementos, int nif) {
    struct Cliente *cliente = getCliente(ap_clientes, nElementos, nif);
    
    if(cliente != NULL) {
        if(cliente->status == Ativo) {
            cliente->status = Desativo;
            printf("O cliente foi desativado com sucesso\n");
        }
        else {
            printf("O cliente que pretende desativar já foi desativado.\n");
        }
    }
    else {
        printf("Cliente não existe!\n");
    }
}

/**
 * Reativa o cliente depois o ter o removido/desativado
 * 
 * @param ap_clientes array/apontador de cliente
 * @param nElementos nº de elementos no array clientes
 * @param nif identificador do cliente
 */
void ativarCliente(struct Cliente *ap_clientes, int nElementos, int nif) {
    struct Cliente *cliente = getCliente(ap_clientes, nElementos, nif);
    
    if(cliente != NULL) {
        if(cliente->status == Desativo) {
            cliente->status = Ativo;
            printf("O cliente foi reativado com sucesso.");
        }
        else {
            printf("O cliente já está ativo.");
        }
    }
    else {
        printf("Cliente não existe!\n");
    }
}

/**
 * Escreve o conteúdo da lista de clientes em ficheiro
 * 
 * @param ap_clientes um apontador para o primeiro cliente da lista
 * @param nElementos nº de clientes que existem na lista
 */
void guardarDadosCliente(struct Cliente *ap_clientes, int nElementos)
{
    FILE *f;
    
    if ((f = fopen("dados_cliente.bin", "wb")) == NULL)
    {
        perror("Erro ao abrir o ficheiro.");
    }
    else
    {
        fwrite(&nElementos, sizeof(int), 1, f);
        fwrite(ap_clientes, sizeof(struct Cliente), nElementos, f);
        
        printf("Dados do Cliente guardados\n");
        fclose(f);
    }
}

/**
 * Lê dados de um ficheiro (se existir) e preenche a lista de clientes e o seu número
 * 
 * @param ap_clientes um apontador duplo para o endereço de memória do primeiro cliente a preencher
 * @param nElementos um apontador para o nº de clientes que existem na lista
 * @param tam_max_cli um apontador para o tamanho do array clientes
 */
void carregarDadosCliente(struct Cliente **ap_clientes, int *nElementos, int *tam_max_cli)
{
    FILE *f;
    int n1 = 0;
    
    if ((f = fopen("dados_cliente.bin", "rb")) == NULL)
    {
        *nElementos = 0;
        *tam_max_cli = 0;
        perror("Erro ao abrir o ficheiro.");
    }
    else {
        n1 = fread(nElementos, sizeof(int), 1, f);
        
        if (n1 != 1) {
            printf("Erro ao ler o ficheiro.\n");
            *nElementos = 0;
            *tam_max_cli = 0;
            fclose(f);
        }

        *ap_clientes = (struct Cliente*) malloc((*nElementos) * sizeof(struct Cliente));
        if (*ap_clientes == NULL)
        {
            printf("Impossível alocar memória para os clientes.");
            *nElementos = 0;
            *tam_max_cli = 0;
            fclose(f);
        }
        else {
            printf("Alocou %d bytes de memória para os clientes\n",
            (*nElementos) * sizeof(struct Cliente));
            n1 = fread(*ap_clientes, sizeof(struct Cliente), *nElementos, f);
        
            if(n1 == *nElementos) {
                *tam_max_cli = *nElementos;
                *nElementos = n1;
            }
            else {
                printf("Erro ao ler elementos dos clientes!\n");
                *tam_max_cli = 0;
                *nElementos = 0; 
                free(*ap_clientes);
                fclose(f);
            }
        }
        printf("Dados lidos de ficheiro.\n");
        
        fclose(f);
    }
}