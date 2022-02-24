/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   extras.h
 * Author: gonca
 *
 * Created on January 11, 2020, 10:40 PM
 */

#ifndef EXTRAS_H
#define EXTRAS_H

#ifdef __cplusplus
extern "C" {
#endif

// Funcionalidades Extras
void relatorioAnual(struct Encomenda *ap_encomendas, int nEncomendas, int nif,
        int ano);
void relatorioDiario(struct Encomenda *ap_encomendas, int nEncomendas, int nif, 
        int ano, int mes, int dia);
void melhor_piorCliente(struct Encomenda *ap_encomendas, int nEncomendas, struct Cliente *ap_clientes, int nElementos, int ano);

#ifdef __cplusplus
}
#endif

#endif /* EXTRAS_H */

