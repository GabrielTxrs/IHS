<div align="center">
<img src="logo ufs.png" width="100"/>

### Universidade Federal de Sergipe<br>
Interface Hardware Software
Turma 03


Gabriel Teixeira Silveira<br>
Matrícula: 202100011987




### Relatório de tarefas da Aula 3



Professor: <br>
Calebe Micael de Oliveira Conceição




São Cristóvão<br>
Julho de 2024

</div>



## 1. Representação Binária do Float 3.14

Antes, é importante mencionar que o valor N que será guardado no registrador de 32 bits segue o padrão:

**N** = (-1)<sup>sinal</sup> x 1.fração x 2<sup>expoente</sup>

E o expoente é codificado seguindo o padrão:
<div align="left">
0000 0000 &nbsp;&nbsp;&nbsp;"sub-normal"<br>
0000 0001 &nbsp;&nbsp;&nbsp;-126 <br>
   ... <br>
0111 1110 &nbsp;&nbsp;&nbsp;-1 <br>
0111 1110 &nbsp;&nbsp;&nbsp;-1 <br>
0111 1110 &nbsp;&nbsp;&nbsp;-1 <br>
   ... <br>
1111 1110 &nbsp;&nbsp;&nbsp; 127<br>
1111 1111 &nbsp;&nbsp;&nbsp;"not a number (NaN)"</div><br>



Para isso, segui o passo a passo demonstrado abaixo.<br>

<img src="IHS-atividade-2.drawio.png" width="900"/>

<div style="text-align: justify">

## 2. Estudo de Hierarquia de memória
### Memória Cache
Memória Cache são componentes que armazenam dados para que futuras solicitações sejam entregues mais rapidamente para a CPU. Os dados de um Cache costumam ser resultados de cálculos anteriores ou cópias de dados armazenado em memórias de acesso mais lento.
CPUs modernas possuem de 2 a 3 níveis de cache feitos de SRAM ***Static Random-Access Memory***.
<ul>
<li> Cache L1: Integrada na CPU, extremamente rápida e com pouquíssimo armazenamento (16 KB a 128 KB), leva de 1 a 5 clocks para calcular o endereço da memória e trazer o valor da L1.
<li> Cache L2: Maior que a L1 (128 KB e 1 MB), leva de 8 a 20 clocks para calcular o endereço da memória e trazer o valor da L2.
<li> Cache L3: Compartilhada entre os núcleos da CPU, maior (2 MB e 64 MB) e mais lenta que as caches L1 e L2. Leva de 30 a 80 clocks para calcular o endereço da memória e trazer o valor da L3.
</ul>

### Translation Look-aside Buffer (TLB)
Primeiramente, devemos abordar o que são paginações na memória de um sistema.

Uma paginação é um esquema de gerenciamento da memória de um computador, que divide a memória física e a memória virtual em blocos de tamanho fixo, chamados de ***Páginas***. As páginas são alocadas em ***Quadros*** (Frames), que são as unidades da memória física de tamanho correspondente ao tamanho da página.

Para saber em qual quadro cada página será alocada, é usada uma Tabela de Páginas, que faz a tradução dos endereços virtuais para os físicos. Essa tabela é composta pelas páginas virtuais, pelos quadros e pela Entrada da Tabela de Páginas (***Page Table Entry - PTE***)

O ***Translation Look-aside Buffer (TLB)*** é um tipo de cache usada para guardar as traduções recentes da PTE, o TLB fica dentro da CPU e evita que seja necessário fazer dois acessos seguidos para se obter um dado, o primeiro para ler a PTE e o segundo para ler o dado. <br>
O TLB armazena as entradas mais recentes da PTE e é consultado antes da CPU buscar um endereço virtual.
Caso a tradução não esteja no TLB, a PTE é consultada e o TLB armazena a tradução para futuros acessos.

<ul>
<li>O cache TLB costuma ter entre 16 a 512 entradas da PTE</li>
<li>O tempo de acesso está entre 0.5 a 1 ciclo por hit</li>
<li>O custo por miss está entre 10 a 100</li>
<li>A chance de miss está entre 0.01% a 1%</li>
</ul>
<img src=TLB.PNG width="900"/>

#### Políticas de substituição e de proteção

#### Segmentação Paginada
Segmentação paginada é um esquema de gerenciamento de memória que combina os benefícios da segmentação e da paginação para fornecer uma forma eficiente e flexível de alocar e gerenciar a memória em sistemas computacionais.

Conceitos Básicos
Segmentação
Segmento: É uma porção de memória que pode variar em tamanho e é usado para armazenar diferentes tipos de dados ou código. Cada segmento tem um nome ou número e um comprimento.
Tabela de Segmentos: Cada processo tem uma tabela de segmentos que armazena a base (endereço inicial) e o limite (tamanho) de cada segmento.
Paginação
Página: Unidade fixa de memória de tamanho igual. A memória é dividida em páginas (blocos de memória) de tamanho fixo.
Tabela de Páginas: Mapeia endereços virtuais para endereços físicos, contendo entradas que apontam para os quadros de memória (frames).
Como Funciona a Segmentação Paginada
A segmentação paginada combina esses dois métodos, segmentando a memória em segmentos lógicos que são, por sua vez, divididos em páginas físicas.

Passos do Funcionamento:
Divisão em Segmentos: A memória de um processo é dividida em segmentos lógicos, cada um representando uma entidade lógica, como uma função, array ou pilha.
Divisão em Páginas: Cada segmento é dividido em páginas de tamanho fixo.
Tabela de Segmentos: Cada processo tem uma tabela de segmentos que armazena a base e o limite de cada segmento. A base aqui aponta para a tabela de páginas do segmento.
Tabela de Páginas por Segmento: Cada segmento tem sua própria tabela de páginas que mapeia páginas virtuais para quadros de memória física.
Tradução de Endereços
Para traduzir um endereço lógico (ou virtual) em um endereço físico:

Segmentação:

O endereço lógico é dividido em dois componentes: um número de segmento e um deslocamento dentro do segmento.
O número do segmento é usado para acessar a tabela de segmentos e obter a base da tabela de páginas do segmento.
Paginação:

O deslocamento dentro do segmento é dividido em dois componentes: um número de página e um deslocamento dentro da página.
O número de página é usado para acessar a tabela de páginas do segmento e obter o quadro de memória física.
O deslocamento dentro da página é adicionado ao endereço base do quadro de memória física para obter o endereço físico final.
Vantagens da Segmentação Paginada
Flexibilidade: Combina a flexibilidade da segmentação (tratamento de diferentes segmentos de maneira independente) com a eficiência da paginação (gestão de memória em blocos pequenos e fixos).
Proteção e Compartilhamento: Permite a proteção entre segmentos e o compartilhamento de segmentos entre processos.
Gerenciamento de Memória: Facilita o gerenciamento eficiente da memória, reduzindo a fragmentação externa e fornecendo uma maneira de gerenciar grandes espaços de endereçamento.

#### Pesquise sobre a futura extensão de 57 bits (5 níveis)

</div>