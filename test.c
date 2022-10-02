#include <stdio.h>
#include <ecl/ecl.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    cl_boot(argc, argv);

    cl_eval(c_string_to_object("(defun ecl-hello-lisp () \"oh hi\")"));

    cl_object result = cl_eval(c_string_to_object("(ecl-hello-lisp)"));
    ecl_print(result, ECL_T);

    int j = result->string.dim;
    ecl_character* ecl_str = result->string.self;
    char* str = malloc(sizeof("oh hi"));
    for (int i=0; i<j; i++)
        str[i] = (*(ecl_str+i));

    printf("From ECL: %s\n", str);

    ecl_terpri(ECL_T);
    cl_shutdown();

    return 0;
}
