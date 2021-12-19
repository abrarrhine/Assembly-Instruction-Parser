// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the grading code.
//
// <Abrar Islam>
// <abrarr18>

#include <inttypes.h>
#ifndef DEV_REGISTER_H
#define DEV_REGISTER_H
struct _register
{
  char *name;
  uint8_t number;
  char *binaryNumber;
};
typedef struct _register reg;

static reg registerTable[8] = {
    {"$t0", 8, "01000"},
    {"$t1", 9, "01001"},
    {"$t2", 10, "01010"},
    {"$t3", 11, "01011"},
    {"$s0", 16, "10000"},
    {"$s1", 17, "10001"},
    {"$s2", 18, "10010"},
    {"$s3", 19, "10011"},

};
#endif // DEV_REGISTER_H
