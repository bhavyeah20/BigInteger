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
	BigInt operator+(const long long&) const ;
	BigInt operator-(const long long&) const ;
	BigInt operator*(const long long&) const ;
	BigInt operator/(const long long&) const ;
	BigInt operator%(const long long&) const ;
	BigInt operator+(const string&) const ;
	BigInt operator-(const string&) const ;
	BigInt operator*(const string&) const ;
	BigInt operator/(const string&) const ;
	BigInt operator%(const string&) const ;

	//Arithmetic assignment
	BigInt& operator+=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator+=(const long long&);
	BigInt& operator-=(const long long&);
	BigInt& operator*=(const long long&);
	BigInt& operator/=(const long long&);
	BigInt& operator%=(const long long&);
	BigInt& operator+=(const string&);
	BigInt& operator-=(const string&);
	BigInt& operator*=(const string&);
	BigInt& operator/=(const string&);
	BigInt& operator%=(const string&);

	//increment , decrement
	//pre
	BigInt& operator++();    
	BigInt& operator--();
	//post
	BigInt operator++(int);
	BigInt operator--(int);


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
};


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
		tempBase *= tempBase;
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

	if(num == 1)
		return 1;

	//num1xnum2=num. Max value of numi = num/2
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

BigInt& BigInt::operator=(const string& num) {
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

BigInt BigInt::operator+(const BigInt &num) const{

	if(this->sign == '+' && num.sign == '-'){
		BigInt rhs = num;
		rhs.sign = '+';
		return *this - rhs;
	}

	else if(this->sign == '-' && num.sign == '+'){
		BigInt lhs = *this;
		lhs.sign = '+';
		return -(lhs - num);
	}

	string larger = this->to_String();
	string smaller = num.to_String();

	if(smaller.size() > larger.size())
		swap(smaller, larger);

	long long j = smaller.size() - 1;
	for(long long i = larger.size() - 1; j >= 0; i--, j--){
		larger[i] = larger[i] + (smaller[j]-'0');
	}
	int carry = 0, sum = 0;
	for(long long i = larger.size()-1; i >= 0; i--){
		sum = carry + (larger[i]-'0');
		carry = sum / 10;
		larger[i] = (sum%10) + '0';
	}

	if(carry){
		larger = to_string(carry) + larger;
	}

	stripLeadingZeros(larger);
	BigInt res(larger);

	if(this->sign == '-' && res.value != "0")
		res.sign = '-';

	return res;

}

BigInt BigInt::operator+(const long long& num) const {
    return *this + BigInt(num);
}

BigInt operator+(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) + rhs;
}
BigInt BigInt::operator+(const string& num) const {
    return *this + BigInt(num);
}

BigInt operator+(const string& lhs, const BigInt& rhs) {
    return BigInt(lhs) + rhs;
}

BigInt BigInt::operator-(const BigInt& num) const{
	if(this->sign == '+' && num.sign == '-'){
		BigInt rhs = num;
		rhs.sign = '+';
		return *this + rhs;
	}

	else if(this->sign == '-' && num.sign == '+'){
		BigInt lhs = *this;
		lhs.sign = '+';
		return -(lhs + num);
	}

	BigInt result;
	string larger, smaller;
	if(abs(*this) > abs(num)){
		larger = this->value;
		smaller = num.value;

		if(this->sign == '-')
			result.sign = '-';
	}

	else{
		larger = num.value;
		smaller = this->value;

		if(num.sign == '+')
			result.sign = '-';
	}


	long long j = smaller.size() - 1;
	long long i = larger.size() - 1;
	int carry = 0, sum = 0;
	for(j,i; j >= 0; i--,j--){
		sum = (larger[i]-'0') - (smaller[j]-'0') - carry;
		if(sum < 0){
			sum += 10;
			carry = 1; 
		}

		else
			carry = 0;

		larger[i] = sum+'0';
	}

	while(carry && i >= 0){
		sum = (larger[i]-'0')- carry;
		if(sum < 0){
			sum += 10;
			carry = 1; 
		}

		else
			carry = 0;

		larger[i] = sum+'0';
		i--;
	}

	stripLeadingZeros(larger);

	result.value = larger;

	if(result.value == "0")
		result.sign = '+';

	return result;


}

