.data
# DONOTMODIFYTHISLINE
frameBuffer: 	.space 0x80000	# 512 wide X 256 high pixels
M:		.word  200
N:		.word  128
cr:		.word  43
cg:		.word  192
cb:		.word  59
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
		li   $t2,0x00feeb3d	# t2 <- yellow
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
		beq  $t0,$t1,center	# exit loop if colors are fully set
		addi $t0,$t0,4		# t1 <- addr of next crgb value
		j    loopRGB		# iterate
setRGB:		addi $t2,$zero,255	# t2 <- largest crgb value
		j    retRGB		# return to loop

center:		addi $t1,$zero,256	# t1 <- 256
		addi $t2,$s1,8		# t2 <- M+8
		sub  $t0,$t1,$t2	# t0 <- 256-(M+8)
		sll  $t0,$t0,10		# t0 <- bitmap row for centering arrow: (256-(M+8))/2 * 512
		addi $t0,$t0,-2048	# t0 <- bitmap row-1
		sub  $t3,$s1,$s2	# t3 <- M-N
		srl  $t1,$t3,1		# t1 <- (M-N)/2
		add  $t1,$t1,$t2	# t1 <- (M-N)/2 + M+8
		addi $t2,$zero,512      # t2 <- 512
		sub  $t1,$t2,$t1	# t1 <- 512 - ((M-N)/2 + M+8)
		sll  $t1,$t1,1		# t1 <- bitmap column for centering arrow: (512 - ((M-N)/2 + M+8))/2 * 4
		add  $t1,$t1,-4		# t1 <- bitman column - 1
		add  $t0,$s0,$t0	# t0 <- bitmap[row][0]
		add  $t0,$t1,$t0	# t0 <- bitmap[row][col]
		
drawVBox:	add  $t1,$zero,$zero	# t1 <- 0
		add  $t4,$t0,$zero	# t4 <- bitmap[row][col]
loopDVBOut:	slt  $t5,$t1,$t3	# t5 <- 1 if t1 < M-N, else t5 <- 0
		beq  $t5,$zero,drawHBox	# exit loop if part fully drawn
		add  $t2,$zero,$zero	# t2 <- 0
loopDVBIn:	slt  $t5,$t2,$s1	# t5 <- 1 if t2 < M, else t5 <- 0
		beq  $t5,$zero,endDVBIn	# exit loop if line drawn
		sw   $t8,0($t4)		# bitmap pixel <- arrow color
		addi $t4,$t4,2048	# t4 <- bitmap[row+1][col]
		addi $t2,$t2,1		# t2 <- t2 +1
		j    loopDVBIn		# iterate
endDVBIn:	addi $t0,$t0,4		# t0 <- bitmap[row][col+1]
		add  $t4,$t0,$zero	# t4 <- bitmap[row][col+1]
		addi $t1,$t1,1		# t1 <- t1+1
		j    loopDVBOut		# iterate

drawHBox:	sll  $t1,$s2,11		# t1 <- N*4*512
		add  $t0,$t0,$t1	# t0 <- bitmap[row+N][col]
		add  $t4,$t0,$zero	# t4 <- bitmap[row+N][col]
		add  $t1,$zero,$zero	# t1 <- 0
loopDHBOut:	slt  $t5,$t1,$s2	# t5 <- 1 if t1 < N, else t5 <- 0
		beq  $t5,$zero,drawHead	# exit loop if part fully drawn
		add  $t2,$zero,$zero	# t2 <- 0
loopDHBIn:	slt  $t5,$t2,$t3	# t5 <- 1 if t2 < (M-N), else t5 <- 0
		beq  $t5,$zero,endDHBIn	# exit loop if line drawn
		sw   $t8,0($t4)		# bitmap pixel <- arrow color
		addi $t4,$t4,2048	# t4 <- bitmap[row+1][col]
		addi $t2,$t2,1		# t2 <- t2 +1
		j    loopDHBIn		# iterate
endDHBIn:	addi $t0,$t0,4		# t0 <- bitmap[row][col+1]
		add  $t4,$t0,$zero	# t4 <- bitmap[row][col+1]
		addi $t1,$t1,1		# t1 <- t1+1
		j    loopDHBOut		# iterate

drawHead:	addi $t0,$t0,-16384	# t0 <- bitmap[row-8][col]
		add  $t4,$t0,$zero	# t4 <- bitmap[row-8][col]
		addi $t3,$t3,16		# t3 <- (M-N)+16	
loopDAHOut:	beq  $t3,$zero,endCode	# exit loop if arrow drawn
		add  $t1,$zero,$zero	# t1 <- 0
loopDAHIn:	slt  $t5,$t1,$t3	# t5 <- 1 if t1 < t3, else t5 <- 0
		beq  $t5,$zero,endDAHIn	# exit loop if line drawn
		sw   $t9,0($t4)		# bitmap pixel <- arrow color
		addi $t4,$t4,2048	# t4 <- bitmap[row+1][col]
		addi $t1,$t1,1		# t1 <- t1+1
		j loopDAHIn		# iterate
endDAHIn:	addi $t3,$t3,-2		# t3 <- t3-2
		addi $t0,$t0,2052	# t0 <- bitmap[row+1][col+1]
		add  $t4,$t0,$zero	# t4 <- bitmap[row+1][col+1]
		j loopDAHOut		# iterate

endCode:	li   $v0,10	# exit code
		syscall 	# exit to OS
