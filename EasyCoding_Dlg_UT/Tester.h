
// Tester.h : ͷ�ļ�
//

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>  
#include "any_type.h"


typedef EasyCoding::AnyType AnyType;

class EasyCoding_UT: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(EasyCoding_UT);  // ����Ϊ����������
	CPPUNIT_TEST(TestAnyType);        // ����Ϊ���Ժ������������������Ĳ��Ժ�����Ӧ
	CPPUNIT_TEST_SUITE_END();

public:
	EasyCoding_UT::EasyCoding_UT(void)
	{
	}

	EasyCoding_UT::~EasyCoding_UT(void)
	{
	}

	void setUp() {
		// ��������в��Եĳ�ʼ������
	}

	void tearDown() {
		// ��������в�����Ϻ��������
	}

	void TestAnyType();  // ���Ժ�������������Ŀ�����ĳһ��ϸ��
};
