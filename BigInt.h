#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class BigInt{
private:
	string value;
	char sign;

public:

	//constructors
	BigInt();
	BigInt(const BigInt&);
	BigInt(const long long&);
	BigInt(const string&);

	//assignment operators
	BigInt& operator=(const BigInt&);
	BigInt& operator=(const long long&);
	BigInt& operator=(const string&);
 	
 	//unary
 	BigInt operator+() const;   // unary +
    BigInt operator-() const; 

    //Arithmetic
	BigInt operator+(const BigInt&) const ;
	BigInt operator-(const BigInt&) const ;
	BigInt operator*(const BigInt&) const ;
	BigInt operator/(const BigInt&) const ;
	BigInt operator%(const BigInt&) const ;
	BigInt operator+(long long&) const ;
	BigInt operator-(long long&) const ;
	BigInt operator*(long long&) const ;
	BigInt operator/(long long&) const ;
	BigInt operator%(long long&) const ;
	BigInt operator+(const string&) const ;
	BigInt operator-(const string&) const ;
	BigInt operator*(const string&) const ;
	BigInt operator/(const string&) const ;
	BigInt operator%(const string&) const ;

	//Arithmetic assignment
	BigInt operator+=(const BigInt&);
	BigInt operator-=(const BigInt&);
	BigInt operator*=(const BigInt&);
	BigInt operator/=(const BigInt&);
	BigInt operator%=(const BigInt&);
	BigInt operator+=(const long long&);
	BigInt operator-=(const long long&);
	BigInt operator*=(const long long&);
	BigInt operator/=(const long long&);
	BigInt operator%=(const long long&);
	BigInt operator+=(const string&);
	BigInt operator-=(const string&);
	BigInt operator*=(const string&);
	BigInt operator/=(const string&);
	BigInt operator%=(const string&);

	//increment , decrement
	BigInt& operator++();    
	BigInt& operator--();

	//relational 
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const long long&) const;
	bool operator>(const long long&) const;
	bool operator<=(const long long&) const;
	bool operator>=(const long long&) const;
	bool operator==(const long long&) const;
	bool operator!=(const long long&) const;
	bool operator<(const string&) const;
	bool operator>(const string&) const;
	bool operator<=(const string&) const;
	bool operator>=(const string&) const;
	bool operator==(const string&) const;
	bool operator!=(const string&) const;

	//Input/Output
	friend istream& operator>>(istream&, BigInt&);
	friend ostream& operator<<(ostream&, const BigInt&);

	// Conversion functions:
	string to_String() const;
	to_Int() const;
	long long to_Long_Long() const;

	// Random big interger
	friend BigInt big_random(size_t);
	BigInt factorial() const;

};

// ----------------------------------------------

//Constructors

//Default
BigInt::BigInt(){
	value = "0";
	sign = '+';
}

//Copy
BigInt::BigInt(const BigInt &num){
	value = num.value;
	sign = num.sign;
}

//string to bigInt
BigInt::BigInt(const string &num){
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
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
		}
	}
	//if sign isn't specified assign +ve
	else{
		string magnitude = num;
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
	long long i = 0;
	for(i; i < value.size(); i++){
		if(value[i] != '0')
			break;
	}
	if(i == value.size())
		value = "0";
	else
		value = value.substr(i);
}


// ----------------------------------------------

//assignment

BigInt& BigInt::operator=(const BigInt& num){
	value = num.value;
	sign = num.sign;

	return *this;
}

BigInt& BigInt::operator=(const long long& num){
	BigInt temp(num);
	value = temp.value;
	sign = temp.sign;

	return *this;
}

BigInt& BigInt::operator=(const std::string& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}











// ----------------------------------------------

//Conversions

BigInt::BigInt(const long long& num) {
    value = to_string(abs(num));
    if (num < 0)
        sign = '-';
    else
        sign = '+';
}

string BigInt::to_String() const{
	if(this->sign == '-')
		return "-" + this->value;

	return this->value;
}



// ----------------------------------------------


//unary arithmetic

BigInt BigInt::operator+() const{
	return *this;
}

BigInt BigInt::operator-() const{
	BigInt num;
	
	if(value != "0"){
		if(sign == '+'){
			num.sign = '-';
		}
		else{
			num.sign = '+';
		}
	}

	num.value = value;

	return num;
}




// ----------------------------------------------

// Binary arithmetic


// ----------------------------------------------
