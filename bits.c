/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x&~y)&~(x&y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (~x+1)&(x>>31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int src_shift=src<<3;
  int dst_shift=dst<<3;
  int src_val=(x>>src_shift)&0xFF;
  int mask=~(0xFF<<dst_shift);
  return (x&mask)|(src_val<<dst_shift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask_low = 0x0F | (0x0F << 8);
  mask_low = mask_low | (mask_low << 16);   
  int mask_high = 0xF0 | (0xF0 << 8);
  mask_high = mask_high | (mask_high << 16); 
  int low_nibble = x & mask_low;
  int high_nibble = x & mask_high;

  return (low_nibble << 4) | ((high_nibble >> 4) & mask_low);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int lowest_zero=~x&(x+1);
  int x_no_lowest_zero=x|lowest_zero;
  return ~x_no_lowest_zero&(x_no_lowest_zero+1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {  
  int mask16 = 0xFF | (0xFF << 8);   
  x ^= (x >> 16) & mask16;
  x ^= (x >> 8) & 0xFF;
  x ^= (x >> 4) & 0x0F;
  x ^= (x >> 2) & 0x03;
  x ^= (x >> 1) & 0x01;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  n = n & 31;                   
  int shift = 32 + ~n + 1;        
  int s = shift & 31;            
  int mask = ~((~0) << s);       
  return ((x >> n) & mask) | (x << s);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int d=1<<n;
  int half=d>>1;
  int q=x>>n;
  int r=x&(d+~0);
  int r_is_half=!(r+~half+1);
  int r_bigger_than_half=(~((r+~half)>>31))&1;
  int q_is_odd=q&1;
  return (q+(r_bigger_than_half|r_is_half&q_is_odd))<<n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! s~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int mid=(x&y)+((x^y)>>1);
  int odd=(x^y)&1;
  int x_sign=x>>31;
  int y_sign=y>>31;
  int x_and_y_sign_different=x_sign^y_sign;
  int x_bigger_when_sign_different=!x_sign;
  int x_bigger_when_sign_same=(~((x+~y+1)>>31))&1;
  return mid+(odd&(x_and_y_sign_different&x_bigger_when_sign_different|(~x_and_y_sign_different)&x_bigger_when_sign_same));
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int diff_xa = sx ^ sa;
  int diff_xb = sx ^ sb;

  int not_x = ~x;
  int x_minus_a = x + ~a + 1;   
  int a_minus_x = a + not_x + 1; 
  int x_minus_b = x + ~b + 1;   
  int b_minus_x = b + not_x + 1; 

  int x_minus_a_neg = x_minus_a >> 31;
  int a_minus_x_neg = a_minus_x >> 31;
  int x_minus_b_neg = x_minus_b >> 31;
  int b_minus_x_neg = b_minus_x >> 31;

  int ge_xa = (diff_xa & !sx) | (!diff_xa & !x_minus_a_neg); 
  int ge_ax = (diff_xa & !sa) | (!diff_xa & !a_minus_x_neg); 
  int ge_xb = (diff_xb & !sx) | (!diff_xb & !x_minus_b_neg); 
  int ge_bx = (diff_xb & !sb) | (!diff_xb & !b_minus_x_neg); 

  return (ge_xa & ge_bx) | (ge_xb & ge_ax);
}


// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x4 = x << 2;                         
  int high = x >> 29;                      
  int high_is_0 = !high;
  int high_is_m1 = !~high;
  int x4_overflow = !(high_is_0 | high_is_m1); 
  int y = x4 + x;                        
  int add_overflow = ((x4 ^ y) & (x ^ y)) >> 31; 
  int overflow = x4_overflow | (add_overflow & 1); 
  int sign = x >> 31;                      
  int max = ~(1 << 31);                    
  int min = 1 << 31;                        
  int sat = (sign & min) | (~sign & max);   
  int mask = ~overflow + 1;               
  return (y & ~mask) | (sat & mask);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int c1 = ((x & y) | ((x | y) & ~s1)) >> 31 & 1;
  int s2 = s1 + z;
  int c2 = ((s1 & z) | ((s1 | z) & ~s2)) >> 31 & 1;
  int sum_sign = (x >> 31) + (y >> 31) + (z >> 31);
  int H = c1 + c2 + sum_sign;
  int s2_sign = s2 >> 31;
  int h_ge_1   = !(H >> 31) & !!H;          
  int h_is_0   = !H;                      
  int h_is_m1  = !(H ^ ~0);                
  int h_is_m2  = !(H ^ ~1);                
  int h_is_m3  = !(H ^ ~2);                
  int h_le_m2  = h_is_m2 | h_is_m3;         
  int s2_neg    = s2_sign & 1;            
  int s2_nonneg = !s2_neg;                  
  int cond1 = h_ge_1 | (h_is_0 & s2_neg);
  int cond_m1 = h_le_m2 | (h_is_m1 & s2_nonneg);
  return cond1 + ~cond_m1 + 1;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
    if (exp == 0xFF) return uf;             
    if (exp == 0 && frac == 0) return sign;  
    if (exp == 0) {
        unsigned N = frac * 3;            
        if (N >= 0x1000000) {
            unsigned new_frac = (N >> 1) & 0x7FFFFF;
            if ((N & 1) && (new_frac & 1)) {  
                new_frac++;
                if (new_frac == 0x800000)
                    return sign | 0x1000000;  
            }
            return sign | 0x800000 | new_frac; 
        } else {
            unsigned M_non = N >> 1;          
            if ((N & 1) && (M_non & 1))     
                M_non++;
            return sign | M_non;            
        }
    } else {
        unsigned N = ((0x800000) | frac) * 3;  
        unsigned new_exp, new_frac;
        
        if (N >= 0x2000000) {
            new_frac = (N >> 2) & 0x7FFFFF;
            new_exp = exp + 1;
            unsigned round_bits = N & 3;      
            if (round_bits > 2 || (round_bits == 2 && (new_frac & 1))) {
                new_frac++;
                if (new_frac == 0x800000) {
                    new_frac = 0;
                    new_exp++;
                }
            }
        } else {
            new_frac = (N >> 1) & 0x7FFFFF;
            new_exp = exp;
            if (N & 1) {                      
                if (new_frac & 1) {
                    new_frac++;
                    if (new_frac == 0x800000) {
                        new_frac = 0;
                        new_exp++;
                    }
                }
            }
        }
        
        if (new_exp >= 0xFF)                 
            return sign | 0x7F800000;
        return sign | (new_exp << 23) | new_frac;
    }
    }


// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    if (exp == 0xFF) {
        return uf;
    }

    if (exp == 0) {
        return sign;   
    }

    int E = exp - 127;  
    if (E >= 23) {
        return uf;
    }
    if (E < -1) {
        return sign;
    }

    if (E == -1) {
        if (frac == 0) {
            return sign;
        } else {
            return sign | 0x3F800000;
        }
    }
    unsigned M = (1 << 23) | frac;   
    int shift = 23 - E;             
    unsigned I = M >> shift;        
    unsigned frac_part = M & ((1 << shift) - 1); 
    unsigned half = 1 << (shift - 1); 

    if (frac_part > half || (frac_part == half && (I & 1))) {
        I++;
    }
    if (I == 0) {
        return sign;
    }
    int h = 31;
    while ((I & (1 << h)) == 0) {
        h--;
    }
    unsigned exp_new = h + 127;
    unsigned frac_new = (I << (23 - h)) & 0x7FFFFF;
    return sign | (exp_new << 23) | frac_new;
}




// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
 unsigned sign = 0;
 unsigned frac = 0;
  if (x == 0) return 0;
  unsigned ux;
  if (x < 0) {
    sign = 1 << 31;
    ux = -x;
  } else {
    ux = x;
  }
  int h = 31;
  while ((ux & (1 << h)) == 0) {
    h--;
  }
  unsigned exp = h + 127;
  if (h > 23) {
    unsigned lost = ux & ((1 << (h - 23)) - 1);
    frac = (ux >> (h - 23)) & ((1 << 23) - 1);
    unsigned half = 1 << (h - 23 - 1);
    if (lost > half) frac++;
    if (lost == half) {
      if ((frac & 1) != 0) frac++;
    }
    if (frac == (1 << 23)) {
      exp++;
      frac = 0;
    }
  } else {
    frac = (ux << (23 - h)) & 0x7FFFFF;
  }
  return sign | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);
  int m4 = 0x0F | (0x0F << 8);
  m4 = m4 | (m4 << 16);
  int m8 = 0xFF | (0xFF << 16);
  int m16 = 0xFF | (0xFF << 8);
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x & m8) + ((x >> 8) & m8);
  x = (x & m16) + ((x >> 16) & m16);
  return x;
}
 
// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
  int m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);
  int m4 = 0x0F | (0x0F << 8);
  m4 = m4 | (m4 << 16);
  int m8 = 0xFF | (0xFF << 16);
  int m16 = 0xFF | (0xFF << 8);

  x = ((x & m1) << 1) | ((x >> 1) & m1);
  x = ((x & m2) << 2) | ((x >> 2) & m2);
  x = ((x & m4) << 4) | ((x >> 4) & m4);
  x = ((x & m8) << 8) | ((x >> 8) & m8);
  x = ((x & m16) << 16) | ((x >> 16) & m16);
  return x;
}
