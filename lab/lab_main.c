/*
 *  lab.c
 *  lab
 *
 *  Created by Alexey Streltsow on 3/4/10.
 *  Copyright 2010 Zila Networks LLC. All rights reserved.
 *
 */

#include "vmss_common.h"

int main (int argc, const char * argv[]) {
	char rbuff[BUFF_SIZE], *prbuff;
  char convbuff[BUFF_SIZE];
  const char *src_file = 0, *dst_file = 0;
  FILE *hfile, *hfile_dst;
  
  printf("VMSS Lab1.%d\nConversion from base %d to %d\n\n", LAB_ID, SRC_BASE, DST_BASE);
  
  if ( argc < 2 ) {
    printf("usage: lab <input-file> [<output-file>]\n");
    return -1;
  }
  if ( argc < 3 ) {
    dst_file = argv[2];
  }

  src_file = argv[1];
  hfile = fopen( src_file, "rt" );
  if ( ! hfile ) {
    printf("error: cannot open '%s' for reading\n", src_file);
    return -1;
  }
  if ( dst_file ) {
    hfile_dst = fopen( dst_file, "wt" );
  }
  
  prbuff = rbuff;
  while (prbuff = fgets(rbuff, sizeof(rbuff), hfile)) {
    vmss_strchop(prbuff);
    if ( '\0' != *prbuff ) {
      vmss_str2number(prbuff, SRC_BASE, DST_BASE, convbuff, PRECISION);
      fprintf(hfile_dst, "%s\n", convbuff);
    }
  }
  
  fclose(hfile);
  if ( hfile_dst != 0 && hfile_dst != stdin) {
    fclose(hfile_dst);
  }
  
  printf("\ndone.\n");
  return 0;
}