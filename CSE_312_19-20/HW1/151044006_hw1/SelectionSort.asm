       .data
arr:   .word 3, 0, 74, -10, 12, 3, -5, 7, -1	 # -1 indicates end of the list

space: .asciiz " "

        .text
        .globl main
main:
		
		li $t0, 0
		la $t1, arr         

		li $t5, -1 # -1 Constant
		li $s0, 1 # 1 Constant
loop:			# Main loop
		
		add $t3, $t0, $t0    
		add $t3, $t3, $t3    
		add $t4, $t1, $t3    
		lw $t2, 0($t4) 
		j sort
continue:		# Return point for sort

		add $t6, $t0, $t0
		add $t6, $t6, $t6
		add $t6, $t6, $t1

minswap:		# Swaps the adresses of the current element and the smallest
		bne $zero, $s5, skip
		add $s4, $s4, $t1
		lw $t4, 0($t6)
		sw $t8, 0($t6)
		sw $t4, 0($s4)
skip:
		li $v0, 1
        lw $a0, 0($t6)   
        syscall 
		
		li $v0, 4
		la $a0, space
		syscall

		addi $t0, 1 
		bne $t2, $t5, loop

        jr $ra          # return to caller
		j exit
sort:			# Compares the items to find the current smallest
		li $s5, 1
		move $t6, $t0
		add $t3, $t6, $t6  
		add $t3, $t3, $t3
		add $t7, $t3, $t1 #t7 is pointing to current item addr in arr
		 
		lw $t8, 0($t7) #t8 is the current item value in array

		beq $t5, $t8, exit
		nop
		addi $t6, 1
loop2:			# Inner loop
		add $t3, $t6, $t6  
		add $t3, $t3, $t3
		add $t7, $t3, $t1
		lw $s2, 0($t7)
		beq $t5, $s2, continue
		
		slt $t9, $s2, $t8
		beq $t9, $s0, swap
continue2:	# Return point for swap
		addi $t6, 1
		j loop2
swap:
	move $s4, $t3	# index of the smallest
	move $t8, $s2
	li $s5, 0
	j continue2
exit:
	li $v0, 10
	syscall
	nop