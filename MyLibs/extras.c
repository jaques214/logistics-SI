/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../API_Leitura/API_Leitura.h"
#include "gestao_utilizadores.h"
#include "extras.h"

/**
 * Mostra o relatório anual das encomendas expedidas
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param nEncomendas nº de encomendas no array
 * @param nif identificador do cliente, que efetuou a encomenda
 * @param ano ano registado na data/hora de envio da encomenda expedida
 */
void relatorioAnual(struct Encomenda *ap_encomendas,int nEncomendas,int nif,int ano){
    int i,j;
    printf("Relátorio do ano %d\n",ano);
    if(nif == -1){
    for(i = 0;i < nEncomendas;i++){
          if(ap_encomendas[i].hora_envio.tm_year == ano - 1900){
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
    }else{
           for(i = 0;i < nEncomendas;i++){
          if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                                printf("Encomenda Nº%d\n", i + 1);
          
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
}

/**
 * Mostra o relatório diário do nº de encomendas adiconados por um dado cliente
 * 
 * @param ap_encomendas array/apontador de encomendas
 * @param nEncomendas nº de encomendas no array
 * @param nif identificador do cliente, que efetuou a encomenda
 * @param ano ano registado na data/hora de envio da encomenda expedida
 * @param mes
 * @param dia
 */
void relatorioDiario(struct Encomenda *ap_encomendas,int nEncomendas,int nif,int ano,int mes,int dia){
    int i,j;
    printf("Relátorio do ano %d\n",ano);
    if(nif == -1){
    for(i = 0;i < nEncomendas;i++){
          if(ap_encomendas[i].hora_envio.tm_year == ano - 1900 && ap_encomendas[i].hora_envio.tm_mon == mes -1 
                  && ap_encomendas[i].hora_envio.tm_mday == dia){
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
    }else{
           for(i = 0;i < nEncomendas;i++){
          if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_year == ano - 1900 && ap_encomendas[i].hora_envio.tm_mon == mes -1 
                  && ap_encomendas[i].hora_envio.tm_mday == dia){
                                printf("Encomenda Nº%d\n", i + 1);
          
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
}

void melhor_piorCliente(struct Encomenda *ap_encomendas,int nEncomendas,struct Cliente *ap_clientes, int nElementos,int ano){
    int i,j,maior = 0,menor = 0;
    float array_total[nElementos];
    int array_total_encomendas[nElementos];
    for(j = 0;j<nElementos;j++){
        for(i = 0;i < nEncomendas;i++){
          if(ap_encomendas[i].nifcliente == ap_clientes[j].nif && ap_encomendas[i].hora_envio.tm_year == ano - 1900){
              array_total[j] += ap_encomendas[i].custo_total;
              array_total_encomendas[j]++;
          }
    }
  }
  for(j = 0;j<nElementos - 1;j++){
      if(array_total[j]<array_total[j+1]){
          maior = j + 1; 
      }
  }
    for(j = 0;j<nElementos - 1;j++){
      if(array_total[j]>array_total[j+1]){
          menor = j +1;
      }
  }
    printf("Melhor Cliente: %d\n    Nº Encomendas: %d\n    Total: %f\n",ap_clientes[maior].nif,array_total_encomendas[maior],array_total[maior]);
     printf("Pior Cliente: %d\n    Nº Encomendas: %d\n    Total: %f\n",ap_clientes[menor].nif,array_total_encomendas[menor],array_total[menor]);
    
}