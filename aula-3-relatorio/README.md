<div align="center">
<img src="logo ufs.png" alt="logo ufs" width="100"/>

### Universidade Federal de Sergipe<br>
Interface Hardware Software
Turma 03


Gabriel Teixeira Silveira





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

<img src="IHS-atividade-2.drawio.png" alt="logo ufs" width="900"/>

