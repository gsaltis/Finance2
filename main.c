/*****************************************************************************
 * FILE NAME    : main.c
 * DATE         : April 11 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <StringUtils.h>
#include <FileUtils.h>
#include <MemoryManager.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NorthwestCSV.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
static string
MainFilename = "AccountHistory.csv";

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
StringList*
FileUtilGetStringList
(string InFilename);

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  StringList*                           strings;
  NorthwestCSVTransactionList*          transactions;
  NorthwestCSVTransaction*              trans;

  strings = FileUtilGetStringList(MainFilename);
  transactions = NorthwestCSVTransactionListFromStrings(strings);
  trans = NorthwestCSVTransactionListGet(transactions, atoi(argv[1]));

  if ( trans ) {
    NorthwestCSVTransactionDump(trans);
  }
  
  printf("Count = %d\n", NorthwestCSVTransactionListCount(transactions));
  return (EXIT_SUCCESS);
}

/*****************************************************************************!
 * Function : FileUtilGetStringList
 *****************************************************************************/
StringList*
FileUtilGetStringList
(string InFilename)
{
  int                                   i;
  StringList*                           strings;
  string                                buffer;
  int                                   linesCount;
  char**                                lines;
  int                                   bufferSize;
  GetFileBuffer(InFilename, &buffer, &bufferSize);
  GetFileLines(buffer, bufferSize, &lines, &linesCount);
  FreeMemory(buffer);

  strings = StringListCreate();

  for ( i = 0 ; i < linesCount ; i++ ) {
    StringListAppend(strings, StringCopy(lines[i]));
    FreeMemory(lines[i]);
  }

  FreeMemory(lines);
  return strings;
}

  
