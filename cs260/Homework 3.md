### Alias: corbato

# Homework 3

Code: `a[4*k] = a[2*k+5] - (*p);`

```
# Alloc: a->$s0, k->$s1, p->$s2
add  $t0, $s1, $s1    # t0 <- 2*k
addi $t1, $t0, 5      # t1 <- 2*k+5
add  $t1, $t1, $t1    # t1 <- 2*(2*k+5)
add  $t1, $t1, $t1    # t1 <- 4*(2*k+5)
add  $t1, $t1, $s0    # t1 <- addr of a[2*k+5]

lw   $t2, 0($t1)      # t2 <- a[2*k+5]
lw   $t3, 0($s2)      # t3 <- *p
sub  $t1, $t2, $t3    # t1 <- a[2*k+5] - (*p)

add  $t0, $t0, $t0    # t0 <- 4*k
add  $t0, $t0, $t0    # t0 <- 2*(4*k)
add  $t0, $t0, $t0    # t0 <- 4*(4*k)
add  $t0, $t0, $s0    # t0 <- addr of a[4*k]
sw   $t1, 0($t0)      # a[4*k] <- a[2*k+5] - (*p)
```


