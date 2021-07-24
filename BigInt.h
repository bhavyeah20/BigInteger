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
 	//will change (this) only on assignment hence const
 	BigInt operator+() const;   
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
	int to_Int() const;
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

BigInt::BigInt(const long long& num) {
    value = to_string(abs(num));
    if (num < 0)
        sign = '-';
    else
        sign = '+';
}

//string to bigInt
BigInt::BigInt(const string &num){
	//if string is signed
	if(num[0] == '+' || num[0] == '-'){
		string magnitude = num.substr(1);

		if(isValidNumber(magnitude)){
			value = magnitude;
			sign = num[0];
		}else{
            throw invalid_argument("Expected an integer, got \'" + num + "\'");
		}
	}
	//if sign isn't specified assign +ve
	else{
		string magnitude = num;
		if(isValidNumber(magnitude)){
			value = magnitude;
			sign = '+';
		}else{
            throw invalid_argument("Expected an integer, got \'" + num + "\'");
		}	
	}


	stripLeadingZeros(value);
	
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



string BigInt::to_String() const{
	if(this->sign == '-')
		return "-" + this->value;

	return this->value;
}


int BigInt::to_Int() const {
    return stoi(this->to_String());
}

long long BigInt::to_Long_Long() const {
    return stoll(this->to_String());
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



//Basic math

// Functions do not end with const as they are not 
// member functions

BigInt abs(const BigInt& num){
	return num < 0 ? -num : num;
}

BigInt pow(const BigInt &base, long long exp){
	if(exp < 0){
		if(base == 0)
			throw logic_error("Can't divide by zero");
		return abs(base) == 1 ? base : 0;
	}

	if(exp == 0){
		if(base == 0)
			throw logic_error("0 to the power 0 is undefined");
		return 1;
	}

	BigInt res = 1, tempBase = base;
	while(exp){
		if(exp % 2)
			res *= tempBase;
		exp /= 2;
		res *= res;
	}

	return res;

}

BigInt pow(const long long &base, int exp){
	return pow(BigInt(base), exp);
}

BigInt pow(const string &base, int exp){
	return pow(BigInt(base), exp);
}

BigInt sqrt(const BigInt& num){
	if(num < 0)
		throw invalid_argument("Number must be non negative!");


	BigInt start = 0, end = num / 2;
	BigInt ans = 0;
	while(start <= end){
		BigInt mid = (start + end) / 2;
		
		if(mid * mid == num)
			return mid;
	
		else if(mid * mid < num){
			start = mid+1;
			ans = mid;
		}

		else
			end = mid-1;

	}

	return ans;

}

BigInt gcd(const BigInt &num1, const BigInt &num2){
	BigInt absNum1 = abs(num1);
	BigInt absNum2 = abs(num2);

	if(absNum1 == 0)
		return absNum2;

	if(absNum2 == 0)
		return absNum1;

	if(absNum2 > absNum1)
		return gcd(num2, num1);

	BigInt rem = absNum2;

	while(rem != 0){
		rem = absNum1 % absNum2;
		absNum1 = absNum2;
		absNum2 = rem;
	}

	return absNum1;
}


BigInt gcd(const BigInt& num1, const long long& num2){
    return gcd(num1, BigInt(num2));
}


BigInt gcd(const BigInt& num1, const string& num2){
    return gcd(num1, BigInt(num2));
}


BigInt gcd(const long long& num1, const BigInt& num2){
    return gcd(BigInt(num1), num2);
}


BigInt gcd(const string& num1, const BigInt& num2){
    return gcd(BigInt(num1), num2);
}

BigInt lcm(const BigInt& num1, const BigInt& num2){
	if(num1 == 0 || num2 == 0)
		return 0;

	return abs(num1 * num2) / gcd(num1,num2);
}


BigInt lcm(const BigInt& num1, const long long& num2){
    return lcm(num1, BigInt(num2));
}


BigInt lcm(const BigInt& num1, const string& num2){
    return lcm(num1, BigInt(num2));
}


BigInt lcm(const long long& num1, const BigInt& num2){
    return lcm(BigInt(num1), num2);
}


BigInt lcm(const string& num1, const BigInt& num2){
    return lcm(BigInt(num1), num2);
}


bool isValidNumber(const string& magnitude){
	for(auto ch : magnitude){
		if(ch < '0' || ch > '9')
			return false;
	}
	return true;
}

void stripLeadingZeros(string &value){
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
