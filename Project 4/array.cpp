#include <iostream>
#include <cstring>  // Notice this is NOT <string>; we need it because
                    // isValidUppercaseStateCode uses std::strstr
#include <cctype>
#include <cassert>
using namespace std;

bool isValidUppercaseStateCode(const char stateCode[]);

bool hasValidSyntax(const char orders[])
{
        // An empty order string is well-formed.
          if (strcmp(orders, "\0") == 0)
          return true;

            // Each iteration of the loop recognizes one state order
          int k = 0;
          while (orders[k] != '\0')
          {
            // The order must start with two letters

          if (! isalpha(orders[k]))
              return false;
              
          k++;
          if (orders[k] == '\0' ||  ! isalpha(orders[k]))
              return false;
          k++;

            // Those letters must be the code for a state

          char state[3];
              for (int i = 0; i < 3; i++)
              {
                  if (i == 0)
                  state[i] = orders[k - 2];
                  else if (i == 1)
                      state[i] = orders[k - 1];
                  else
                      state[i] = '\0';
              }
          state[0] = toupper(state[0]);
          state[1] = toupper(state[1]);
          if (!isValidUppercaseStateCode(state))
              return false;

            // The state code must be a followed by a digit

          if (orders[k] == '\0'  ||  ! isdigit(orders[k]))
              return false;
          k++;

            // There might be more digits

          while (orders[k] != '\0' &&  isdigit(orders[k]))
              k++;

            // There must be a status code

          if (orders[k] == '\0' ||  (orders[k] != '+'  &&  orders[k] != '-'))
              return false;
          k++;
      }
          return true;

}


int countCases(const char orders[], char status, int& caseCount)
{
    // Define return values

    const int RET_OK              = 0;
    const int RET_BAD_SYNTAX      = 1;
    const int RET_BAD_STATE_ORDER = 2;
    const int RET_BAD_STATUS      = 3;

      // A bad status character prevents counting

    if (status != '+'  &&  status != '-')
    return RET_BAD_STATUS;

      // An order string with incorrect syntax prevents counting

    if (!hasValidSyntax(orders))
    return RET_BAD_SYNTAX;

      // We will count cases in an int named result, and modify the caseCount
      // parameter only if processing the entire order string succeeds.

    int result = 0;

      // Each iteration of the loop deals with one state order.  Since we
      // know at this point the order string has correct syntax, we are
      // guaranteed there are digits, etc.

    int k = 0;
    while (orders[k] != '\0')
    {
      // Skip over the state code (we know there must be one)

    k += 2;

      // Determine the state case count

    int stateCaseCount = 0;
    while (isdigit(orders[k]))  // we know there's at least one digit
    {
        stateCaseCount = 10 * stateCaseCount + orders[k] - '0';
        k++;
    }

      // The state order must not specify zero cases

    if (stateCaseCount == 0)
        return RET_BAD_STATE_ORDER;

      // If the status code (we know there must be one) matches, record
      // the cases

    if (orders[k] == status)
        result += stateCaseCount;
    k++;
    }

      // We've successfully processed the entire string, so set caseCount.

    caseCount = result;

    return RET_OK;
}

bool isValidUppercaseStateCode(const char stateCode[])
{
    const char codes[] =
       "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.GU.HI.ID.IL.IN.IA.KS."
       "KY.LA.ME.MD.MA.MI.MN.MS.MO.MP.MT.NE.NV.NH.NJ.NM.NY.NC."
       "ND.OH.OK.OR.PA.PR.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    for (int k = 0; k != '\0'; )
    {
        if (stateCode[0] == codes[k] && stateCode[1] == codes[k + 1])
            return(isupper(stateCode[0])  &&  isupper(stateCode[1])  &&
            stateCode[2] == '\0'  &&  strstr(codes, stateCode) != nullptr && true);
        else
            return (isupper(stateCode[0])  &&  isupper(stateCode[1])  &&
            stateCode[2] == '\0'  &&  strstr(codes, stateCode) != nullptr && false);
    }
    
    return (isupper(stateCode[0])  &&  isupper(stateCode[1])  &&
            stateCode[2] == '\0'  &&  strstr(codes, stateCode) != nullptr);
}


int main()
{
    assert(hasValidSyntax("TX38-CA132+Ms6-nY290-UT006+MS8+CA15+"));
    assert(!hasValidSyntax("MX38-CA132+"));
    int cases;
    cases = -999;    // so we can detect whether countCases sets cases
    assert(countCases("TX38-CA132+Ms6-nY290-UT006+MS8+CA15+", '+', cases) == 0  &&  cases == 161);
    cases = -999;    // so we can detect whether countCases leaves cases unchanged
    assert(countCases("TX38-CA132+", '%', cases) == 3  &&  cases == -999);
    cout << "All tests succeeded" << endl;
}
