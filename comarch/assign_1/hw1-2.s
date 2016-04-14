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
# (insert_heap) labeled with "FILL IN YOUR CODE HERE!!". 
#
# insert_heap (int curr, int input) takes two arguments:
#    curr = current index of heap ($a0)
#    input = input number ($a1)
#
# Please refer to Lab #1 description slides available at the
# course website on iCampus for more details.
#
# Copyright (C) 2014 SungKyunKwan University 
# 
# -----------------------------------------------------------

.data
input     :  .asciiz     "hw1-2_input.txt"
line      :  .asciiz     "\n---------------\n"
space     :  .asciiz     " "
enter     :  .asciiz     "\n"
error_msg :  .asciiz     "There is no input file\n"
heap      :  .word	     0:10
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

	li      $s0, 1            # number of insertions:= curr
	move    $s1, $v0          # file descriptor saved in $s1
	li      $t1, 10           # enter check
	li      $t0, 0

file_read:
	###  file read  ###
	li     $v0, 14
	move   $a0, $s1
	la     $a1, buffer
	li     $a2, 1
	syscall

	beq    $v0, $zero, print_heap

	la     $t2, buffer
	lb     $t2, 0($t2)
	beq    $t2, $t1, make_input
	addi   $t2, $t2, -48       # ascii to int
	mul    $t0, $t0, $t1
	add    $t0, $t0, $t2
	j file_read

error_print:
	###  print error_msg  ###
	move    $s7, $v0
	la      $a0, error_msg
	li      $v0, 4
	syscall
	j       exit

make_input:
	addi    $sp, $sp, -16
	sw      $v0, 0($sp)
	sw      $s0, 4($sp)
	sw      $s1, 8($sp)
	sw      $a1, 12($sp)

	# Setting the argument value
    # "Conventionally" $ax contains argument value before
    # function call(jal)
    # In contrast, $vx saves return value of the function
    # Please refer to the text book
	# 5th Edition: 96p ~ 106p and Appendix A.6 Procedure call convention
    # 4th Edition: 112p ~ 122p and Appendix B.6 Procedure call convention
	move    $a0, $s0
	move    $a1, $t0
	jal     insert_heap

	lw      $v0, 0($sp)
	lw      $s0, 4($sp)
	lw      $s1, 8($sp)
	lw      $a1, 12($sp)
	addi    $sp, $sp, 16
	move    $t0, $zero
	li      $t1, 10
	addi    $s0, $s0, 1
	j       file_read

print_heap:
	###  file close  ###
	move   $a0, $s1
	li     $v0, 16
	syscall

	###  print heap  ###
	la      $t0, heap
	addi    $t0, $t0, 4       # $t0:= heap[i] (i=1)
	addi    $s0, $s0, -1
	li      $s1, 0            # $s1:= level
	li      $s2, 0            # $s2:= print_cnt
	li      $s3, 1            # $s3:= level_num

print_heap_loop:
	###  if (print_cnt == level_num)  ###
	beq     $s2, $s3, draw_line

just_print:
	###  print space  ###
	la      $a0, space
	li      $v0, 4
	syscall

	###  print one element in heap  ###
	lw      $a0, ($t0)
	li      $v0, 1
	syscall

	###  print space  ###
	la      $a0, space
	li      $v0, 4
	syscall

	addi    $t0, $t0, 4
	addi    $s0, $s0, -1
	addi    $s2, $s2, 1       # print_cnt ++;
	bgt     $s0, $zero, print_heap_loop

	###  print enter  ###
	la      $a0, enter
	li      $v0, 4
	syscall
	j       exit

draw_line:
	addi    $s1, $s1, 1       # level ++;
	li      $t1, 2
	mul     $s3, $s3, $t1     # level_num *= 2;
	move    $s2, $zero

	###  print line  ###
	la      $a0, line
	li      $v0, 4
	syscall	
	j       just_print

exit:
	###  exit  ###
	li      $v0, 10
	syscall

insert_heap:
##################################################################
# You are allowed to modify this part of the code only: START
##################################################################

        ## FILL IN YOUR CODE HERE!! ##

##################################################################
# You are allowed to modify this part of the code only: END
##################################################################

    jr      $ra
