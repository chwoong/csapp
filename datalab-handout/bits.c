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
/*Makefile 에서 m32를 m64로 바꾸자!!!!!!!!!!*/
int bitXor(int x, int y) {
	return (~(x & y)) & (~(~x & ~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return (1<<31);
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
	return (!(~(x^(x+1)))) & (!((!(x+1))&1));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	//make 0xAAAAAAAA by 0xAA
	int mask = (0xAA << 8) + 0xAA;
	mask = (mask <<16)+ mask;
	return !((x&mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return (~x)+1;
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
	//a이상 b이하인지 확인
	int neg = 1<<31;
	int less = ~(neg | 0x39); // 여기다가 x를 더했을 때 음수가 나오면 x는 b초과
	int great = ~(0x30); //여기다가 x를 더하고 거기다가 1을 더 더했을 때도 음수면 a미만
	int v=0;
	//즉 less와 great가 둘 다 양수이어야 함
	less = neg & (less+x);
	great = neg & (great + x +1);
	v= less | great;
	return !(v>>31);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int mask = (!x +~(0x00));
	return ( (mask&y) | ((~mask)&z) );
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int y_x=y+(~x+1);
	int sx=(x>>31)&1;
	int sy=(y>>31)&1;
	int sy_x=(y_x>>31)&1;
	/*
	1. x가 음수이고 y가 양수 일 경우
	2. 둘이 같은 부호이고 y-x가 양수인 경우
	*/
	return (sx & !sy) | ( !(sx^sy) & !sy_x);
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
	//x=0: 음수
	//x!=0: 양수 알고리즘
	int _x = (~x+1);
	int mask = (~x) & (~_x);
	return (mask>>31)&1;
	//return ((x | (~x + 1)) >> 31) + 1;
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
	//2의 보수로 표현되었다는 것을 알려줄 수 있는 필요한 최소 자릿수의 개수를 구하는 문제이다.
	//x = x<0 ? -x-1 : x;
	int s0,s1,s2,s4,s8,s16;
	x=(x>>31)^x;
	s16=(!!(x>>16))<<4;
	x=x>>s16;
	s8=(!!(x>>8))<<3;
	x=x>>s8;
	s4=(!!(x>>4))<<2;
	x=x>>s4;
	s2=(!!(x>>2))<<1;
	x=x>>s2;
	s1=(!!(x>>1));
	x=x>>s1;
	s0=x;
	return 1+s0+s1+s2+s4+s8+s16;
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
	int sign = uf & 0x80000000;
	//+0 or -0
	if(uf==0 || uf==0x80000000) return uf;
	//nan
	if(((uf>>23)&0xff) == 0xff) return uf;
	//smallest positive
	if(((uf>>23)&0xff) == 0){
		//부호는 그대로, frac은 2배로
		return ((uf & (1<<31)) | (uf<<1));
	}
	//2배해서 infinity되는 경우
	if( ((uf>>23)& 0xff) ==0xfe ) return 0x7f800000+sign;
	return uf+(1<<23);
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
	int sign=0;
	int frac;
	int e=127+31;
	if(x==0) return 0;
	if(x == (1<<31)) return (1<<31) | ((127+31)<<23);
	if(x<0){
		sign =1<<31;
		x=~x+1;
	}
	while(!(x&(1<<31))){
		x=x<<1;
		e--;
	}
	//맨앞에 1은 뗌(by 0x7fffffff) : 1이상의 normalized
	frac = (x & 0x7fffffff) >>8;
	// 현재 32bit 중: 1/8/frac
	//round to even
	//x의 가장 오른쪽 8비트의 정보가 손실됨(그 정보를 abcdefgh라 하자)
	//일단 a가 1일때 근사한다.
	//frac이 홀수이면 +1로 근사
	//frac이 짝수이면 bcdefgh>0이면 +1로 근사
	if (x&0x80 && ((x&0x7F) > 0 || frac&1))
        frac = frac + 1;
	return sign+(e<<23)+frac;
	
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
int float_f2i(unsigned uf) {
	
	int sign = (uf>>31) & 1;
	int exp = (uf >>23) & 0xff;
	int frac = uf & 0x7fffff;
	int E = exp-0x7f;
	int nan=0x80000000u;
	
	//infinity
	if(exp ==0xff) return nan;
	//overflow 2^31
	if(E>=31) return nan;
	//less than 1
	if(E<0) return 0;
	
	//normalized
	if(E>22) frac=frac<<(E-23);
	else frac=frac>>(23-E);
	//normalized이므로 2^E 추가
	frac+=(1<<E);
	if(sign) frac=-frac;
	return frac;
}
