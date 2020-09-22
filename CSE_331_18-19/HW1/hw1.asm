.data
	filename: .asciiz "input_hw1.txt"
	zero: .asciiz "zero"
	one: .asciiz "one"
	two: .asciiz "two"
	three: .asciiz "three"
	four: .asciiz "four"
	five: .asciiz "five"
	six: .asciiz "six"
	seven: .asciiz "seven"
	eight: .asciiz "eight"
	nine: .asciiz "nine"
	Zero: .asciiz "Zero"
	One: .asciiz "One"
	Two: .asciiz "Two"
	Three: .asciiz "Three"
	Four: .asciiz "Four"
	Five: .asciiz "Five"
	Six: .asciiz "Six"
	Seven: .asciiz "Seven"
	Eight: .asciiz "Eight"
	Nine: .asciiz "Nine"
	sentencebuffer: .space 256
	
.text
.globl main

	main:
		#Opening File...
		li $v0, 13
		la $a0, filename
		li $a1, 0
		syscall
		#Done!
		
		move $t5, $v0 #The descriptor.
		
		#Reading the content...
		move $a0, $t5
		li $v0, 14
		la $a1, sentencebuffer
		la $a2, 256
		syscall
		#Done!		
		
		#Closing File...
		li   $v0, 16       
 		move $a0, $t5      
  		syscall  
		#Done!
		
		li $t7, 0
		loop:
			la $t2, sentencebuffer($t7)

			lb $a0, ($t2)
			
			beq $a0, $zero, exit
			
			li $t3, 48  
			beq $t3, $a0, found0
			
			li $t3, 49 
			beq $t3, $a0, found1
					
			li $t3, 50 
			beq $t3, $a0, found2
			
			li $t3, 51 
			beq $t3, $a0, found3
			
			li $t3, 52 
			beq $t3, $a0, found4
			
			li $t3, 53 
			beq $t3, $a0, found5
			
			li $t3, 54 
			beq $t3, $a0, found6	
			
			li $t3, 55 
			beq $t3, $a0, found7
			
			li $t3, 56 
			beq $t3, $a0, found8	
			
			li $t3, 57 
			beq $t3, $a0, found9
			
			addi $t7, $t7, 1 
			
			li $v0, 11
			lb $a0, ($t2)
			syscall	
    		
    			j loop
    			
    		found0:	
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    		
    			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter0:		
    			#Done!
    			
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!
    			
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found0		
			#Done!    		

			#Printing with letters instead...
    			li $v0, 4
			la $a0, zero	
			syscall
			#Done!
						
    			addi $t7, $t7, 1
    			j loop

    		found1:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    		
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter1:		
    			#Done!
    			
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!
    			
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found1	 		
    			#Done! 
    			
    			#Printing with letters instead...
    			li $v0, 4
			la $a0, one	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop
    			
    		found2:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    			
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter2:		
    			#Done!   		
    		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!    		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found2	
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, two	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		found3:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    		
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter3:		
    			#Done!    		
    		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!   		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found3	
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, three	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		found4:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    			
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter4:		
    			#Done!    		
   
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!    		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found4
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, four	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop
    			
    		found5:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    		
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter5:		
    			#Done!    		
    		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!    		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found5	
			#Done! 
				
			#Printing with letters instead...
    			li $v0, 4
			la $a0, five	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		found6:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    			
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter6:		
    			#Done!    		
    		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!    		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found6	
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, six	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop    			
 
     		found7:
     			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
     				
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter7:		
    			#Done!     		
     		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!     		
     		
     			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found7	
			#Done!
			 	
			#Printing with letters instead...
    			li $v0, 4
			la $a0, seven
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		found8:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    			
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter8:		
    			#Done!    		
    		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!    		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found8
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, eight	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop   			

    		found9:
    			#Checking Multi-digit situation...
    			jal multidigit
    			#Done
    		
   			#Checking if the number comes after a sentence-finisher dot...
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, sentencestarter
    			#Wrong alarm...
    			notsentencestarter9:		
    			#Done!    		
    		
    			#Checking if there is a dot on the left...	
    			addi $t6, $t7, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotLeft
    			#Done!
    			
    			#Checking if there is a dot on the right...
    			addi $t6, $t7, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			beq $s3, $s4, dotRight
    			#Done!    		
    		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found9
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, nine	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop       			   			
    		Found0:		
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Zero	
			syscall
			#Done!
						
    			addi $t7, $t7, 1
    			j loop

    		Found1:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, One	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop
    			
    		Found2:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Two	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Found3:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Three	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Found4:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Four	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop
    			
    		Found5:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Five	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Found6:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Six	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop    			
 
     		Found7:		
     			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Seven	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Found8:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Eight
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop   			

    		Found9:
    			#Leading digit detected, printing uppercase...
    			li $v0, 4
			la $a0, Nine	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop       			   			    			   			   			
    			   			   			   			
    			
    		dotRight:
    			addi $t6, $t6, 1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)    			
    			li $s4, 32  #ASCII OF SPACE
    			beq $s3, $s4, dotRightandspace #Then it's end of the sentence
    			j dotRightandnumber #Then it's a floating point number
    			
    		dotRightandspace: #End of sentence
    		
    			#The digit in the end, needs speacial threatment...    			
			li $t3, 48  
			beq $t3, $a0, Purefound0
			
			li $t3, 49 
			beq $t3, $a0, Purefound1
					
			li $t3, 50 
			beq $t3, $a0, Purefound2
			
			li $t3, 51 
			beq $t3, $a0, Purefound3
			
			li $t3, 52 
			beq $t3, $a0, Purefound4
			
			li $t3, 53 
			beq $t3, $a0, Purefound5
			
			li $t3, 54 
			beq $t3, $a0, Purefound6	
			
			li $t3, 55 
			beq $t3, $a0, Purefound7
			
			li $t3, 56 
			beq $t3, $a0, Purefound8	
			
			li $t3, 57 
			beq $t3, $a0, Purefound9  
			#Done!		
    		
    		dotRightandnumber: #Floating point
    			#Floating point number detected, leaving it as digits... 			   			   			   			
    			li $v0, 11
			syscall	 
			#Done!		
				   			   			   			   			   			   			   			
    			addi $t7, $t7, 1
    			j loop       		
    		dotLeft:	  
    			#Floating point number detected, leaving it as digits... 			   			   			   			
    			li $v0, 11
			syscall	 
			#Done!		
				   			   			   			   			   			   			   			
    			addi $t7, $t7, 1
    			j loop   	
    			
    		Purefound0:		
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found0		
			#Done!    		

			#Printing with letters instead...
    			li $v0, 4
			la $a0, zero	
			syscall
			#Done!
						
    			addi $t7, $t7, 1
    			j loop

    		Purefound1:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found1	 		
    			#Done! 
    			
    			#Printing with letters instead...
    			li $v0, 4
			la $a0, one	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop
    			
    		Purefound2:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found2	
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, two	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Purefound3:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found3	
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, three	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Purefound4:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found4
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, four	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop
    			
    		Purefound5:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found5	
			#Done! 
				
			#Printing with letters instead...
    			li $v0, 4
			la $a0, five	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Purefound6:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found6	
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, six	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop    			
 
     		Purefound7:	
     			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found7	
			#Done!
			 	
			#Printing with letters instead...
    			li $v0, 4
			la $a0, seven
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop

    		Purefound8:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found8
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, eight	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop   			

    		Purefound9:
    			#Checking for leading digit...
			li $s1, 0
			beq $s1, $t7, Found9
			#Done! 
			
			#Printing with letters instead...
    			li $v0, 4
			la $a0, nine	
			syscall
			#Done!
			
    			addi $t7, $t7, 1
    			j loop  
    			
    		sentencestarter:
    			addi $t6, $t6, -1
    			la $s2, sentencebuffer($t6)
    			lb $s3, ($s2)
    			li $s4, 46  #ASCII OF '.'
    			bne $s3, $s4, notsentencestarter
    			
			#The Sentence-starter digit, needs speacial threatment...    			
			li $t3, 48  
			beq $t3, $a0, Found0
			
			li $t3, 49 
			beq $t3, $a0, Found1
					
			li $t3, 50 
			beq $t3, $a0, Found2
			
			li $t3, 51 
			beq $t3, $a0, Found3
			
			li $t3, 52 
			beq $t3, $a0, Found4
			
			li $t3, 53 
			beq $t3, $a0, Found5
			
			li $t3, 54 
			beq $t3, $a0, Found6	
			
			li $t3, 55 
			beq $t3, $a0, Found7
			
			li $t3, 56 
			beq $t3, $a0, Found8	
			
			li $t3, 57 
			beq $t3, $a0, Found9  
			#Done!		    			
    					
    		        addi $t7, $t7, 1
    			j loop	
    			
    		notsentencestarter:
    			
			#Wrong alarm situation. Go to the needed notsentencestarter...    			
			li $t3, 48  
			beq $t3, $a0, notsentencestarter0
			
			li $t3, 49 
			beq $t3, $a0, notsentencestarter1
					
			li $t3, 50 
			beq $t3, $a0, notsentencestarter2
			
			li $t3, 51 
			beq $t3, $a0, notsentencestarter3
			
			li $t3, 52 
			beq $t3, $a0, notsentencestarter4
			
			li $t3, 53 
			beq $t3, $a0, notsentencestarter5
			
			li $t3, 54 
			beq $t3, $a0, notsentencestarter6	
			
			li $t3, 55 
			beq $t3, $a0, notsentencestarter7
			
			li $t3, 56 
			beq $t3, $a0, notsentencestarter8	
			
			li $t3, 57 
			beq $t3, $a0, notsentencestarter9 
			#Done!    							   			   			   			   			   			   			   			   			   			   			   			   			   			   			   		  					   			   			   			   			   			   			   			   			   			   			   			   			   			   			   							   			   			   			   			   			   			   			   			   			   			   			   			   			   			   		  					   			   			   			   			   			   			   			   			   			   			   			   			   			   			   			
