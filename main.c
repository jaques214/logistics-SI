/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Gonçalo Nobre, Jaques Resende e Miguel
 *
 * Created on 11 de Dezembro de 2019, 10:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "API_Leitura/API_Leitura.h"
#include "MyLibs/gestao_utilizadores.h"
#include "MyLibs/gestao_encomendas.h"
#include "MyLibs/gestao_precos.h"
#include "MyLibs/gestao_faturas.h"
#include "MyLibs/menus.h"

/*
 * 
 */

int main(int argc, char** argv) {
    FILE *f;
    int nif, pos, i;
    int opt = 0, nElementos = 0, tam_max_cli = 0;
    int nEncomendas = 0, tam_max_enc = 0;
    struct Cliente *ap_clientes;
    struct Encomenda *ap_encomendas;
    struct Preco precos;
    f = fopen("tabela_precos_default.bin", "rb");
    fread(&precos,sizeof(struct Preco),1,f);
    fclose(f);
    ap_clientes = (struct Cliente*) malloc(TAM_INICIAL * sizeof(struct Cliente));
    ap_encomendas = (struct Encomenda*) malloc(TAM_INICIAL * sizeof(struct Encomenda));
    
    if(ap_clientes == NULL || ap_encomendas == NULL) {
        printf("A alocação de memória falhou!\n");
    }
    else {
        tam_max_cli = TAM_INICIAL;
        tam_max_enc = TAM_INICIAL; 
       
        do {
            readInt(&opt, 0, 4, "1 - Menu Clientes\n2 - Menu Diretor\n3 - Carregar Dados\n"
                    "4 - Guardar Dados\n0 - Sair do Menu\n\nInsira a opcao: ");
            switch(opt) {
                case 1: //Menu Cliente
                    readInt(&nif,0,999999999,"Insira o seu NIF: ");
                    pos = pesquisa(ap_clientes,nElementos,nif);
                    if(pos == -1){
                    readInt(&opt,0,1,"Não tem conta deseja criar uma?\n1 - Sim   0 - Não\n");
                    switch(opt){
                        case 0:
                            printf("A voltar ao menu..");
                            opt = 1;
                            break;
                        case 1:
                            adicionarCliente(&ap_clientes,&nElementos,&tam_max_cli, nif);
                            break;
                    }
                    
                    
                }else{
                        if((ap_clientes+pos)->status == Desativo) {
                            printf("A sua conta foi desativada\n");         
                        }
                        else {
                            printf("A enviá-lo para o menu...\n");
                            MenuPrincipal(opt, &ap_clientes, &ap_encomendas,&nElementos, &nEncomendas, &tam_max_cli, &tam_max_enc, &precos, nif);
                        }
                }
                break;
                case 2: //Menu Diretor
                    MenuPrincipal(opt, &ap_clientes, &ap_encomendas, &nElementos, &nEncomendas, &tam_max_cli, &tam_max_enc, &precos, nif);
                break;
                case 3: carregarDadosCliente(&ap_clientes, &nElementos, &tam_max_cli);
                        carregarDadosEncomenda(&ap_encomendas, &nEncomendas, &tam_max_enc);
                        carregarDadosPreco(&precos);
                break;
                case 4: guardarDadosCliente(ap_clientes, nElementos);
                        guardarDadosEncomenda(ap_encomendas, nEncomendas); 
                        guardarDadosPreco(&precos);
                break;
                case 0: printf("A sair obrigada");
                break;
            }
        }
        while (opt != 0);

        for (i = 0; i<nEncomendas; i++)
            free(ap_encomendas[i].artigo);

        free(ap_encomendas);
        free(ap_clientes);
    }
    return (EXIT_SUCCESS);
}