/*
 *  lab.c
 *  lab
 *
 *  Created by Alexey Streltsow on 3/4/10.
 *  Copyright 2010 Zila Networks LLC. All rights reserved.
 *
 */

#include "lab.h"

#include <stdio.h>
#include <math.h>

typedef int BOOL;

#define TRUE 1
#define FALSE 0 

// 23.	из четверичной в шестнадцатеричную

void vmss_strrev(char *h) {
  char *t = h;
  while(t && *t) ++t;
  for(--t; h < t; ++h, --t) {
    *h = *h ^ *t,
    *t = *h ^ *t,
    *h = *h ^ *t;
  }
}

int vmss_char2digit(char ch) {
  if ( ch >= '0' && ch <= '9' ) {
    return ch - '0';
  }
  if ( ch >= 'a' && ch <= 'z' ) {
    return 10 + (ch - 'a');
  }
  if ( ch >= 'A' && ch <= 'Z' ) {
    return 10 + (ch - 'A');
  }
  return -1;
};

char vmss_digit2char(int digit) {
  if ( digit >= 0 && digit <= 9 ) {
    return '0' + digit;
  }
  else if ( digit <= ('Z'-'A') ) {
    return 'A' + (digit - 10);
  }
  return '?';
}

int vmss_convert2int(const char *src, int base, unsigned int *output) {
  int i = 0;
  const char *src_end = src;
  
  *output = '\0';
  while (*src_end) src_end++;
  
  while(*src++) {
    char digit = vmss_char2digit( *(--src_end) );
    if ( digit < 0 ) {
      return -1;
    }
    if ( digit >= base ) {
      return -2;
    }
    *output += digit*pow(base, i++);
  }
  return 0;
}

int vmss_convert2str(unsigned int value, int base, char* output) {
  char* pstr = output;
  while (value > 0) {
    int remainder = value % base;
    value /= base;
    *pstr++ = vmss_digit2char(remainder);
  }
  *pstr = '\0';;
  vmss_strrev(output);
  
  return 0;
}

/*void fract2hex(int input, char* buffer) {
 char b2[256];
 int2hex(input, b2);
 for (int i=0; i<strlen(b2); ++i ) {
 int src_rank = v_rank(input);
 input *= 0x10;
 int digit = input / pow10(src_rank);
 input %= pow10(src_rank);
 *buffer++ = alph[digit];
 }
 *buffer = 0;
 }
*/ 

int vmss_rank10(unsigned int val) {
  int rank = 0;
	while(val=val/10) rank++;
	return rank+1;
}

int vmss_fractal2str(unsigned int fractal, int base, char* output, char limit) {
  for (int i=0; i<limit, fractal > 0; ++i) {
    int srcrank = vmss_rank10(fractal);
    int pow10 = pow(10, srcrank);
    fractal *= base;
    int digit = fractal / pow10;
    fractal %= pow10;
    *output++ = vmss_digit2char(digit);
  }
  *output = '\0';
  return 0;
}

//43981
int main (int argc, const char * argv[]) {
	int error;
  //printf("%d\n", vmss_convert2int("1230", 4, &error));
  
	// insert code here...
  char buffer[32];
  vmss_convert2str(0xabcdef, 0x10, buffer);
  vmss_fractal2str(25, 8, buffer, 5);
  
	printf("%s", buffer);
  
	return 0;
}