/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menus.c
 * Author: Jaques
 *
 * Created on 19 de Dezembro de 2019, 16:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../API_Leitura/API_Leitura.h"
#include "gestao_utilizadores.h"
#include "gestao_encomendas.h"
#include "gestao_precos.h"
#include "gestao_faturas.h"
#include "extras.h"
#include "menus.h"

/*
 * 
 */

/**
 * 
 * @param opt
 * @param nif
 * @param ap_encomendas
 * @param nEncomendas
 * @param ap_clientes
 * @param nElementos
 */
void MenuExtras(int opt, int nif, struct Encomenda *ap_encomendas,
        int nEncomendas, struct Cliente *ap_clientes, int nElementos) {
    int opt1,ano,mes,dia,i,con = 0;
     do{
        if(opt == 2){
        readInt(&opt1, 0, 4, "Extras Menu:\n1 - Relatório Anual\n2 - Relatório Diário\n3 - Melhor e Pior Cliente\n4 - Km Mês"
        "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1:
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                relatorioAnual(ap_encomendas,nEncomendas,-1,ano);
            }else{
                printf("Não existem encomendas nesse ano");
            }
            break;
            case 2:
            readInt(&dia,1,31,"Insira o dia: ");
            readInt(&ano,1,12,"Insira o mes: ");
                readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].hora_envio.tm_year == ano - 1900 && ap_encomendas[i].hora_envio.tm_mon == mes -1 
                  && ap_encomendas[i].hora_envio.tm_mday == dia){
                            con++;
                        }
            }
            if (con > 0){
                relatorioDiario(ap_encomendas,nEncomendas,-1,ano,mes,dia);
            }else{
                printf("Não existem encomendas nesse dia");
            }
            break;
            case 3:
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                melhor_piorCliente(ap_encomendas,nEncomendas,ap_clientes,nElementos,ano);
            }else{
                printf("Não existem encomendas nesse ano");
            }
            break;
        }
        }else{
        readInt(&opt1, 0, 2, "Extras Menu:\n1 - Relatório Anual\n2 - Relatório Diário"
        "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1: 
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                 relatorioAnual(ap_encomendas,nEncomendas,nif,ano);
            }else{
                printf("Não existem encomendas nesse ano");
            }
            break;
            case 2: printf("Opção 2 - Consultar Preços\n");
             readInt(&dia,1,31,"Insira o dia: ");
            readInt(&ano,1,12,"Insira o mes: ");
                readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_year == ano - 1900 && ap_encomendas[i].hora_envio.tm_mon == mes -1 
                  && ap_encomendas[i].hora_envio.tm_mday == dia){
                            con++;
                        }
            }
            if (con > 0){
                relatorioDiario(ap_encomendas,nEncomendas,nif,ano,mes,dia);
            }else{
                printf("Não existem encomendas nesse dia");
            }
            break;
        }
        } 
    }
    while (opt1 != 0);
}

/**
 * 
 * @param opt
 * @param nif
 * @param ap_encomendas
 * @param nEncomendas
 */
void MenuFaturas(int opt, int nif, struct Encomenda *ap_encomendas,int nEncomendas){
    int opt1,rec,ano,mes,i,con = 0;
    char nome[0x100];
do{
    if(opt == 2){
    readInt(&opt1, 0, 2, "Gestão de Faturas Menu:\n1 - Gerar Fatura\n2 - Reimprimir Fatura"
            "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
    switch(opt1) {
        case 0: printf("A voltar...");
        break;
        case 1:
            con  = 0;
            readInt(&nif,0,999999999,"Insira o NIF: ");
            readInt(&mes,1,12,"Insira o mês: ");
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_mon == mes - 1 && 
                                ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                 readInt(&rec,0,1,"Deseja criar ficheiro?\n0 - Não 1 - Sim\n");
                 snprintf(nome, sizeof(nome), "./Faturas/%d_%d_%d.txt", nif,mes,ano);
                 gerarFatura(ap_encomendas,nEncomendas,nif,mes,ano,nome,rec);
            }else{
                printf("Não existem encomendas desse cliente nesse mês");
            }
        break;
        case 2:
            con  = 0;
            readInt(&nif,0,999999999,"Insira o NIF: ");
            readInt(&mes,1,12,"Insira o mês: ");
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_mon == mes - 1 && 
                                ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                readInt(&rec,0,1,"Deseja criar ficheiro?\n0 - Não 1 - Sim\n");
                 snprintf(nome, sizeof(nome), "./Faturas/%d_%d_%d.txt", nif,mes,ano);
                 gerarFatura(ap_encomendas,nEncomendas,nif,mes,ano,nome,rec);
            }else{
                printf("Não existem encomendas desse cliente nesse mês");
            }
        break;
    }
    }else{
        readInt(&opt1, 0, 2, "Gestão de Faturas Menu:\n1 - Gerar Fatura\n2 - Reimprimir Fatura"
            "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
    switch(opt1) {
        case 0: printf("A voltar...");
        break;
        case 1:
                        con  = 0;
         readInt(&mes,1,12,"Insira o mês: ");
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_mon == mes - 1 && 
                                ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                readInt(&rec,0,1,"Deseja criar ficheiro?\n0 - Não 1 - Sim\n");
                 snprintf(nome, sizeof(nome), "./Faturas/%d_%d_%d.txt", nif,mes,ano);
                 gerarFatura(ap_encomendas,nEncomendas,nif,mes,ano,nome,rec);
            }else{
                printf("Não existem encomendas desse cliente nesse mês");
            }
        break;
        case 2:
                        con  = 0;
            readInt(&mes,1,12,"Insira o mês: ");
            readInt(&ano,0,2020,"Insira o ano: ");
            printf("\n");
            for(i = 0;i < nEncomendas;i++){
                        if(ap_encomendas[i].nifcliente == nif && ap_encomendas[i].hora_envio.tm_mon == mes - 1 && 
                                ap_encomendas[i].hora_envio.tm_year == ano - 1900){
                            con++;
                        }
            }
            if (con > 0){
                readInt(&rec,0,1,"Deseja criar ficheiro?\n0 - Não 1 - Sim\n");
                 snprintf(nome, sizeof(nome), "./Faturas/%d_%d_%d.txt", nif,mes,ano);
                 gerarFatura(ap_encomendas,nEncomendas,nif,mes,ano,nome,rec);
            }else{
                printf("Não existem encomendas desse cliente nesse mês");
            }
        break;
    }
    }
}
while (opt1 != 0);
}

