#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>
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

bool Sop(string expression) {
	if (!regex_match(expression, regex("^[a-z'\\s+]+"))) {		// ab+cd      			// should not accept '' , should not end in +
			return false;
        }
}


bool Pos(string expression) {
	if (!regex_match(expression, regex("\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\)(\\*\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\))*"))) {			
			return false;
        }
		return true;				
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
	

void trutht(std::string expression) {
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
	int n = vars.size();
	set<int> :: iterator it;
	int outputs = pow(2, n);				// number of outputs in truth table
	int rows = outputs;
	int columns = n;
	for (auto it = vars.begin(); it!=vars.end();it++)
    {
        cout<<*it << "\t";							// display variables 
    }
	cout << "Output" << endl;

	vector<vector<int>> output(n, vector<int>(1 << n));

    unsigned num_to_fill = 1U << (n - 1);									// fill truth table 
    for(unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
    {
        for(unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
        {
            std::fill_n(&output[col][row], num_to_fill, 1);
        }
    }
    for(unsigned x = 0; x < (1 << n); ++x)
    {
        for(unsigned y = 0; y < n; ++y)
        {
            cout << output[y][x] << "\t";
        }
        cout << endl;
    }
	
	return;	
} 


int main() {
   string sopExpression;
   cin >> sopExpression;
   string posExpression;

	getline(std::cin, posExpression);
	getline(std::cin, posExpression);

	
for (auto& x : sopExpression) { 
        x = tolower(x); 
    } 
for (auto& x : posExpression) { 
        x = tolower(x); 
    } 
    
    if (validateBooleanExpression(sopExpression)) {
    	if(Sop(sopExpression)) {
        cout << "'" << sopExpression << "' is a valid SoP expression." << endl;
    } else {
        cout << "'" << sopExpression << "' is not a valid SoP expression." << endl;
    }
}
	else cout << "Invalid Format" << endl;

    if (validateBooleanExpression(posExpression)) { 
    	if(Pos(posExpression)) {
        cout << "'" << posExpression << "' is a valid PoS expression." << endl;
    }   else {
        cout << "'" << posExpression << "' is not a valid PoS expression." << endl;
    } 
}
	else 	cout << "Invalid Format" << endl; 
	
trutht(sopExpression);
trutht(posExpression);

	
    return 0;
}
