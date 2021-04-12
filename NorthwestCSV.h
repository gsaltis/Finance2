/*****************************************************************************
 * FILE NAME    : NorthwestCSV.h
 * DATE         : April 11 2021
 * PROJECT      : NONE
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _northwestcsv_h_
#define _northwestcsv_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <StringUtils.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NorthwestCSVTransaction.h"
#include "NorthwestCSVTransactionList.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
NorthwestCSVTransactionListAppend
(NorthwestCSVTransactionList* InList, NorthwestCSVTransaction* InTransaction);

int
NorthwestCSVTransactionListCount
(NorthwestCSVTransactionList* InList);

void
NorthwestCSVTransactionDump
(NorthwestCSVTransaction* InTransaction);

NorthwestCSVTransactionList*
NorthwestCSVTransactionListFromStrings
(StringList* InStrings);

NorthwestCSVTransactionList*
NorthwestCSVTransactionListCreate
();

NorthwestCSVTransaction*
NorthwestCSVTransactionFromLine
(string InLine);

NorthwestCSVTransaction*
NorthwestCSVCreateTransaction
();

NorthwestCSVTransaction*
NorthwestCSVTransactionListGet
(NorthwestCSVTransactionList* InList, int InIndex);

#endif // _northwestcsv_h_
