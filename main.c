#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main() {
  int fds[2];
  pipe(fds);

  int fds2[2];
  pipe(fds2);

  int f;
  f = fork();

  if (f) {
    close(fds[READ]);
    close(fds2[WRITE]);
    while(1) {
      printf("Enter input: ");
      char line[1000];
      fgets(line, sizeof(line), stdin);
      write(fds[WRITE], line, strlen(line));
      printf("Response: ");
      char line2[1000];
      read(fds2[READ], line2, sizeof(line2));
      printf("%s\n", line2);
    }
  }
  else {
    close(fds[WRITE]);
    close(fds2[READ]);
    while(1) {
    char line[1000];
    read(fds[READ], line, sizeof(line));
    int i = 0;
    while(line[i]) {
      if(line[i] >= 'a' && line[i] <= 'z') {
        line[i] = line[i] - 'a' + 'A';
      }
      i++;
    }
    write(fds2[WRITE], line, strlen(line));
    }
  }
  return 0;
}
