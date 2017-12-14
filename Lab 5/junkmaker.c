#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
int k = 32;                        // Characters from the space ' ' (char ' ' = 32) and 95 characters past that. Can adjust to more characters in extended ASCII.
int i = 0;
int j = 0;
int lim = 20;                     // Words approximately of length 20 (because of random spaces).
srand (time(NULL));
while (i < 5000) {                     // At least 5000 words. Adjust to however many you want to generate. (At this amount, approx 33000 bytes per run? I think.)
j = 0;
lim = 1 + (rand() % 15);           // Word length randomizer.
while (j < lim) {
putchar(k + (rand() % 95));      // Random characters from space to ---. Can adjust 95 to larger number for extended ASCII characters as well, but it doesn't matter.
j++;
}
putchar(' ');
i++;
}
}