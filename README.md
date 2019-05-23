# LISTA 5 - ESTRUTURA DE DADOS 2 - 2019/1

### Henrique Martins de Messias - 17/0050394
### Victor Rodrigues Silva - 16/0019516

<br>

### Instalações necessárias
- No teminal, digite os seguinte comando para instalar as dependências:
  ```bash
    $ sudo apt-get install build-essential
    $ sudo apt-get install qt5-default
  ```


### Instruções de uso

- No terminal, vá até o diretório do exercício, que contém, além de arquivos como o README, a pasta "tree"
- Digite o seguinte comando:

  ```bash
    $ cd tree
    $ qmake
  ```

  - Para compilar o código, digite:

  ```bash
    $ make
  ```

- Para executar o código, digite:

  ```bash
    $ ./tree
  ```

### Detalhes da Lista 5

O software deste repositório é de uma <b>Coleção de Filmes</b>.

Cada filme possui os seguintes dados:
 - Título
 - Ano de lançamento
 - Bilheteria
 - Diretor
 - País em que o filme foi feito
 - Duração (em minutos)

O software armazena os filmes em árvores, sendo que dois tipos de árvores estão disponíveis:
 - Árvore AVL
 - Árvore Red-Black (Vermelha-Preta)

 O usuário pode escolher qual tipo de árvore utilizar para armazenar os dados. Independente de qual seja sua escolha, ele terá as seguintes opções:
  - Gerar uma árvore aleatória (o usuário dirá quantos dados quer na árvore e o programa criará essa quantidade de filmes aleatórios)
  - Inserir (o usuário informará os dados do filme e o programa irá adicioná-lo à árvore)
  - Remover (o usuário informará os dados do filme, o programa irá procurá-lo na árvore e, caso encontre, irá removê-lo da árvore)
  - Buscar (o usuário informará os dados do filme, o programa irá procurá-lo na árvore e, caso encontre, informará o usuário que o filme foi encontrado)
  - Ver dados da árvore (o programa mostrará ao usuário dados como: quantidade de elementos, vezes que usou rotação à esquerda e rotação à direita, tamanho da árvore)
  - Ver árvore (o programa mostrará uma imagem que representa a árvore)

  Além disso, o usuário ainda pode:
   - Comparar Performance (as duas árvores estarão vazias, o usuário dirá quantas inserções, buscas e remoções quer fazer e o programa fará as operações dos mesmos dados aleatórios nas duas árvores e mostrará ao usuário algumas informações sobre as três operações)
   - Comparar Inserções (as duas árvores estarão vazias, o usuário dirá quantas inserções quer fazer e o programa fará as inserções dos mesmos dados aleatórios nas duas árvores e mostrará ao usuário algumas informações sobre as inserções)
   - Comparar Remoções (as duas árvores terão os mesmos dados, o usuário dirá quantas remoções quer fazer e o programa fará as remoções dos mesmos dados nas duas árvores e mostrará ao usuário algumas informações sobre as remoções)
   - Comparar Buscas (as duas árvores terão os mesmos dados, o usuário dirá quantas buscas quer fazer e o programa fará as buscas dos mesmos dados aleatórios nas duas árvores e mostrará ao usuário algumas informações sobre as buscas)
   