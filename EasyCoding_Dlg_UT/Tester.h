
// Tester.h : 头文件
//

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>  
#include "any_type.h"


typedef EasyCoding::AnyType AnyType;

class EasyCoding_UT: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(EasyCoding_UT);  // 参数为本测试类名
	CPPUNIT_TEST(TestAnyType);        // 参数为测试函数名，与下面声明的测试函数对应
	CPPUNIT_TEST_SUITE_END();

public:
	EasyCoding_UT::EasyCoding_UT(void)
	{
	}

	EasyCoding_UT::~EasyCoding_UT(void)
	{
	}

	void setUp() {
		// 在这里进行测试的初始化工作
	}

	void tearDown() {
		// 在这里进行测试完毕后的清理工作
	}

	void TestAnyType();  // 测试函数，用来测试目标类的某一个细节
};
