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
char vmss_char2digit(char ch) {
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

int vmss_convert2int(const char *src, int base, int *error) {
  int result = 0;
  int i = 0;
  const char *src_end = src;
  
  *error = 0;
  while (*src_end) src_end++;
  
  while(*src++) {
    char digit = vmss_char2digit( *(--src_end) );
    if ( digit < 0 ) {
      *error = 1;
      return 0;
    }
    if ( digit >= base ) {
      *error = 2;
      return 0;
    }
    result += digit*pow(base, i++);
  }
  return result;
}


int main (int argc, const char * argv[]) {
	int error;
  printf("%d\n", vmss_convert2int("FFFF", 0x10, &error));
  
	// insert code here...
	printf("Hello, World!\n");
	return 0;
}