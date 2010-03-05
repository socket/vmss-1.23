/*
 *  vmss_convert.c
 *  lab
 *
 *  Created by Alexey Streltsow on 3/5/10.
 *  Copyright 2010 Zila Networks LLC. All rights reserved.
 *
 */

#include "vmss_common.h"

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
  for (int i=0; i<limit && fractal > 0; ++i) {
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
  
  if ( *src == '-' ) {
    *output++ = *src++;
  }
  
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
