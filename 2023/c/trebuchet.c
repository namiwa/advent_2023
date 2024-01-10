#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *trim(char *str) {
  char *end;

  while(isspace((unsigned char) *str)) str++;

  if(*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  end[1] = '\0';
  return str;
}

// Stores the trimmed input string into the given output buffer, which must be
// large enough to store the result.  If it is too small, the output is
// truncated.
size_t trimwhitespace(char *out, size_t len, const char *str)
{
  if(len == 0)
    return 0;

  const char *end;
  size_t out_size;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
  {
    *out = 0;
    return 1;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len-1 ? (end - str) : len-1;

  // Copy trimmed string and add null terminator
  memcpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("please specify a file.\n");
    exit(EXIT_FAILURE);
  }

  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  stream = fopen(argv[1], "r");
  if (stream == NULL) exit(EXIT_FAILURE);

  // just cat file into this
  long total = 0;
  int val = -1;

  while ((read = getline(&line, &len, stream)) != -1) {
    len = trimwhitespace(line, len, line);

    char number[2];
    for (int i = 0; i < len; i++) {
      if (isdigit(line[i])) {
        number[0] = line[i];
        break;
      }
    }

    while (len > 0) {
      len--;
      if (isdigit(line[len])) {
        number[1] = line[len];
        break;
      }
    }

    total += atoi(number);
    printf("processing line: %s number: %s \n", line, number);
  }

  printf("%ld", total);
  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);

  return 0;
}
