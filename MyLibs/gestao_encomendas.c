/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../API_Leitura/API_Leitura.h"
#include "gestao_utilizadores.h"
#include "gestao_encomendas.h"

/**
 * Devolve a posição em que ocorre a encomenda com o nif do cliente dado
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param nEncomendas nº de encomendas no array
 * @param nif identificador do cliente, que efetuou a encomenda
 * @return índice da encomenda, se existir, ou -1 caso contrário
 */
int pesquisaEncomenda (struct Encomenda *ap_encomendas, int nEncomendas,
        int nif) {
    int i = 0;
    
    while (i < nEncomendas && ap_encomendas[i].nifcliente != nif) {
        i++;
    }
    
    if(i == nEncomendas) {
        //Não existe esse identificador
        return -1;
    }
    else {
        return i;
    }
}

/**
 * Calcula o custo total através do produto entre dados da encomenda e o 
 * somatório dos preços
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param pos a posição em que o novo elemento vai ser inserido
 * @param precos apontador para a estrutura de dados Preco
 */
void calcularTotal(struct Encomenda *ap_encomendas, int pos, struct Preco *precos)
{
    int i,j,peso = 0,volume = 0,fragil = 0,total_tipo = 0;
    if(precos == NULL) {
        printf("O diretor ainda não criou a tabela de preços");
    }else {
    for (i = 0; i < (ap_encomendas + pos)->nartigos; i++) {
        peso += (ap_encomendas + pos)->artigo[i].peso;
        volume += (ap_encomendas + pos)->artigo[i].volume;
        if((ap_encomendas + pos)->artigo[i].descricao == Fragil){
            fragil = 1;
        }
    }
    i = (ap_encomendas + pos)->endereco_destino.codPostal[0] - '0';
    j = (ap_encomendas + pos)->endereco_origem.codPostal[0] -'0';
    i--;
    j--;
    if((ap_encomendas + pos)->tipo_transporte == Regular){
    total_tipo += (precos)->regular;
    }else{
    total_tipo += (precos)->urgente;
    }
    if(peso > 20){
        total_tipo += (precos)->pesada;
    } 
    if(volume > 0.125){
        total_tipo += (precos)->volumosa;
    }
    if(fragil == 1){
        total_tipo += (precos)->fragil;
    }
    (ap_encomendas + pos)->custo_total = (total_tipo + ((ap_encomendas + pos)->distancia_km * (precos)->km))*(precos)->codip[i][j];
    printf("O custo da encomenda será: %.2f€\n",(ap_encomendas + pos)->custo_total);
    }
}

/**
 * Lê os dados da encomenda e guarda numa determinada posição da lista
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param ap_clientes array/apontador de clientes
 * @param pos a posição em que o novo elemento vai ser inserido
 * @param nElementos apontador para o nº de clientes no array
 * @param nif indentificador do cliente, que faz a encomenda
 * @param precos apontador para a estrutura de dados Preco
 * 
 * @pre precisa da função getCliente para copiar os dados da morada de
 * origem do cliente na mesma posição que o nif inserido
 */
