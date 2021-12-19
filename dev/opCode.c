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

#include "opCode.h"
opCode opFind(instructionTpye type)
{
  switch (type)
  {
  case ADDI:
    return Opcode_table[0];
  case MUL:
    return Opcode_table[1];
  case MULT:
    return Opcode_table[2];
  case LUI:
    return Opcode_table[3];
  case SUB:
    return Opcode_table[4];
  case LW:
    return Opcode_table[5];
  default:
    return Opcode_table[0];
  }
}
