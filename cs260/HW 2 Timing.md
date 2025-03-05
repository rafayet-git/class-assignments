### Alias: corbato

# Homework 2 Timing

1. Code segment instruction count:

| R-type arithmetic | Imm. arithmetic | Jumps | Mem    | Branches |
| ----------------- | --------------- | ----- | ------ | -------- |
| $1+4N$            | $1+2N$          | $2N$  | $4N+3$ | $2N+1$   |

Cycles count:

| R-type arithmetic | Imm. arithmetic | Jumps | Mem      | Branches |
| ----------------- | --------------- | ----- | -------- | -------- |
| $1+4N$            | $2+4N$          | $6N$  | $16N+12$ | $10N+5$  |

Total Cycles: $40N +20$ 

Find N for 0.1ms execution time:

$$
0.1\text{ms} = 10^{-4}\text{ s} = \frac{40N+20}{4*10^9 \text{ Hz}} \hspace{10cm} \\[5px] 
10^{-4} * 4 * 10^9 = 400,000 \text{ Cycles} = 40N+20 \hspace{10cm} \\[5px] 
\frac{400,000 - 20}{40} = N = 9999.5 \hspace{10cm} \\[5px] 
\textbf{N = 10,000} \hspace{10cm}
$$

2. Max value for $N = 32,767$ (16 bit signed immediate)
   
   $$
   \frac{40(32,767)+20}{4*10^9 \text{Hz}} = 3.2767*10^{-4} \text{ s} = \textbf{0.328 ms} \hspace{10cm}
   $$
