/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../API_Leitura/API_Leitura.h"
#include "gestao_utilizadores.h"
#include "gestao_faturas.h"

/**
 * Imprime as faturas do mês
 * 
 * @param ap_encomendas array/apontador das encomenddas
 * @param nEncomendas nº de encomendas no array
 * @param nif identificador do cliente que efetuou a encomenda
 * @param mes valor do mês retirado da data de envio da encomenda
 * @param ano valor do ano retirado da data de envio da encomenda
 * @param nome nome do cliente
 * @param rec valida se o utilizador quer 
 */
void gerarFatura(struct Encomenda *ap_encomendas, int nEncomendas, int nif, 
        int mes, int ano, char nome[], int rec)
{
    int i,j;
    float total = 0;
    FILE *fatura =  fopen(nome,"w");
    if (rec == 1){
    if (fatura != NULL){
        if(fprintf(fatura,"Fatura do mês: %d/%d\n",mes,ano) < 0){
            printf("Erro a escrever mês no ficheiro");
        }else{
            printf("Fatura do mês: %d/%d\n",mes,ano);
            if(fprintf(fatura,"\nNIF: %d",nif) < 0){
                printf("Erro a escrever NIF no ficheiro");
            }else{
                printf("\nNIF: %d",nif);
                if(fprintf(fatura,"\nEncomendas:") < 0){
                    printf("Erro a escrever Encomendas");
                }else{
                    printf("\nEncomendas:");
                    for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_mon == mes - 1 && 
                                ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            total += ap_encomendas[i].custo_total;
                            if(fprintf(fatura,"\n Encomenda nº%d - %.2f€\n Hora: %d:%d\n  Artigos:",i+1,ap_encomendas[i].custo_total,ap_encomendas[i].hora_envio.tm_hour, 
                            ap_encomendas[i].hora_envio.tm_min) < 0){
                                printf("Erro a escrever Encomenda %d", i+1);
                            }else{
                                printf("\n Encomenda nº%d - %.2f€\n  Hora: %d:%d\n  Artigos:",i+1,ap_encomendas[i].custo_total,ap_encomendas[i].hora_envio.tm_hour, 
                                ap_encomendas[i].hora_envio.tm_min);
                                for (j = 0; j < ap_encomendas[i].nartigos; j++) {
                                        if(fprintf(fatura,"\n   Artigo nº%d", j+1) < 0){
                                            printf("Erro a escrever Artigo %d", j+1);
                                        }else{
                                            printf("\n   Artigo nº%d",j+1);
                                        }
                                    }
                            }
                        }
                    }
                  if(fprintf(fatura,"\n------------------------\nTotal: %.2f",total) < 0){
                     printf("Erro a escrever Total");
                  }else{
                      printf("\n------------------------\nTotal: %.2f",total);
                  }
                }
            }
        }
     }
    }else{
        printf("Fatura do mês: %d/%d\n",mes,ano);
        printf("\nNIF: %d",nif);
        printf("\nEncomendas:");
        for(i = 0;i < nEncomendas;i++){
          if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_mon == mes - 1 && 
           ap_encomendas[i].hora_envio.tm_year == ano - 1900){
           total += ap_encomendas[i].custo_total;
           printf("\n Encomenda nº%d - %.2f€\n Hora: %d:%d",i+1,ap_encomendas[i].custo_total,ap_encomendas[i].hora_envio.tm_hour, 
           ap_encomendas[i].hora_envio.tm_min);
            for (j = 0; j < ap_encomendas[i].nartigos; j++) {
                printf("\n     Artigo nº%d",j+1);
            }
            }
         }
    }
    fclose(fatura);
}