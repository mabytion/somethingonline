#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::HashFilter;
using CryptoPP::ArraySource;
using CryptoPP::Redirector;
using CryptoPP::word64;

#include <cryptopp/hmac.h>
using CryptoPP::HMAC;

#include <cryptopp/sha.h>
using CryptoPP::SHA256;

#include <cryptopp/config.h>
using CryptoPP::byte;

#include <cryptopp/base64.h>
using CryptoPP::Base64URLEncoder;
using CryptoPP::Base64URLDecoder;

#include <cryptopp/algparam.h>
using CryptoPP::AlgorithmParameters;
using CryptoPP::MakeParameters;

#include <cryptopp/argnames.h>
using CryptoPP::Name::Pad;
using CryptoPP::Name::InsertLineBreaks;


using namespace std;

#ifndef JWT_HS256_H
#define JWT_HS256_H

vector<string> split(string, char);

class JWToken
{
private:
	string plain;
	string skey;
	string res;

public:
	JWToken();
	JWToken(string);
	JWToken(string, string);
	void setPlain(string);
	void setKey(string);
	string createVerify(void);
	string createVerify(string, string);
	string verifyToken(string);
	string B64Encode(string);
	string B64Decode(string);
	
};

#endif
