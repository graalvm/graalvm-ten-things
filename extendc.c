#include <stdlib.h>
#include <stdio.h>

#include <polyglot_api.h>

int main(int argc, char **argv) {
  graal_isolate_t *isolate = NULL;
  graal_isolatethread_t *thread = NULL;
  
  if (graal_create_isolate(NULL, &isolate, &thread) != 0) {
    fprintf(stderr, "graal_create_isolate error\n");
    return 1;
  }
  
  poly_context context = NULL;
  
  if (poly_create_context(thread, NULL, 0, &context) != poly_ok) {
    fprintf(stderr, "poly_create_context error\n");
    return 1;
  }
  
  char* language = "js";
  
  for (int n = 1; n < argc; n++) {
    if (argv[n][0] == '-') {
      language = &argv[n][1];
    } else {
      poly_value result = NULL;
      
      if (poly_context_eval(thread, context, language, "eval", argv[n], &result) != poly_ok) {
        fprintf(stderr, "poly_context_eval error\n");
        
        const poly_extended_error_info *error;
        
        if (poly_get_last_error_info(thread, &error) != poly_ok) {
          fprintf(stderr, "poly_get_last_error_info error\n");
          return 1;
        }

        fprintf(stderr, "%s\n", error->error_message);
        
        return 1;
      }
      
      char buffer[1024];
      size_t length;
      
      if (poly_value_to_string_utf8(thread, result, buffer, sizeof(buffer), &length) != poly_ok) {
        fprintf(stderr, "poly_value_to_string_utf8 error\n");
        return 1;
      }
      
      printf("%s\n", buffer);
    }
  }
  
  return 0;
}