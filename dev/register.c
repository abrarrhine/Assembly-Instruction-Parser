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

#include "register.h"
#include <string.h>
reg registerFind(char *reg)
{
  if (strcmp(reg, "$t0") == 0)
  {
    return registerTable[0];
  }
  else if (strcmp(reg, "$t1") == 0)
  {
    return registerTable[1];
  }
  else if (strcmp(reg, "$t2") == 0)
  {
    return registerTable[2];
  }
  else if (strcmp(reg, "$t3") == 0)
  {
    return registerTable[3];
  }
  else if (strcmp(reg, "$s0") == 0)
  {
    return registerTable[4];
  }
  else if (strcmp(reg, "$s1") == 0)
  {
    return registerTable[5];
  }
  else if (strcmp(reg, "$s2") == 0)
  {
    return registerTable[6];
  }
  else // $s3
  {
    return registerTable[7];
  }
}
