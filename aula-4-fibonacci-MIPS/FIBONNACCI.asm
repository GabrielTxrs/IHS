.data
	inputMessage: .asciiz "Digite o numero de fibonacci\n"
	outputMessage: .ascii "O resultado e: "
	input:       .word 0
	output:     .word 0

.text
	.globl main
	main:
	
	li $v0, 4 # print_string
	la $a0, inputMessage # coloco a mensagem de imput em $a0
	syscall # Mostro a mensagem de input
	
	li $v0, 5 # read_int
	syscall # Leio o inteiro digitado
	
	sw $v0, input # Salvo o inteiro passado na variavel global input
	
	lw $a0, input # passo input como parametro de fibonacci
	jal fibonnacci # jump para a funcao fibonacci
	sub $v0, $v0, $a0 # Diminuo o output pelo input inicial, pois defini a variavel globalmente
	sw $v0, output 
	
	li $v0, 4 # print_string
	la $a0, outputMessage # coloco a mensagem de saida no registrador $a0
	syscall # Imprimo a mensagem de saida
	
	li $v0, 1 # print_int
	lw $a0, output # coloco o output no registrador $a0
	syscall # Imprimo o output no terminal
	
	
	li $v0, 10 # exit
	syscall # Termino o programa
	
.globl fibonnacci 
fibonnacci:
    sub $sp, $sp, 8  # Aloco espaco na pilha para 2 variaveis, n e para o endereco de memoria da pilha
	sw $ra, 0($sp)
	sw $a0, 4($sp) 

	# Nas duas linhas abaixo, testo se n > 2. Se for, jump para recursao 
    slti $t0, $a0, 2          # Test if less than. O registrador $t0 é usado para condições. If n < 2 $t0 = 1, else $t0 = 0
    beq $t0, $zero, recursao  # se $t0 == 0 jump para recursao
    add $v0, $v0, $a0         # somo o valor de n a $v0, mas como usei $v0 para guardar o input, vou ter q subtrair ao sair da funcao
    add $sp, $sp, 8           # volto o registrador $sp para o topo da pilha
    jr $ra                    # pulo para a linha seguinte à chamada de fibonnacci

recursao:
    sub $a0, $a0, 1         # n = n - 1
    jal fibonnacci           # volto para fibonnacci, fazendo F(n - 1)
    sub $a0, $a0, 1         # n = n - 1
    jal fibonnacci            # volto para fibonnacci, fazendo F(n - 2)
    lw $a0, 4($sp)            # recupero o valor de n
    lw $ra, 0($sp)            # recupero o endereco da linha jal no main
    add, $sp, $sp, 8         # volto $sp para o topo da pilha
    jr $ra                    # pulo para a linha seguinte à recursao