void dadosEncomenda(struct Encomenda *ap_encomendas, struct Cliente *ap_clientes,
        int *pos, int *nElementos, int nif, struct Preco *precos) {
    int morada, i, opt,tipo;
    struct Cliente *cliente = getCliente(ap_clientes, *nElementos, nif);
   
    for (i = 0; i < (ap_encomendas + *pos)->nartigos; i++) {
        printf("\nArtigo nº%d:\n", i + 1);
        readFloat(&(ap_encomendas + *pos)->artigo[i].peso, 0.0, 999.99, "Peso (kg): ");
        readFloat(&(ap_encomendas + *pos)->artigo[i].volume, 0.0, 999.99, "Volume (m^3): ");
        readInt(&opt, 0, 1, "O artigo requer tratamento especial?\n1 - Sim   0 - Não\n");
        if(opt == 0)
            (ap_encomendas + *pos)->artigo[i].descricao = NFragil;
        else
            (ap_encomendas + *pos)->artigo[i].descricao = Fragil;
    }
    
    if(cliente != NULL) {
        readInt(&morada, 0, 1, "Quer alterar a morada de origem do cliente?\n1 - Sim   0 - Não\n");
        ap_encomendas[*pos].nifcliente = cliente->nif;
        
    if(morada == 1) {
        printf("Morada Origem:");
        readString(ap_encomendas[*pos].endereco_origem.rua, (TAM_STR - 1) , "Rua: ");
        readInt(&ap_encomendas[*pos].endereco_origem.num, 0, 9999, "Número: ");
        readString(ap_encomendas[*pos].endereco_origem.localidade, (TAM_STR - 1), "Localidade: ");
        readString(ap_encomendas[*pos].endereco_origem.codPostal, (TAM_STR - 1), "Código-Postal (XXXX-XXX): ");
        readString(ap_encomendas[*pos].endereco_origem.pais, (TAM_STR - 1), "País: ");
    }
    else {
        printf("Morada Origem:\n");
        strcpy(ap_encomendas[*pos].endereco_origem.rua, cliente->mpredef.rua);
        ap_encomendas[*pos].endereco_origem.num = cliente->mpredef.num;
        strcpy(ap_encomendas[*pos].endereco_origem.localidade, cliente->mpredef.localidade);
        strcpy(ap_encomendas[*pos].endereco_origem.codPostal, cliente->mpredef.codPostal);
        strcpy(ap_encomendas[*pos].endereco_origem.pais, cliente->mpredef.pais);
            printf("Rua: %s\nNúmero: %d\nLocalidade %s\n"
            "Código-Postal (XXXX-XXX): %s\nPaís: %s\n",
            ap_encomendas[*pos].endereco_origem.rua,
            ap_encomendas[*pos].endereco_origem.num,
            ap_encomendas[*pos].endereco_origem.localidade,
            ap_encomendas[*pos].endereco_origem.codPostal,
            ap_encomendas[*pos].endereco_origem.pais);
    }
    printf("\nMorada Destino:");
    readString(ap_encomendas[*pos].endereco_destino.rua, (TAM_STR - 1) , "Rua: ");
    readInt(&ap_encomendas[*pos].endereco_destino.num, 0, 9999, "Número: ");
    readString(ap_encomendas[*pos].endereco_destino.localidade, (TAM_STR - 1), "Localidade: ");
    readString(ap_encomendas[*pos].endereco_destino.codPostal, 9, "Código-Postal (XXXX-XXX): ");
    readString(ap_encomendas[*pos].endereco_destino.pais, (TAM_STR - 1), "País: ");
    
    readFloat(&ap_encomendas[*pos].distancia_km, 0.0, 9999.99, "Introduza a distância a percorrer em km: ");
    
    readInt(&tipo, 0, 1, "Qual o tipo de transporte da encomenda?\n0 - Regular   1 - Urgente\n");
    
    if(tipo == 0) {
        (ap_encomendas + *pos)->tipo_transporte = Regular;
    }
    else {
       (ap_encomendas + *pos)->tipo_transporte = Urgente;
    }
    
    calcularTotal(ap_encomendas, *pos, precos);
    
    enum Expedicao estado = NExpedida;
    ap_encomendas[*pos].expedicao = estado;
    (*pos)++;
    }
    else {
        printf("Cliente não existe!\n");
    }
}

/**
 * Adiciona uma ou mais encomendas à lista de encomendas, juntamente com os artigos
 * 
 * @param ap_encomendas apontador duplo para o endereço da primeira encomenda da lista
 * @param precos apontador para a estrutura de dados Preco
 * @param ap_clientes array/apontador de clientes
 * @param nEncomendas apontador para o número de encomendas que existem atualmente no array
 * @param nElementos apontador para o número de clientes que existem atualmente no array
 * @param tam_max_enc apontador para o tamanho do array encomendas
 * @param nif identificador do cliente, que adiciona a encomenda
 */
