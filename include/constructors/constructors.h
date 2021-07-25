#include "../BigInt.h"

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



