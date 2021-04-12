/*****************************************************************************!
 * Exported Type : NorthwestCSVTransaction
 *****************************************************************************/
#ifndef _northwestcsvtransaction_h_
#define _northwestcsvtransaction_h_
struct _NorthwestCSVTransaction
{
  string                                AccountNumber;
  string                                PostData;
  uint16_t                              CheckNumber;
  string                                Description;
  double                                DebitAmount;
  double                                CreditAmount;
  string                                Status;
  double                                Balance;
  string                                Category;
  struct _NorthwestCSVTransaction*      next;
  struct _NorthwestCSVTransaction*      prev;
};
typedef struct _NorthwestCSVTransaction NorthwestCSVTransaction;
#endif // _northwestcsvtransaction_h_
