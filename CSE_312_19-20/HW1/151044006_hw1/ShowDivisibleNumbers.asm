       .data
int1:  .space 4
int2:  .space 4
int3:  .space 4

space: .asciiz " "

        .text
        .globl main
main:   

		# Get the first integer from the user
		li $v0, 5
        syscall  

		la $t0, int1 
		sw $v0, 0($t0) 

		# Get the second integer from the user

		li $v0, 5
        syscall  

		la $t0, int2 
		sw $v0, 0($t0) 

		# Get the third integer from the user

	    li $v0, 5
        syscall  

		la $t0, int3 
		sw $v0, 0($t0) 

		# Find Divisible

		lw $t1, int1
		lw $t2, int2
		sub $t2, $t2, 1
loop:
		addi $t1, $t1, 1

		lw $t4, int3
		div $t1, $t4
		mfhi $t3
		beq $t3, 0, jump

		bne $t1, $t2, loop

		# End of the program
        
        jr $ra          # return to caller
jump:
		li $v0, 1
		la $a0, 0($t1)
		syscall		

		li $v0, 4
		la $a0, space
		syscall

		j loop

exit:


