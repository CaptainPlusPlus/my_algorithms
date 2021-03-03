# Find AND of numbers from the range [L, R] where L <= R    
<details>
  <summary>tl;dr - My own algorithm (Click to Expand)</summary>
</details>  

Given two integers L and R, the task is to find the AND of elements of the range [L, R].  
E.g.  
```
L = 5,  
R = 9,  
Expected output = 5 & 6 & 7 & 8 & 9
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
```
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

##### The new acceptable algorithm now that we are smarter:
1. Find highest MSB in L and R.
2. If it is not the same bit, return 0.
3. Return the largest sequence of identical bits between L and R.
  
Most online solutions look a little worse than this (the horror):
```
int and_range(int l, int r)
{
  int key = 0;
  
