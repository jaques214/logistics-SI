/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gestao_precos.h
 * Author: samsung
 *
 * Created on 10 de janeiro de 2020, 10:58
 */

#ifndef GESTAO_PRECOS_H
#define GESTAO_PRECOS_H

#ifdef __cplusplus
extern "C" {
#endif

void guardarDadosPreco(struct Preco *precos);
void carregarDadosPreco(struct Preco *precos);
void mudarPrecos(struct Preco *precos);
void consultarPrecos(struct Preco *precos);


#ifdef __cplusplus
}
#endif

#endif /* GESTAO_PRECOS_H */

