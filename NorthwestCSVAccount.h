/*****************************************************************************!
 * Exported Type : NorthwestCSVAccount
 *****************************************************************************/
#ifndef _northwestcsvaccount_h_
#define _northwestcsvaccount_h_
struct _NorthwestCSVAccount
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
  struct _NorthwestCSVAccount*          next;
};
typedef struct _NorthwestCSVAccount NorthwestCSVAccount;
#endif // _northwestcsvaccount_h_
