#ifndef FILME_H
#define FILME_H

#include <string>

using namespace std;

class Filme {
public:
    Filme(const char* titulo, short int ano, unsigned int bilheteria, const char* diretor, const char* pais, unsigned char duracao);
    string get_titulo() const { return titulo; }
    short int get_ano() const { return ano; }
    unsigned int get_bilheteria() const { return bilheteria; }
    string get_diretor() const { return diretor; }
    string get_pais() const { return pais; }
    unsigned char get_duracao() const { return duracao; }
    bool operator <(const Filme &outro) const { return titulo < outro.titulo; }
    bool operator >(const Filme &outro) const { return titulo > outro.titulo; }
    bool operator ==(const Filme &outro) const { return titulo == outro.titulo; }
    bool operator >=(const Filme &outro) const { return titulo >= outro.titulo; }

private:
    string titulo;
    short int ano;
    unsigned int bilheteria;
    string diretor;
    string pais;
    unsigned char duracao;
};

#endif // FILME_H