void adicionarEncomenda(struct Encomenda **ap_encomendas, struct Preco *precos,
        struct Cliente *ap_clientes, int *nEncomendas, int *nElementos, int *tam_max_enc, int nif) {
    struct Encomenda *novo;
    int numArtigos;
    int tam;
    
        //Se o array estiver cheio
        if(*nEncomendas == *tam_max_enc) {
            tam = ((*nEncomendas) + TAM_INCREMENTO); 
            novo = realloc(*ap_encomendas, tam * sizeof(struct Encomenda));
            
            if(novo == NULL) {
                printf("Realocação de memória falhou, encomenda não adicionada");
            }
            else {
                printf("Realocou memória. Novo Tamanho %d bytes", 
                        tam * sizeof(struct Encomenda));
                *ap_encomendas = novo;
                (*tam_max_enc) += TAM_INCREMENTO;
               
                readInt(&(*ap_encomendas + *nEncomendas)->nartigos, 1, 100, "Insira o número de artigos: ");
                numArtigos = (*ap_encomendas + *nEncomendas)->nartigos;
                (*ap_encomendas + *nEncomendas)->artigo = (struct Artigo*)
                        malloc(numArtigos * sizeof(struct Artigo));
                if( (*ap_encomendas + *nEncomendas)->artigo == NULL) {
                     printf("A alocação de memória para os artigos falhou!\n");
                }
                else {
                    dadosEncomenda(*ap_encomendas, ap_clientes, nEncomendas, nElementos, nif, precos);
                }
            }
        }
        else {
            readInt(&(*ap_encomendas + *nEncomendas)->nartigos, 1, 100, "Insira o número de artigos: ");
            numArtigos = (*ap_encomendas + *nEncomendas)->nartigos;
            (*ap_encomendas + *nEncomendas)->artigo = (struct Artigo*)malloc(numArtigos * sizeof(struct Artigo));
               
                if( (*ap_encomendas + *nEncomendas)->artigo == NULL) {
                     printf("A alocação de memória para os artigos falhou!\n");
                }
                else {
                    dadosEncomenda(*ap_encomendas, ap_clientes, nEncomendas, nElementos, nif, precos);
                }
                 
        }
}

/**
 * Devolve todas as encomendas e artigos que um cliente inseriu
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param nEncomendas nº de encomendas no array
 * @param nif identificador do cliente, que efetuou a encomenda
 */
