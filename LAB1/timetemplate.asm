  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc: 
	andi $a0, $a0, 0xf 	# a bitwise AND operation to preserve/keep the 4 least significant bit
	
	li $v0, 0x30		# load the value 0x30 to $v0, modifying the syscall number. (zero in ascii) 
	ble $a0, 0x09, JD	# if $a0 <= 0x9 jump to JD, otherwise continue
	nop
	
	addi $v0, $v0, 0x7	# add 0x7 and modify the syscall number in $v0
JD:
	add $v0, $v0, $a0	# add $v0 and $a0 and store the value in $v0. 
	jr $ra
	nop
delay:
	PUSH $ra
	PUSH $s0
	
	addi $s0, $0, 0		# i = 0
	addi $t1, $0, 34000	# t1 = 4711
	move $t0, $a0		# move the argument to t0
	
while: 
	ble $t0, $0, done	# jump to done if $t0 (ms) <= 0
	nop
	
	addi $t0, $t0, -1	# $t0 - 1 / ms - 1
for: 
	beq $s0, $t1, done	# if i == t1 jump to done
	nop			# do nothing
	
	addi $s0, $s0, 1	#i++ / i = i + 1
	
	j for
	nop
done: 
	POP $s0
	POP $ra
		
	jr $ra
	nop

time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	
	
	move $s0, $a0
	move $s1, $a1
	
	andi $t0, $s1, 0xffff
	beq $t0, 0x0, HOUR
	nop 
							
	andi $t0, $s1, 0xf000  # Extract/take the upper 4 bits of $a1 by performing bitwise AND
    	sra $a0, $t0, 12       # Shift Right by 12 bits to isolate the uppermost 4 bits (E.g 1000 -> 0001)
    	jal hexasc             # Call hexasc to convert the value in $a0 to its ASCII representation
    	nop                    # No operation/placeholder
    	sb $v0, 0($s0)         # Store the result of "hexasc" in $v0 in the memory location pointed to by $t4
    	
    	andi $t0, $s1, 0xf00   # Extract the next 4 bits of $a1
    	sra $a0, $t0, 8        # Shift right by 8 bits to isolate the next 4 bits
    	jal hexasc             # Call hexasc to convert the value in $a0 to its ASCII representation
    	nop                    # No operation/placeholder
    	sb $v0, 1($s0)         # Store the result of "hexasc" in $v0 in the memory location pointed to by $t4
    	  	
    	li $t0, 0x3A           # Load the value 0x3A (colon) to $t6
    	sb $t0, 2($s0)         # Store the colon (":") in memory at position $t4 + 2

       	andi $t0, $s1, 0xf0    # Extract the next 4 bits of $a1
    	sra $a0, $t0, 4        # Shift right by 4 bits to isolate the next 4 bits   	    	
    	jal hexasc             # Call hexasc to convert the value in $a0 to its ASCII representation
    	nop                    # No operation/placeholder
    	sb $v0, 3($s0)         # Store the result of "hexasc" in $v0 in the memory location pointed to by $t4
    	    
    	andi $t0, $s1, 0xf     # Extract the last 4 bits of $a1
      	move $a0, $t0          # copy the uppermost 4 bits to $a0, copying the value at $t0 to $a0
    	jal hexasc             # Call hexasc to convert the value in $a0 to its ASCII representation
    	nop                    # No operation/placeholder
    	sb $v0, 4($s0)         # Store the result of "hexasc" in $v0 in the memory location pointed to by $t4
    	
    	li $t0, 0x00           # Load the value 0x00 (null terminator) to $t6
    	sb $t0, 5($s0)         # Store the null terminator in memory at position $t4 + 5
Done:  	
    	POP $s0
    	POP $s1
	POP $ra
	
	jr $ra
	nop	
 	
HOUR: 	
      	li $v0, 0x48
      	sb $v0, 0($s0) 
      	
      	li $v0, 0x4f
      	sb $v0, 1($s0) 
      	
      	li $v0, 0x55
      	sb $v0, 2($s0) 
      	
      	li $v0, 0x52
      	sb $v0, 3($s0)  
      	
      	li $t0, 0x00           # Load the value 0x00 (null terminator) to $t6
    	sb $t0, 4($s0)         # Store the null terminator in memory at position $t4 + 5
    	
    	j Done
    	nop

	
