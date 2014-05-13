#include "stdafx.h"
#include "CppUnitTest.h"
#include "MyString.h"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Construction) 
		{ 
			using namespace std;
			String s0; 
			String s1(""); 
			String s2("abc");

			Assert::AreEqual("",s0.toCString().get());
			Assert::AreEqual("",s1.toCString().get());
			Assert::AreEqual("abc",s2.toCString().get());

			//test copy ctor
			String s00(s0); 
			String s11(s1);
			String s22(s2); 
			Assert::AreEqual("",s00.toCString().get());
			Assert::AreEqual("",s11.toCString().get());
			Assert::AreEqual("abc",s22.toCString().get());

			//test move ctor
			String s000(move(s0));
			String s111(move(s1));
			String s222(move(s2));
			Assert::AreEqual("",s000.toCString().get());
			Assert::AreEqual("",s111.toCString().get());
			Assert::AreEqual("abc",s222.toCString().get());
		}

		TEST_METHOD(CharAt)
		{
			String test1("abc");
			Assert::AreEqual(test1.charAt(0),'a');
			Assert::AreEqual(test1.charAt(1),'b');
			Assert::AreEqual(test1.charAt(2),'c');
		}
	
		TEST_METHOD(CharAtException)
		{	
			try 
			{
				String test1("abc");
				// Should raise an exception:
				test1.charAt(3);
				
				Assert::Fail();
			}
			catch(std::out_of_range ex)
			{
				//correct exception catched
			}
			catch(...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(CompareTo)
		{
			String compare("abc");

			Assert::AreEqual(compare.compareTo(String("")),1);
			Assert::AreEqual(compare.compareTo(String("ab")),1);
			Assert::AreEqual(compare.compareTo(String("aacde")),1);

			Assert::AreEqual(compare.compareTo(String("abcd")),-1);
			Assert::AreEqual(compare.compareTo(String("b")),-1);
			Assert::AreEqual(compare.compareTo(String("bcde")),-1);
			Assert::AreEqual(compare.compareTo(String("abd")),-1);

			Assert::AreEqual(compare.compareTo(String("abc")),0);
		}

		TEST_METHOD(Length) 
		{ 
			Assert::IsTrue(String().length() == 0); 
			Assert::IsTrue(String("").length() == 0);
			Assert::IsTrue(String("abc").length() == 3); 
		}

		TEST_METHOD(Concat)
		{
			//char concat
			String s1("ab");
			String s2 = s1.concat('c');
			Assert::AreEqual("abc",s2.toCString().get());
			
			//test move concat
			s2 = s1.concat("c");
			Assert::AreEqual("abc",s2.toCString().get());

			//test normal copy concat
			String s3 = s1.concat(s2);
			Assert::AreEqual("ababc",s3.toCString().get());
		}

		TEST_METHOD(Substring)
		{
			String s1("abcd");

			Assert::AreEqual("abc",s1.substring(0,2).toCString().get());
			Assert::AreEqual("bc",s1.substring(1,2).toCString().get());
			Assert::AreEqual("bcd",s1.substring(1,3).toCString().get());
			Assert::AreEqual("",s1.substring(4,3).toCString().get());
			Assert::AreEqual("b",s1.substring(0,2).substring(1,1).toCString().get());
		}

		TEST_METHOD(ToCString)
		{
			//tested
		}


		TEST_METHOD(ConcatAfterSubstring)
		{
			String s1("abcd");

			//check concat after substring
			Assert::AreEqual("abce",s1.substring(0,2).concat("e").toCString().get());
		}

		TEST_METHOD(ValueOf)
		{
			String s1 = String::valueOf(0);
			String s2 = String::valueOf(1337);

			Assert::AreEqual("0",s1.toCString().get());
			Assert::AreEqual("1337",s2.toCString().get());
		}

	};
}