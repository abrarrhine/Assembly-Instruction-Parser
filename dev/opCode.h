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

#ifndef DEV_OPCODE_H
#define DEV_OPCODE_H
enum _instructionType
{
  ADDI,
  MUL,
  MULT,
  LUI,
  LW,
  SUB
};
typedef enum _instructionType instructionTpye;

struct _opCode
{
  instructionTpye mnemonic;
  char *opcode;
  char *Funct;
};
typedef struct _opCode opCode;
static opCode Opcode_table[6] = {

    {ADDI, "001000", "001000"},
    {MUL, "011100", "000010"},
    {MULT, "000000", "011000"},
    {LUI, "001111", "001111"},
    {SUB, "000000", "100010"},
    {LW, "100011", "100011"}};
#endif // DEV_OPCODE_H
