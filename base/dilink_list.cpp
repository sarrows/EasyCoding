#include "dilink_list.h"





#ifdef UNITTEST
CPPUNIT_TEST_SUITE_REGISTRATION(DiLinkListTest);

struct Node
{
	int n_;
};

void DiLinkListTest::setUp()
{
	printf("\n begin to test DiLinkListTest class\n");
}
void DiLinkListTest::tearDown()
{
	printf("\n end of testing DiLinkListTest class\n");
}
void DiLinkListTest::test_linklist()
{
	DiLinkList<Node> dilist, dilist2;
	DiLinkList<int>  intlist, intlist2;
	DiLinkList<int>::Iterator itint;
	DiLinkList<Node>::Iterator it;
	//先测试结构
	for (int i = 0; i < 10; i++) {
		intlist.append (i);
	}
	CPPUNIT_ASSERT(intlist.size() == 10);
	CPPUNIT_ASSERT(intlist.empty() == false);
	CPPUNIT_ASSERT(intlist.full() == false);
	//遍历
	for (i = 0, itint = intlist.begin (); itint != intlist.end (); ++itint, ++i)
		CPPUNIT_ASSERT(*itint == i);
	itint = intlist.begin ();
	intlist.advance (itint, 5);
	intlist.insert (itint, 100);
	CPPUNIT_ASSERT(intlist.distance(itint) == 5);
	intlist.clear();
	CPPUNIT_ASSERT(intlist.size() == 0);
}
#endif
