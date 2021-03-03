# Find AND of numbers from the range [L, R] where L <= R    
<details>
  <summary>tl;dr - final algorithm (Click to Expand)</summary>  
  
  
```c
/*
* O(1) with no conditionals/loops. pure arithmetics.
* Could be written as one liner, broken down for clarity
*/
int and_range(int l, int r)
{
  int r_msb = msb(r);       /* find msb in r */
  int xor_msb = msb(r ^ l); /* find msb in xor */
  int sequence_mask = ((r_msb) - (xor_msb)) | (xor_msb); /* Mask of bits between xor msb and r msb */
  
  return (sequence_mask & (xor_msb ^ r_msb)) & r; /*Nullify mask if MSB is different in l and r*/
}

int msb(unsigned int v)
{
  static const int pos[32] = {0, 1, 28, 2, 29, 14, 24, 3,
    30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19,
    16, 7, 26, 12, 18, 6, 11, 5, 10, 9};
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v = (v >> 1) + 1;
  return pos[(v * 0x077CB531UL) >> 27];
}
```
</details>  

Given two integers L and R, the task is to find the AND of elements of the range [L, R].  
E.g.  
```
L = 5,  
R = 9,  
Expected output = 5 & 6 & 7 & 8 & 9 = 0
```


You are encouraged to take a moment and reflect on this on your own before reading ahead.  
hint: Aim for O(1).  
(I'm not your mom though, you can keep going)  
## Efficiency and solutions
### Naive solution - Time complexity O(N)
As the name suggests, this is essentialy coding the problem.  
1. Create a key to hold traversing result.  
2. AND every number within range into the key.  

##### Implementation in C
```c
int and_range(int l, int r)
{
  int key = l;
  while (l <= r)
  {
    key &= l;
    ++l;
  }
  return key;
}
```
### What they want you to say at an interview - Time complexity arguebly O(1)
To nobody's surprise, being the only element in the problem,  
The more efficient solution has to do with the properties of and.  
Well let's look at some inputs and outputs and try observing a pattern.
```
Input: l = 9, r = 15  
In binary - l = 01001, r = 01111 
Output: 8
In binary - 01000

Input: l = 13, r = 15  
In binary - l = 01101, r = 01111 
Output: 12
In binary - 01100

Input: l = 7, r = 15  
In binary - l = 00111, r = 01111 
Output: 0
In binary - 00000
```
Onto anything?  
If you look just at the binary representations, you'll notice  
* The result is the sequence of the highest matching bits.  
* When the sequence is over, everything to the right is 0'ed out.

I'm still not your mom but I still suggest you try and understand why.
##### What is behind this sorcery?!
This has to do with the process occuring when enumerating binary numbers.
To go from 01001 to 11100, we have to go through 01111 and 10000 along the way.  
Since & is a restrictive operation, once one of the binary positions in such a set of &'s is set to 0,  
This position will make the result of every bit &ing with it a 0.  
Knowing that we forever lose set bits when we introduce a new position, we can understand this behavior.

##### The new acceptable middleground algorithm now that we are smarter:
1. Find highest MSB in L and R.
2. If it is not the same bit, return 0.
3. Return the largest sequence of identical bits between L and R.
  
Most online solutions look worse than this (the horrors):
```c
int and_range(int l, int r)
{
  int result_key = 0;
  int curr_set_bit = 1 << (sizeof(int) * 8 - 1); /* Create highest int bit in system */
  
  /* Traversing from MSB to LSB */
  while (curr_set_bit)
  {
    /* msb found in target */
    if (curr_set_bit & r)
    {
      if (r & l) result_key |= curr_set_bit; /* Sequence exists in initial integer */
      else return result_key;                /* End of sequence */
    }
    curr_set_bit =>> 1;
  }
  return result_key;
}  
```

##### So what do we have here?  
Yes, this achieves the notion of arguebly O(1).
Why arguebly?
* To find the highest set bit, as well as to determine sequence, we loop through the bits.     
most implementations find current set bit by traversing the entire bit array, whilst  
some don't even break the iteration when sequence is over.
* It could also be claimed that the size of integer in memory can not be predetermined, therefore the solution is O(sizeof(int)),  
Not to mention we can do much better.

### Achieving true O(1) and taking performance to the final form.
* **Finding differentiating bits IS THE DEFINITION OF XOR**.
* Finding MSB can be achieved with O(logn) for any bitarray with Brian Kerningham's algorithm,  
and O(1) with Mul De Brujin/Hammingbird method if sizeof integer is known (can also be dynamically constructed for any size).

##### The detailed pseudo code will now be:
1. Find MSB of R   (single operation).
2. XOR L and R     (single operation).
3. Find MSB in XOR (single operation).
4. return the bits in R/L that are between R MSB and XOR MSB (single operation).  

And there you have an algorithm that takes 4 operations, regardless of the input.  
It has no loops, no if statments, and 0 read ahead needed. just an arithmetic sequence of operations.

##### C implementation of O(1) without conditions or loops
```c
int and_range(int l, int r)
{
  int r_msb = msb(r);       /* find msb in r */
  int xor_msb = msb(r ^ l); /* find msb in xor */
  int sequence_mask = ((r_msb) - (xor_msb)) | (xor_msb); /* Mask of bits between xor msb and r msb */
  
  return (sequence_mask & (xor_msb ^ r_msb)) & r; /*Nullify mask if MSB is different in l and r*/
}

/* Mul De Brujin O(1) arithmetic find MSB */
/* This version is 32 bit, can be dynamically made for any sizeof(int) in O(1) */
/* Could also use Brian Kerningham's algorithm */
int msb(unsigned int v)
{
  static const int pos[32] = {0, 1, 28, 2, 29, 14, 24, 3,
    30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19,
    16, 7, 26, 12, 18, 6, 11, 5, 10, 9};
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v = (v >> 1) + 1;
  return pos[(v * 0x077CB531UL) >> 27];
}
```
