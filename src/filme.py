class Filme(object):

    __slots__ = ['titulo', 'ano', 'bilheteria', 'diretor', 'pais', 'duracao']

    def __init__(self, titulo, ano, bilheteria, diretor, pais, duracao):
        self.titulo = titulo
        self.ano = ano
        self.bilheteria = bilheteria 
        self.diretor = diretor
        self.pais = pais
        self.duracao = duracao