.text
.globl multidigit

	multidigit:
	
		addi $t6, $t7, -1
    		la $s2, sentencebuffer($t6)
    		lb $t8, ($s2)
  				
		li $t3, 48  
		beq $t3, $t8, applymultidigit
			
		li $t3, 49 
		beq $t3, $t8, applymultidigit
					
		li $t3, 50 
		beq $t3, $t8, applymultidigit
			
		li $t3, 51 
		beq $t3, $t8, applymultidigit
			
		li $t3, 52 
		beq $t3, $t8, applymultidigit
			
		li $t3, 53 
		beq $t3, $t8, applymultidigit
			
		li $t3, 54 
		beq $t3, $t8, applymultidigit	
			
		li $t3, 55 
		beq $t3, $t8, applymultidigit
			
		li $t3, 56 
		beq $t3, $t8, applymultidigit	
			
		li $t3, 57 
		beq $t3, $t8, applymultidigit

 		addi $t6, $t7, 1
    		la $s2, sentencebuffer($t6)
    		lb $t8, ($s2)
  				
		li $t3, 48  
		beq $t3, $t8, applymultidigit
			
		li $t3, 49 
		beq $t3, $t8, applymultidigit
					
		li $t3, 50 
		beq $t3, $t8, applymultidigit
			
		li $t3, 51 
		beq $t3, $t8, applymultidigit
			
		li $t3, 52 
		beq $t3, $t8, applymultidigit
			
		li $t3, 53 
		beq $t3, $t8, applymultidigit
			
		li $t3, 54 
		beq $t3, $t8, applymultidigit	
			
		li $t3, 55 
		beq $t3, $t8, applymultidigit
			
		li $t3, 56 
		beq $t3, $t8, applymultidigit	
			
		li $t3, 57 
		beq $t3, $t8, applymultidigit
		
		jr $ra    
		
		applymultidigit:
		
			li $v0, 11
			syscall
			
			addi $t7, $t7, 1
    			j loop	   			   			   			   			   			   			   			   			   			   			   			   			   			   					   			   			   			   			   			   			   			   			   			   			   			   			   			   			   					   			   			   			   			   			   			   			   			   			   			   			   			   			   			   			
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
			exit:																																																																																																																																																																																																																																																																																																																																																																																																																																																																		
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																								
