#! /bin/bash
#
#  Last modified:  Sept 6, 2021
#
#  This script must be executed in a directory that contains the grading harness
#  tar file (c01Grader.tar) posted on the course website; that tar file must
#  contain the files:
#
#     c01driver.c
#     ASMParser.h
#     ParseResult.h
#     Grader.h
#     Grader.o
#     Generate.h
#     Generate.o
#
#  The directory must also contain a tar file containing your completed files:
#
#     ASMParser.c
#     ParseResult.c
#
#  We recommend that  you name that file yourPID.tar, using your VT email PID as
#  the first part of the file name.
#
#  Invoke as:  ./gradeC01.sh <name of your solution tar file>
#
#  This will create the following files (if all goes well):
#     tests.txt       teh instructions generated for the testing
#     
#
#  Alternate invocation:  ./gradec01.sh -clean
#
#  This will remove the files created by an earlier run of the grading script;
#  it's useful if you just want to restart with a pristine environment.
#
#  To use this test script see the included README file.
#
# Configuration variables:
#
#   Names for directories:
graderTar="c01Grader.tar"
buildDir="build"

#   Names for log files created by this script:
buildLog="buildLog.txt"
testLog="testLog.txt"
gccLog="gccLog.txt"
testCaseFile="tests.txt"
tempDir="tempFiles"
seedValue="1506282647"

#   Name for the executable
exeName="c01"

#   Names for output files created by the test driver:
scoreResultsLog="Scores.txt"

#   Delimiter to separate sections of report file:
Separator="============================================================"

############################################# fn to check for tar file
#                 param1:  name of file to be checked
isTar() {

   mimeType=`file -b --mime-type $1`
   if [[ $mimeType == "application/x-tar" ]]; then
      return 0
   fi
   if [[ $mimeType == "application/x-gzip" ]]; then
      return 0
   fi
   return 1
}

