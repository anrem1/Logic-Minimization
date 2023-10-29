#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>
#include <set>
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
	if (!regex_match(expression, regex("\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\)(\\*\\([a-z]{1}[']?(\\+[a-z]{1}[']?)*\\))*"))) {			
			return false;
        }
		return true;				
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

vector<string> findAndPrintUncommonChars(string str1, string str2)
{
    // to store the answer
    string ans = "";
    string my_ans = "";
	string my_ans_2 = ""; 
      // to handle the case of duplicates
    vector<int> used(26, false);
 
    // check first for str1
    for (int i = 0; i < str1.size(); i++) {
        // keeping a flag variable
        bool found = false;
 
        for (int j = 0; j < str2.size(); j++) {
            // if found change the flag
            // and break from loop
            if (str1[i] == str2[j]) {
                found = true;
                break;
            }
        }
 
        // if duplicate character not found
        // then add it to ans
        if (!found && !used[str1[i] - 'a']) {
            used[str1[i] - 'a'] = true;
            ans += str1[i];
            my_ans += str1[i];
			}
    }
 
    // now check for str2
    for (int i = 0; i < str2.size(); i++) {
        // keeping a flag variable
        bool found = false;
 
        for (int j = 0; j < str1.size(); j++) {
            // if found change the flag
            // and break from loop
            if (str2[i] == str1[j]) {
                found = true;
                break;
            }
        }
 
        // if duplicate character not found
        // then add it to ans
        if (!found and !used[str2[i] - 'a']) {
            used[str2[i] - 'a'] = true;
            ans += str2[i];
            my_ans_2 += str2[i];
        }
    }
 
    // to match with output
    sort(ans.begin(), ans.end());
 
      // if not found any character
    if (ans.size() == 0)
        cout << "-1";
     
      // else print the answer
      else
      {
	  
        vector <string> missing;
        missing.push_back(my_ans);
        missing.push_back(my_ans_2);
        return missing; 
	}	
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
/*	string first_group;
	string second_group;
	vector<string> missing_vars;
	for(int j = 0; j<iteration_number /* how to loop? ; j++) {
		for(int r = 0; r< cntDistinct(product[r]) ; r++) {
			first_group =	product[j];
			second_group = product[j+1];
			sort(first_group.begin(), first_group.end());
			sort(second_group.begin(), second_group.end());
			if(first_group.compare(second_group) != 0) {
				missing_vars = findAndPrintUncommonChars(first_group, second_group);	
				product[j] = product[j] + missing_vars[1];
				product.insert(product.begin()+1, ???.begin(), ???.end());
				product[j+1] = product[j+1] + missing_vars[0];
			}
		}
	} */
	return product;			
																				// compare between strings, if contain different elements, add them to each string	
																								
}

	

void trutht(std::string sopExpression) {
	set<char> vars;	
	int k = 0;
	while(sopExpression[k] != '\0') {
		if(sopExpression[k] != '+' && sopExpression[k] != '(' && sopExpression[k] != ')' && sopExpression[k] != '*' && sopExpression[k] != '\'') {
				vars.insert(sopExpression[k]);
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

    unsigned num_to_fill = 1U << (n - 1);
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
	
	vector <string> v;
	
//ToCanonicalSop(sopExpression);
//	cout << v;

trutht(sopExpression);

 const unsigned n = 10;
    
//v = findAndPrintUncommonChars(a, b);
//cout << v;
	
    return 0;
}
