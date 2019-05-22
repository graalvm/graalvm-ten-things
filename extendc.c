#include <stdlib.h>
#include <stdio.h>

#include <polyglot_api.h>

int main(int argc, char **argv) {
  poly_isolate isolate = NULL;
  poly_thread thread = NULL;
  
  if (poly_create_isolate(NULL, &isolate, &thread) != poly_ok) {
    fprintf(stderr, "poly_create_isolate error\n");
    return 1;
  }
  
  poly_context context = NULL;
  
  if (poly_create_context(thread, NULL, 0, &context) != poly_ok) {
    fprintf(stderr, "poly_create_context error\n");
    goto exit_isolate;
  }
  
  char* language = "js";
  
  for (int n = 1; n < argc; n++) {
    if (argv[n][0] == '-') {
      language = &argv[n][1];
    } else {
      poly_value result = NULL;

      if (poly_open_handle_scope(thread) != poly_ok) {
        fprintf(stderr, "poly_open_handle_scope error\n");
        goto exit_context;
      }
      
      if (poly_context_eval(thread, context, language, "eval", argv[n], &result) != poly_ok) {
        fprintf(stderr, "poly_context_eval error\n");
        
        const poly_extended_error_info *error;
        
        if (poly_get_last_error_info(thread, &error) != poly_ok) {
          fprintf(stderr, "poly_get_last_error_info error\n");
          goto exit_scope;
        }

        fprintf(stderr, "%s\n", error->error_message);
        goto exit_scope;
      }
      
      char buffer[1024];
      size_t length;
      
      if (poly_value_to_string_utf8(thread, result, buffer, sizeof(buffer), &length) != poly_ok) {
        fprintf(stderr, "poly_value_to_string_utf8 error\n");
        goto exit_scope;
      }

      if (poly_close_handle_scope(thread) != poly_ok) {
        fprintf(stderr, "poly_close_handle_scope error\n");
        goto exit_context;
      }

      buffer[length] = '\0';
      printf("%s\n", buffer);
    }
  }

  if (poly_context_close(thread, context, true) != poly_ok) {
    fprintf(stderr, "poly_context_close error\n");
    goto exit_isolate;
  }

  if (poly_tear_down_isolate(thread) != poly_ok) {
    fprintf(stderr, "poly_tear_down_isolate error\n");
    return 1;
  }
  
  return 0;

exit_scope:
  poly_close_handle_scope(thread);
exit_context:
  poly_context_close(thread, context, true);
exit_isolate:
  poly_tear_down_isolate(thread);
  return 1;
}
