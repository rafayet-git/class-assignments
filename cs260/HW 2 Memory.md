### Alias: corbato

# Homework 2 Memory

1. Short integers: 16 bits, based on output's 2 bytes
   
   Regular integers: 32 bits, based on output's 4 bytes
   
   Long integers: 64 bits. based on output's 8 bytes

2. Pointers always use 64 bits of memory, which is the same as a long integer.
   
   ```cpp
   // MOD
   cout << "Pointers:" << sizeof(p) << "\n";
   ```

3. | Address        | Value | Name          |
   | -------------- | ----- | ------------- |
   | 0x7ffeb76c36e0 | 300   | foo.x[0] <- q |
   | ???            | 300+k | foo.x[k]      |
   | 0x7ffeb76c36f4 | 305   | foo.x[5] <- p |
   | 0x7ffeb76c386c | 399   | foo.x[99]     |
   | 0x7ffeb76c3870 | 440   | foo.var1      |
   | 0x7ffeb76c3874 | 800   | foo.y[0]      |
   | ???            | 800+k | foo.y[k]      |
   | 0x7ffeb76c3898 | 809   | foo.y[9]      |
   
   Based on the address of q, which points to foo, we can move to the next integer in the struct by jumping 4 bytes across. To find integer K we can just add 4*k into the foo address.

4. q returns a large number because it is based on variable `i = ((long) p + 17);`. However this variable appends p by 17 bytes , which is not divisible by 4 (size of integers), so it is not a valid location for a integer.

5. They are different, as C++ appends integers with account of the value type's size, but pointers are appended only on single byte counts.  For example, `q = p+16` adds the two integers to print out `321`, but `i = ((long) p) + 16;` adds the pointer which prints out `309`.

6. First blank: 101
   
   Second blank: 404
   
   I got the first blank by appending the amount of integers from foo.x[5] to foo.y[5], and the second blank by multiplying that number by 4, then adding it.

7. Third blank: (8*111) + 100
   
   I got this by multiplying the amount of integers in a foo_t by 8, which moves from bar[0] to bar[8]. Then i added 100 to skip the bar[8].x array, which gives us bar[8].var1.

8. It is going down in memory. This is because of the address of foo, which was allocated first, is `0x753de0`, but the address of var2 that was allocated later is `0x753db4`, which is less.
