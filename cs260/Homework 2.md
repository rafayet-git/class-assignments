### Alias: corbato

# Homework 2

Code: `n= 17 - 19 * n`

```python
# Alloc n->$s0
addi $t1,$zero,17    # t1 <- 17
add $t2,$s0,$s0      # t2 <- 2*n
add $t3,$t2,$t2      # t3 <- 4*n
add $t2,$t3,$t3      # t2 <- 8*n
add $t2,$t2,$t2      # t2 <- 16*n
add $t2,$t2,$t3      # t2 <- 20*n
sub $t2,$t2,$s0      # t2 <- 19*n
sub $s0,$t1,$t2      # n <- 17 - 19*n
```




