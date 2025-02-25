## Alias: corbato

# Homework 2 Funcode

```
mask:  .word 0xFFFFF83F       # zero bits: 6-10, one bits: 1-5,11-31
start: la    $t0, mask        # t0 <- addr of mask
       lw    $t0, 0($t0)      # t0 <- mask
       la    $t3, shftr       # t3 <- addr of shftr sll instruction
       lw    $t3, 0($t3)      # t3 <- shftr: sll $t3, $t1, ..
       and   $t3, $t3, $t0    # t3 <- shftr clear bits 6-10  
       andi  $t2, $t2, 0x001f # t2 <- t2 clear bits 5-32
       sll   $t2, $t2, 6      # t2 <- t2 shifted to bits 6-10
       or    $t3, $t3, $t2    # t3 <- shftr: sll $t3, $t1, t2
       la    $t5, shftr       # t5 <- addr of shiftr sll instruction
       sw    $t3, 0($t5)      # shftr <- sll $t3, $t1, t2
shftr: sll   $t3, $t1, 0      # t3 <- t1<<t2
```

This function just shifts register t1 left by t2 bits.

Self-modifying code like this is a bad idea, because shftr can potentially be edited with malicious instructions (especially with the address being stored in t5). Also, it is much more resource intensive to do this than to just call the sll instruction itself.
