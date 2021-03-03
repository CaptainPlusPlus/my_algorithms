/***********************************************************************************/
/***************** AND operation between integers in input range *******************/
/*********** No conditions, no read aheads, no loops. pure arithmetics, O(1) *******/
/**************** For further analysis read AND_of_range.markdown ******************/
/***********************************************************************************/

/* Could be written as a one liner, broken down for clarity */
int and_range(int l, int r)
{
  int r_msb = msb(r);       /* find msb in r */
  int xor_msb = msb(r ^ l); /* find msb in xor */
  int sequence_mask = ((r_msb) - (xor_msb)) | (xor_msb); /* Mask of bits between xor msb and r msb */
  
  return (sequence_mask & !!(xor_msb ^ r_msb)) & r; /*Nullify mask if MSB is different in l and r*/
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
