#ifndef PARSERESULT_H
#define PARSERESULT_H
#include <inttypes.h>
#include <stdio.h>

/**  Represents the possible field values for a MIPS32 machine instruction.
 * 
 *   A ParseResult object is said to be proper iff:
 * 
 *     - Each of the char* members is either NULL or points to a zero-
 *       terminated C-string.
 *     - If ASMInstruction is not NULL, the contents of the array represent
 *       a MIPS32 assembly instruction.
 *     - If ASMInstruction is not NULL, the other fields are set to properly
 *       represent the corresponding fields of the MIPS32 assembly instruction
 *       stored in ASMInstruction.
 *     - Each field that is not relevant to the MIPS32 assembly instruction
 *       is set as described in the comments below.
 */
struct _ParseResult {
   // Each char* member will be NULL or point to dynamically-allocated char array
   // holding a zero-terminated C string.

   // The assembly code portion
   char* ASMInstruction;    // the assembly instruction, as a C-string
   char* Mnemonic;          // the symbolic name of the instruction
   char* rdName;            // the symbolic names of the registers, as C-strings;
   char* rsName;            //    NULL if the register field is not specified
   char* rtName;            //    in the assembly instruction
   
   //   The following are integer values
   int16_t  Imm;            // the immediate field, as a signed integer;
                            //   0 if not relevant for the assembly instruction
   uint8_t  rd;             // the three register fields, as small unsigned integers;
   uint8_t  rs;             //   255 if not relevant for the assembly instruction
   uint8_t  rt;

   // The computed machine code portion
   //   These are malloc'd zero-terminated C-strings
   char* Opcode;            // the opcode field bits
   char* Funct;             // the funct field bits
                            //   NULL if not relevant for the assembly instruction
   char* RD;                // the bit representations of the register numbers; 
   char* RS;                //   NULL if not relevant for the assembly instruction
   char* RT;
   char* IMM;               // 2's complement bit representation of the immediate;
                            //   NULL if not relevant for the assembly instruction
};

typedef struct _ParseResult ParseResult;

/**  Frees the dynamic content of a ParseResult object.
 * 
 *   Pre:  pPR points to a proper ParseResult object.
 *   Post: All of the dynamically-allocated arrays in *pPR have been
 *         deallocated.
 *         *pPR is proper.
 * 
 *   Comments:
 *     -  The function has no information about whether *pPR has been
 *        allocated dynamically, so it cannot risk attempting to 
 *        deallocate *pPR.
 *     -  The function is intended to provide the user with a simple
 *        way to free memory; the user may or may not reuse *pPR.  So,
 *        the function does set the pointers in *pPR to NULL.
 */
void clearResult(ParseResult* const pPR);

/**  Prints the contents of a ParseResult object.
 * 
 *   Pre:  Log is open on an output file.
 *         pPR points to a proper ParseResult object.
 */
void printResult(FILE* Log, const ParseResult* const pPR);

#endif
