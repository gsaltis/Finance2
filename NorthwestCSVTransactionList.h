/*****************************************************************************!
 * Exported Type : NorthwestCSVTransactionList
 *****************************************************************************/
#ifndef _northwestcsvtransactionlist_h_
#define _northwestcsvtransactionlist_h_
struct _NorthwestCSVTransactionList
{
  NorthwestCSVTransaction*              head;
  NorthwestCSVTransaction*              tail;
};
typedef struct _NorthwestCSVTransactionList NorthwestCSVTransactionList;
#endif // _northwestcsvtransactionlist_h_
