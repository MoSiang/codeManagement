#include"ComplexLinkList.h"

ComplexNode* CreateComplexLinkList()
{
	ComplexNode* head1 = new ComplexNode(1);
	ComplexNode* head2 = new ComplexNode(2);
	ComplexNode* head3 = new ComplexNode(3);
	ComplexNode* head4 = new ComplexNode(4);
	ComplexNode* head5 = new ComplexNode(5);

	head1->_next = head2;
    head2->_next = head3;
    head3->_next = head4;
    head4->_next = head5;
    
	head1->_random = head3;
	head2->_random = head4;
	head3->_random = head1;
	head5->_random = head2;
	return head1;
}
void PrintComplexLinkList(ComplexNode* list)
{
	while(list)
	{
		cout << list->_data ;
		if(list->_random != NULL)
		{
			cout << ":"<< list->_random->_data;
		} 
		cout<<" ";
		list = list->_next;
	}
	cout <<endl;
}
void Test()
{
	ComplexNode* list1 = CreateComplexLinkList();
	PrintComplexLinkList(list1);
	ComplexNode* list2 = CopyComplexLinkList(list1);
	PrintComplexLinkList(list2);
}
int main()
{
	Test();
	getchar();
	return 0;
}