#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8 // Max string length read from the file.

struct dial {
  int new_pos;
  int pass_zero;
};

struct dial rotate_left(char buffer[], int dial);
struct dial rotate_right(char buffer[], int dial);

int main(int argc, char *argv[])
{
  // Check for correct usage of args.
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  struct dial turn_dial;
  int dial = 50; // Dial starts pointing at 50
  int counter = 0; // Count every time the dial is left at 0
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
      turn_dial = rotate_left(buffer, dial);
      dial = turn_dial.new_pos;
      counter += turn_dial.pass_zero;

      // Check to see if the dial is at 0
      if (dial == 0) {
        counter++;
      }
    }

    // If the first letter is an R then turn the dial right
    if (buffer[0] == 'R') {
      turn_dial = rotate_right(buffer, dial);
      dial = turn_dial.new_pos;
      counter += turn_dial.pass_zero;

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

// Returns the new position of the dial after rotation and returns how many times it passed zero
struct dial rotate_left(char buffer[], int dial) {
  struct dial rotate;
  rotate.pass_zero = 0;

  // Gets the factor of 100 to add to the counter since 100 will pass zero and leave the dial at the same spot
  if ((atoi(&buffer[1])) > 99) {
    int fofh = buffer[1] - '0';
    rotate.pass_zero = fofh;
  }

  // Gets the mod of the buffer by 100 since rotating 100 is redundant
  int x = (atoi(&buffer[1])) % 100;

  // Update the dial position
  rotate.new_pos = dial - x;

  // Take care of looping past 0 and adds 1 to the counter only if it doesn't land on zero. Those get counted in the main function
  if (rotate.new_pos <= 0) {
    rotate.new_pos += 100;
    if (rotate.new_pos != 0 && dial != 0) {
      rotate.pass_zero++;
    }
  }

  return rotate;
}

// Returns the new position of the dial after rotation and returns how many times it passed zero
struct dial rotate_right(char buffer[], int dial) {
  struct dial rotate;
  rotate.pass_zero = 0;

  // Gets the factor of 100 to add to the counter since 100 will pass zero and leave the dial at the same spot
  if ((atoi(&buffer[1])) > 99) {
    int fofh = buffer[1] - '0';
    rotate.pass_zero = fofh;
  }

  // Gets the mod of the buffer by 100 since rotating 100 is redundant
  int x = (atoi(&buffer[1])) % 100;

  // Update the dial position
  rotate.new_pos = dial + x;

  // Take care of looping past 0
  if (rotate.new_pos <= 0) {
    rotate.new_pos += 100;
    if (rotate.new_pos != 0 && dial != 0) {
      rotate.pass_zero++;
    }
  }

  return rotate;
}
