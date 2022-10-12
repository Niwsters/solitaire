#include <stdio.h>
#include <string.h>
#include <ecl/ecl.h>
#include <ecl/external.h>

int main (int argc, char **argv) {
  /* Initialize ECL */
  cl_boot(argc, argv);

  /* Initialize the library we linked in. Each library
   * has to be initialized. It is best if all libraries
   * are joined using ASDF:MAKE-BUILD.
   */
  extern void init_test(cl_object);
  ecl_init_module(NULL, init_test);

  cl_object wut_fun = cl_eval(c_string_to_object("(lambda (msg) (receive-message msg))"));
  const char *msg = "oh hi :D";
  cl_object result = cl_funcall(2, wut_fun, ecl_make_constant_base_string(msg, strlen(msg)));

  /*
  cl_object result = cl_eval(c_string_to_object("(hello-lisp)"));
  ecl_print(result, ECL_T);


  cl_object my_fun = cl_eval(c_string_to_object("(lambda (x) (1+ x))"));
  ecl_print(my_fun, ECL_T);

  result=cl_funcall(2, my_fun, ecl_make_fixnum(8));
  ecl_print(result, ECL_T);
  */

  ecl_terpri(ECL_T);

  cl_shutdown();
  return 0;
}
