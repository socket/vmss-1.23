/*
 *  lab.c
 *  lab
 *
 *  Created by Alexey Streltsow on 3/4/10.
 *  Copyright 2010 Zila Networks LLC. All rights reserved.
 *
 */

#include "lab.h"

#include <string.h>
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

char* vmss_strend(char* str) {
  while (*str) {
    str++;
  }
  return str;
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

int vmss_convert2str(unsigned int value, int base, char *output) {
  char* pstr = output;
  do {
    int remainder = value % base;
    value /= base;
    *pstr++ = vmss_digit2char(remainder);
  }
  while (value > 0);
  
  *pstr = '\0';
  vmss_strrev(output);
  
  return 0;
}

int vmss_rank10(unsigned int val) {
  int rank = 0;
	while(val=val/10) rank++;
	return rank+1;
}

int vmss_fractal2str(unsigned int fractal, int base, char* output, char limit) {
  int srcrank = vmss_rank10(fractal);
  for (int i=0; i<limit, fractal > 0; ++i) {
    int pow10 = pow(10, srcrank);
    fractal *= base;
    int digit = fractal / pow10;
    fractal %= pow10;
    *output++ = vmss_digit2char(digit);
  }
  *output = '\0';
  return 0;
}

int vmss_str2number(char *src, int src_base, int dst_base, char* output, char limit) {
  char *left, *right;
  unsigned int src_value, src_fractal;
  int result = 0;
  left = right = src;
  while(*right && *right != '.') right++;
  *right++ = '\0';
  
  result |= vmss_convert2int(left, src_base, &src_value);
  result |= vmss_convert2int(right, src_base, &src_fractal);
  
  if ( result != 0 ) {
    return -1;
  }
  
  vmss_convert2str(src_value, dst_base, output);
  output = vmss_strend( output );
  *output++ = '.';
  vmss_fractal2str(src_fractal, dst_base, output, limit);
  
  return 0;
}

//43981
int main (int argc, const char * argv[]) {
	int error;
  //printf("%d\n", vmss_convert2int("1230", 4, &error));
  
	// insert code here...
  char src[256];
  char buffer[256];
  
  strcpy(src, "10.50390625");
  vmss_str2number(src, 10, 16, buffer, 8);
  
	printf("%s", buffer);
  
	return 0;
}