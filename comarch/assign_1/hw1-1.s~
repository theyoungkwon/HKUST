# ------------------------------------------------------------
#
# ICE3003-43 Computer Architecture (Spring 2014)
# 
# Instructor: Prof. Jae W. Lee (jaewlee@skku.edu)
#
# Authors: Chung Ha Sung   (sch8906@gmail.com) 
#          Yunkeuk Kim     (giocafe87@gmail.com)
#
# Description:
# 
# For this assignment, you must implement function the
# (fib) labeled with "FILL IN YOUR CODE HERE!!".
#
# fib (int input) takes one argument:
#    input = input number of fibonacci ($a0)
#
# The result of finonacci should be saved in return value ($v0)
#
# Please refer to Lab #1 description slides available at the
# course website on iCampus for more details.
#
# Copyright (C) 2014 SungKyunKwan University 
# 
# -----------------------------------------------------------

.data
input     :  .asciiz     "hw1-1_input3.txt"
output    :  .asciiz     "Result of Fibonacci: "
error_msg :  .asciiz     "There is no input file\n"
enter     :  .asciiz     "\n"
buffer    :

.text
main:
	###  file open  ###
	la      $a0, input
	li      $a1, 0
	li      $a2, 0644
	li      $v0, 13
	syscall

	###  file open error check  ###
	li      $a0, -1
	beq     $v0, $a0, error_print

	###  file read  ###
	move    $a0, $v0
	la      $a1, buffer
	li      $a2, 1024
	li      $v0, 14
	syscall
	move    $s0, $v0          # $s0 := amount of read

	###  file close  ###
	li      $v0, 16
	syscall
	
	li      $t1, 0            # temp buffer
	li      $t2, 10

atoi:
	addi    $s0, $s0, -1
	lb      $t3, ($a1)
	addi    $a1, 1
	beq     $t3, $t2, save2arr
	addi    $t3, $t3, -48     # ascii to int
	mul     $t1, $t1, $t2
	add     $t1, $t1, $t3
	bne     $s0, $zero, atoi
	j       save2arr

error_print:
	###  print error_msg  ###
	move    $s7, $v0
	la      $a0, error_msg
	li      $v0, 4
	syscall
	j       exit

save2arr:
	# Setting the argument value
    # "Conventionally" $ax contains argument value before
    # function call(jal)
    # In contrast, $vx saves return value of the function
    # Please refer t the text book
	# 5th Edition: 96p ~ 106p and Appendix A.6 Procedure call convention
    # 4th Edition: 112p ~ 122p and Appendix B.6 Procedure call convention
	move    $a0, $t1
	jal     fib

	###  print ouput  ###
	move    $s7, $v0
	la      $a0, output
	li      $v0, 4
	syscall
	
	###  print number  ###
	move    $a0, $s7
	li      $v0, 1
	syscall
	
	###  print enter  ###
	la      $a0, enter
	li      $v0, 4
	syscall
	j       exit

exit:
	###  exit  ###
	li      $v0, 10
	syscall

fib:
##################################################################
# You are allowed to modify this part of the code only: START
##################################################################
	addi $sp, $sp, -12
	#sw $v1, 8($sp)
	sw $ra, 4($sp)
	sw $a0, 0($sp)
	
	bne $a0, $zero, L1		# case of ( a0 != 0 )
	addi $v1, $zero, 0
	addi $sp, $sp, 12
	jr $ra
	
L1 :
	addi $t0, $zero, 1		
	bne $a0, $t0, L2		# case of ( a0 != 1 )
	addi $v1, $zero, 1
	addi $sp, $sp, 12
	jr $ra
	
L2 :
	addi $a0, $a0, -1
	jal fib
	addi $a0, $a0, -1
	sw $v1, -4($sp)
	jal fib

	lw $a0, 0($sp)
	lw $ra, 4($sp)
	lw $v1, 8($sp)
	addi $sp, $sp, 12
	add $v0, $v1, $v0
	jr $ra

        ## FILL IN YOUR CODE HERE!! ##

##################################################################
# You are allowed to modify this part of the code only: END
##################################################################

    jr      $ra
