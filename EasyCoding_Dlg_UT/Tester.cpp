
// EasyCoding_Dlg_UTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tester.h"
#include <cppunit/extensions/HelperMacros.h>

CPPUNIT_TEST_SUITE_REGISTRATION(EasyCoding_UT);

void EasyCoding_UT::TestAnyType()
{
	AnyType* pAny;

	pAny = new AnyType(0x12345678);
	CPPUNIT_ASSERT_EQUAL(0x12345678, (INT32)*pAny);
	CPPUNIT_ASSERT_EQUAL(AnyType::INT_T, pAny->vt_);

	delete pAny;
	pAny = new AnyType((UINT32)12345678);
	CPPUNIT_ASSERT((UINT32)12345678 == (UINT32)*pAny);
	CPPUNIT_ASSERT_EQUAL(AnyType::UINT_T, pAny->vt_);
	CPPUNIT_ASSERT_MESSAGE(pAny->to_string().c_str(), pAny->to_string() == "12345678");

	delete pAny;
}
