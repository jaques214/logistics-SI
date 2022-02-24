/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menus.h
 * Author: Jaques
 *
 * Created on 19 de Dezembro de 2019, 18:00
 */

#ifndef MENUS_H
#define MENUS_H

#ifdef __cplusplus
extern "C" {
#endif
    
// Menus e Submenus
void MenuExtras(int opt, int nif, struct Encomenda *ap_encomendas, 
        int nEncomendas, struct Cliente *ap_clientes, int nElementos);
void MenuFaturas(int opt, int nif, struct Encomenda *ap_encomendas,int nEncomendas);
void MenuPrecos(int opt, struct Preco *precos);
void MenuEncomendas(int opt, struct Cliente *ap_clientes, struct Preco *precos,
        struct Encomenda **ap_encomendas, int *nEncomendas, int *nElementos, int *tam_max_enc,
        int nif);
int MenuUtilizadores(int opt, struct Cliente **ap_clientes, int *nElementos,
        int *tam_max_cli, int nif);
void MenuPrincipal(int opt, struct Cliente **ap_clientes,
        struct Encomenda **ap_encomendas, int *nElementos, int *nEncomendas,
        int *tam_max_cli, int *tam_max_enc, struct Preco *precos, int nif);


#ifdef __cplusplus
}
#endif

#endif /* MENUS_H */

