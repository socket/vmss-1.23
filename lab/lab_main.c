/*
 *  lab.c
 *  lab
 *
 *  Created by Alexey Streltsow on 3/4/10.
 *  Copyright 2010 Zila Networks LLC. All rights reserved.
 *
 */

#include "vmss_common.h"

// 23.	из четверичной в шестнадцатеричную

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