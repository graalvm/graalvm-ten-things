#include <stdlib.h>
#include <stdio.h>

#include <libdistance.h>

int main(int argc, char **argv) {
  graal_isolate_t *isolate = NULL;
  graal_isolatethread_t *thread = NULL;
  
  if (graal_create_isolate(NULL, &isolate, &thread) != 0) {
    fprintf(stderr, "graal_create_isolate error\n");
    return 1;
  }
  
  double a_lat   = strtod(argv[1], NULL);
  double a_long  = strtod(argv[2], NULL);
  double b_lat   = strtod(argv[3], NULL);
  double b_long  = strtod(argv[4], NULL);
  
  printf("%.2f km\n", distance(thread, a_lat, a_long, b_lat, b_long));

  if (graal_detach_thread(thread) != 0) {
    fprintf(stderr, "graal_detach_thread error\n");
    return 1;
  }
  
  return 0;
}