void consultarEstado(struct Encomenda* ap_encomendas, int nEncomendas, int nif)
{
    int i, j, pos;
    pos = pesquisaEncomenda(ap_encomendas, nEncomendas, nif);
    
    if (pos != -1) {
    for(i = 0; i < nEncomendas; i++) {
        if(ap_encomendas[i].nifcliente == nif) {
            printf("Encomenda Nº%d\n", i + 1);
            printf("\tNIF do Cliente: %d\n", ap_encomendas[i].nifcliente);
          
            for (j = 0; j < (ap_encomendas + i)->nartigos; j++) {
                printf("\tArtigo nº%d:\n", j+1);
                printf("\t\tPeso: %.2f kg\n", (ap_encomendas + i)->artigo[j].peso);
                printf("\t\tVolume: %.2f m^3\n", (ap_encomendas + i)->artigo[j].volume);
                    if((ap_encomendas + i)->artigo[j].descricao == 0)
                        printf("\t\tEncomenda não frágil\n");
                    else
                        printf("\t\tEncomenda Frágil\n");
            }
            printf("\tMorada Origem:\n");
            printf("\t\tRua: %s\n", ap_encomendas[i].endereco_origem.rua);
            printf("\t\tNúmero: %d\n", ap_encomendas[i].endereco_origem.num);
            printf("\t\tLocalidade: %s\n", ap_encomendas[i].endereco_origem.localidade);
            printf("\t\tCódigo-Postal: %s\n", ap_encomendas[i].endereco_origem.codPostal);
            printf("\t\tPaís: %s\n", ap_encomendas[i].endereco_origem.pais);
            printf("\tMorada Destino:\n");
            printf("\t\tRua: %s\n", ap_encomendas[i].endereco_destino.rua);
            printf("\t\tNúmero: %d\n", ap_encomendas[i].endereco_destino.num);
            printf("\t\tLocalidade: %s\n", ap_encomendas[i].endereco_destino.localidade);
            printf("\t\tCódigo-Postal: %s\n", ap_encomendas[i].endereco_destino.codPostal);
            printf("\t\tPaís: %s\n", ap_encomendas[i].endereco_destino.pais);
            if((ap_encomendas + i)->tipo_transporte == 0)
                printf("\tTransporte Regular\n");
            else
                printf("\tTransporte Urgente\n");
            
            printf("\tCusto Total da Encomenda: %.2f€\n",ap_encomendas[i].custo_total);
            if (ap_encomendas[i].expedicao == 0) {
                printf("\tEstado: Não expedida\n");
            }
            else {
                printf("\tEstado: Expedida\n");
                printf("\tData de Envio: \n\t\tData: %d-%d-%d \n\t\tHora: %d:%d\n",ap_encomendas[i].hora_envio.tm_mday , 
                ap_encomendas[i].hora_envio.tm_mon + 1,ap_encomendas[i].hora_envio.tm_year + 1900, 
                ap_encomendas[i].hora_envio.tm_hour, 
                ap_encomendas[i].hora_envio.tm_min);
            }
        }
    }
    }
    else {
        printf("Nenhuma encomenda encontrada nos seus registos");
    }
}

void verEncomendas(struct Encomenda* ap_encomendas, int nEncomendas, int nif)
{
    int i, j, pos;
    pos = pesquisaEncomenda(ap_encomendas, nEncomendas, nif);
    
    if (pos != -1) {
    for(i = 0; i < nEncomendas; i++) {
        printf("Encomenda Nº%d\n", i + 1);
        printf("\tNIF do Cliente: %d\n", ap_encomendas[i].nifcliente);
          
            for (j = 0; j < (ap_encomendas + i)->nartigos; j++) {
                printf("\tArtigo nº%d:\n", j+1);
                printf("\t\tPeso: %.2f kg\n", (ap_encomendas + i)->artigo[j].peso);
                printf("\t\tVolume: %.2f m^3\n", (ap_encomendas + i)->artigo[j].volume);
                    if((ap_encomendas + i)->artigo[j].descricao == 0)
                        printf("\t\tEncomenda não frágil\n");
                    else
                        printf("\t\tEncomenda Frágil\n");
            }
            printf("\tMorada Origem:\n");
            printf("\t\tRua: %s\n", ap_encomendas[i].endereco_origem.rua);
            printf("\t\tNúmero: %d\n", ap_encomendas[i].endereco_origem.num);
            printf("\t\tLocalidade: %s\n", ap_encomendas[i].endereco_origem.localidade);
            printf("\t\tCódigo-Postal: %s\n", ap_encomendas[i].endereco_origem.codPostal);
            printf("\t\tPaís: %s\n", ap_encomendas[i].endereco_origem.pais);
            printf("\tMorada Destino:\n");
            printf("\t\tRua: %s\n", ap_encomendas[i].endereco_destino.rua);
            printf("\t\tNúmero: %d\n", ap_encomendas[i].endereco_destino.num);
            printf("\t\tLocalidade: %s\n", ap_encomendas[i].endereco_destino.localidade);
            printf("\t\tCódigo-Postal: %s\n", ap_encomendas[i].endereco_destino.codPostal);
            printf("\t\tPaís: %s\n", ap_encomendas[i].endereco_destino.pais);
            if((ap_encomendas + i)->tipo_transporte == 0)
                printf("\tTransporte Regular\n");
            else
                printf("\tTransporte Urgente\n");
            
            printf("\tCusto Total da Encomenda: %.2f€\n",ap_encomendas[i].custo_total);
            if (ap_encomendas[i].expedicao == 0) {
                printf("\tEstado: Não expedida\n");
            }
            else {
                printf("\tEstado: Expedida\n");
                printf("\tData de Envio: \n\t\tData: %d-%d-%d \n\t\tHora: %d:%d\n",ap_encomendas[i].hora_envio.tm_mday , 
                ap_encomendas[i].hora_envio.tm_mon + 1,ap_encomendas[i].hora_envio.tm_year + 1900, 
                ap_encomendas[i].hora_envio.tm_hour, 
                ap_encomendas[i].hora_envio.tm_min);
            }
    }
    }
    else {
        printf("Nenhuma encomenda encontrada nos seus registos");
    }
}

