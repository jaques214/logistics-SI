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
 * Escreve o conteúdo da lista de precos em ficheiro
 * 
 * @param precos apontador para a estrutura de dados Preco
 */
void guardarDadosPreco(struct Preco *precos) {
    FILE *f;
    
    if ((f = fopen("tabela_precos.bin", "wb")) == NULL)
    {
        perror("Erro ao abrir o ficheiro.");
    }
    else
    {
        fwrite(precos, sizeof(struct Preco), 1, f);
        printf("\nDados Tabela Preços guardados");
        fclose(f);
    }
}

/**
 * Lê dados de um ficheiro (se existir) e preenche a lista de preços
 * 
 * @param precos apontador para a estrutura de dados Preco
 */
void carregarDadosPreco (struct Preco *precos) {
    FILE *f;
    int nr;
    if ((f = fopen("tabela_precos.bin", "rb")) == NULL)
    {
        perror("Erro ao abrir o ficheiro.");
    }
    else {
        nr = fread(precos,sizeof(struct Preco),1,f);
        if (nr != 1) {
            printf("Erro ao ler o ficheiro dos preços.\n");
            fclose(f);
        }
     
        printf("Dados lidos de ficheiro.\n");
        
        fclose(f);
    }
}

/**
 * Adiciona os preços utilizados no cálculo do custo total
 * 
 * @param precos apontador para a estrutura de dados Preco
 */
void mudarPrecos(struct Preco *precos){
    int i,j;
    readFloat(&precos->regular,0.01,99.99,"Insira o preço para tipo regular de encomenda: ");
    readFloat(&precos->urgente,0.01,99.99,"Insira o preço para tipo urgente de encomenda: ");
    readFloat(&precos->pesada,0.01,99.99,"Insira o preço para encomenda pesada: ");
    readFloat(&precos->volumosa,0.01,99.99,"Insira o preço para encomenda volumosa: ");
    readFloat(&precos->km,0.01,99.99,"Insira o preço por km: ");
    for(i = 0; i < 9;i++){
        for(j = i; j < 9;j++){
            printf("Codigo Postal Origem %d - Codigo Postal Destino %d", i + 1, j + 1);
            readFloat(&precos->codip[i][j],0.01,99.99,"Insira o preço: ");
            precos->codip[j][i] = precos->codip[i][j];
        }
    }
}

/**
 * Consulta os preços inseridos e organiza-os numa tabela de preços (matriz)
 * 
 * @param precos apontador para a estrutura de dados Preco
 */
void consultarPrecos(struct Preco *precos){
    int i,j;
    printf("O preço para tipo regular de encomenda %.2f€\n",precos->regular);
    printf("O preço para tipo urgente de encomenda %.2f€\n",precos->urgente);
    printf("O preço para encomenda pesada %.2f€\n",precos->pesada);
    printf("O preço para encomenda volumosa %.2f€\n",precos->volumosa);
    printf("O preço por km %.2f€\n",precos->km);
    printf("\tPreco Código Postal:\nCódigo Postal Destino/Código Postal Origem\n");
    for(i = 0; i < 9;i++){
        if(i == 0){
            printf("    %d",i+1);
        }else{
        printf("  %d",i+1);
        }
    }
    for(i = 0; i < 9;i++){
       printf("\n");
        for(j = 0; j < 9;j++){
            if(j == 0){
                printf("%d  ",i+1);
            }
            printf("  %.2f",precos->codip[i][j]);
        }
    }
}