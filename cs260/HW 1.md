### Alias: corbato

# Homework 1

1. CPI \* Instructions = Cycles
   
   $(3 * 1000) + (6 * 200) + (7 * 400) = 7000 $ Cycles
   
   Cycles / clock (hz)  = time (microseconds)
   
   $$
   \frac{7000}{4*10^9\text{ Hz}} = 1.75*10^{-6}\text{ s} = \textbf{1.75} \mu \text{s} \hspace{10cm}
   $$

2. CPI \* Mix % = avg CPI
   
   $(3 * .55) + (6 * .30) + (7 * .15) = 4.5$ CPI
   
   Clock (hz) \* IPS / 4.5 CPI = $4*10^9 * \frac{\text{1}}{4.5} \approx 8.89*10^8$ IPS
   
   $8.89*10^8 $ IPS = $\textbf{889 MIPS}$ 

3. | Type       | CPI | Mix |
   | ---------- | --- | --- |
   | Arithmetic | 3   | 65% |
   | Memory     | 6   | 30% |
   | Control    | 7   | 10% |
   
   Calculate MIPS
   
   $(3 * .65) + (6 * .30) + (7 * .10) = 4.45$ CPI
   
   $4 * 10^9 * \frac{1}{4.45} \approx 8.99 * 10^8 \text{ IPS} = 899 \text{ MIPS}$
   
   Calculate difference: $899 / 889 = 1.0112 = 1.12$%
   
   **C2 is 1.12% faster than C1.**

4. 1000 MIPS = $10^9$ IPS
   
   IPS / Clock (hz) = CPI = $10^9 / (4*10^9) = 4.0$ CPI.
   
   CPI = type CPI \* Mix %. Control is the same mix at 15%, so we need to calculate the rest of the 85% with most of it being in arithmetic. 
   
   $4.0 = (3* (0.85-x)) + (6x) + (7*.15)$
   
   $4.0 =3x + 3.6$
   
   $x \approx 0.13$ 
   
   New instruction set:
   
   | Type       | CPI | Mix |
   | ---------- | --- | --- |
   | Arithmetic | 3   | 72% |
   | Memory     | 6   | 13% |
   | Control    | 7   | 15% |

5. Power = clock$^2$ (hz)
   
   $$
   \frac{70\text{W}}{140\text{W}} = \left( \frac{\text{Clock}}{4*10^9} \right)  \hspace{10cm}
\\[5px] 0.5 = \frac{\text{Clock}}{4*10^9} \hspace{10cm}
\\[5px] \frac{0.5}{4*10^9} = 2*10^9 = 2 \text{GHz} \hspace{10cm}
   $$
   
    Calculate new mips using previously calculated 4.5CPI
   
   $$
   2*10^9 \text{ Hz} /4.5 \text{ CPI} = 4.44*10^8 \text{ IPS} = \textbf{444 MIPS}\hspace{10cm}
   $$
