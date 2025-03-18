.data
# DONOTMODIFYTHISLINE
frameBuffer: 	.space 0x80000 # 512 wide X 256 high pixels
M:		.word 15
N:		.word 10
cr:		.word 32
cg:		.word 64
cb:		.word 128
# DONOTMODIFYTHISLINE
# Your other variables go BELOW here only
.text
drawLine: la $t1,frameBuffer
li $t3,0x0000FF00 # $t3 ← green
sw $t3,15340($t1)
sw $t3,15344($t1)
sw $t3,15348($t1)
sw $t3,15352($t1)
sw $t3,15356($t1)
sw $t3,15360($t1)
sw $t3,15364($t1)
sw $t3,15368($t1)
sw $t3,15372($t1)
sw $t3,15376($t1)
li $v0,10 # exit code
syscall # exit to OS