// driver.c for MIPS32 assembly instruction parser
//
// Requires:  Generate.h, Generate.o, Grader.h, Grader.o   <-- test harness
//            ASMParser.h                                  <-- supplied
//            ParseResult.h                                <-- supplied
//            ASMParser.c                                  <-- student file
//            ParseResult.c                                <-- student file
//            + any other implementation files supplied by student
//
// Invocation options:
//
//    parse <asm code file> <results file name> [-seed N]
//       param1:  name of file containing MIPS32 assembly instructions,
//                one per line; created by driver.c as specified
//       param2:  name of file to hold results from parser
//       param3:  (optional) if absent, random valid assembly instructions will
//                be generated and written to the specified input file, before
//                the parser is executed;
//                if present, rand() will be seeded with N
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Generate.h"          // for generating test cases
#include "ParseResult.h"       // for reporting parse results
#include "ASMParser.h"         // for student's solution
#include "Grader.h"            // for comparison/scoring logic

#define MAX_INSTR_LENGTH  99
#define NUM_TESTS         25   // modify this if you want to run more/fewer tests

int main(int argc, char** argv) {
    
   uint32_t nTests = NUM_TESTS;
   
   // Set seed value for testing; use system clock unless user has specified
   // a seed value in the invocation:
   uint32_t seed = time( NULL );            // get system clock, for default
   if ( argc == 5 && strcmp(argv[3], "-seed") == 0 ) {
      seed = atoi(argv[4]);
   }
   
   // Store seed value into testing module:
   setSeed(seed);
   
   // Generate test data
   GenerateInput(argv[1], nTests);
   
   // Open specified input file and verify it's available:
   FILE* src   = fopen(argv[1], "r");
   if ( src == NULL ) {
      printf("Unable to find file %s... exiting.\n", argv[1]);
      return 2;
   }
   // Open specified results file; taking its creation for granted:
   FILE* results  = fopen(argv[2], "w");
   
   // Record the seed value in the output log:
   fprintf(results, "Seed value: %"PRIu32"\n\n", seed);
   
   // Variables for instruction processing:
   char asmInstruction[MAX_INSTR_LENGTH + 1];   // holder for current asm instruction
   uint32_t totalScore = 0;                     // student's score for test run
   uint32_t numInstructions = 0;                // assembly instruction count
   
   // Storage for a list of scores on the test cases:
   uint32_t *scores = malloc(nTests*sizeof(uint32_t));
   for (uint32_t idx = 0; idx < nTests; idx++) {
		scores[idx] = -1;
	}

   uint32_t nCase = 1;
   // Process as long as there are more instructions:
   while ( fgets(asmInstruction, MAX_INSTR_LENGTH + 1, src) != NULL ) {
      
      // erase trailing newline from string
      asmInstruction[strlen(asmInstruction) - 1] = '\0';
      
      // Make backup copy of instruction string for grading:
      char* asmCopy = calloc(MAX_INSTR_LENGTH + 1, sizeof(char));
      strcpy(asmCopy, asmInstruction);
      
      fprintf(results, "Test case %"PRIu32":\n", nCase);
      fprintf(results, "Testing with:  %s\n", asmInstruction);
      
      // Invoke student's ASM parser on current instruction:
      ParseResult* studentParse = parseASM(asmInstruction);
      
      // Check for NULL return:
      if ( studentParse == NULL ) {
			fprintf(results, "Error:  parseASM() returned NULL for \"%s\"\n", asmCopy);
			return 1;
		}
      
      // Compare student's translation to reference translation and score it:
      uint32_t currScore = scoreResult(results, studentParse, asmCopy);
      
      // Update score information:
      totalScore += currScore;
      scores[numInstructions] = currScore;
      numInstructions++;
      
      // Clean up dynamic allocations that should have occurred on this test:
      free(asmCopy);
      clearResult(studentParse);
      free(studentParse);
      nCase++;
   }

   // Log score results:
   fprintf(results, "Scores:\n");
   for (uint32_t idx = 0; idx < nTests; idx++) {
		fprintf(results, "  Test %2"PRIu32":%5"PRIu32"/%"PRIu32"\n", 
		                           idx + 1, scores[idx], PTS_PER_TEST);
	}
	fprintf(results, "\n");
   fprintf(results, "Total score:  %"PRIu32"/%"PRIu32"\n", 
                                     totalScore, nTests * PTS_PER_TEST);
   
   // Clean up last allocation:
   free(scores);
   
   // Close input/output files:
   fclose(src);
   fclose(results);
   
   return 0;
}
