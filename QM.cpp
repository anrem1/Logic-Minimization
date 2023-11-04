#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>
#include <stack>
#include <set>

using namespace std; 


bool validateBooleanExpression(const string& expression) {
    // Check for valid characters
    if (!regex_match(expression, regex("^[a-z()+*\\s']+"))) { 
        return false; 
    } 

    // Check for balanced parentheses
    int openParentheses = 0;
    int closeParentheses = 0;
    for (char c : expression) {
        if (c == '(') {
            openParentheses++;
        } else if (c == ')') {
            closeParentheses++;
        }
    }
    if (openParentheses != closeParentheses) { 
        return false;
    }

    // Check for valid operator usage
    if (expression.find("**") != string::npos || expression.find("++") != string::npos) {		// add +* or *+  or var * or * var or +var+ or aa etc.
        return false;
    }																				
    return true;
} 

bool Sop(string expression) {																			// should not accept '' , should not end in +
        return (regex_match(expression, regex("^[a-z'*\\s+]+")));
}


bool Pos(string expression) {
	return(regex_match(expression, regex("\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\)(\\*\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\))*")));			
}

ostream& operator<<(ostream& os,
                    const vector<string>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}

// Function to evaluate a Boolean expression
bool evaluateExpression(const string& expression, const vector<bool>& inputValues) {
    string evaluatedExpression = expression;
    for ( int i = 0; i < inputValues.size(); i++) {
        char variable = 'a' + i;
         int pos = evaluatedExpression.find(variable);
        while (pos != string::npos) {
            evaluatedExpression.replace(pos, 1, inputValues[i] ? "1" : "0");
            pos = evaluatedExpression.find(variable, pos + 1);
        }
    }

    stack<bool> operandStack;
    stack<char> operatorStack;

    for (char c : evaluatedExpression) {
        if (c == '0' || c == '1') {
            operandStack.push(c - '0');
        } else if (c == '+' || c == '*') {
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        bool operand1 = operandStack.top();
        operandStack.pop();
        bool operand2 = operandStack.top();
        operandStack.pop();

        if (op == '+') {
            operandStack.push(operand1 || operand2);
        } else if (op == '*') {
            operandStack.push(operand1 && operand2);
        }
    }

    return operandStack.top();
}


// Function to generate a truth table from a Boolean expression
vector<vector<bool>> generateTruthTable(const string& expression, int numVariables) {
    int numRows = pow(2, numVariables);
    vector<vector<bool>> truthTable;
    vector<bool> inputValues(numVariables, false);
	
	for (int i = 0; i < numVariables; i++) {
        cout << char('a' + i) << "\t";
    }
    cout << "Result" << endl;
    
    for (int row = 0; row < numRows; row++) {
        // Set the input values for this row
        for (int var = 0; var < numVariables; var++) {
            inputValues[var] = (row >> var) & 1;
            cout << inputValues[var] << "\t";
        }
	
        // Evaluate the expression for the input values
        bool result = evaluateExpression(expression, inputValues);
		cout << result;
		cout << endl;
        // Store the row in the truth table
        vector<bool> rowValues = inputValues;
        rowValues.push_back(result);
        truthTable.push_back(rowValues);
    }

    return truthTable;
}

// Function to get canonical SOP form
string getCanonicalSOP(const vector<vector<bool>>& truthTable, int numVariables) {
    string canonicalSOP = "";
    for (const vector<bool>& row : truthTable) {
        if (row[numVariables]) {
            if (!canonicalSOP.empty()) {
                canonicalSOP += " + ";
            }
            for (int i = 0; i < numVariables; i++) {
                if (row[i]) {
                    canonicalSOP += ('a' + i);
                } else {
                    canonicalSOP += ('a' + i);
                    canonicalSOP += '\'';
                }
            }
        }
    }
    return canonicalSOP;
}

// Function to get canonical POS form
string getCanonicalPOS(const vector<vector<bool>>& truthTable, int numVariables) {
    string canonicalPOS = "";
    for (const vector<bool>& row : truthTable) {
        if (!row[numVariables]) {
            if (!canonicalPOS.empty()) {
                canonicalPOS += " * ";
            }
            canonicalPOS += "(";
            for (int i = 0; i < numVariables; i++) {
                if (row[i]) {
                    canonicalPOS += ('a' + i);
                    canonicalPOS += '\'';
                } else {
                    canonicalPOS += ('a' + i);
                }
                if (i < numVariables - 1) {
                    canonicalPOS += " + ";
                }
            }
            canonicalPOS += ")";
        }
    }
    return canonicalPOS;
}		
    
    
    std::vector<std::string> get_minterms(const std::vector<std::vector<bool>>& truth_table) {
    std::vector<std::string> minterms;

    for (int row = 0; row < truth_table.size(); row++) {
        if (truth_table[row].back() == true) { // Check the last column for the result
            std::string minterm = "";
            for (int col = 0; col < truth_table[row].size() - 1; col++) {
                minterm += (truth_table[row][col] ? '1' : '0');
            }
            minterms.push_back(minterm);
        }
    }

    return minterms;
}

std::vector<std::string> get_maxterms(const std::vector<std::vector<bool>>& truth_table) {
    std::vector<std::string> maxterms;

    for (int row = 0; row < truth_table.size(); row++) {
        if (truth_table[row].back() == false) { // Check the last column for the result
            std::string maxterm = "";
            for (int col = 0; col < truth_table[row].size() - 1; col++) {
                maxterm += (truth_table[row][col] ? '1' : '0');
            }
            maxterms.push_back(maxterm);
        }
    }

    return maxterms;
}

// Function to check if two terms differ in only one bit
bool differByOneBit(const std::string& term1, const std::string& term2) {
    int differences = 0;
    for ( int i = 0; i < term1.size(); i++) {
        if (term1[i] != term2[i]) {
            differences++;
            if (differences > 1) {
                return false;
            }
        }
    }
    return differences == 1;
}

// Function to perform pair-wise comparisons of minterms and find prime implicants
std::vector<std::string> getPrimeImplicants(const std::vector<std::string>& minterms) {
    std::vector<std::string> primeImplicants;

    std::vector<std::string> currentTerms = minterms;
    std::vector<std::string> nextTerms;

    while (!currentTerms.empty()) {
        std::vector<bool> used(currentTerms.size(), false);

        for ( int i = 0; i < currentTerms.size(); i++) {
            if (used[i]) {
                continue;
            }

            for ( int j = i + 1; j < currentTerms.size(); j++) {
                if (differByOneBit(currentTerms[i], currentTerms[j])) {
                    used[i] = true;
                    used[j] = true;

                    // Create a new term with a dash in the differing bit
                    std::string combinedTerm = currentTerms[i];
                    for ( int k = 0; k < currentTerms[i].size(); k++) {
                        if (currentTerms[i][k] != currentTerms[j][k]) {
                            combinedTerm[k] = '-';
                        }
                    }
                    nextTerms.push_back(combinedTerm);
                }
            }
        }

        for ( int i = 0; i < currentTerms.size(); i++) {
            if (!used[i]) {
                primeImplicants.push_back(currentTerms[i]);
            }
        }

        currentTerms = nextTerms;
        nextTerms.clear();
    }

    return primeImplicants;
}

void displayMinterms(const vector<string>& primeImplicants) {
    cout << "Prime Implicants and Their Covered minterms:" << endl;
    for ( int i = 0; i < primeImplicants.size(); i++) {
        cout << primeImplicants[i] << ": ";

        // Calculate the minterms covered by the prime implicant
        for ( int j = 0; j < primeImplicants[i].size(); j++) {
            if (primeImplicants[i][j] == '0') {
                cout << (char)('a' + j) << "'";
            } else if (primeImplicants[i][j] == '1') {
                cout << (char)('a' + j);
            }

            if (j < primeImplicants[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}
string binaryToLetters(const string& binaryRepresentation) {
    string letters;
    for ( int i = 0; i < binaryRepresentation.size(); i++) {
        if (binaryRepresentation[i] == '0') {
            letters += char('a' + i) + "'";
        } else if (binaryRepresentation[i] == '1') {
            letters += char('a' + i);
        }
    }
    return letters;
}

string lettersToBinary(const string& lettersExpression) {
    string binaryRepresentation;
    for ( int i = 0; i < lettersExpression.size(); i++) {
        char currentChar = lettersExpression[i];
        if (currentChar >= 'a' && currentChar <= 'z') {
            // It's a variable (e.g., a or a')
            binaryRepresentation += (currentChar != '\'') ? '1' : '0';
        }
        // You can add more conditions for other characters if needed
    }
    return binaryRepresentation;
}

// Function to check if an implicant covers a minterm
bool covers(const string& minterm, const string& prime_implicant) {
    for ( int i = 0; i < minterm.size(); i++) {
        if (minterm[i] != '-' && minterm[i] != prime_implicant[i]) {
            return false;
        }
    }
    return true;
}

// Function to create a cover chart of prime implicants and minterms
vector<vector<string>> create_coverchart(
    const vector<string>& prime_implicants,
    const vector<string>& minterms
) {
    vector<vector<string>> cover_chart(minterms.size() + 1, vector<string>(prime_implicants.size() + 1, ""));

    // Label the columns (prime implicants)
    for ( int j = 1; j < cover_chart[0].size(); j++) {
        cover_chart[0][j] = prime_implicants[j - 1];
    }

    // Label the rows (minterms)
    for ( int i = 1; i < cover_chart.size(); i++) {
        cover_chart[i][0] = minterms[i - 1];
    }

    // Fill in the chart based on coverage
    for ( int i = 1; i < cover_chart.size(); i++) {
        for ( int j = 1; j < cover_chart[0].size(); j++) {
            // Check if the prime implicant covers the minterm
            if (covers(minterms[i - 1], prime_implicants[j - 1])) {
                cover_chart[i][j] = "X"; // Use "1" to indicate coverage
            }
        }
    }

    return cover_chart;
}

// Function to print the cover chart
void print_coverchart(const vector<vector<string>>& cover_chart) {
    for ( int i = 0; i < cover_chart.size(); i++) {
        for ( int j = 0; j < cover_chart[0].size(); j++) {
            cout << cover_chart[i][j] << '\t';
        }
        cout << endl;
    }
}

// Function to get essential primes from the cover chart
vector<string> getEssentialPrimes(const vector<vector<string>>& coverChart) {
    vector<string> essentialPrimes;
    vector<bool> coveredMinterms(coverChart[0].size(), false);

    for ( int j = 0; j < coverChart[0].size(); j++) {
        int count = 0;
        int lastRowIndex = -1;
        for ( int i = 0; i < coverChart.size(); i++) {
            if (!coveredMinterms[j] && !coverChart[i][j].empty()) {
                count++;
                lastRowIndex = i;
            }
        }

        if (count == 1) {
            if (!coveredMinterms[j]) {
                essentialPrimes.push_back(coverChart[lastRowIndex][j]);
                for ( int i = 0; i < coverChart.size(); i++) {
                    if (!coverChart[i][j].empty()) {
                        coveredMinterms[j] = true;
                        break;
                    }
                }
            }
        }
    }
    return essentialPrimes;
}

// Function to check if a prime implicant covers a minterm
bool covers2(const string& minterm, const string& prime_implicant) {
    for ( int i = 0; i < minterm.size(); i++) {
        if (minterm[i] != '-' && minterm[i] != prime_implicant[i]) {
            return false;
        }
    }
    return true;
}

// Function to print minterms not covered by essential PIs
void print_uncovered_minterms(
    const vector<string>& essential_pis,
    const vector<string>& minterms
) {
    set<string> covered_midterms;

    // Collect the minterms covered by essential PIs
    for (const string& pi : essential_pis) {
        for (const string& minterm : minterms) {
            if (covers2(minterm, pi)) {
                covered_midterms.insert(minterm);
            }
        }
    }

    cout << "Minterms not covered by essential Prime Implicants:" << endl;
    
    for (const string& minterm : minterms) {
        if (covered_midterms.find(minterm) == covered_midterms.end()) {
            cout << minterm << endl;
        }
    }
}

void run(string expression) {
	
   // cout << "Enter the number of variables: ";
//    cin >> numVariables;
 //   cin.ignore();  // Clear the newline character from the buffer
	
	
	set<char> vars;	
	int k = 0;
	while(expression[k] != '\0') {
		if(expression[k] != '+' && expression[k] != '(' && expression[k] != ')' && expression[k] != '*' && expression[k] != '\'') {
				vars.insert(expression[k]);												// put variables only once in set  
				k++;
		}
		else
		k++;
	}
	int numVariables = vars.size();
	
 //   cout << "Enter the Boolean expression in SOP or POS form: ";
//	getline(cin, expression);
	
	for (auto& x : expression) { 
	        x = tolower(x); 
	    } 
	for (auto& x : expression) { 
	        x = tolower(x); 
  	    } 
    
    if (validateBooleanExpression(expression)) {
    	if(Sop(expression)) {
        cout << "'" << expression << "' is a valid SoP expression." << endl;
    } else {
        cout << "'" << expression << "' is not a valid SoP expression." << endl;
    }
}
	else cout << "Invalid Format" << endl;

    if (validateBooleanExpression(expression)) { 
    	if(Pos(expression)) {
        cout << "'" << expression << "' is a valid PoS expression." << endl;
    }   else {
        cout << "'" << expression << "' is not a valid PoS expression." << endl;
    } 
}
	else 	cout << "Invalid Format" << endl;  
	
	if(Sop(expression) || Pos(expression)) {

	vector<vector<bool>> truthTable = generateTruthTable(expression, numVariables);
	string canonicalSOP = getCanonicalSOP(truthTable, numVariables);
    string canonicalPOS = getCanonicalPOS(truthTable, numVariables);

    cout << "Canonical SOP Form: " << canonicalSOP << endl;
    cout << "Canonical POS Form: " << canonicalPOS << endl;


std::vector<std::string> minterms = get_minterms(generateTruthTable(expression, numVariables));

    std::cout << "Minterms: ";
    for (const std::string& minterm : minterms) {
        std::cout << minterm << " ";
    }
    std::cout << std::endl;

std::vector<std::string> maxterms = get_maxterms(generateTruthTable(expression, numVariables));
std::cout << "Maxterms: ";
    for (const std::string& maxterm : maxterms) {
        std::cout << maxterm << " ";
    }
    std::cout << std::endl;
	
	std::vector<std::string> primeImplicants = getPrimeImplicants(minterms);

    std::cout << "Prime Implicants: ";
    for (const std::string& term : primeImplicants) {
        std::cout << term << " ";
    }
    std::cout << std::endl;
	
	displayMinterms(primeImplicants);
	
    
    string binaryRepresentation = lettersToBinary(expression);

    cout << "Binary Representation: " << binaryRepresentation << endl;
    
 
   vector<vector<string>> cover_chart = create_coverchart(primeImplicants, minterms);
    vector<string> essential_primes = getEssentialPrimes(cover_chart);

    print_coverchart(cover_chart);
    
    for (const string& implicant : essential_primes) {
    	string letterexp = binaryToLetters(implicant);
    	cout << "essential: " << letterexp << endl;
    }
    
    print_uncovered_minterms(essential_primes, minterms);
}
}

int main() {

	string test_case[10] = {"a*b", "a+b", "a*b+c", "a*b*c*d*e", "a+bc", "(ab+c)", "a'+b", "a++b", "(a+b", "a+b*c+d*e+f"};
	
	for(int i = 0; i<10; i++) {
		run(test_case[i]);
		cout << endl; 
		cout << endl;
		cout << endl;
	}
	

    
    return 0;
}
