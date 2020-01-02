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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x&y    : 1 if (1,1)
  // ~(x&y) : 1 if (1,0),(0,1) or (0,0)
  // (~x) & (~y) : 1 if both 0
  // ~((~x) & (~y)) : 1 if (1,0),(0,1),(1,1)
  // ~((~x) & (~y)) & (~(x&y)) : 1 if (1,0) or (0,1) so XOR
  return (~(x & y)) & (~(~x & ~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // Tmin: 1000...000
  return (1 << 31);
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  // Tmax = 0111...111, Tmin = 1000...000
  int tmax = ~(1 << 31);
  // x^tmax, gives us the bit difference between x and tmax, diff = 0, when x = Tmax
  int diff = (~(x & tmax)) & (~(~x & ~tmax));
  // !0 = 1; !(anything else) = 0;
  int result = !diff;
  return result;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // A = 10 = 1010, thus 0xAAAAAAAA = 0b10101010...1010
  int oddOnes = 0xAAAAAAAA;
  // if x have 1's for all odd bits, then andResult = oddOnes
  //                           else, andResult have 0's for some odd bits.
  int andResult = x & oddOnes;
  // Same as last question, we want to return 1 if andResult is the same as oddOnes
  return !(~(oddOnes & andResult)) & (~(~oddOnes & ~andResult));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // This is the classic: -x = ~x + 1. Tmin = -Tmin
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  //0x30 = 0011,0000      0x39 = 0011,1001
  // 0x30 <= x <= 0x39
  // compare x to 0x30
  int x_30 = x + (~0x30 + 1);       // x - 0x30
  int sign_x_30 = (x_30 >> 31) & 1; // sign(x-0x30)
  int result1 = !sign_x_30;         // result1 = 1 if sign_x_30 = 0 <=> x >= 0x30

  // compare x to 0x39
  int x_39 = 0x39 + (~x + 1);       // 0x39-x
  int sign_39_x = (x_39 >> 31) & 1; // sign(0x39-x)
  int result2 = !sign_39_x;         // result2 = 1 if sign_39_x = 0 <=> 0x39 >= x
  // returns 1 when they are both 1 <=> 0x30<=x<=0x39
  return result1 & result2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // if x = 0 => false, return z
  // if x is anything else => true, return y
  // x | -x = 111..111 for everything else, = 000...000 for x = 0
  // mappedX : map 0 to 0, and everything else to -1.
  int mappedX = ((x | (~x + 1)) >> 31);
  // yResult = y if mappedX = -1, = 0 if mappedX = 0
  int yResult = y & mappedX;
  // zResult = z if mappedX = 0, = 0 if mappedX = -1
  int zResult = z & (~mappedX);
  // yResult + zResult = yResult if mappedX = -1 <=> x != 0
  // yResult + zResult = zResult if mappedX = 0  <=> x == 0
  return yResult + zResult;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
/**
 * There are 6 different cases:
 * isLessOrEqual(x, y):
 * 0<x<y => 1, same sign
 * 0<y<x => 0, same sign
 * x<y<0 => 1, same sign
 * y<x<0 => 0, same sign
 * x<0<y => 1, diff sign
 * y<0<x => 0, diff sign
 * so this function returns 1 if x,y same sign and x<y, or x<0<y
 */
int isLessOrEqual(int x, int y) {
  // shift x(y) right by 31 , then & 1, we have the sign bit of x(y).
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  // y - x = y + (-x), where -x = ~x + 1
  int yMinusX = y + (~x + 1);
  // sign of y-x
  int signYX = (yMinusX >> 31) & 1;
  // left  side: 1 if x,y same sign and y>x, 0 otherwise
  // right side: 1 if x < 0 < y
  int result = ((!(signX ^ signY)) & !signYX) | (signX & !signY);
  return result;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // !x = 1 if x = 0, !x = 0 if x is anything else.
  // we did this in the conditional question.
  // example for 4 bits.
  // 1. x = 0011 = 3, ~x+1 = 1100+1 = 1101 = -3. x | -x = 1111. 1111 >>3 = 1111 = -1
  // 2. x = 0000 = 0, ~x+1 = 1111+1 = 10000(truncate additional bit) = 0000, x|-x=0000, 0000>>3 = 0.
  // 3. whole expression + 1 : 0 if x!=0, 1 if x = 0
  return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // if uf is 0 or         -0
  if (uf == 0 || uf == (1 << 31)) return uf;
  // Special value: inf, -inf, NaN if exp = 1111,1111
  // 0xFF: 1111,1111.  float: sign 1-bit | exp 8-bits            | frac 23-bits
  //                                   31|20,29,28,27,26,25,24,23|22,....,1,0
  // So shift uf by 23 bits to the right & 0xFF = 0xFF means, exp = 1111,1111, 
  // uf is special value, return uf.
  if (((uf >> 23) & (0xFF)) == 0xFF) return uf;
  // Denormalized: if exp = 0000,0000
  if (((uf >> 23) & 0xff) == 0x00)
  { 
    // 0x007FFFFF = 0,00000000,1111..111
    // uf & 0x007FFFFF gives us all the frac fields. *2 means we need to shift left by 1
    // we need to put the sign bit back: shift 1 left by 31 & uf, gives us the sign bit of uf.
    // this would gives us the sign bit of uf,00000001,frac as before,0
    return ((uf & 0x007FFFFF) << 1) | ((1 << 31) & uf);
  }
  // normalized: when exp != 0000, exp != 1111
  // just +1 to its exp field, we are *2
  return uf + (1 << 23);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  // return 0 if x is 0
  // if x = 100...00 = Tmin, x = -2^31,
  // Represent Tmin in floating point, x = (-1)^sign * 1.frac * 2^E, s = 1, frac = 0, E = 31
  // s = 1 (sign bit), E = Exp - 127 = 31 => Exp = 158, frac = 0.
  // x in floating = 1 | 10011110 | 0000...0000
  // in 0x (hex) : x = 0xCF000000
  // else if (x == 0x80000000) return 0xCF000000; 
  unsigned abs_x = x;
  unsigned sign = x & 0x80000000;
  int flag = 0;
  int n = 30;

  if (x == 0)
    return x;
  else if (x == 0x80000000)
    return 0xcf000000;

  if (sign)
    abs_x = -x;

  while (!(abs_x & (1 << n)))
    n--;
  abs_x <<= 32 - n;

  if ((abs_x & 0x01ff) > 0x0100)
    flag = 1;
  else if ((abs_x & 0x03ff) == 0x0300)
    flag = 1;
  else
    flag = 0;

  return sign + ((n << 23) + 0x3F800000) + (abs_x >> 9) + flag;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/**
 * Normalized values: when exp != 111,...,111 and exp != 000,...,000
 * value = (-1)^s * M * 2^E
 * E = Exp - Bias, Bias = 2^(k-1) - 1, k = number of exp bits, in our case, single precision, k = 2^7 - 1 = 127
 * M = 1 + 0.frac
 * Sign 1bit| exp  8bits  | frac  23bits
 * 31       | 30,29,..,23 | 22, 21,..., 1, 0
 * ---------------------------------------------
 * Denormalized values: when exp = 000,...,000
 * value = (-1)^s * M * 2^E
 * E = 1 - Bias
 * M = 0.frac, note that we have +0 and -0, since sign bit still have two values
 * -----------------------------------------------
 * Special Values: exp = 111,...,111
 * when exp = 111...1, frac = 000...0, it is +infinity and -infinity
 * when exp = 111...1, frac != 000...0, it is NaN(not a number), such as sqrt(-1), inf - inf, inf * 0 
 * -----------------------------------------------
 * When casting double/float -> int
 * 1. Truncates fractional part,  2. like rounding towards zero,  3. not defined when out of range or NaN : sets to TMin.
 */ 
int float_f2i(unsigned uf) {
  int sign = (uf >> 31) & 0x1;    // get the sign bit
  int exp  = (uf >> 23) & 0xFF;   // get the  exp bit
  int frac = uf & 0x7FFFFF;       // get the frac bit
  int E = exp - 127;              // E = Exp - bias, bias = 127
  
  // if exp == 0 : denorm, round it to 0 when casting to integer
  // if exp < 0  : round it to 0
  if (E < 0 || exp == 0) return 0;
  // if E >= 31, it overflows when casting to integer
  // when exp = 0xFF = 11111111, it is special value
  // return TMin
  if (E >= 31 || exp == 0xFF) return 0x80000000;
  // Normalized values
  // float: v = sign * 1.frac * 2^E.
  // example: frac is only 4 bits, v = 1.0011 * 2^5, then v = 10011 * 2 when we shift the dot.
  // in our case, the break point is 24 bits. 23 bits for the frac, 1 for the normalized value
  // Add the implicit one
  frac = frac | 0x800000;
  // if E < 23, we need to shift frac left by 23 bits
  if (E < 23) frac = frac >> (23 - E);
  else        frac = frac << (E - 23);
 
  // negate it if signed
  if (sign) frac = ~frac + 1;
  
  return frac;
}