/**
 * 
 * @param opt
 * @param precos
 */
void MenuPrecos(int opt, struct Preco *precos){
    int opt1;
    do{
        if(opt == 2){
        readInt(&opt1, 0, 2, "Gestão de Preços Menu:\n1 - Editar Preços\n2 - Consultar Preços "
        "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1: printf("Opção 1 - Editar Preços\n");
                mudarPrecos(precos);
            break;
            case 2: printf("Opção 2 - Consultar Preços\n");
                consultarPrecos(precos);
            break;
        }
        }else{
        readInt(&opt1, 0, 1, "Gestão de Preços Menu:\n1 - Consultar Preços"
        "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1: printf("Opção 1 - Consultar Preços\n");
                consultarPrecos(precos);
            break;
        }
        } 
    }
    while (opt1 != 0);
}

/**
 * 
 * @param opt
 * @param ap_clientes
 * @param precos
 * @param ap_encomendas
 * @param nEncomendas
 * @param nElementos
 * @param tam_max_enc
 * @param nif
 */
void MenuEncomendas(int opt, struct Cliente *ap_clientes, struct Preco *precos,
        struct Encomenda **ap_encomendas, int *nEncomendas, int *nElementos, int *tam_max_enc,
        int nif){
    int opt1, pos;
   do{
       if(opt == 2){
        readInt(&opt1, 0, 2, "Gestão de Encomendas Menu:\n1 - Atualizar Estado\n2 - Consultar todas as Encomendas\n"
                "0 - Voltar para o menu principal\nSelecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1: printf("Opção 1 - Atualizar Estado\n");
            readInt(&nif,0,999999999,"Insira o NIF do cliente a que pertence a encomenda que deseja alterar: ");
            if(pesquisaEncomenda(*ap_encomendas, *nEncomendas, nif) != -1){
                consultarEstado(*ap_encomendas,*nEncomendas,nif);
                readInt(&pos,1,*nEncomendas,"Insira o número da encomenda que deseja alterar: ");
                pos--;
                alterarEstado(*ap_encomendas,pos);
            }else{
                printf("\nEsse cliente ainda não têm qualquer encomenda\n");
            }
            break;
            case 2: 
                verEncomendas(*ap_encomendas, *nEncomendas, nif);
                break;
        }
       }else{
       readInt(&opt1, 0, 4, "Gestão de Encomendas Menu:\n1 - Adicionar Encomenda\n2 - Consultar o Estado\n"
               "3 - Alterar Encomenda\n4 - Eliminar Encomenda\n0 - Voltar para o menu principal\n"
               "Selecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1: printf("Opção 1 - Adicionar Encomenda\n");
                adicionarEncomenda(ap_encomendas, precos, ap_clientes, nEncomendas,
                        nElementos, tam_max_enc, nif);
            break;
            case 2: printf("Opção 2 - Consultar o Estado\n");
                consultarEstado(*ap_encomendas, *nEncomendas, nif);
            break;
            case 3: printf("Opção 3 - Alterar Encomenda\n");
                alterarEncomenda(ap_encomendas, *nEncomendas, nif,precos);
            break;
            case 4: printf("Opção 4 - Eliminar Encomenda\n");
                removerEncomenda(ap_encomendas, nEncomendas, tam_max_enc);
            break;
        }
       }
    }
    while (opt1 != 0);
}