##################################### fn to extract token from file name
#                 param1: (possibly fully-qualified) name of file
#  Note:  in production use, the first part of the file name will be the
#         student's PID
#
getPID() { 

   fname=$1
   # strip off any leading path info
   fname=${fname##*/}
   # extract first token of file name
   sPID=${fname%%.*}
}

###################################### fn to clean up earlier test results
cleanFiles() {
   
   rm -Rf $buildDir $tempDir *.txt  *_c02
}

############################################################ Check command line
   
   # Check for name of student's tar file on command line:
   if [[ $# -eq 0 ]]; then
      echo "Please supply the name of your tar file on the command line."
      exit 2
   fi
   
   if [[ $# -eq 1  ]] && [[ $1 == "-clean" ]]; then
      cleanFiles
      exit 3
   fi

   # Verify presence of named file
   tarFile="$1"
   tarFile=${tarFile##*/}
   if [ ! -e $tarFile ]; then
      echo "The file $tarFile does not exist."
      exit 3
   fi

   # Verify parameter is really a tar file
   isTar "$tarFile"
   if [[ ! $? -eq 0 ]]; then
      echo "The file $tarFile is not a valid tar file."
      exit 4
   fi

############################################################ Get student's PID
   
   # Extract first token of tar file name (student PID when we run this)
   getPID $tarFile
   # Set name for the summary results file
   resultsLog="$sPID".txt
   
   # Reset name for executable file
   exeName=${sPID}_${exeName}

   # Initiate header for grading log
   headerLog="header.txt"
   echo "Grading:  $tarFile" > $headerLog
   echo -n "Time:     " >> $headerLog
   echo `date` >> $headerLog
   echo >> $headerLog

############################################################ Build executable:
   
   # Create log file:
   echo "Executing gradeC02.sh..." > $buildLog
   echo >> $buildLog
   
   # Create build directory and put files into it:
   echo "Creating build subdirectory" >> $buildLog
   echo >> $buildLog
   # Create build directory if needed; empty it if it already exists
   if [[ -d $buildDir ]]; then
      rm -Rf ./$buildDir/*
   else
      mkdir $buildDir
   fi
   
   # Unpack student's tar file to a temp directory
   if [[ ! -e $tempDir ]]; then
      mkdir "./$tempDir"
   fi
   
   echo "Copying student source file to $tempDir:" >> $buildLog
   tar xvf $1 -C $tempDir >> $buildLog
   
   # Remove student versions of "locked" header files
   if [[ -e "$tempDir/ParseResult.h" ]]; then
      echo "Discarding student version of ParseResult.h" >> $buildLog
      rm -Rf "$tempDir/ParseResult.h"
   fi

   if [[ -e "$tempDir/ASMParser.h" ]]; then
      echo "Discarding student version of ASMParser.h" >> $buildLog
      rm -Rf "$tempDir/ASMParser.h"
   fi
   
   # Verify and copy the two mandatory files into the build directory:
   mFile1="ASMParser.c"
   mFile2="ParseResult.c"
   
   if [[ -e "$tempDir/$mFile1" ]]; then
      cp "$tempDir/$mFile1" ./$buildDir
   else
      echo "Student tar does not contain $mFile1"
      exit 5
   fi
   if [[ -e "$tempDir/$mFile2" ]]; then
      cp "$tempDir/$mFile2" ./$buildDir
   else
      echo "Student tar does not contain $mFile2"
      exit 5
   fi
   
   # Copy any additional student .c and .h files into the build directory:
   cp -f $tempDir/*.c $buildDir
   cp -f $tempDir/*.h $buildDir
   
   # Unpack the grading files into the build directory
   echo "Unpacking the grading code to the build directory:" >> $buildLog
   tar xvf $graderTar -C ./$buildDir >> $buildLog 2>&1
   echo "Note:  that may have overwritten files you submitted (but should not have)." >> $buildLog

   # Move to build directory
   cd ./$buildDir

   #   Build command:
   buildCmd="gcc -o $exeName -std=c11 -lm -Wall -W -ggdb3 *.c *.o"

   # Build the executable; save gcc output to log file
   echo "Invoking gcc..." >> ../$buildLog
   $buildCmd >> ../$buildLog 2>&1
   # gcc -o $exeName -std=c99 -Wall -ggdb3 *.c *.o >> ../$buildLog 2>&1
   echo >> ../$buildLog

   # Verify existence of executable
   if [[ ! -e $exeName ]]; then
      echo "Build failed; the file driver does not exist" >> ../$buildLog
      mv ../$buildLog ../$resultsLog
      exit 7
   fi
   if [[ ! -x $exeName ]]; then
      echo "Permissions error; the file driver is not executable" >> $buildLog
      echo $Separator >> $buildLog
      mv $buildLog $resultsLog
      exit 8
   fi
   echo "Build succeeded..." >> $buildLog
   
   # Move executable up to test directory and return there
   echo "Moving the executable $exeName to the test directory." >> $buildLog
   mv ./$exeName .. >> $buildLog
   cd .. >> $buildLog
   
   # Delimit this section of the report file:
   echo $Separator >> $buildLog

############################################################ Test

   # Initiate test Log
   echo "Executing the test driver..." > $testLog
   echo >> $testLog
   
   # The following sets the seed to the current time; comment out if you
   # want to use a hardwired seed for random data generation:
   seedValue=`date +%s`
   echo $seedValue >> $testLog
   echo >> $testLog

   # Set execution command
   exeCmd="./$exeName $testCaseFile $scoreResultsLog -seed $seedValue"
      
   # Execute driver:
   timeout -s SIGKILL 30 $exeCmd >> $testLog 2>&1
   timeoutStatus="$?"
   # echo "timeout said: $timeoutStatus"
   if [[ $timeoutStatus -eq 124 || $timeoutStatus -eq 137 ]]; then
      echo "The test of your solution timed out after 30 seconds." >> $testLog
      echo "Valgrind testing will NOT be done." >> $testLog
      killed="yes"
   elif [[ $timeoutStatus -eq 134 ]]; then
      echo "The test of your solution was killed by a SIGABRT signal." >> $testLog
      echo "Possible reasons include:" >> $testLog
      echo "    - a segfault error" >> $testLog
      echo "    - a serious memory access error" >> $testLog
      echo "Valgrind testing will NOT be done." >> $testLog
      killed="yes"
   fi
   
   # Verify existence of output file from driver:
   outputExists="yes"
   if [[ ! -e $scoreResultsLog ]]; then
      echo "$scoreResultsLog was not created." >> $testLog
      outputExists="no"
   fi
   if [[ "$outputExists" == "no" ]]; then
      echo $Separator >> $resultsLog
      cat $testLog >> $resultsLog
      echo $Separator >> $resultsLog
      cat $buildLog >> $resultsLog
      exit 9
   fi
   
############################################################ Run valgrind check

   # run same tests on valgrind
   #   full valgrind output is in $vgrindLog
   #   extracted counts are in $vgrindIssues
   vgrindLog="vgrindLog.txt"
   echo "Running valgrind test..." >> $vgrindLog
   vgrindSwitches=" --leak-check=full --show-leak-kinds=all --log-file=$vgrindLog --track-origins=yes -v"
   scoreResultsLog2="ScoresValgrind.txt"
   valgrind $vgrindSwitches ./$exeName $testCaseFile $scoreResultsLog2 2>&1
   
   # accumulate valgrind error counts
   if [[ -e $vgrindLog ]]; then
      vgrindIssues="vgrind_issues.txt"
      echo "Valgrind issues:" > $vgrindIssues
      grep "in use at exit" $vgrindLog >> $vgrindIssues
      grep "total heap usage" $vgrindLog >> $vgrindIssues
      grep "definitely lost" $vgrindLog >> $vgrindIssues
      echo "Invalid reads: `grep -c "Invalid read" $vgrindLog`" >> $vgrindIssues
      echo "Invalid writes: `grep -c "Invalid write" $vgrindLog`" >> $vgrindIssues
      echo "Uses of uninitialized values: `grep -c "uninitialised" $vgrindLog`" >> $vgrindIssues
   else
      echo "Error running Valgrind test." >> $testLog
   fi
   
############################################################ File report

   # Write header and score summary to start report
   cat $headerLog > $resultsLog
   echo ">>Scores from testing<<" >> $resultsLog
   grep -w "Total score:" $scoreResultsLog >> $resultsLog
   echo >> $resultsLog
   #grep -w "Total" $scoreResultsLog >> $resultsLog
   echo $Separator >> $resultsLog
   
   # Write valgrind summary counts to report
   if [[ -e $vgrindIssues ]]; then
      cat $vgrindIssues >> $resultsLog
   else
      echo "Valgrind results summary is not available." >> $resultsLog
   fi
   echo $Separator >> $resultsLog
   
   # Append instruction file to report; the existence check is redundant
   if [[ -e $testCaseFile ]]; then
      echo "Test instructions:" >> $resultsLog
      echo >> $resultsLog
      cat $testCaseFile >> $resultsLog
      echo $Separator >> $resultsLog
   else
      echo "The file $instructionLog was not created." >> $resultsLog
   fi
   
   # Append grading details to report; the existence check is redundant
   if [[ -e $scoreResultsLog ]]; then
      echo "Grading details:" >> $resultsLog
      cat $scoreResultsLog >> $resultsLog
      echo $Separator >> $resultsLog
   else
      echo "The file $scoreResultsLog was not created." >> $resultsLog
   fi
   
   # Append test log to report:
   if [[ -e $testLog ]]; then
      echo "Output from executing test driver:" >> $resultsLog
      cat $testLog >> $resultsLog
   else
      echo "The file $testLog was not created." >> $resultsLog
   fi
   echo $Separator >> $resultsLog
  
   # Append valgrind log to report:
   if [[ -e $vgrindLog ]]; then
      cat $vgrindLog >> $resultsLog
   else
      echo "Detailed Valgrind output is not available." >> $resultsLog
   fi
   echo $Separator >> $resultsLog
   
   # Append build log to report:
   echo "Output from build process:" >> $resultsLog
   cat $buildLog >> $resultsLog

exit 0