/**
 * Altera o estado da encomenda para expedida, fornecendo a data/hora de envio
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param pos a posicao atual do array encomendas
 */
void alterarEstado(struct Encomenda *ap_encomendas, int pos){
    if((ap_encomendas+pos)->expedicao == 0){
    time_t t = time(NULL);
    (ap_encomendas+pos)->hora_envio = *localtime(&t);
    (ap_encomendas+pos)->expedicao = 1;
    printf("O estado da encomenda foi mudado para expedida com sucesso!\n");
    }else{
    printf("A encomenda já foi expedida impossível alterar estado!\n");
    }
}

/**
 * Remove uma encomenda e os seus artigos dado nº da encomenda
 * 
 * @param ap_encomendas apontador duplo para o endereço do array encomenda
 * @param nEncomendas apontador para o nº de encomendas que existem atualmente no array
 * @param tam_max_enc apontador para o tamanho do array
 */
void removerEncomenda(struct Encomenda **ap_encomendas, int *nEncomendas, int *tam_max_enc) {
    int i;
    struct Encomenda *novo;
    //pos = pesquisaEncomenda (*ap_encomendas, *nEncomendas, nif);
    readInt(&i, 1, *nEncomendas, "Introduza o número da encomenda que deseja remover? ");
    i--;
    
    if((*ap_encomendas)[i].expedicao == 0) {
    while (i < (*nEncomendas) - 1) {
        (*ap_encomendas)[i] = (*ap_encomendas)[i+1];
        i++;
    }
    (*nEncomendas)--;
    printf("Encomenda foi removida!\n");
    
    if(*tam_max_enc - ( *nEncomendas - 1) >= TAM_DECREMENTO) {
        novo = realloc(*ap_encomendas, ((*tam_max_enc) *sizeof(struct Encomenda))-
        TAM_DECREMENTO*sizeof(struct Encomenda));
            
        if(novo == NULL) {
            printf("Realocação de memória falhou.\n");
        }
        else {
            *ap_encomendas = novo;
            (*tam_max_enc) -= TAM_DECREMENTO;
         }
    }
    }
    else {
        printf("Não é possível eliminar uma encomenda expedida");
    }
}

void adicionarArtigo(struct Encomenda **ap_encomendas, struct Preco *precos, int pos) {
    struct Artigo *novo;
    int numArtigos, tratEsp;
    numArtigos = (*ap_encomendas + pos)->nartigos + 1; 
    novo = realloc((*ap_encomendas + pos)->artigo, numArtigos*sizeof(struct Artigo));
    if(novo == NULL) {
        printf("Realocação de memória falhou, artigo não adicionado");
    }
    else {
        (*ap_encomendas + pos)->artigo = novo;
        printf("\nArtigo nº%d:\n", numArtigos);
        readFloat(&(*ap_encomendas + pos)->artigo[(*ap_encomendas + pos)->nartigos].peso, 0.0, 999.99, "Peso: ");
        readFloat(&(*ap_encomendas + pos)->artigo[(*ap_encomendas + pos)->nartigos].volume, 0.0, 999.99, "Volume: ");
        readInt(&tratEsp, 0, 1, "O artigo requer tratamento especial?\n1 - Sim   0 - Não\n");
        if(tratEsp == 0)
            (*ap_encomendas + pos)->artigo[(*ap_encomendas + pos)->nartigos].descricao = NFragil;
        else
            (*ap_encomendas + pos)->artigo[(*ap_encomendas + pos)->nartigos].descricao = Fragil;
        ((*ap_encomendas + pos)->nartigos)++;
        calcularTotal(*ap_encomendas, pos, precos);
    }
}

