addi $1, $0, 5              # $1 = 5
ori  $2, $1, 3              # $2 = 7
andi $3, $2, -1             # $3 = 7
add  $4, $3, $1             # $4 = 5 + 7 = 12
sub  $5, $4, $3             # $5 = 12 - 7 = 5
xor  $6, $1, $4             # $6 = 5 & 12 = 9
sw   $4, 100($5)            # memory[100 + 0] = 12
lw   $7, 100($5)            # $7 = memory[100 + 0] = 12
slt  $8, $1, $2             # $8 = $1 < $2 = 5 < 7 = 1
goback: beq $8, $5, finish		# not taken the first time.
xor $8, $6, $4				# $8 = 9 xor 12 = 5
jal goback					# jump back to label 1. store next instruction address in register 31.
add $9,$9,$0					# infinite loop
finish: jr $31 			# jumping to previous instruction


