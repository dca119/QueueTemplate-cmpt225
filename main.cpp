#include "QueueT.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

void simpleTest();

int main(){
    simpleTest();
    return 0;
}

void simpleTest()
{
	cout << "SIMPLE TEST" << endl;
	QueueT<int> q1;
 
	q1.enqueue(2);
	q1.enqueue(4);
	q1.enqueue(6);
 
	cout << "empty: 0 = " << q1.empty() << endl;
	cout << "print: {2,4,6} = ";
	q1.print();
	cout << endl << "size: 3 = " << q1.size() << endl;
 
	QueueT<int> q2(q1);
	QueueT<int> q3;
	q3 = q1;
 
	q1.dequeue();
 
	cout << "q1 post copy: {4,6} = ";
	q1.print();
	cout << endl << "q2 (copy): {2,4,6} = ";
	q2.print();
	cout << endl << "q3 (op=): {2,4,6} = ";
	q3.print();
 
	QueueT<int> q4;
	q4.enqueue(5);
 
	QueueT<int> q5(q1.merge(q4));
	cout << endl << "q5 (merge): {4,5,6} = ";
	q5.print();
 
	q1.concatenate(q4, 1);
	cout << endl << "q1 (concatenate): {4,6,5} = ";
	q1.print();
 
	NodeT<int>* front = q1.getFront();
	cout << endl << "front->next->data: 6 = " << front->next->data << endl;
	cout << "END SIMPLE TEST" << endl;
	
	cout << endl << "REAL TEST" << endl;
	cout << "q1 now: ";
	q1.print();
	cout << "q1 after: ";
	q1.dequeue();
	q1.dequeue();
	q1.dequeue();
	q1.print();
	cout << endl;

	cout << "String Test" << endl;

	QueueT<string> test1;
	test1.enqueue("First");
	test1.enqueue("Second");
	test1.enqueue("Third");
	test1.enqueue("Fourth");
	test1.enqueue("Fifth");
	cout << endl << "test1: {First, Second, Third, Fourth, Fifth} = ";
	test1.print();

	test1.dequeue();
	cout << endl << "test1 after remove: {Second, Third, Fourth, Fifth} = ";
	test1.print();

	QueueT<string> test2;
	test2.enqueue("Sixth");
	test2.enqueue("Seventh");
	cout << endl << "test2: {Sixth, Seventh} = ";
	test2.print();

	QueueT<string> test3 (test1.merge(test2));
	cout << endl << "test3 (merging test 1 and 2): {Second, Sixth, Third, Seventh, Fourth, Fifth} = ";
	test3.print();

	test1.concatenate(test3, 6);
	cout << endl << "concatenating test1 and test3: {Second, Third, Fourth, Fifth, Second, Sixth, Third, Seventh, Fourth, Fifth} = ";
	test1.print();
	cout << "test1 size 10 = " << test1.size();

	cout << endl << "printing test 3 after concatenate: {} = ";
	test3.print();
	cout << "test3 size 0 = " << test3.size() << endl; 

	QueueT<string> test4;
	test4.getFront();


}