BigInt BigInt::operator-(const long long& num) const {
    return *this - BigInt(num);
}

BigInt operator-(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) - rhs;
}
BigInt BigInt::operator-(const string& num) const {
    return *this - BigInt(num);
}

BigInt operator-(const string& lhs, const BigInt& rhs) {
    return BigInt(lhs) - rhs;
}


BigInt BigInt::operator*(const BigInt &num) const{

	if(*this == 0 || num == 0)
		return BigInt(0);

	if(*this == 1)
		return num;

	if(num == 1)
		return *this;

	BigInt product;


	string num1 = this->to_String();
	string num2 = num.to_String();

	string res(num1.size()+num2.size(),'0');

	if(num1.size() < num2.size())
		swap(num1,num2);

    for(long long i = num1.size()-1; i >= 0; i--){
        for(long long j = num2.size()-1; j >= 0; j--){
            long long number = (num1[i]-'0') * (num2[j]-'0') + (res[i+j+1] - '0');
            res[i+j] = res[i+j] + number/10;
            res[i+j+1] = (number % 10) + '0'; 
            
        }
    }
    
   	stripLeadingZeros(res);
 	product = res;

 	if(this->sign == num.sign)
 		product.sign = '+';

 	else
 		product.sign = '-';

 	return product;

}

BigInt BigInt::operator*(const long long& num) const {
    return *this * BigInt(num);
}

BigInt operator*(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) * rhs;
}

BigInt BigInt::operator*(const string& num) const {
    return *this * BigInt(num);
}


BigInt operator*(const string& lhs, const BigInt& rhs) {
    return BigInt(lhs) * rhs;
}

BigInt BigInt::operator/(const BigInt &num) const{

	BigInt dividend = abs(*this);
	BigInt divisor = abs(num);

	if(num == 0)
		throw logic_error("Divisor can't be zero");

	if(dividend < divisor)
		return BigInt(0);

	if(num == 1)
		return *this;

	if(num == -1)
		return *this;

	BigInt quotent = 0, factor = 1;
	while(dividend >= divisor){
		factor = 1;
		while(2*divisor <= dividend){
			divisor *= 2;
			factor *= 2;
		}

		dividend -= divisor;
		quotent += factor;
		divisor = abs(num);
	}

	stripLeadingZeros(quotent.value);

	if(this->sign == num.sign)
		quotent.sign = '+';
	else
		quotent.sign = '-';

	return quotent;


}



BigInt BigInt::operator/(const long long& num) const {
    return *this / BigInt(num);
}

BigInt operator/(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) / rhs;
}


BigInt BigInt::operator/(const string& num) const {
    return *this / BigInt(num);
}

BigInt operator/(const string& lhs, const BigInt& rhs) {
    return BigInt(lhs) / rhs;
}



BigInt BigInt::operator%(const BigInt &num) const{

	BigInt dividend = abs(*this);
	BigInt divisor = abs(num);

	if(num == 0)
		throw logic_error("Divisor can't be zero");

	if(divisor == 1 || dividend == divisor)
		return BigInt(0);

	BigInt quotent = dividend / divisor;
	BigInt remainder = dividend - (quotent * divisor);

	remainder.sign = this->sign;
	if(remainder.value == "0")
		remainder.sign = '+';

	return remainder;

}






BigInt BigInt::operator%(const long long& num) const {
    return *this % BigInt(num);
}


BigInt operator%(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) % rhs;
}



BigInt BigInt::operator%(const string& num) const {
    return *this % BigInt(num);
}


BigInt operator%(const string& lhs, const BigInt& rhs) {
    return BigInt(lhs) % rhs;
}



// ----------------------------------------------

// I/O Stream

istream& operator>>(istream &in, BigInt &num){
	string input;
	in >> input;
	num = BigInt(input);

	return in;
}

ostream& operator<<(ostream &out, const BigInt& num){
	if(num.sign == '-')
		out << num.sign;
	out << num.value;
	return out;
}

// ----------------------------------------------

// relational arithmetic

bool BigInt::operator==(const BigInt& num) const{
	return (sign == num.sign) && (value == num.value);
}

bool BigInt::operator!=(const BigInt& num) const{
	return !(*this == num);
}

