#include<iostream>
#include<string>
#include<math.h>
using namespace std;

class BigInt{
	string value;
	char sign;

public:

	//constructors
	BigInt();
	BigInt(BigInt&);
	BigInt(const long long&);
	BigInt(string&);

	//assignment operators
	BigInt& operator=(BigInt&);
	BigInt& operator=(long long&);
	BigInt& operator=(string&);
 	
 	//unary
 	BigInt operator+();   // unary +
    BigInt operator-(); 

    //Arithmetic
	BigInt operator+(BigInt&);
	BigInt operator-(BigInt&);
	BigInt operator*(BigInt&);
	BigInt operator/(BigInt&);
	BigInt operator%(BigInt&);
	BigInt operator+(long long&);
	BigInt operator-(long long&);
	BigInt operator*(long long&);
	BigInt operator/(long long&);
	BigInt operator%(long long&);
	BigInt operator+(std::string&);
	BigInt operator-(std::string&);
	BigInt operator*(std::string&);
	BigInt operator/(std::string&);
	BigInt operator%(std::string&);

	//Arithmetic assignment
	BigInt operator+=(BigInt&);
	BigInt operator-=(BigInt&);
	BigInt operator*=(BigInt&);
	BigInt operator/=(BigInt&);
	BigInt operator%=(BigInt&);
	BigInt operator+=(long long&);
	BigInt operator-=(long long&);
	BigInt operator*=(long long&);
	BigInt operator/=(long long&);
	BigInt operator%=(long long&);
	BigInt operator+=(std::string&);
	BigInt operator-=(std::string&);
	BigInt operator*=(std::string&);
	BigInt operator/=(std::string&);
	BigInt operator%=(std::string&);

	//increment , decrement
	BigInt& operator++();    
	BigInt& operator--();

	//relational 
	bool operator<(BigInt&);
	bool operator>(BigInt&);
	bool operator<=(BigInt&);
	bool operator>=(BigInt&);
	bool operator==(BigInt&);
	bool operator!=(BigInt&);
	bool operator<(long long&);
	bool operator>(long long&);
	bool operator<=(long long&);
	bool operator>=(long long&);
	bool operator==(long long&);
	bool operator!=(long long&);
	bool operator<(std::string&);
	bool operator>(std::string&);
	bool operator<=(std::string&);
	bool operator>=(std::string&);
	bool operator==(std::string&);
	bool operator!=(std::string&);

	//Input/Output
	friend istream& operator>>(istream&, BigInt&);
	friend ostream& operator<<(ostream&, BigInt&);

	// Conversion functions:
	string to_String();
	to_Int();
	long long to_Long_Long();

	// Random big interger
	friend BigInt big_random(size_t);

};


//Default
BigInt::BigInt(){
	value = "0";
	sign = '+';
}

//Copy
BigInt::BigInt(BigInt &num){
	value = num.value;
	sign = num.sign;
}

//string to bigInt
BigInt::BigInt(string &num){
	//if string is signed
	if(num[0] == '+' || num[0] == '-'){
		string magnitude = num.substr(1);
		bool isNumber = 1;
		for(auto ch : magnitude){
			if(ch < '0' || ch > '9'){
				isNumber = 0;
				break;
			}
		}
		if(isNumber){
			value = magnitude;
			sign = num[0];
		}else{
            throw invalid_argument("Expected an integer, got \'" + num + "\'");
		}
	}
	//if sign isn't specified assign +ve
	else{
		string magnitude = num.substr(1);
		bool isNumber = 1;
		for(auto ch : magnitude){
			if(ch < '0' || ch > '9'){
				isNumber = 0;
				break;
			}
		}
		if(isNumber){
			value = magnitude;
			sign = '+';
		}else{
            throw invalid_argument("Expected an integer, got \'" + num + "\'");
		}	
	}

	// strip leading zeros
	long long i = 1;
	for(i; i < value.size(); i++){
		if(value[i] != '0')
			break;
	}
	if(i == value.size())
		value = "0";
	else
		value = value.substr(i);
}
//-------------------------------------------------------------


BigInt::BigInt(const long long& num) {
    value = to_string(abs(num));
    if (num < 0)
        sign = '-';
    else
        sign = '+';
}



