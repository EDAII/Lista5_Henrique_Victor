#include "filme.h"

Filme::Filme(const char* titulo, short int ano, unsigned int bilheteria, const char* diretor, const char* pais, unsigned char duracao) {
    string aux_titulo(titulo);
    this->titulo = aux_titulo;

    this->ano = ano;
    this->bilheteria = bilheteria;

    string aux_diretor(diretor);
    this->diretor = aux_diretor;

    string aux_pais(pais);
    this->pais = pais;

    this->duracao = duracao;
}
