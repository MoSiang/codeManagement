#include"HashTable.hpp"

void Test()
{
	//1.
	//HashTable<int,int> ht;
	//ht.Insert(2,2);
	//ht.Insert(4,4);
	//ht.Insert(7,7);
	//ht.Insert(9,9);
	//ht.Print();

	//cout<< ht.Find(2)->_key << ":"<<ht.Find(2)->_value <<endl;

	//ht.Remove(9);
	//ht.Print();

	//HashTable<int,int> ht2(ht);
	//ht2.Print();

	//ht2 = ht;
	//ht2.Print();

	/*HashTable<string,string> ht3;
	ht3.Insert("abcdefgh","abcdefgh");
	ht3.Insert("123456789","123456789");
	ht3.Print();*/


	//2.
	HashTable<int> ht(10);
	ht.Insert(8);
	ht.Insert(4);
	ht.Print();

}
int main()
{
	Test();
	getchar();
	return 0;
}