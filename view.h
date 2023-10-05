#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <vector>
#include <limits>
#include "operator.h"
#include "utils.h"

class View {
public:
    static string getOperatorNameFromUserInput(int operatorNumber);

    static int selectOperatorToSignPDF(vector<Operator>& operators);

    static int selectOperatorFromAll(string header, vector<Operator>& operators);

    static string getPDFpath();

    static int showMainMenu();

    static int showAllSignedMenu();

    static int askNumberOfOperators();

    static void displayOperatorInfo(int operatorNumber, const Operator& operatorInstance);

    static void displaySignedOperators(vector<Operator> operators);

    static void displaySimpleMessage(string message);
};

#endif // VIEW_H
