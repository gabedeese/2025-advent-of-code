#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *fp = fopen(argv[1], "r");
  char buffer[MAX];
  const char *x = "-";
  const char *y = ",";
  char *id_start;
  char *id_end;

  if (fp == NULL) {
    fprintf(stderr, "Failed to read file.\n");
    return EXIT_FAILURE;
  }

  // while (fgets(buffer, sizeof(buffer), fp) != NULL) {
  // Get the first range of IDs before starting the loop
  id_start = strtok(fgets(buffer, sizeof(buffer), fp), x);
  id_end = strtok(NULL, y);

  while (id_start != NULL || id_end != NULL) {
    printf("id range starting at: %s\nid range ending at: %s\n", id_start,
           id_end);

    id_start = strtok(NULL, x);
    id_end = strtok(NULL, y);
  }
  // }

  return EXIT_SUCCESS;
}