/**
 * 
 * 
 * @param opt
 * @param ap_clientes
 * @param nElementos
 * @param tam_max_cli
 * @param nif
 * @return 
 */
int MenuUtilizadores(int opt, struct Cliente **ap_clientes, int *nElementos, int *tam_max_cli, int nif) {
    int opt1;
    do {
        //se selecionar diretor
       if(opt == 2) {
       readInt(&opt1 , 0, 4, "Gestão de Utilizadores:\n1 - Criar Cliente\n"
               "2 - Editar Cliente\n3 - Remover Cliente "
       "\n4 - Reativar Cliente\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
        switch(opt1) {
            case 0: printf("A voltar...");
            break;
            case 1: printf("Opção 1 - Criar Cliente\n");
                readInt(&nif,0,999999999,"Insira o NIF: ");
                adicionarCliente(ap_clientes, nElementos, tam_max_cli, nif);
            break;
            case 2: printf("Opção 2 - Editar Cliente\n");
                readInt(&nif,0,999999999,"Insira o NIF: ");
                editarCliente(*ap_clientes, *nElementos, nif);
            break;
            case 3: printf("Opção 3 - Remover Cliente\n");
                readInt(&nif,0,999999999,"Insira o NIF: ");
                removeCliente(*ap_clientes, *nElementos, nif);
            break;
            case 4: printf("Opção 4 - Reativar Cliente\n");
                readInt(&nif,0,999999999,"Insira o NIF: ");
                ativarCliente(*ap_clientes, *nElementos, nif);
            break;
         }
       }
       //selecionar cliente
       else {
            readInt(&opt1, 0, 2, "Gestão de Utilizadores:\n1 - Editar Cliente\n2 - Remover Cliente "
                        "\n0 - Voltar para o menu principal\nSelecione uma das opções: ");
            switch(opt1) {
                case 0: printf("A voltar...");
                break;
                case 1: printf("Opção 2 - Editar Cliente\n");
                    editarCliente(*ap_clientes, *nElementos, nif);
                break;
                case 2: printf("Opção 3 - Remover Cliente\n");
                    removeCliente(*ap_clientes, *nElementos, nif);
                return 0;
                break;
            }
       }
    }
        while (opt1 != 0);
        return 1;
}

/**
 * Cria um menu principal que chama todas as funções que contêm menus secundários
 * 
 * @param opt opção a selecionar no menu
 * @param ap_clientes apontador duplo para o endereco do array de clientes
 * @param ap_encomendas apontador duplo para o endereco do array de encomendas
 * @param nElementos apontador para o nº atual de clientes
 * @param nEncomendas apontador para o nº atual de encomendas
 * @param tam_max_cli apontador para o tamanho do array clientes
 * @param tam_max_enc apontador para o tamanho do array encomendas
 * @param precos apontador para a estrutura de dados preço
 * @param nif identificador único para os clientes
 */
void MenuPrincipal(int opt, struct Cliente **ap_clientes, struct Encomenda **ap_encomendas, int *nElementos,
        int *nEncomendas, int *tam_max_cli, int *tam_max_enc, struct Preco *precos, int nif)
{
    int opt1;
       do {
            readInt(&opt1, 0, 5, "1 - Gestão de Utilizadores\n2 - Gestão de Encomendas\n3 - Gestão de "
         "Preços\n4 - Gestão de Faturas\n5 - Extras\n0 - Logout\nSelecione uma das opções: ");
           switch (opt1){
                case 0: printf("A sair...\n");
                    break;
                case 1: printf("Opção 1 - Gestão de Utilizadores\n");
                    opt1 = MenuUtilizadores(opt, ap_clientes, nElementos, tam_max_cli, nif);
                    break;     
                case 2: printf("Opcão 2 - Gestão de Encomendas\n");
                    MenuEncomendas(opt, *ap_clientes, precos, ap_encomendas,
                            nEncomendas, nElementos, tam_max_enc, nif);
                    break;
                case 3: printf("Opção 3 - Gestão de Preços\n");
                    MenuPrecos(opt, precos);
                    break;
                case 4: printf("Opção 4 - Gestão de Faturas\n");
                    MenuFaturas(opt,nif,*ap_encomendas,*nEncomendas);
                    break;
                    case 5: printf("Opção 5 - Extras\n");
                    MenuExtras(opt,nif,*ap_encomendas,*nEncomendas,*ap_clientes,*nElementos);
                    break;
            }
       }
while(opt1 != 0);
}