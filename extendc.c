#include <stdlib.h>
#include <stdio.h>

#include <polyglot_api.h>

int main(int argc, char **argv) {
  graal_isolate_t *isolate = NULL;
  graal_isolatethread_t *thread = NULL;
  
  if (graal_create_isolate(NULL, &isolate) != 0 || (thread = graal_current_thread(isolate)) == NULL) {
    fprintf(stderr, "initialization error\n");
    return 1;
  }
  
  poly_context context = NULL;
  
  if (poly_create_context(thread, NULL, 0, &context) != poly_ok) {
    fprintf(stderr, "initialization error\n");
    return 1;
  }
  
  char* language = "js";
  
  for (int n = 1; n < argc; n++) {
    if (argv[n][0] == '-') {
      language = &argv[n][1];
    } else {
      poly_value result = NULL;
      
      if (poly_context_eval(thread, context, language, "unicalc", argv[n], &result) != poly_ok) {
        fprintf(stderr, "eval error\n");
        return 1;
      }
      
      char buffer[1024];
      size_t length;
      
      if (poly_value_to_string_utf8(thread, result, buffer, sizeof(buffer), &length) != poly_ok) {
        fprintf(stderr, "to string error\n");
        return 1;
      }
      
      buffer[length] = '\0';
      printf("%s\n", buffer);
      
      poly_destroy_handle(thread, result);
    }
  }
  
  return 0;
}
