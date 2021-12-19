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

#include "ASMParser.h"

/***  Add include directives for here as needed.  ***/

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "opCode.h"
#include "register.h"

void get_bin(int16_t n, char *ptr);
opCode opFind(instructionTpye type);

reg registerFind(char *reg);
static void init_pASM(ParseResult *pASM);

static instructionTpye getatype(char *mnemonic);

ParseResult *parseASM(const char *const pASM)
{

   /***  Implementation here is up to you!  ***/
   ParseResult *r = calloc(1, sizeof(ParseResult));
   init_pASM(r);

   char copy[100];
   char *Mnem_token;
   r->ASMInstruction = calloc(strlen(pASM) + 1, sizeof(char));
   r->Mnemonic = calloc(5, sizeof(char));
   r->Opcode = calloc(7, sizeof(char));

   strcpy(copy, pASM);
   strcat(r->ASMInstruction, copy);

   Mnem_token = strtok(copy, " ");

   instructionTpye insrt_type = getatype(Mnem_token);
   opCode op = opFind(insrt_type);

   strcpy(r->Mnemonic, Mnem_token);
   strcpy(r->Opcode, op.opcode);

   char *rd_token = NULL;
   char *rs_token = NULL;
   char *rt_token = NULL;
   if (insrt_type == SUB)
   {

      uint8_t rd, rs, rt;
      rd_token = strtok(NULL, ", ");
      rs_token = strtok(NULL, ", ");
      rt_token = strtok(NULL, ", ");

      rd = registerFind(rd_token).number;
      rs = registerFind(rs_token).number;
      rt = registerFind(rt_token).number;

      r->rdName = calloc(strlen(rd_token) + 1, sizeof(char));
      r->rsName = calloc(strlen(rs_token) + 1, sizeof(char));
      r->rtName = calloc(strlen(rt_token) + 1, sizeof(char));
      r->Funct = calloc(7, sizeof(char));
      r->RD = calloc(6, sizeof(char));
      r->RS = calloc(6, sizeof(char));
      r->RT = calloc(6, sizeof(char));

      strcpy(r->Funct, op.Funct);
      strcpy(r->rdName, rd_token);
      strcpy(r->rsName, rs_token);
      strcpy(r->rtName, rt_token);
      r->rd = rd;
      r->rs = rs;
      r->rt = rt;
      strcpy(r->RD, registerFind(rd_token).binaryNumber);
      strcpy(r->RS, registerFind(rs_token).binaryNumber);
      strcpy(r->RT, registerFind(rt_token).binaryNumber);
   }
   else if (insrt_type == MUL)
   {
      uint8_t rd, rs, rt;
      rd_token = strtok(NULL, ", ");
      rs_token = strtok(NULL, ", ");
      rt_token = strtok(NULL, ", ");

      rd = registerFind(rd_token).number;
      rs = registerFind(rs_token).number;
      rt = registerFind(rt_token).number;

      r->rdName = calloc(strlen(rd_token) * 2 + 1, sizeof(char));
      r->rsName = calloc(strlen(rs_token) + 1, sizeof(char));
      r->rtName = calloc(strlen(rt_token) + 1, sizeof(char));
      r->Funct = calloc(7, sizeof(char));
      r->RD = calloc(12, sizeof(char));
      r->RS = calloc(6, sizeof(char));
      r->RT = calloc(6, sizeof(char));

      strcpy(r->Funct, op.Funct);
      strcpy(r->rdName, rd_token);
      strcpy(r->rsName, rs_token);
      strcpy(r->rtName, rt_token);
      r->rd = rd;
      r->rs = rs;
      r->rt = rt;
      strcpy(r->RD, registerFind(rd_token).binaryNumber);
      strcpy(r->RS, registerFind(rs_token).binaryNumber);
      strcpy(r->RT, registerFind(rt_token).binaryNumber);
   }
   else if (insrt_type == MULT)
   {
      uint8_t rs, rt, rd;

      rs_token = strtok(NULL, ", ");
      rt_token = strtok(NULL, ", ");

      rs = registerFind(rs_token).number;
      rt = registerFind(rt_token).number;

      r->rsName = calloc(strlen(rs_token) + 1, sizeof(char));
      r->rtName = calloc(strlen(rt_token) + 1, sizeof(char));
      r->Funct = calloc(7, sizeof(char));
      r->RS = calloc(6, sizeof(char));
      r->RT = calloc(6, sizeof(char));
      r->RD = calloc(6, sizeof(char));
      // r->RD = calloc(6, sizeof(char));
      // r->RD = "00000";
      // r->Funct = 011000;

      strcpy(r->rsName, rs_token);
      strcpy(r->rtName, rt_token);
      r->rs = rs;
      r->rt = rt;
      r->rd = 0;
      strcpy(r->Funct, op.Funct);
      strcpy(r->RS, registerFind(rs_token).binaryNumber);
      strcpy(r->RT, registerFind(rt_token).binaryNumber);
      // strcpy(r->RD, registerFind(rt_token).binaryNumber);
      strcpy(r->RD, "00000");
   }
   else if (insrt_type == ADDI)
   {
      uint8_t rs, rt, rd;
      int32_t imm;

      rt_token = strtok(NULL, ", ");
      rs_token = strtok(NULL, ", ");
      // rd_token = strtok(NULL,", ");
      imm = atoi(strtok(NULL, ", "));

      rs = registerFind(rs_token).number;
      rt = registerFind(rt_token).number;
      // rd = registerFind(rd_token).number;

      r->rsName = calloc(strlen(rs_token) + 1, sizeof(char));
      r->rtName = calloc(strlen(rt_token) + 1, sizeof(char));
      r->RS = calloc(6, sizeof(char));
      r->RT = calloc(6, sizeof(char));
      // r->RD = calloc(6, sizeof(char));
      r->IMM = calloc(17, sizeof(char));

      strcpy(r->rsName, rs_token);
      strcpy(r->rtName, rt_token);
      r->rs = rs;
      r->rt = rt;
      r->rd = 0;
      strcpy(r->RS, registerFind(rs_token).binaryNumber);
      strcpy(r->RT, registerFind(rt_token).binaryNumber);

      r->Imm = imm;
      imm = 0x0000FFFF & imm;
      char *binary = calloc(20, sizeof(char));
      get_bin(imm, binary);
      // Edit
      size_t i = 0;
      for (i = 0; i < 16 - strlen(binary); i++)
      {
         strcat(r->IMM, "0");
      }
      strcat(r->IMM, binary);
      free(binary);
   }
   else if (insrt_type == LUI) // lui
   {
      int16_t imm;
      rt_token = strtok(NULL, ", ");
      imm = atoi(strtok(NULL, ", "));

      r->RS = calloc(6, sizeof(char));
      r->RT = calloc(6, sizeof(char));
      r->IMM = calloc(17, sizeof(char));
      r->rtName = calloc(strlen(rt_token) + 1, sizeof(char));

      r->Imm = imm;
      imm = 0xFFFF & imm;
      char *binary = calloc(20, sizeof(char));
      get_bin(imm, binary);
      // Edit
      size_t i = 0;
      for (i = 0; i < 16 - strlen(binary); i++)
      {
         strcat(r->IMM, "0");
      }
      strcat(r->IMM, binary);

      strcpy(r->rtName, rt_token);
      free(binary);
      r->rs = 0;
      r->rd = 0;
      r->rt = registerFind(rt_token).number;

      strcpy(r->RS, "00000");
      strcpy(r->RT, registerFind(rt_token).binaryNumber);
   }
   else // lw
   {
      rt_token = strtok(NULL, ", ");
      int16_t imm = atoi(strtok(NULL, "("));
      rs_token = strtok(NULL, ")");

      r->RS = calloc(6, sizeof(char));
      r->RT = calloc(6, sizeof(char));
      r->IMM = calloc(17, sizeof(char));
      r->rsName = calloc(strlen(rs_token) + 1, sizeof(char));
      r->rtName = calloc(strlen(rs_token) + 1, sizeof(char));

      r->Imm = imm;
      char *binary = calloc(20, sizeof(char));
      get_bin(imm, binary);
      int length = strlen(binary);
      int j = 0;
      for (j = 0; j < 16 - length; j++)
      {
         strcat(r->IMM, "0");
      }
      strcat(r->IMM, binary);
      strcpy(r->rsName, rs_token);
      strcpy(r->rtName, rt_token);
      free(binary);
      r->rs = registerFind(rs_token).number;
      r->rt = registerFind(rt_token).number;
      r->rd = 0;
      strcpy(r->RS, registerFind(rs_token).binaryNumber);
      strcpy(r->RT, registerFind(rt_token).binaryNumber);
   }

   return r;
}

