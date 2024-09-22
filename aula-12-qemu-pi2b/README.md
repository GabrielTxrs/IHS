<center>
<img src="logo ufs.png" width="100"/>

### Universidade Federal de Sergipe<br>
Interface Hardware Software
Turma 03


Gabriel Teixeira Silveira<br>
Curso: Ciência da Computação<br>
Matrícula: 202100011987




### Configurando uma plataforma virtual Raspberry Pi 2B com QEMU



Professor: <br>
Calebe Micael de Oliveira Conceição




São Cristóvão<br>
Setembro de 2024

</center>

## 1. Introdução

O primeiro passo é decidir o código assembly vamos rodar em nosso Raspberry Pi 2B, que é a placa arm escolhida para esse trabalho.

Nesse trabalho, vamos rodar um código que faz uma simples soma dos inteiros 4 e 5, que serão carregados nos registradores r0 e r1 e o resultado da soma será guardado no registrador r2.

```
    .text
start:              @ Label, not really required
    mov r0, #5      @ Load register r0 with the value 5
    mov r1, #4      @ Load register r0 with the value 4
    add r2, r1, r0  @ Add r0 and r1 and store in r2

stop: b stop        @ Infinite loop to stop execution
```

## 2. Configuração inicial

Em seguida, vamos instalar, em meu Ubuntu 24.04 LTS.
1. QEMU para sistemas ARM 
2. Toolchain usada para gerar binários arm bare metal (sem SO) 
3. GDB específico para cross compilation.
   
```
1.
$ sudo apt install qemu-system-arm
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
qemu-system-arm is already the newest version (1:8.2.2+ds-0ubuntu1.2).
0 upgraded, 0 newly installed, 0 to remove and 4 not upgraded.

2.
$ sudo apt install gcc-arm-none-eabi
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
gcc-arm-none-eabi is already the newest version (15:13.2.rel1-2).
0 upgraded, 0 newly installed, 0 to remove and 4 not upgraded.

3.
$ sudo apt install gdb-multiarch
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following NEW packages will be installed:
  gdb-multiarch
0 upgraded, 1 newly installed, 0 to remove and 4 not upgraded.
Need to get 5,152 kB of archives.
After this operation, 20.7 MB of additional disk space will be used.
Get:1 http://br.archive.ubuntu.com/ubuntu noble/universe amd64 gdb-multiarch amd64
15.0.50.20240403-0ubuntu1 [5,152 kB]
Fetched 5,152 kB in 1s (6,281 kB/s)
Selecting previously unselected package gdb-multiarch.
(Reading database ... 224918 files and directories currently installed.)
Preparing to unpack .../gdb-multiarch_15.0.50.20240403-0ubuntu1_amd64.deb ...
Unpacking gdb-multiarch (15.0.50.20240403-0ubuntu1) ...
Setting up gdb-multiarch (15.0.50.20240403-0ubuntu1) ...
```

## 3. Gerar o arquivo binário

Agora que temos as ferramentas instaladas, vamos gerar o arquivo binário que vai executar em nossa plataforma virtual, a partir do código assembly da etapa 1.

```
$ arm-none-eabi-as -o add.o add.s
add.s: Assembler messages:
add.s: Warning: end of file not at end of a line; newline inserted

$ arm-none-eabi-ld -Ttext=0x0 -o add.elf add.o
arm-none-eabi-ld: warning: cannot find entry symbol _start; defaulting to 00000000

$ arm-none-eabi-nm add.elf
00001010 T __bss_end__
00001010 T _bss_end__
00001010 T __bss_start
00001010 T __bss_start__
00001010 T __data_start
00001010 T _edata
00001010 T __end__
00001010 T _end
00080000 B _stack
         U _start
00000000 t start
0000000c t stop     <-Como temos 3 instruções e cada instrução tem 4 bytes, 0xC(12)
```

A saída do comando arm-none-eabi-ld é um arquivo ELF, mas como nosso sistema ARM não possui sistema operacional, temos que converter para binário.

Para isso, utilizamos o comando abaixo:

```
$ arm-none-eabi-objcopy -O binary add.elf add.bin
```

Agora, vamos testar se o binário gerado tem o tamanho esperado.

```
$ ls -lah add.bin
-rwxrwxr-x 1 gabriel gabriel 16 Sep 22 19:07 add.bin
```
o arquivo binário gerado tem exatamente 16 bytes, uma vez que temos 4 instruções de 32 bits (4 bytes) cada.

## 4. Criando a memória Flash e carregando o binário

Em processadores ARM, a execução do programa começa a partir da posição 0x00.

Então, precisamos adicionar o binário a uma memória Flash de 16MB para que a placa Raspberry Pi 2B execute o código.

