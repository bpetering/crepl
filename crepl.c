#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * very rudimentary version. this works:
 * > printf("%02x\n", '5' - '0');
 * 05
 * ... but not yet very useful
 */


char *compile_command = "gcc -o .crepl_bin .crepl_src.c -lm";
char *run_command = "./.crepl_bin";

char *template_before = "\
    #include <stdio.h>      \n\
    #include <stdlib.h>     \n\
    #include <math.h>       \n\
    #include <limits.h>     \n\
    #include <time.h>       \n\
                            \n\
    int main(int argc, char *argv[]) {      \n\
";

char *template_after = "                    \n\
        return 0;                           \n\
    }                                       \n\
";

void compile_and_run(const char *code) {
    FILE *f = fopen(".crepl_src.c", "w");
    fwrite(template_before, strlen(template_before), 1, f);
    fwrite(code, strlen(code), 1, f);
    fwrite(template_after, strlen(template_after), 1, f);
    fclose(f);
    system(compile_command);
    system(run_command);
}

int main() {
    char buf[1024];
    while (1) {
        printf("> ");
        fgets(buf, 1024, stdin);
        compile_and_run(buf);
    }
}
