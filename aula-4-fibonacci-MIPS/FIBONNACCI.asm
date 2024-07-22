.data
	inputMessage: .asciiz "Digite o numero de fibonacci\n"
	outputMessage: .ascii "O resultado e: "
	input:       .word 0
	output:     .word 0

.text
	.globl main
	main:
	# Mostro a mensagem de input
	li $v0, 4
	la $a0, inputMessage
	syscall
	
	# Leio o inteiro digitado
	li $v0, 5
	syscall
	
	# Salvo o inteiro na variavel global input
	sw $v0, input
	
	
	lw $a0, input
	jal fibonnacci # Chamo a funcao fibonacci
	sub $v0, $v0, $a0 # Diminuo o resultado pelo input inicial, pois defini a variavel global
	sw $v0, output
	
	# Imprimo a mensagem de saida
	li $v0, 4
	la $a0, outputMessage
	syscall
	
	# Imprimo o output no terminal
	li $v0, 1
	lw $a0, output
	syscall
	
	# Termino o programa
	li $v0, 10
	syscall
	
.globl fibonnacci 
fibonnacci:
    sub $sp, $sp, 8  # Aloco espaco na pilha para 2 variaveis
	sw $ra, ($sp)
	sw $a0, 4($sp)

	# Abaixo testo se n > 2. Se for, jump para recursao 
    slti $t0, $a0, 2          # $t0 é usado para condições. If n < 2 $t0 = 1, else $t0 = 0
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
    lw $ra, 0($sp)            # volto para a linha jal
    add, $sp, $sp, 8         # volto $sp para o topo da pilha
    jr $ra                    # pulo para a linha seguinte à recursao