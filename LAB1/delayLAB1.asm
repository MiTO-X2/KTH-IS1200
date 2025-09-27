.data
.text

delay:
	addi $s0, $0, 0		# i = 0
	addi $t1, $0, 4711	# t1 = 4711
	move $t0, $a0		# move the argument to t0
	
while: 
	ble $t0, $0, done	# jump to done if $t0 (ms) <= 0
	nop
	
	addi $t0, $t0, -1	# $t0 - 1 / ms - 1
for: 
	beq $s0, $t1, done
	nop			# do nothing
	
	addi $s0, $s0, 1	#i++ / i = i + 1
	
	j for
	nop
done: 	
	jr $ra
	nop
	
