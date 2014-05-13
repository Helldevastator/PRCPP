#include "stdafx.h"
#include "MyString.h"
#include <exception>
#include <math.h>

String::String(void) :m_len(0),m_start(0),m_string(nullptr)
{

}

String::String(const char* s) :m_len(0),m_start(0)
{
	using namespace std;
	int i = 0;
	while(*(s+i) != '\0') i++;		//get length of char array
	this->m_len = i;

	m_string = shared_ptr<char>(new char[m_len+1],default_delete<char[]>());
	//this->m_string = shared_ptr<char>(unique_ptr<char[],default_delete<char[]>>(new char[this->m_len+1]));

	//copy contents
	memcpy(m_string.get(), s, this->m_len); *(m_string.get() +m_len) = '\0';
}

String::String(const String& s): m_len(s.m_len), m_start(s.m_start), m_string(s.m_string)
{
	
}

String::String(String&& s): m_len(s.m_len), m_start(s.m_start), m_string(s.m_string)
{
	s.m_string = nullptr;
	s.m_len = 0;
	s.m_start = 0;
	//delete s;
}

String::~String(void)
{
	if(m_string != nullptr)
	{
		//std::cout << "delete[] " << this->m_string << "\n";
	}
	
}

//returns exception, if index is out of range
char String::charAt(size_t index) const
{
	char* p = this->m_string.get() + this->m_start;

	if (index < this->length())
	{
		return p[index];
	} 
	else 
	{
		throw std::out_of_range("index out of range.");
	}
}

String String::concat(const char c) const
{
	using namespace std;

	String ret;
	size_t length = this->length();
	ret.m_len = length + 1;
	ret.m_string = shared_ptr<char>(new char[length + 2],default_delete<char[]>());
	const char* p = this->m_string.get() + this->m_start;

	memcpy(ret.m_string.get(),p,length);
	*(ret.m_string.get()+length) = c; *(ret.m_string.get()+length+1)  = '\0';
	
	return move(ret);
}

String String::concat(const String& s) const
{
	using namespace std;

	size_t currLen = this->length();
	size_t concLen = s.length();
	String ret;
	ret.m_len = currLen+ concLen;
	ret.m_string = shared_ptr<char>(new char[ret.m_len+ 1],default_delete<char[]>());

	char* dest = ret.m_string.get();
	const char* source1 = this->m_string.get() + this->m_start;
	const char* source2 = s.m_string.get() + s.m_start;

	memcpy(dest,source1,currLen); //copy current values
	memcpy(dest+currLen,source2,concLen);dest[currLen + concLen] = '\n';

	return move(ret);
}

String String::concat(String&& s) const
{
	using namespace std;

	const char* source1 = this->m_string.get() + this->m_start;
	const char* source2 = s.m_string.get()+s.m_start;
	size_t oldLen = s.length();
	size_t currLen = this->length();

	s.m_len = currLen+ oldLen;
	s.m_start = 0;
	char* tmp = new char[s.m_len+ 1];

	memcpy(tmp,source1,currLen); //copy current values
	memcpy(tmp+currLen,source2,oldLen);
	tmp[currLen + oldLen] = '\0';

	s.m_string = shared_ptr<char>(tmp,default_delete<char[]>());

	return move(s);
}

String String::substring(size_t beg, size_t end) const
{
	String ret(*this);

	end = end >= this->length() ? this->length() -1 : end;	//ensure that end is inside the string

	if(beg >=  this->length() && end <= beg)
	{
		ret.m_len = 0;
		ret.m_start = 0;
	} 
	else 
	{
		ret.m_start += beg;
		ret.m_len = end - beg + 1;
	}

	return std::move(ret);
}

int String::compareTo(const String& s) const
{
	size_t thisLen = this->length();
	size_t compareLen = s.length();
	size_t len = thisLen < compareLen ? thisLen : compareLen;
	int result = thisLen == compareLen ? 0 : thisLen < compareLen ? -1 : 1;	//set result according to length

	int i = 0;
	while(i < len && this->charAt(i) == s.charAt(i)) i++;
	
	//check if comparison ran through whole string
	if (i == len)
		return result;	//ran through whole string, only length indicates if -1,0,1. Return result 
	else
		return charAt(i) < s.charAt(i) ? -1 : 1;
}

std::unique_ptr<char[]> String::toCString() const 
{ 
	using namespace std;
	unique_ptr<char[]> r = unique_ptr<char[]>(new char[m_len + 1]); 
	const char * const tc = m_string.get(); 
	
	//for (size_t i=0; i < m_len; i++) r[i] = tc[m_start + i]; 
	
	memcpy(r.get(), tc + m_start, m_len); r[m_len] = '\0';
	return move(r); 
}

String& String::operator=(String&& s)
{
	m_string = s.m_string;
	m_len = s.m_len;
	m_start = s.m_start;

	s.m_string = nullptr;
	s.m_len = 0;
	s.m_start = 0;

	return *this;
}

String String::valueOf(int i)
{
	using namespace std;

	//count digits
	int digits = 1;
	double compareVal = pow(10,digits);
	while(compareVal < INT32_MAX && compareVal < i) {
		digits++;
		compareVal = pow(10,digits);
	}
	
	String ret;
	ret.m_len = digits;
	ret.m_string = shared_ptr<char>(new char[ret.m_len+ 1],default_delete<char[]>());

	//modulo magix
	for(int j = digits-1; j >= 0;j--)
	{
		*(ret.m_string.get()+j) = '0'+i%10; //convert to character digit
		i = i /10;
	}

	*(ret.m_string.get()+ret.m_len) = '\0';

	return move(ret);
}