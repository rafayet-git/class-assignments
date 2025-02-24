### Alias: corbato

# Homework 2 Memory

CFG:

<img title="" src="file:///home/cart/Documents/class-assignments/cs260/1740336.png" alt="1740336.png" width="425">

Code:

```
# Alloc: a1->$s0, a2->$s1, n->$s2
       addi $t0, $zero, 0     # t0 <- 0
Loop:  slt  $t1, $t0, $s2     # t1 <- 1 if t0 < n, else t1 <- 0
       beq  $t1, $zero, Lexit # exit Loop if t0 >= n
    
       sll  $t1, $t0, 2       # t1 <- 4*t0
       add  $t1, $t1, $s0     # t1 <- addr of a1[t0]
       lw   $t2, 0($t1)       # t2 <- a1[t0]
       sll  $t1, $t0, 3       # t1 <- 8*t0
       add  $t1, $t1, $s1     # t1 <- addr of a2[t0]
       sw   $t2, 0($t1)       # a2[t0] <- a1[t0]

       sra  $t2, $t2, 31      # t2 <- a1[t0]>>31 (sign ext.)
       sw   $t2, 4($t1)       # a2[t0]>>32 <- a1[t0]>>31

       addi $t0, $t0, 1       # t0 <- t0 + 1
       j    Loop              # iterate
Lexit: ...
```
