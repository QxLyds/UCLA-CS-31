#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isValidUppercaseStateCode(string stateCode, int& j);
bool hasValidSyntax(string orders);
int countCases(string orders, char status, int& caseCount);
bool noOrders(string orders, int& zero);
int sumCases(string orders, char status, int& pos);

int main(){
    cerr << "Enter Order String: " << endl;
    string os;
    getline(cin, os);
    cerr << "Enter Status: " << endl;
    char status;
    cin >> status;
    
    //Check hasValidSyntax function
    if (!hasValidSyntax(os))
    {
        cerr << "wrong syntax" << endl;
    } else
        cerr << "right syntax" << endl;
    
    //Check countCases function
    int cases = 0;
       switch (countCases(os, status, cases))
           {
               case 0:
                  cerr << "correct" << endl;
                   cerr << cases << endl;
                   break;
               case 1:
                   cerr << "not valid syntax" << endl;
                   break;
               case 2:
                   cerr << "state has no order " << endl;
                   break;
               case 3:
                   cerr << "not right status" << endl;
                   break;
           }

}


//Valid State Code
bool isValidUppercaseStateCode(string stateCode, int& j)
{
    j += 2;
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.GU.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MP.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.PR.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
               
}


//Syntax Check
bool hasValidSyntax(string orders)
{
    //Capitalize String
    for (int i = 0; i != orders.size(); i++ )
       {
           orders[i] = toupper(orders[i]);
       }
    
   //Check for empty string
    if (orders == "")
               return true;
    
    //Ends with order status
    if (orders.back() != '+' && orders.back() != '-')
           return false;
    
    for (int k = 0; k < orders.size() ; k++)
    {
        //Check for Space
        if (isspace(orders.at(k)))
        {
            return false;
        }
        
        //Check for correct State code
        if (isalpha(orders.at(k)))
        {
            string state = (orders.substr(k, 2));
            //cerr << state << endl;
            if (!isValidUppercaseStateCode(state, k ))
            {
                return false;
            }
        
        }
            //Checks for Status
        if ((isdigit(orders.at(k))))
        {
            if (orders.at(k + 1) != '+'  &&  orders.at(k + 1) != '-' && !isdigit(orders.at(k + 1)))
            {
                       return false;
            }
        }

    }
    return true;
}


int countCases(string orders, char status, int& caseCount)
{
    //Check Valid Syntax
    if (!hasValidSyntax(orders))
        return 1;
    //Check Valid Status
    if (status != '+' && status != '-')
        return 3;
    //Check zero order
    if (orders.size()== 0)
    {
        caseCount = 0;
        return 0;
    }
    
    // check for State with no orders
    int i = 0;
    while (i != orders.size())
    {
        if (isdigit(orders.at(i)))
        {
            if (noOrders(orders, i))
            {
                return 2;
            }
        }
        i++;
    }
    
//Sum up same status cases
    int x = 0;
    int k = 0;
    while (k != orders.size())
    {
        if (isdigit(orders.at(k)))
        {
            x += sumCases(orders, status, k);
        }
        caseCount = x;
        k++;
    }
    return 0;
}

//check if state has no orders
bool noOrders(string orders, int& zero)
{
    int y = 0;
   string temp;
     for (temp = ""; isdigit(orders.at(zero)); zero++)
         temp += orders.at(zero);
        if (orders.at(zero) == '+' || orders.at(zero) == '-')
        {
            y = stoi(temp);
        }
    if (y == 0)
    {
        return true;
    }
    return false;
}



//Sums orders with same status
int sumCases(string orders, char status, int& pos)
{
    int cases = 0;
    string distance;
    for (distance = ""; isdigit(orders.at(pos)); pos++)
        distance += orders.at(pos);
         if (orders.at(pos) == status)
         {
             cases = stoi(distance);
         }
    return cases;
}
