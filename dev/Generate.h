#ifndef GENERATE_H
#define GENERATE_H
#include <inttypes.h>

/**  Generates input data for testing MIPS32 machine code translations.
 * 
 *   Pre:  fName is a valid file name
 *         nCases == 0 or > 7 means generate 7 test cases (one for each
 *            specified instruction)
 *         1 <= nCases <= 7 means generate nCases tests
 *   Post: A file, named fName, has been created and holds the number of
 *            valid test cases described above. 
 */
uint32_t GenerateInput(char* fName, uint32_t nCases);

/**  Write summary of scores to a log file.
 * 
 *   Pre:  fp is open on a log file
 */
void setSeed(uint32_t seed);

#endif
