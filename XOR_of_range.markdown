# Find XOR of numbers from the range [L, R] where L <= R    

Given two integers L and R, the task is to find the XOR of elements of the range [L, R].  
E.g.  
```
L = 5,  
R = 9,  
Expected output = 5 ^ 6 ^ 7 ^ 8 ^ 9
```
You are encouraged to take a moment and reflect on this on your own before reading ahead.  
(I'm not your mom though, you can keep going)  
## Efficiency and solutions
### Naive solution - Time complexity O(N)

As the name suggests, this is essentialy coding the problem.  
1. Create a key to hold traversing result.  
2. XOR every number within range into the key.  
(XOR is commutative)

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
