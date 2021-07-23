//if big int is not defined then define it
//else move on
// #ifndef TEST_H
// #define TEST_H
#include<string>
#include<iostream>
#include<sstream>
#include<math.h>

#include"test.h"

BigInt::BigInt() // empty constructor initializes zero
{
	value = "0";
	sign = '+';
}
//-------------------------------------------------------------
BigInt::BigInt(string s) // "string" constructor
{
	if( isdigit(s[0]) ) // if not signed
	{
		setNumber(s);
		sign = '+'; // +ve
	}
	else
	{
		setNumber( s.substr(1) );
		sign = s[0];
	}
}
//-------------------------------------------------------------
BigInt::BigInt(int n) // "int" constructor
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;


	if( isdigit(s[0]) ) // if not signed
	{
		setNumber( s );
		sign = '+'; // +ve
	}
	else
	{
		setNumber( s.substr(1) );
		sign = s[0];
	}
}


void BigInt::setNumber(string s){
	value = s;
}

const string& BigInt::getNum(){
	return value;
}

// #endif