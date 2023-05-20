#include "JWT_HS256.h"

vector<string> split(string src, char sep)
{
	vector<string> res;
	stringstream ss(src);
	string tmp;

	while(getline(ss, tmp, sep))
	{
		res.push_back(tmp);
	}

	return res;
}


JWToken::JWToken()
{
}

JWToken::JWToken(string _skey)
{
	skey = _skey;
}
JWToken::JWToken(string _plain, string _skey)
{
	plain = _plain;
	skey = _skey;
}
void JWToken::setPlain(string _plain) { plain = _plain; }
void JWToken::setKey(string _skey) { skey = _skey; };
string JWToken::createVerify(void)
{
	string mac;

	try
	{
		HMAC<SHA256> hmac((byte*)skey.c_str(), skey.length());

		StringSource(plain, true, new HashFilter(hmac, new StringSink(mac)));
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
	}

	return B64Encode(mac);
}
string JWToken::createVerify(string _plain, string _skey)
{
	setPlain(_plain);
	setKey(_skey);
	return createVerify();
}
string JWToken::verifyToken(string _token)
{
	vector<string> token = split(_token, '.');
	string hpp = token[0];
	hpp.push_back('.');
	hpp.append(token[1]);

	cout << hpp.data() << endl;

	string vtoken = createVerify(hpp, skey);
	
	if(vtoken.compare(token[2]) == 0)
	{
		return "OK";
	}
	else
	{
		return "Fail";
	}

	return "OK";
}
string JWToken::B64Encode(string _plain)
{
	Base64URLEncoder encoder;
	string encoded;

	AlgorithmParameters params = MakeParameters(Pad(), false)(InsertLineBreaks(), false);
	encoder.IsolatedInitialize(params);
	encoder.Attach(new StringSink(encoded));

	ArraySource as((byte*)_plain.c_str(), _plain.length(), true, new Redirector(encoder));

	return encoded;

}
string JWToken::B64Decode(string _encoded)
{
	Base64URLDecoder decoder;
	string decoded;

	decoder.Put((byte*)_encoded.c_str(), _encoded.length());
	decoder.MessageEnd();

	word64 size = decoder.MaxRetrievable();
	if(size && size <= SIZE_MAX)
	{
		decoded.resize(size);
		decoder.Get((byte*)&decoded[0], decoded.size());
	}

	return decoded;
}
