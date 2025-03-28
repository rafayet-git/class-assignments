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

setup:		la   $s0,frameBuffer	# s0 <- addr of bitmap start
		la   $s1,M		# s1 <- addr of M
		addi $s3,$s1,8		# s3 <- addr of cr
		lw   $s2,4($s1)		# s2 <- N
		lw   $s1,0($s1)		# s1 <- M

makeBG: 	add  $t0,$zero,$s0	# t0 <- bitmap start
		addi $t1,$zero,512	# t1 <- 512
		sll  $t1,$t1,10		# t1 <- 512 * 256 * 4
		add  $t1,$t0,$t1 	# t1 <- addr of bitmap end
		li   $t2,0x00FFFF00	# t2 <- yellow
loopBG:		sw   $t2,0($t0)		# bitmap pixel <- yellow
		addi $t0,$t0,4		# t0 <- next pixel on bitmap
		beq  $t0,$t1,checkInput	# exit loopBG if t0 == end of bitmap 
		j    loopBG		# iterate
		
		# Check M and N if they are within range
checkInput:	slti $t4,$s1,241	# t4 <- 1 if M <= 240 (height - overhang), else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		slt  $t4,$s2,$s1	# t4 <- 1 if N < M, else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		slt  $t4,$zero,$s2	# t4 <- 1 if 0 < N, else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		slt  $t4,$zero,$s1	# t4 <- 1 if 0 < M, else t4 <- 0
		beq  $t4,$zero,endCode	# exit code if invalid input
		# Check if centerable by checking if M and N are divisible by 4 (account for arrowhead width)
		andi $t4,$s1,0x0003	# t4 <- 0 if 4 divides M, else t4 <- 1
		bne  $t4,$zero,endCode	# exit code if invalid input
		andi $t4,$s2,0x0003	# t4 <- 0 if 4 divides N, else t4 <- 1
		bne  $t4,$zero,endCode	# exit code if invalid input



calcRGB:	addi $t9,$zero,0	# t9 <- arrowhead color (0,0,0)
		addi $t8,$zero,0	# t8 <- arrow color (0,0,0)
		add  $t0,$zero,$s3	# t0 <- addr of cr
		addi $t1,$t0,8		# t1 <- addr of cb 
loopRGB:	lw   $t2,0($t0)		# t2 <- crgb value 
		sll  $t9,$t9,8		# t9 <- shift color to next field
		sll  $t8,$t8,8		# t8 <- shift color to next field
		add  $t9,$t9,$t2	# t9 <- arrowhead color (-,-,crgb)
		sll  $t2,$t2,2		# t2 <- crgb*4
		slti $t4,$t2,256	# t4 <- 1 if crgb*4 < 256, else t4 <- 0
		beq  $t4,$zero,setRGB 	# branch if invalid color 
retRGB:		add  $t8,$t8,$t2	# t8 <- arrow color (-,-,crgb*4)
		beq  $t0,$t1,draw	# exit loop if colors are fully set
		addi $t0,$t0,4		# t1 <- addr of next crgb value
		j    loopRGB		# iterate
setRGB:		addi $t2,$zero,255	# t2 <- largest crgb value
		j    retRGB		# return to loop

draw:		

endCode:	li   $v0,10	# exit code
		syscall 	# exit to OS
