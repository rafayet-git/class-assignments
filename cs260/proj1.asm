.data
# DONOTMODIFYTHISLINE
frameBuffer: 	.space 0x80000	# 512 wide X 256 high pixels
M:		.word  100
N:		.word  76
cr:		.word  10
cg:		.word  64
cb:		.word  10
# DONOTMODIFYTHISLINE
# Your other variables go BELOW here only
.text
makeBG: 	la   $t1,frameBuffer	# t1 <- addr of bitmap start
		addi $t2,$zero,512	# t2 <- 512
		sll  $t2,$t2,10		# t2 <- 512 * 256 * 4
		add  $t2,$t1,$t2 	# t2 <- addr of bitmap end
		li   $t3,0x00FFFF00	# t3 <- yellow
loopBG:		sw   $t3,0($t1)		# bitmap pixel <- yellow
		addi $t1,$t1,4		# t1 <- next pixel on bitmap
		beq  $t1,$t2,checkInput	# exit loopBG if t1 == end of bitmap 
		j    loopBG		# iterate
		
		# Check M and N if they are within range
checkInput:	la   $t1,M		# t1 <- addr of M
		lw   $t2,0($t1)		# t2 <- M
		lw   $t3,4($t1)		# t3 <- N
		slti $t4,$t2,256	# t4 <- 1 if M < 256 (height), else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		slt  $t4,$t3,$t2	# t4 <- 1 if N < M, else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		slt  $t4,$zero,$t3	# t4 <- 1 if 0 < N, else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		slt  $t4,$zero,$t2	# t4 <- 1 if 0 < M, else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		# Check if centerable by checking bit 0 for even value.
		andi $t4,$t2,0x0001	# t4 <- 0 if M is even, else t4 <- 1
		bne  $t4,$zero,endCode	# exit code if invalid input
		andi $t4,$t3,0x0001	# t4 <- 0 if N is even, else t4 <- 1
		bne  $t4,$zero,endCode	# exit code if invalid input
calcRGB:

endCode:	li $v0,10	# exit code
		syscall 	# exit to OS