### Alias: corbato

# Homework 2 Arrays

Code: `a[4*k] = a[2*k+5] - (*p);`

```
# Alloc: a->$s0, k->$s1, p->$s2
add  $t0, $s1, $s1    # t0 <- 2*k
add  $t0, $t0, $t0    # t0 <- 2(2*k) = 4*k
add  $t0, $t0, $t0    # t0 <- 4(2*k) = 2(4*k)
add  $t1, $t0, $t0    # t1 <- 4(4*k)
add  $t1, $t1, $s0    # t1 <- addr of a[4*k]
addi $t0, $t0, 20     # t0 <- 4(2*k+5)
add  $t0, $t0, $s0    # t0 <- addr of a[2*k+5]

lw   $t2, 0($t0)      # t2 <- a[2*k+5]
lw   $t3, 0($s2)      # t3 <- *p
sub  $t0, $t2, $t3    # t0 <- a[2*k+5] - (*p)
sw   $t0, 0($t1)      # a[4*k] <- a[2*k+5] - (*p)
```
