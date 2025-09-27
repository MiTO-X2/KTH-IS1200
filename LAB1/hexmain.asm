  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0, 17		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc: 
	andi $a0, $a0, 0xf 	# a bitwise AND operation to preserve/keep the 4 least significant bits
	
	li $v0, 0x30		# load the value 0x30 to $v0, modifying the syscall number. (zero in ascii)
	ble $a0, 0x09, JD	# if $a0 <= 0x9 jump to JD, otherwise continue
	nop

	addi $v0, $v0, 0x7	# add 0x7 and modify the syscall number in $v0
JD:
	add $v0, $v0, $a0	# add $v0 and $a0 and store the value in $v0.  
	jr $ra			# 0x37 + 0x0D = 0x44, $a0 = 13 = 0x0D
	nop