void removerArtigo(struct Encomenda **ap_encomendas, struct Preco *precos, int pos) {
    struct Artigo *novo;
    int j, numArtigos;
    if((*ap_encomendas + pos)->nartigos == 1) {
        printf("A encomenda só tem um artigo. Se deseja remover o artigo cancele a encomenda\n");
    }
    else {
        readInt(&j, 1, (*ap_encomendas + pos)->nartigos, "Qual o artigo que deseja remover? ");
        j--;
        while (j < (*ap_encomendas + pos)->nartigos - 1) {
            (*ap_encomendas + pos)->artigo[j] = (*ap_encomendas + pos)->artigo[j+1];
            j++;
        }
        printf("Artigo removido!\n");
        numArtigos = (*ap_encomendas + pos)->nartigos; 
        if(numArtigos - ((*ap_encomendas + pos)->nartigos - TAM_DECREMENTO) >= 1) {
            novo = realloc((*ap_encomendas + pos)->artigo, (numArtigos *sizeof(struct Artigo))-
                TAM_DECREMENTO*sizeof(struct Artigo));
            
            if(novo == NULL) {
                printf("Realocação de memória falhou.\n");
            }
            else {
                ((*ap_encomendas + pos)->nartigos)--;
                (*ap_encomendas + pos)->artigo = novo;
                calcularTotal(*ap_encomendas, pos, precos);
            }
        }
    }
}

/**
 * Altera a informação da encomenda ou adiciona, edita e remove artigos
 * 
 * @param ap_encomendas apontador duplo para o endereço do array encomenda
 * @param nEncomendas o nº de encomendas no array
 * @param nifcliente identificador do cliente, que efetuou a encomenda
 * @param precos apontador para a estrutura de dados Preco
 */
