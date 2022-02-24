/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gestao_encomendas.h
 * Author: Jaques
 *
 * Created on 23 de Dezembro de 2019, 19:41
 */

#ifndef GESTAO_ENCOMENDAS_H
#define GESTAO_ENCOMENDAS_H

#ifdef __cplusplus
extern "C" {
#endif

//Gestão de Encomendas
int pesquisaEncomenda (struct Encomenda *ap_encomendas, int nEncomendas,
        int nif);
void calcularTotal(struct Encomenda *ap_encomendas, int pos, struct Preco *precos);
void dadosEncomenda(struct Encomenda *ap_encomendas, struct Cliente *ap_clientes,
        int *pos, int *nElementos, int nif, struct Preco *precos);
void adicionarEncomenda(struct Encomenda **ap_encomendas, struct Preco *precos,
        struct Cliente *ap_clientes, int *nEncomendas, int *nElementos,
        int *tam_max_enc, int nif);
void consultarEstado(struct Encomenda* ap_encomendas, int nEncomendas, int nif);
void verEncomendas(struct Encomenda* ap_encomendas, int nEncomendas, int nif);
void alterarEstado(struct Encomenda *ap_encomendas, int pos);
void removerEncomenda(struct Encomenda **ap_encomendas, int *nEncomendas, int *tam_max_enc);
void adicionarArtigo(struct Encomenda **ap_encomendas, struct Preco *precos, int pos);
void removerArtigo(struct Encomenda **ap_encomendas, struct Preco *precos, int pos);
void alterarEncomenda(struct Encomenda **ap_encomendas, int nEncomendas,
        int nifcliente, struct Preco *precos);
void guardarDadosEncomenda(struct Encomenda *ap_encomendas, int nEncomendas);
void carregarDadosEncomenda(struct Encomenda **ap_encomendas, int *nEncomendas, int *tam_max_enc);

#ifdef __cplusplus
}
#endif

#endif /* GESTAO_ENCOMENDAS_H */

