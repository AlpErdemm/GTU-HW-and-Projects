       .data
key:   .space 4
strsucc: .asciiz "Success!"
strfail: .asciiz "Failure."

arr:   .word 3, 0, 74, -10, 12, 3, -5, 7, 8, -1		# -1 indicates end of the list

        .text
        .globl main

		# Selection Sort Starts, check SelectionSort.asm for further information
main:		
		li $t0, 0
		la $t1, arr         

		li $t5, -1 # -1 Constant
		li $s0, 1 # 1 Constant
loop:
		
		add $t3, $t0, $t0    
		add $t3, $t3, $t3    
		add $t4, $t1, $t3    
		lw $t2, 0($t4) 
		j sort
continue:

		add $t6, $t0, $t0
		add $t6, $t6, $t6
		add $t6, $t6, $t1

minswap:
		bne $zero, $s5, skip
		add $s4, $s4, $t1
		lw $t4, 0($t6)
		sw $t8, 0($t6)
		sw $t4, 0($s4)
skip:
		addi $t0, 1 
		bne $t2, $t5, loop

        jr $ra          # return to caller
		j start
sort:
		li $s5, 1
		move $t6, $t0
		add $t3, $t6, $t6  
		add $t3, $t3, $t3
		add $t7, $t3, $t1 #t7 is pointing to current item addr in arr
		 
		lw $t8, 0($t7) #t8 is the current item value in array

		beq $t5, $t8, start
		nop
		addi $t6, 1
loop2:
		add $t3, $t6, $t6  
		add $t3, $t3, $t3
		add $t7, $t3, $t1
		lw $s2, 0($t7)
		beq $t5, $s2, continue
		
		slt $t9, $s2, $t8
		beq $t9, $s0, swap
continue2:
		addi $t6, 1
		j loop2
swap:
	move $s4, $t3	# index of the smallest
	move $t8, $s2
	li $s5, 0
	j continue2
	# Selection Sort Ends.


	# Binary Search Starts
start:		
		li $t0, 0
		la $t1, arr         

		li $t5, -1 # -1 Constant
		li $s0, 1 # 1 Constant
		# Get the first integer from the user
		li $v0, 5
        syscall  

		la $t0, key 
		sw $v0, 0($t0) 

		li $t0, 0	# Start Index
		la $t1, arr         

		li $t5, -1 # -1 Constant

count:		# Finds the size of the array
		add $t3, $t0, $t0    
		add $t3, $t3, $t3    
		add $t4, $t1, $t3    
		lw $t2, 0($t4) 
		addi $t0, 1
		bne $t2, $t5, count

		move $s1, $t0
		li $t6, 2 # 2 Constant
		div $s1, $t6
		mfhi $t6
		beq $t6, $zero, even
		j odd

even:	# If the size is an even number
		li $t0, 0
		la $t1, arr         

		addi $s1, -1
evenLoop:
		add $s2, $s1, $t0
		li $t6, 2 # 2 Constant
		div $s2, $t6
		mflo $s2		 #s1 End Index
		beq $s2, $t0, fail
		add $t3, $s2, $s2    
		add $t3, $t3, $t3    
		add $t4, $t1, $t3    
		lw $t2, 0($t4) 
		la $t6, key
		lw $t6, 0($t6)
		beq $t2, $t6, success
		slt $t3, $t2, $t6
		li $t2, 1
		beq $t3, $t2, evenBigger
		j evenSmaller
continuev:		
		bne $s1, $zero, evenLoop
		j fail
evenSmaller:
		add $s1, $s1, $t0
		li $t6, 2 # 2 Constant
		div $s1, $t6
		mflo $s1
		j continuev
evenBigger:
		move $t0, $s2
		j continuev

odd:	# If the size is an odd number
		li $t0, 0
		la $t1, arr         

		addi $s1, -1
oddLoop:
		add $s2, $s1, $t0
		li $t6, 2 # 2 Constant
		div $s2, $t6
		mflo $s2		 #s1 End Index
		beq $s2, $t0, fail
		add $t3, $s2, $s2    
		add $t3, $t3, $t3    
		add $t4, $t1, $t3    
		lw $t2, 0($t4) 
		la $t6, key
		lw $t6, 0($t6)
		beq $t2, $t6, success
		slt $t3, $t2, $t6
		li $t2, 1
		beq $t3, $t2, oddBigger
		j oddSmaller
continuek:		
		bne $s1, $zero, oddLoop
		j fail
oddSmaller:
		add $s1, $s1, $t0
		li $t6, 2 # 2 Constant
		div $s1, $t6
		mflo $s1
		j continuek
oddBigger:
		move $t0, $s2
		j continuek
success:			# Prints the success string
		li $v0, 4
		la $a0, strsucc
		syscall
		j exit
fail:				# Prints the failure string
		li $v0, 4
		la $a0, strfail
		syscall
		j exit
exit:
		li $v0, 10
		syscall
		nop