void alterarEncomenda(struct Encomenda **ap_encomendas, int nEncomendas,
        int nifcliente, struct Preco *precos) {
    int i, j, opt,opt1;
    if (nEncomendas == 0) {
        printf("Ainda não inseriu nenhuma encomenda");
    }
    else {
        readInt(&i, 1, nEncomendas, "Introduza o número da encomenda que deseja alterar? ");
        i--;
        if((*ap_encomendas + i)->expedicao != Expedida && 
                (*ap_encomendas + i)->nifcliente == nifcliente) {
        do {
            readInt(&opt, 0, 2, "Qual alteração deseja efetuar na encomenda:\n1 - Alteração Artigo\n"
                "2 - Alteração Encomenda\nSelecione uma das opções: ");
        switch(opt) {
            case 1:
                do {
                for (j = 0; j < (*ap_encomendas + i)->nartigos; j++) {
                printf("\tArtigo nº%d:\n", j+1);
                printf("\t\tPeso: %.2f\n", (*ap_encomendas + i)->artigo[j].peso);
                printf("\t\tVolume: %.2f\n", (*ap_encomendas + i)->artigo[j].volume);
                    if((*ap_encomendas + i)->artigo[j].descricao == 0)
                        printf("\t\tEncomenda não frágil\n");
                    else
                        printf("\t\tEncomenda Frágil\n");
                 }
                readInt(&opt1,0,3,"Menu Alteração Artigo\n1 - Adicionar "
                        "Artigo\n2 - Alterar Artigo\n3 - Remover Artigo\n0 - Cancelar\n");
                switch(opt1){
                    case 1: adicionarArtigo(ap_encomendas, precos, i);
                        break;
                    case 2:
                        readInt(&j,1,(*ap_encomendas + i)->nartigos,"Introduza o "
                                "número do artigo que deseja alterar");
                        printf("\nArtigo nº%d:\n", j);
                        j--;
                        readFloat(&(*ap_encomendas + i)->artigo[j].peso, 0.0, 999.99, "Peso: ");
                        readFloat(&(*ap_encomendas + i)->artigo[j].volume, 0.0, 999.99, "Volume: ");
                        readInt(&opt, 0, 1, "O artigo requer tratamento especial?\n1 - Sim   0 - Não\n");
                        if(opt == 0)
                            (*ap_encomendas + i)->artigo[j].descricao = NFragil;
                        else
                            (*ap_encomendas + i)->artigo[j].descricao = Fragil;
                        
                        calcularTotal(*ap_encomendas, i, precos);
                        break;
                    case 3: removerArtigo(ap_encomendas, precos, i);
                        break;
                    case 0: printf("A voltar");
                        break;
                }
                }while(opt1 != 0);
            break;
            case 2:
                do {
                   readInt(&opt1, 0, 3, "Menu Alteração Encomenda\n1 - Alterar Morada de Origem\n"
                   "2 - Alterar Morada de Destino\n3 - Alterar Tipo de Transporte\n0 - Cancelar\n"); 
                   switch(opt1) {
                       case 0: printf("A voltar");
                           break;
                       case 1:
                           printf("Morada Origem:");
                            readString((*ap_encomendas + i)->endereco_origem.rua, (TAM_STR - 1) , "Rua: ");
                            readInt(&(*ap_encomendas + i)->endereco_origem.num, 0, 9999, "Número: ");
                            readString((*ap_encomendas + i)->endereco_origem.localidade, (TAM_STR - 1), "Localidade: ");
                            readString((*ap_encomendas + i)->endereco_origem.codPostal, (TAM_STR - 1), "Código-Postal (XXXX-XXX): ");
                            readString((*ap_encomendas + i)->endereco_origem.pais, (TAM_STR - 1), "País: ");
                            readFloat(&(*ap_encomendas + i)->distancia_km, 0.0, 9999.99, "Introduza a distância a percorrer em km:");
                            calcularTotal(*ap_encomendas, i, precos);
                           break;
                       case 2:
                            printf("Morada Destino:");
                            readString((*ap_encomendas + i)->endereco_destino.rua, (TAM_STR - 1) , "Rua: ");
                            readInt(&(*ap_encomendas + i)->endereco_destino.num, 0, 9999, "Número: ");
                            readString((*ap_encomendas + i)->endereco_destino.localidade, (TAM_STR - 1), "Localidade: ");
                            readString((*ap_encomendas + i)->endereco_destino.codPostal, (TAM_STR - 1), "Código-Postal (XXXX-XXX): ");
                            readString((*ap_encomendas + i)->endereco_destino.pais, (TAM_STR - 1), "País: ");
                            readFloat(&(*ap_encomendas + i)->distancia_km, 0.0, 9999.99, "Introduza a distância a percorrer em km:");
                            calcularTotal(*ap_encomendas, i, precos);
                           break;
                       case 3:     
                            if((*ap_encomendas + i)->tipo_transporte == Urgente) {
                                (*ap_encomendas + i)->tipo_transporte = Regular;
                            }
                            else {
                               (*ap_encomendas + i)->tipo_transporte = Urgente;
                            }
                            calcularTotal(*ap_encomendas, i, precos);
                            printf("O tipo de transporte foi alterado com sucesso");
                           break;
                   }
                }
                while (opt1 != 0);   
        
            break;
        }
        }
        while (opt != 0);
        }
        else {
            printf("Impossível alterar encomenda\n");
        }          
    }
}

