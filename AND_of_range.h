/***********************************************************************************/
/***************** AND operation between integers in input range *******************/
/*********** No conditions, no read aheads, no loops. pure arithmetics, O(1) *******/
/**************** For further analysis read AND_of_range.md ************************/
/***********************************************************************************/

/* Could be written as a one liner, broken down for clarity */
int and_range(int l, int r)
{
  int r_msb = msb(r);       /* find msb in r */
  int xor_msb = msb(r ^ l); /* find msb in xor */
  int sequence_mask = ((r_msb) - (xor_msb)) | (xor_msb); /* Mask of bits between xor msb and r msb */
  
  return (sequence_mask & (xor_msb ^ r_msb)) & r; /*Nullify mask if MSB is different in l and r*/
}

/* 32 bit */
int msb(int x)
{
        x |= (x >> 1);
        x |= (x >> 2);
        x |= (x >> 4);
        x |= (x >> 8);
        x |= (x >> 16);
        return(x & ~(x >> 1));
}
