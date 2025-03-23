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
		slti $t4,$t2,241	# t4 <- 1 if M < 241 (height - overhang), else t4 <- 0
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
		
calcRGB:	addi $t7,$zero,0	# t7 <- arrow color (0,0,0)
		addi $t6,$zero,0	# t6 <- arrowhead color (0,0,0)
		addi $t1,$t1,8		# t1 <- addr of cr
		addi $t2,$t1,8		# t2 <- addr of cb
loopRGB:	lw   $t3,0($t1)		# t3 <- addr of crgb value 
		sll  $t7,$t7,8		# t7 <- shift color to next field
		sll  $t6,$t6,8		# t6 <- shift color to next field
		add  $t7,$t7,$t3	# t7 <- color (-,-,crgb)
		sll  $t3,$t3,2		# t3 <- crgb*4
		slti $t4,$t3,256	# t4 <- 1 if crgb*4 < 256, else t4 <- 0
		beq  $t4,$zero,setRGB 	# branch if invalid color 
retRGB:		add  $t6,$t6,$t3	# t6 <- color (-,-,crgb*4)
		beq  $t1,$t2,draw	# exit loop if t6,t7 colors are fully set
		addi $t1,$t1,4		# t1 <- addr of next crgb value
		j    loopRGB		# iterate
setRGB:		addi $t3,$zero,255	# t3 <- largest crgb value
		j retRGB		# return to loop
		
draw:

endCode:	li $v0,10	# exit code
		syscall 	# exit to OS
