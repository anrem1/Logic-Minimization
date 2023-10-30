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

bool Sop(string expression) {																			// should not accept '' , should not end in +
        return (regex_match(expression, regex("^[a-z'\\s+]+")));
}


bool Pos(string expression) {
	return(regex_match(expression, regex("\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\)(\\*\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\))*")));
	/*	if (!regex_match(expression, regex("\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\)(\\*\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\))*"))) {			
			return false;
        }
		return true; */				
}

ostream& operator<<(ostream& os, const vector<string>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}
	
	vector<string> Products(string &sopExpression) {
	vector <string> product; 
	int k, i = 0;
	string pstorage = "";
	int iteration_number = count(sopExpression.begin(), sopExpression.end(), '+') + 1;

		for (string::iterator it=sopExpression.begin(); it!=sopExpression.end(); ++it)
		 {
		 	if(sopExpression.at(k) != '+') {		
				pstorage += sopExpression.at(k);	   // store each product in string (separated by +)
					k++; 
				
			}
			else {
			k++;
			i++;
			product.push_back(pstorage);
			pstorage = "";													
	}
	
}
product.push_back(pstorage);	
		return product;		
}

vector<string> Sums(string &posExpression) {
	vector <string> sum; 
	int k, i = 0;
	string sstorage = "";
	int iteration_number = count(posExpression.begin(), posExpression.end(), '+') + 1;

		for (string::iterator it=posExpression.begin(); it!=posExpression.end(); ++it)
		 {
		 	if(posExpression.at(k) != '*') {		
			 	if(posExpression.at(k) == '(' || posExpression.at(k) == ')')	{
			 		k++;
			}
				else {
				sstorage += posExpression.at(k);	   // store each sum in string (separated by +)
					k++; 
				}
			}
			else {
			k++;
			i++;
			sum.push_back(sstorage);
			sstorage = "";														
	}
	
}
	sum.push_back(sstorage);	
		return sum;			
}

/*void bool_func::set_canonical_sop() {

    sop.reserve(minterms.size());

    char product[11];
    int len;
    for (auto u : minterms) {
        len = 0;
        for (int i = 0; i < get_var_count(); ++i) {
            product[len++] = char(i + ((u & (1 << i)) ? 'a' : 'A'));
        }
        product[len] = 0;
        sop.emplace_back(product);
    }
} */

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

	vector<char> row1;
	char c;

	for (auto it = vars.begin(); it!=vars.end();it++)
    {						
       cout << *it << "\t";
	    c = *it;
        row1.push_back(c);							// store variables into first row
    }
 
	vector<int> col(outputs, 0);								// column for output
	cout << 'Y';
																				
	vector<vector<int>> output(n, vector<int>(1 << n));
		
    unsigned num_to_fill = 1U << (n - 1);									// fill truth table 
    for(unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
    {
        for(unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
        {
            fill_n(&output[col][row], num_to_fill, 1);						// *** fix: put 0 
        }
    }																			// add another loop that puts 0 into table when it's not ==1 (before adding extra row & colum)
	   
	output.push_back(col);								// append output column

 														
    cout << endl;
    for (unsigned x = 0; x < (1 << n); ++x) { 
        for (unsigned y = 0; y<(n+1); ++y) {
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

//	getline(std::cin, posExpression);				// can make this cin if you specify in the beginning user can't add spaces
//	getline(std::cin, posExpression);

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

  /*  if (validateBooleanExpression(posExpression)) { 
    	if(Pos(posExpression)) {
        cout << "'" << posExpression << "' is a valid PoS expression." << endl;
    }   else {
        cout << "'" << posExpression << "' is not a valid PoS expression." << endl;
    } 
}
	else 	cout << "Invalid Format" << endl;  */
	
trutht(sopExpression);
cout << endl;
//trutht(posExpression);

	
    return 0;
}
