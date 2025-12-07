#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 8 // Max string length read from the file.

int rotate_left(char buffer[], int dial);
int rotate_right(char buffer[], int dial);

int main(int argc, char *argv[])
{
  // Check for correct usage of args.
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  int counter = 0; // Count every time the dial is left at 0
  int dial = 50; // Dial starts pointing at 50
  char buffer[MAX]; // Buffer to hold the string from the input.txt
  FILE *fp = fopen(argv[1], "r"); // File pointer to input.txt

  // Check for valid file
  if (fp == NULL) {
    perror("Failed to read file");
    return 1;
  }

  // Start reading the file line by line
  while (fgets(buffer, MAX, fp) != NULL) {

    // If the first letter is an L then turn the dial left
    if (buffer[0] == 'L') {
      dial = rotate_left(buffer, dial);

      // Check to see if the dial is at 0
      if (dial == 0) {
        counter++;
      }
    }

    // If the first letter is an R then turn the dial right
    if (buffer[0] == 'R') {
      dial = rotate_right(buffer, dial);

      // Check to see if the dial is at 0
      if (dial == 0) {
        counter++;
      }
    }
  }

  // Print the number of times the dial was left at 0 after each turn
  printf("%d\n", counter);

  return 0;
}

// Convert the string to an integer and subtract that from the current dial position
int rotate_left(char buffer[], int dial) {

  // Gets the mod of the buffer by 100 since rotating 100 is redundant
  int x = (atoi(&buffer[1])) % 100;

  // Update the dial position
  int new_dial = dial - x;

  // Take care of looping past 0
  if (new_dial < 0) {
    new_dial += 100;
  }

  return new_dial;
}

// Convert the string to an integer and add that to the current dial position
int rotate_right(char buffer[], int dial) {

  // Gets the mod of the buffer by 100 since rotating 100 is redundant
  int x = (atoi(&buffer[1])) % 100;

  // Update the dial position
  int new_dial = dial + x;

  // Take care of looping past 0
  if (new_dial > 99) {
    new_dial -= 100;
  }

  return new_dial;
}
