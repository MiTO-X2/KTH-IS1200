.text
# Initialize registers
    addi $a0, $0, 3       # $a0 = n
    addi $v0, $0, 1       # result, value = 1 to start with if (!0 == 1)
    addi $v1, $a0, 1      # v1 = n + 1
    addi $a2, $0, 1       # initialize i (a2) to 1

loop1:
    beq $a2, $v1, stop    # if i(a2) == v1 jump to done
    nop
    
    addi $a2, $a2, 1      # i++, increment loop variable
    addi $a1, $0, 0       # initialize the product (a1) to 0    
    addi $a3, $0, 1       # initialize j (a3) to 1
    
Mult:
    beq $a3, $a2, loop2   # if a3 == a2 jump to loop2
    nop
    
    mul $a1, $v0, $a3     # product = value * j
    addi $a3, $a3, 1      # j++, increment inner loop variable
    
    beq $0, $0, Mult      # jump back to Mult
    nop

loop2:
    addi $v0, $a1, 0      # set return variable to product
    beq $0, $0, loop1     # jump back to loop1
    nop

stop:
    beq $0, $0, stop
    nop