static void init_pASM(ParseResult *pASM)
{
   pASM->ASMInstruction = NULL;
   pASM->Mnemonic = NULL;

   pASM->rdName = NULL;
   pASM->rsName = NULL;
   pASM->rtName = NULL;

   pASM->Imm = 0;
   pASM->rd = 255;
   pASM->rs = 255;
   pASM->rt = 255;

   pASM->Opcode = NULL;
   pASM->Funct = NULL;

   pASM->RD = NULL;
   pASM->RS = NULL;
   pASM->RT = NULL;
   pASM->IMM = NULL;
}

static instructionTpye getatype(char *mnemonic)
{
   if (strcmp(mnemonic, "addi") == 0)
   {
      return ADDI;
   }
   else if (strcmp(mnemonic, "mul") == 0)
   {
      return MUL;
   }
   else if (strcmp(mnemonic, "mult") == 0)
   {
      return MULT;
   }
   else if (strcmp(mnemonic, "lui") == 0)
   {
      return LUI;
   }
   else if (strcmp(mnemonic, "lw") == 0)
   {
      return LW;
   }
   else
   {
      return SUB;
   }
}

void get_bin(int16_t n, char *ptr)
{
   int l = sizeof(n) * 8;
   int i = 2;
   if (i == 0)
   {
      return;
   }
   for (i = l - 1; i >= 0; i--)
   {
      if (n & (1 << i))
         break;
   }

   for (; i >= 0; i--)
   {
      if ((n & (1 << i)) != 0)
      {
         strcat(ptr, "1");
      }
      else
      {
         strcat(ptr, "0");
      }
   }
}
