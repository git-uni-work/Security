#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

void modifystring(string & x)
{
	for( int i = x.length()-1 ; i >= 0 ; i-- )
	{
		if(x[i] != 'z')
		{
			x[i]++;
      break;
		}
		else
    { x[i] = 'a'; }
	}
  cout << x << endl;
}

string DecToBinary( int n )
{
  string binary = "";
  for (int i = 7; i >= 0; i--) {
      int k = n >> i;
      if (k & 1)
          binary += "1";
      else
          binary += "0";
  }
  return binary;
}

string HexToBin( string hex )
{
  string binary = "";
  for( char & c : hex )
  {
    switch( c )
    {
      case '0':
          binary +=  "0000";
          break;
      case '1':
          binary +=  "0001";
          break;
      case '2':
          binary +=  "0010";
          break;
      case '3':
          binary +=  "0011";
          break;
      case '4':
          binary +=  "0100";
          break;
      case '5':
          binary +=  "0101";
          break;
      case '6':
          binary += "0110";
          break;
      case '7':
          binary +=  "0111";
          break;
      case '8':
          binary += "1000";
          break;
      case '9':
          binary +=  "1001";
          break;
      case 'A':
      case 'a':
          binary +=  "1010";
          break;
      case 'B':
      case 'b':
          binary += "1011";
          break;
      case 'C':
      case 'c':
          binary +=  "1100";
          break;
      case 'D':
      case 'd':
          binary += "1101";
          break;
      case 'E':
      case 'e':
          binary +=  "1110";
          break;
      case 'F':
      case 'f':
          binary += "1111";
          break;
      default:
          cout << "Invalid HEX" << endl;
          break;
    }
  }
  return binary;
}

void HexMap( unordered_map<string, char> *m )
{
    (*m)["0000"] = '0';
    (*m)["0001"] = '1';
    (*m)["0010"] = '2';
    (*m)["0011"] = '3';
    (*m)["0100"] = '4';
    (*m)["0101"] = '5';
    (*m)["0110"] = '6';
    (*m)["0111"] = '7';
    (*m)["1000"] = '8';
    (*m)["1001"] = '9';
    (*m)["1010"] = 'A';
    (*m)["1011"] = 'B';
    (*m)["1100"] = 'C';
    (*m)["1101"] = 'D';
    (*m)["1110"] = 'E';
    (*m)["1111"] = 'F';
}

string BinToHex( string x )
{
    unordered_map<string, char> hexmap;
    HexMap(&hexmap);

    size_t i = 0;
    string hex = "";
    while (1)
    {
        hex += hexmap[x.substr(i, 4)];
        i += 4;
        if (i == x.size())
        {break;}
    }
    return hex;
}

int BinaryToDec( int x )
{
  int decimal = 0, i = 0, remainder;
  while( x != 0 )
  {
    remainder = x % 10;
    x /= 10;
    decimal += remainder*pow(2,i);
    i++;
  }
  return decimal;
}

string StringToHex( const string & x )
{
    static const char hex[] = "0123456789ABCDEF";
    string result;
    result.reserve(x.length() * 2);
    for ( unsigned char c : x )
    {
        result.push_back(hex[c >> 4]);
        result.push_back(hex[c & 15]);
    }
    return result;
}

int Hex( char x )
{
    switch(x)
    {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        return x - '0';

    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        return x - 'A' + 10;

    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        return x - 'a' + 10;
    }
    cout << "Invalid HEX" << endl;
    return 0;
}

string HexToString( const string & x )
{
    const auto lenf = x.length();
    if(lenf & 1)
    {cout << "odd length" << endl;}

    string result;
    result.reserve(lenf / 2);
    for (auto it = x.begin(); it != x.end(); )
    {
        int hi = Hex(*it++);
        int lo = Hex(*it++);
        result.push_back(hi << 4 | lo);
    }
    return result;
}

int main()
{

  string ye = "Test string";
  string x = StringToHex(ye);
  cout << "\""<< HexToString(x) << "\""<<  " IN HEX => " << x << endl;
  cout << "===============================" << endl;

  string hex1 = "fc57c9cfdac7202694e8c2712d1f0e8e21b8c6f6d612d6c96847e42e6257b3f9ea98466cfc8761ed5e0308311deb15";
  string hex2 = "a83fa0bcfaae5306f5c8b1144e6d6bfa01cca38ea23cf68707258b4a1b77c09185ed2a08dcf5048c3a237c5974983b";
  string bin1 = HexToBin(hex1);
  string bin2 = HexToBin(hex2);
  string res = bin1;
  for( size_t i = 0 ; i < bin1.length() ; i++ )
  {
    res[i] = ((bin1[i]-'0') ^ (bin2[i]-'0')) + '0';
  }
  string hexres = BinToHex(res);
  cout << "MESSAGE = " << HexToString(hexres) << endl;

  // string a = "aaa";
  // while(1)
  //   modifystring(a);

  return 0;
}