/**
 * Escreve o conteúdo da lista de encomendas em ficheiro
 * 
 * @param ap_encomendas um apontador para a primeira encomenda da lista
 * @param nEncomendas nº de encomendas que existem na lista
 */
void guardarDadosEncomenda(struct Encomenda *ap_encomendas, int nEncomendas)
{
    FILE *f;
    int i;
    
    if ((f = fopen("dados_encomenda.bin", "wb")) == NULL)
    {
        perror("Erro ao abrir o ficheiro.");
    }
    else
    {
        fwrite(&nEncomendas, sizeof(int), 1, f);
        fwrite(ap_encomendas, sizeof(struct Encomenda), nEncomendas, f);
        
        //escrever cada lista de artigos
        for (i=0; i < nEncomendas; i++) {
            fwrite(ap_encomendas[i].artigo, sizeof(struct Artigo), ap_encomendas[i].nartigos, f);
        }
        printf("Dados da Encomenda guardados");
        fclose(f);
    }
}

/**
 * Lê dados de um ficheiro (se existir) e preenche a lista de encomendas e o seu número
 * 
 * @param ap_encomendas um apontador duplo para o endereço de memória da primeira encomenda a preencher
 * @param nEncomendas um apontador para o nº de encomendas que existem na lista
 * @param tam_max_enc um apontador para o tamanho do array encomendas
 */
void carregarDadosEncomenda(struct Encomenda **ap_encomendas, int *nEncomendas, int *tam_max_enc)
{
    FILE *f;
    int i, n1 = 0;
    
    if ((f = fopen("dados_encomenda.bin", "rb")) == NULL)
    {
        *nEncomendas = 0;
        *tam_max_enc = 0;
        perror("Erro ao abrir o ficheiro.");
    }
    else {
        n1 = fread(nEncomendas, sizeof(int), 1, f);
        
        if (n1 != 1) {
            printf("Erro ao ler o ficheiro.\n");
            *nEncomendas = 0;
            *tam_max_enc = 0;
            fclose(f);
        }

        *ap_encomendas = (struct Encomenda*) malloc((*nEncomendas) * sizeof(struct Encomenda));
        if (*ap_encomendas == NULL)
        {
            printf("Impossível alocar memória para as encomendas.");
            *nEncomendas = 0;
            *tam_max_enc = 0;
            fclose(f);
        }
        else {
            printf("Alocou %d bytes de memória para as encomendas\n",
            (*nEncomendas) * sizeof(struct Encomenda));
            n1 = fread(*ap_encomendas, sizeof(struct Encomenda), *nEncomendas, f);
        
            if(n1 != *nEncomendas) {
                printf("Erro ao ler o ficheiro das encomendas!\n");
                *tam_max_enc = 0;
                *nEncomendas = 0; 
                free(*ap_encomendas);
                fclose(f);
            }
            for (i=0; i<*nEncomendas;i++) {
            
            (*ap_encomendas)[i].artigo = (struct Artigo*) 
                malloc((*ap_encomendas)[i].nartigos * sizeof(struct Artigo));
            if ((*ap_encomendas)[i].artigo == NULL){
                printf("Erro ao alocar memória dos artigos\n");
                for (i = 0; i<*nEncomendas; i++)
                    free((*ap_encomendas)[i].artigo);

                free(*ap_encomendas);
                *nEncomendas = 0;
                fclose(f);
            }
            
            n1 = fread((*ap_encomendas)[i].artigo, sizeof(struct Artigo), (*ap_encomendas)[i].nartigos, f);
           
            if (n1 != (*ap_encomendas)[i].nartigos){
                printf("Erro ao ler o ficheiro.\n");
                *nEncomendas = 0;
                for (i = 0; i<*nEncomendas; i++)
                    free((*ap_encomendas)[i].artigo);
                *nEncomendas = 0;
                free(*ap_encomendas); 
                fclose(f);
            }
            }
        }
        printf("Dados lidos de ficheiro.\n");
        
        fclose(f);
    }
}