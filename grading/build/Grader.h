#ifndef GRADER_H
#define GRADER_H
#include <inttypes.h>
#include <stdio.h>
#include "ParseResult.h"


/*** DO NOT MODIFY THIS FILE IN ANY WAY!!  ***/



#define PTS_PER_TEST  60

/**  Evaluates a student's translation of a MIPS32 assembly instruciton to
 *   a ParseResult object.
 * 
 *   Pre:  fp is open on an output file
 *         *stu is a proper ParseResult object created by a student's
 *             implement of parseASM()
 *         *pASM is one of the specified MIPS32 assembly instructions
 * 
 *   Post: the evaluation of *stu has been written to the output file
 * 
 *   Returns: a score for that evaluation
 */
uint32_t scoreResult(FILE* fp, const ParseResult* const stu, const char* const pASM);

#endif
