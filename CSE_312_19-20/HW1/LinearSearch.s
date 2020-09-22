       .data
key:   .space 4
strsucc: .asciiz "Success!"
strfail: .asciiz "Failure."

arr:   .word 3, 0, 74, -10, 12, 3, -5, 7, -1	# -1 indicates end of the list

space: .asciiz " "

        .text
        .globl main
main:   

		# Get the first integer from the user
		li $v0, 5
        syscall  

		la $t0, key 
		sw $v0, 0($t0) 

		li $t0, 0
		la $t1, arr         

		li $t5, -1 # -1 Constant

loop:		# Main loop that looks for the item
		
		add $t3, $t0, $t0    
		add $t3, $t3, $t3    
		add $t4, $t1, $t3    
		lw $t2, 0($t4) 
		la $t6, key
		lw $t6, 0($t6)
		addi $t0, 1
		beq $t2, $t6, success
		bne $t2, $t5, loop
		j fail
success:	# Prints out success string
		li $v0, 4
		la $a0, strsucc
		syscall
		j exit
fail:		# Prints out failure string
		li $v0, 4
		la $a0, strfail
		syscall
		j exit
exit:
		li $v0, 10
		syscall
		nop