bool BigInt::operator<(const BigInt& num) const{
	if(sign == num.sign){
		if(sign == '+'){
			if(value.length() == num.value.length())
				return value < num.value;
			else
				return value.length() < num.value.length();
		}
		else
			return -(*this) > -num;
	}

	else
		return sign == '-';
}


bool BigInt::operator>(const BigInt& num) const{
	return !((*this < num) || (*this == num));
}


bool BigInt::operator<=(const BigInt& num) const{
	return (*this < num) || (*this == num);
}

bool BigInt::operator>=(const BigInt& num) const{
	return !(*this < num);
}


bool BigInt::operator==(const long long& num) const {
    return *this == BigInt(num);
}

bool operator==(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}


bool BigInt::operator!=(const long long& num) const {
    return *this != BigInt(num);
}

bool operator!=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}


bool BigInt::operator<(const long long& num) const {
    return *this < BigInt(num);
}

bool operator<(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}

bool BigInt::operator>(const long long& num) const {
    return *this > BigInt(num);
}

bool operator>(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}

bool BigInt::operator<=(const long long& num) const {
    return *this <= BigInt(num);
}

bool operator<=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}


bool BigInt::operator>=(const long long& num) const {
    return *this >= BigInt(num);
}

bool operator>=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
}


bool BigInt::operator==(const string& num) const {
    return *this == BigInt(num);
}

bool operator==(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}


bool BigInt::operator!=(const std::string& num) const {
    return *this != BigInt(num);
}

bool operator!=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}


bool BigInt::operator<(const std::string& num) const {
    return *this < BigInt(num);
}

bool operator<(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}


bool BigInt::operator>(const std::string& num) const {
    return *this > BigInt(num);
}

bool operator>(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}


bool BigInt::operator<=(const std::string& num) const {
    return *this <= BigInt(num);
}

bool operator<=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}


bool BigInt::operator>=(const std::string& num) const {
    return *this >= BigInt(num);
}


bool operator>=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
}



// ----------------------------------------------

//Arithmetic assignment 


BigInt& BigInt::operator+=(const BigInt& num){
	*this = *this + num;

	return *this;
}


BigInt& BigInt::operator-=(const BigInt& num){
	*this = *this - num;

	return *this;
}

BigInt& BigInt::operator*=(const BigInt& num){
	*this = *this * num;

	return *this;
}

BigInt& BigInt::operator/=(const BigInt& num){
	*this = *this / num;

	return *this;
}

BigInt& BigInt::operator%=(const BigInt& num){
	*this = *this % num;

	return *this;
}


BigInt& BigInt::operator+=(const long long& num) {
    *this = *this + BigInt(num);

    return *this;
}

BigInt& BigInt::operator-=(const long long& num) {
    *this = *this - BigInt(num);

    return *this;
}

BigInt& BigInt::operator*=(const long long& num) {
    *this = *this * BigInt(num);

    return *this;
}

BigInt& BigInt::operator/=(const long long& num) {
    *this = *this / BigInt(num);

    return *this;
}

BigInt& BigInt::operator%=(const long long& num) {
    *this = *this % BigInt(num);

    return *this;
}


BigInt& BigInt::operator+=(const string& num) {
    *this = *this + BigInt(num);

    return *this;
}


BigInt& BigInt::operator-=(const string& num) {
    *this = *this - BigInt(num);

    return *this;
}


BigInt& BigInt::operator*=(const string& num) {
    *this = *this * BigInt(num);

    return *this;
}



BigInt& BigInt::operator/=(const string& num) {
    *this = *this / BigInt(num);

    return *this;
}


BigInt& BigInt::operator%=(const string& num) {
    *this = *this % BigInt(num);

    return *this;
}

	

// ----------------------------------------------

// Increment / Decrement


//Pre
BigInt& BigInt::operator++(){
	*this += 1;
	return *this;
}


BigInt& BigInt::operator--(){
	*this -= 1;
	return *this;
}

//Post

BigInt BigInt::operator++(int){
	BigInt temp = *this;
	*this += 1;
	return temp;
}

BigInt BigInt::operator--(int){
	BigInt temp = *this;
	*this -= 1;
	return temp;
}


// ----------------------------------------------
