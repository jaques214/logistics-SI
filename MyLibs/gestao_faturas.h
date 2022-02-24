/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gestao_faturas.h
 * Author: gonca
 *
 * Created on January 11, 2020, 6:35 PM
 */

#ifndef GESTAO_FATURAS_H
#define GESTAO_FATURAS_H

#ifdef __cplusplus
extern "C" {
#endif

void gerarFatura(struct Encomenda *ap_encomendas, int nEncomendas, int nif, 
        int mes, int ano, char nome[], int rec);


#ifdef __cplusplus
}
#endif

#endif /* GESTAO_FATURAS_H */

