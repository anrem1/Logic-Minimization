#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>

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
	if (!regex_match(expression, regex("^([\\(][a-z][']?([\\+][a-z][']?)*[\\)](\\*[\\(][a-z][']?([\\+][a-z][']?)+[\\)]))"))) {			
			return false;
        }				
}


int cntDistinct(string str)
{
    unordered_set<char> s;  
    for (int i = 0; i < str.size(); i++) {
        s.insert(str[i]);
    }

    return s.size();
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

vector<string> ToCanonicalSop(string &sopExpression) {
	vector <string> product; 
	int k, i = 0;
	char c;
	string pstorage = "";
	int iteration_number = count(sopExpression.begin(), sopExpression.end(), '+') + 1;

		for (string::iterator it=sopExpression.begin(); it!=sopExpression.end(); ++it)
		 {
		 	if(sopExpression.at(k) != '+') {		
			 	if(sopExpression.at(k) == '\'')	{
			 		k++;
			}
				else {
				pstorage += sopExpression.at(k);	   // store each product in string (separated by +)
					k++; 
				}
			}
			else {
			k++;
			i++;
			product.push_back(pstorage);
			pstorage = "";														// try to match elements in string, if they don't match add missing variables
	}
	
}
	product.push_back(pstorage);	
	
//	return product;			
																				// compare between strings, if contain different elements, add them to each string	
																								
}
								

void trutht(std::string sopExpression) {
	int n = cntDistinct(sopExpression);		// number of variables
	int outputs = pow(2, n);				// number of outputs in truth table
	
	return;
	// make all sop's 1 and everything else 0 
	
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
    
  /*  if (validateBooleanExpression(sopExpression)) {
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
	else 	cout << "Invalid Format" << endl; */
	
	vector <string> v;
	
//	v = ToCanonicalSop(sopExpression);
//	cout << v;
	
    return 0;
}