Quando o QEMU emula a placa Raspberry Pi 2B, é necessário especificar um arquivo que será tratado como a memória flash do dispositivo.

Então, vamos criar um arquivo de 16MB chamado flash.bin, contendo apensar zeros,
copiados de /dev/zero, usando dd, copiados em blocos de 4KB.

```
$ dd if=/dev/zero of=flash.bin bs=4096 count=4096
4096+0 records in
4096+0 records out
16777216 bytes (17 MB, 16 MiB) copied, 0.029638 s, 566 MB/s
```

Agora vamos copiar o binário add.bin gerado anteriormente para o início da ﬂash.

O comando *notrunc* garante que o restante do conteúdo da ﬂash.bin (somente 0s) será mantido.
```
$ dd if=add.bin of=flash.bin bs=4096 conv=notrunc
0+1 records in
0+1 records out
16 bytes copied, 9.042e-05 s, 177 kB/s
```
 
## 5. Executando no QEMU

Para descobrir como utilizar o QEMU com a placa, rodei o camando:

```
qemu-system-arm -machine help
```
Que me retornou uma lista de máquinas suportadas pelo QEMU, deixei o arquivo com todas as respostas no arquivo maquinas-arm-qemu.txt.

```
Supported machines are:
akita                Sharp SL-C1000 (Akita) PDA (PXA270)
ast1030-evb          Aspeed AST1030 MiniBMC (Cortex-M4)
ast2500-evb          Aspeed AST2500 EVB (ARM1176)
ast2600-evb          Aspeed AST2600 EVB (Cortex-A7)
bletchley-bmc        Facebook Bletchley BMC (Cortex-A7)
borzoi               Sharp SL-C3100 (Borzoi) PDA (PXA270)
bpim2u               Bananapi M2U (Cortex-A7)
canon-a1100          Canon PowerShot A1100 IS (ARM946)
cheetah              Palm Tungsten|E aka. Cheetah PDA (OMAP310)
collie               Sharp SL-5500 (Collie) PDA (SA-1110)
connex               Gumstix Connex (PXA255)
...
quanta-q71l-bmc      Quanta-Q71l BMC (ARM926EJ-S)
rainier-bmc          IBM Rainier BMC (Cortex-A7)
raspi0               Raspberry Pi Zero (revision 1.2)
raspi1ap             Raspberry Pi A+ (revision 1.1)
raspi2b              Raspberry Pi 2B (revision 1.1)
realview-eb          ARM RealView Emulation Baseboard (ARM926EJ-S)
...
```

Em seguida, rodei o comando:

```
$ qemu-system-arm -S -M raspi2b -drive file=flash.bin,if=pflash,format=raw -nographic -serial /dev/null
QEMU 8.2.2 monitor - type 'help' for more information
qemu-system-arm: -drive file=flash.bin,if=pflash,format=raw: machine type does not support if=pflash,bus=0,unit=0
```
Esse erro me indicou que a placa Raspberry Pi 2B não possui uma interface de flash paralela (pflash), assim como a placa Gumstix Connex, então após pesquisar um pouco, rodei o comando:

```
$ qemu-system-arm -S -M raspi2b -kernel flash.bin -nographic -serial /dev/null
QEMU 8.2.2 monitor - type 'help' for more information
(qemu) gdbserver
Waiting for gdb connection on device 'tcp::1234'
```

Sucesso! Em seguida iniciei o servidor GDB e abri um novo terminal para conectar o GDB-Multiarch.

## 6. GDB-Multiarch
No novo terminal, executei os comandos:

```
$ gdb-multiarch add.o
(gdb) target remote localhost:1234
Remote debugging using localhost:1234
(gdb)
```
Passamos o add.o para carregar a tabela de símbolos no depurador.

E em seguida comecei a depuração!

```
(qemu) info registers
CPU#0
R00=00000005 R01=00000004 R02=00000009 R03=00000000
R04=00000000 R05=00000000 R06=00000000 R07=00000000
R08=00000000 R09=00000000 R10=00000000 R11=00000000
R12=00000000 R13=00000000 R14=0000000c R15=0001000c
PSR=400001d3 -Z-- A NS svc32
s00=00000000 s01=00000000 d00=0000000000000000
s02=00000000 s03=00000000 d01=0000000000000000
s04=00000000 s05=00000000 d02=0000000000000000
...
s60=00000000 s61=00000000 d30=0000000000000000
s62=00000000 s63=00000000 d31=0000000000000000
FPSCR: 00000000
(qemu) quit
```
Como podemos ver, de fato conseguimos executar o programa, os registradores receberam os valores 4 e 5 e a soma foi efetuada.