/*****************************************************************************
 * FILE NAME    : NorthwestCSV.c
 * DATE         : April 11 2021
 * PROJECT      : NONE
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <MemoryManager.h>
#include <ctype.h>

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

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/


/*****************************************************************************!
 * Function : NorthwestCSVCreateTransaction
 *****************************************************************************/
NorthwestCSVTransaction*
NorthwestCSVCreateTransaction
()
{
  int                                   n;
  NorthwestCSVTransaction*              transaction;

  n = sizeof(NorthwestCSVTransaction);

  transaction = (NorthwestCSVTransaction*)GetMemory(n);
  memset(transaction, 0x00, n);
  return transaction;
}


/*****************************************************************************!
 * Function : NorthwestCSVTransactionFromLine
 *****************************************************************************/
NorthwestCSVTransaction*
NorthwestCSVTransactionFromLine
(string InLine)
{
  string                                start;
  string                                s;
  string                                b;
  int                                   n;
  NorthwestCSVTransaction*              transaction;
  if ( NULL == InLine ) {
    return NULL;
  }

  transaction = NorthwestCSVCreateTransaction();

  b = InLine;

  b++;
  start = b;
  while (*b != '"') {
    b++;
  }
  n = b - start;
  transaction->AccountNumber = StringNCopy(start, n);

  b += 2;

  //! Get the Post Date
  start = b;
  while (*b != ',' ) {
    b++;
  }
  n = b - start;
  transaction->PostData = StringNCopy(start, n);
  b++;

  //! Get the Check Number (if there is one)
  if ( isdigit(*b) ) {
    start = b;
    while (*b != ',') {
      b++;
    }
    n = b - start;
    s = StringNCopy(start, n);
    transaction->CheckNumber = atoi(s);
    FreeMemory(s);
  }

  //! Get Description
  b += 2;
  start = b;
  while (*b != '"' ) {
    b++;
  }
  n = b - start;
  transaction->Description = StringNCopy(start, n);
  b += 2;

  //! Check for a Debit Transaction
  if ( *b != ',' ) {
    start = b;
    while ( *b != ',' ) {
      b++;
    }

    n = b - start;
    s = StringNCopy(start, n);
    transaction->DebitAmount = atof(s);
    FreeMemory(s);
  }
  b++;

  //! Check for a Credit Transaction
  if ( *b != ',' ) {
    start = b;
    while ( *b != ',' ) {
      b++;
    }

    n = b - start;
    s = StringNCopy(start, n);
    transaction->CreditAmount = atof(s);
    FreeMemory(s);
  }
  b++;

  //! Get the status
  start = b;
  while ( *b != ',' ) {
    b++;
  }
  n = b - start;
  transaction->Status = StringNCopy(start, n);
  b++;

  //! Get the Balance
  start = b;
  while ( *b != ',' ) {
    b++;
  }
  
  n = b - start;
  s = StringNCopy(start, n);
  transaction->Balance = atof(start);
  FreeMemory(s);
  b+= 2;

  //! Get the Category
  start = b;
  while ( *b != '"' ) {
    b++;
  }
  n = b - start;
  
  transaction->Category = StringNCopy(start, n);
  return transaction;
}


/*****************************************************************************!
 * Function : NorthwestCSVTransactionListCreate
 *****************************************************************************/
NorthwestCSVTransactionList*
NorthwestCSVTransactionListCreate
()
{
  int                                   n;
  NorthwestCSVTransactionList*          list;

  n = sizeof(NorthwestCSVTransactionList);
  list = (NorthwestCSVTransactionList*)GetMemory(n);
  memset(list, 0x00, n);
  return list;
}


/*****************************************************************************!
 * Function : NorthwestCSVTransactionListFromStrings
 *****************************************************************************/
NorthwestCSVTransactionList*
NorthwestCSVTransactionListFromStrings
(StringList* InStrings)
{
  int                                   i;
  string                                line;
  NorthwestCSVTransaction*              trans;
  NorthwestCSVTransactionList*          list;

  list = NorthwestCSVTransactionListCreate();

  for ( i = 1; i < InStrings->stringCount; i++ ) {
    line = InStrings->strings[i];
    trans = NorthwestCSVTransactionFromLine(line);
    NorthwestCSVTransactionListAppend(list, trans);
  }
  return list;
}

/*****************************************************************************!
 * Function : NorthwestCSVTransactionDump
 *****************************************************************************/
void
NorthwestCSVTransactionDump
(NorthwestCSVTransaction* InTransaction)
{
  if ( NULL == InTransaction ) {
    return;
  }

  printf("  Account Number : %s\n", InTransaction->AccountNumber);
  printf("Transaction Date : %s\n", InTransaction->PostData);
  printf("    Check Number : %d\n", InTransaction->CheckNumber);
  printf("     Description : %s\n", InTransaction->Description);
  printf("    Debit Amount : %.02f\n", InTransaction->DebitAmount);
  printf("   Credit Amount : %.02f\n", InTransaction->CreditAmount);
  printf("          Status : %s\n", InTransaction->Status);
  printf("         Balance : %.02f\n", InTransaction->Balance);
  printf("        Category : %s\n", InTransaction->Category);
}

/*****************************************************************************!
 * Function : NorthwestCSVTransactionListCount
 *****************************************************************************/
int
NorthwestCSVTransactionListCount
(NorthwestCSVTransactionList* InList)
{
  int                                   count;
  NorthwestCSVTransaction*              trans;
  if ( NULL == InList ) {
    return 0;
  }

  count = 0;
  for ( trans = InList->head; trans ; trans = trans->next) {
    count++;
  }
  return count;
}


/*****************************************************************************!
 * Function : NorthwestCSVTransactionListAppend
 *****************************************************************************/
void
NorthwestCSVTransactionListAppend
(NorthwestCSVTransactionList* InList, NorthwestCSVTransaction* InTransaction)
{
  if ( NULL == InList || NULL == InTransaction ) {
    return;
  }

  if ( InList->head == NULL ) {
    InList->head = InTransaction;
  }
  if ( InList->tail != NULL ) {
    InList->tail->next = InTransaction;
  }
  InTransaction->prev = InList->tail;
  InList->tail = InTransaction;
}

/*****************************************************************************!
 * Function : NorthwestCSVTransactionListGet
 *****************************************************************************/
NorthwestCSVTransaction*
NorthwestCSVTransactionListGet
(NorthwestCSVTransactionList* InList, int InIndex)
{
  NorthwestCSVTransaction*              trans;
  int                                   i;

  
  trans = InIndex > 0 ? InList->head : InList->tail;
  i = abs(InIndex);
  while ( --i > 0 ) {
    trans = InIndex > 0 ? trans->next : trans->prev;
  }
  return trans;
}

