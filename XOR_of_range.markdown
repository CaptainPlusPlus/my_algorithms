# Find XOR of numbers from the range [L, R] where L <= R    

Given two integers L and R, the task is to find the XOR of elements of the range [L, R].  
E.g.  
```
L = 5,  
R = 9,  
Expected output = 5 ⊕ 6 ⊕ 7 ⊕ 8 ⊕ 9
```
You are encouraged to take a moment and reflect on this on your own before reading ahead.  
(I'm not your mom though, you can keep going)  
## Efficiency and solutions
### Naive solution - Time complexity O(N)

As the name suggests, this is essentialy coding the problem.  
1. Create a key to hold traversing result.  
2. XOR every number within range into the key (XOR is commutative).  

##### Implementation in C
```
int xor_range(int l, int r)
{
  int key = 0;
  while (l <= r)
  {
    key ^= l;
    ++l;
  }
  return key;
}
```
### What they want you to say at an interview - Time complexity arguebly O(1)
To nobody's surprise, being the only element in the problem,  
The more efficient solution has to do with the properties of xor which we will now strive to understand:  

1. Commutative : A ⊕ B = B ⊕ A  
    This is clear from the definition of XOR: it doesn’t matter which way round you order the two inputs.  
2. Associative : A ⊕ ( B ⊕ C ) = ( A ⊕ B ) ⊕ C  
    XOR operations can be chained together and the order doesn’t matter.  
3. Identity element : A ⊕ 0 = A  
    Any value XOR’d with zero is left unchanged.  
4. Self-inverse : A ⊕ A = 0  
    This means that any value XOR’d with itself gives zero.  
