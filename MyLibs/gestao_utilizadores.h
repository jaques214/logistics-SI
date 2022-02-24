/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gestao_utilizadores.h
 * Author: Jaques
 *
 * Created on 11 de Dezembro de 2019, 15:53
 */

#ifndef GESTAO_UTILIZADORES_H
#define GESTAO_UTILIZADORES_H

#include <time.h>

    #define TAM_STR 100
    #define TAM_INICIAL 1
    #define TAM_INCREMENTO 1
    #define TAM_DECREMENTO 1

    enum Decricao {NFragil, Fragil};
    enum Status {Desativo, Ativo};
    enum Tipo {Regular, Urgente};
    enum Expedicao {NExpedida, Expedida};

struct Artigo {
    float peso;
    float volume;
    enum Decricao descricao;
};

struct Morada {
    char rua[TAM_STR];
    int num;
    char localidade[TAM_STR];
    char codPostal[TAM_STR];
    char pais[TAM_STR];
};

struct Cliente {
    char nome[TAM_STR];
    int nif;
    int cc;
    enum Status status;
    struct Morada mpredef;
};

struct Encomenda {
    struct Artigo *artigo;
    int nartigos;
    int nifcliente;
    struct tm hora_envio;
    enum Expedicao expedicao;
    enum Tipo tipo_transporte;
    float custo_total;
    float distancia_km;
    struct Morada endereco_origem;
    struct Morada endereco_destino;
};

struct Preco{
    float regular;
    float urgente;
    float km;
    float volumosa;
    float fragil;
    float pesada;
    float codip[9][9];
};

#ifdef __cplusplus
extern "C" {
#endif

// Gestão de Utilizadores
int pesquisa (struct Cliente *ap_clientes, int nElementos, int nif);
void dadosCliente(struct Cliente *ap_clientes, int *pos, int nif);
void adicionarCliente(struct Cliente **ap_clientes, int *nElementos,
        int *tam_max_cli, int nif);
struct Cliente* getCliente(struct Cliente *ap_clientes, int nElementos, int nif);
void editarCliente(struct Cliente *ap_clientes, int nElementos, int nif);
void removeCliente(struct Cliente *ap_clientes, int nElementos, int nif);
void ativarCliente(struct Cliente *ap_clientes, int nElementos, int nif);
void guardarDadosCliente(struct Cliente *ap_clientes, int nElementos);
void carregarDadosCliente(struct Cliente **ap_clientes, int *nElementos,
        int *tam_max_cli);
    
    
#ifdef __cplusplus
}
#endif

#endif /* GESTAO_UTILIZADORES_H */

