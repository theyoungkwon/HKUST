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
# (execute_anagram) labeled with "FILL IN YOUR CODE HERE!!". 
#
# execute_anagram (int size) takes one argument:
#    size = the number of characters ($a0)
#
# if you want to run print() function, use "jal print".
#
# Please refer to Lab #1 description slides available at the
# course website on iCampus for more details.
#
# Copyright (C) 2014 SungKyunKwan University 
# 
# -----------------------------------------------------------

.data
input         :  .asciiz     "hw1-3_input.txt"
error_msg     :  .asciiz     "There is no input file\n"
enter         :  .asciiz     "\n"
space         :  .asciiz     " "
original_array:	 .byte       0:4
print_array   :  .byte       0:4
array_index   :  .word       0, 0, 0, 0
static_cnt    :  .word       1
cnt           :  .word       0
buffer:

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

	move    $s1, $v0                  # file descriptor saved in $s1
	li      $t2, 10                   # enter check $t2
	la      $a1, original_array       # buffer address $a1
	li      $t1, 0                    # temp buffer $t1
	li      $s7, 0
	j       file_read

file_read:
	###  file read  ###
	move    $a0, $s1
	li      $a2, 1024                 # $a2:= amount of read in bytes
	li      $v0, 14
	syscall                           # $v0:= amount of read from input

	add     $t0, $v0, $a1
	lb      $t0, 0($t0)
	bne     $t0, 0, run
	addi    $v0, $v0, -1              # delete enter

run:
	move    $t3, $v0
	jal     close_file

	# Setting the argument value
    # "Conventionally" $ax contains argument value before
    # function call(jal)
    # In contrast, $vx saves return value of the function
    # Please refer to the text book
	# 5th Edition: 96p ~ 106p and Appendix A.6 Procedure call convention
    # 4th Edition: 112p ~ 122p and Appendix B.6 Procedure call convention
	move    $a0, $t3
	jal     execute_anagram
	j       exit

close_file:
	move    $a0, $s1
	li      $v0, 16
	syscall
	j       $ra

error_print:
	###  print error_msg  ###
	move    $s7, $v0
	la      $a0, error_msg
	li      $v0, 4
	syscall
	j       exit

exit:
	###  exit  ###
	li     $v0, 10
	syscall

print:
	############################  print  ##############################
	# print() function prints the print_array.                        #
	# print() function does not pollute other registers while calling.#
	###################################################################
	addi    $sp, $sp, -20
	sw      $t0, 0($sp)
	sw      $t1, 4($sp)
	sw      $t2, 8($sp)
	sw      $a0, 12($sp)
	sw      $v0, 16($sp)   
	move    $t0, $zero
	li      $t2, 4                    # t2:= MAX
	la      $t1, print_array
	j       print_loop

print_loop:	
	add     $a0, $t1, $t0
	lb      $a0, 0($a0)
	addi    $v0, $zero, 11
	syscall
	addi    $t0, $t0, 1
	beq     $t0, $t2, print_end
	j       print_loop

print_end:
	addi    $v0, $zero, 4
	la      $a0, space
	syscall

	addi    $v0, $zero, 1
	la      $t2, static_cnt
	lw      $a0, 0($t2)
	syscall

	addi    $a0, $a0, 1
	sw      $a0, 0($t2)
	addi    $v0, $zero, 4
	la      $a0, enter
	syscall

	lw      $t0, 0($sp)
	lw      $t1, 4($sp)
	lw      $t2, 8($sp)
	lw      $a0, 12($sp)
	lw      $v0, 16($sp)
	addi    $sp, $sp, 20
	j       $ra
	
execute_anagram:
##################################################################
# You are allowed to modify this part of the code only: START
##################################################################

        ## FILL IN YOUR CODE HERE!! ##

##################################################################
# You are allowed to modify this part of the code only: END
##################################################################

    jr      $ra
