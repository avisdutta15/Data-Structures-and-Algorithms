#include <iostream>
using namespace std;

struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

class LinkedList {
public:
    ListNode* removeNthFromEnd(ListNode *head, int n) {
        if (head == nullptr)
            return head;

        //if n = size of the list then we will modify the head. Hence keep a dummy head.
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* prev = dummyHead;
        ListNode* ptr1 = head, * ptr2 = head;
        int index = 1;
        while (ptr1 != nullptr && index != n) {
            ptr1 = ptr1->next;
            index++;
        }
        
        while (ptr1->next != nullptr) {
            //ptr2 is the final nth node so keep track of its prev
            prev = ptr2;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        ListNode* nodeToDelete = ptr2;
        prev->next = ptr2->next;
        delete(ptr2);
        ptr2 = nullptr;

        return dummyHead->next;
    }    
};

void printList(ListNode* node) {
	if (node == nullptr) {
		cout << "List is empty."<<endl;
		return;
	}
	while (node != nullptr) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

int main() {
	Solution obj;

	//Test 1
	ListNode* head1 = new ListNode(1);
	head1->next = new ListNode(2);
	head1->next->next = new ListNode(3);
	head1->next->next->next = new ListNode(4);
	head1->next->next->next->next = new ListNode(5);
	printList(head1);

	cout << "Removing 2nd node from end" << endl;
	ListNode* newHead = obj.removeNthFromEnd(head1, 2);
	printList(newHead);

	//Test 2
	ListNode* head2 = new ListNode(1);
	printList(head2);

	cout << "Removing 1st node from end" << endl;
	newHead = obj.removeNthFromEnd(head2, 1);
	printList(newHead);

	//Test 3
	ListNode* head3 = new ListNode(1);
	head3->next = new ListNode(2);
	printList(head3);

	cout << "Removing 1st node from end" << endl;
	newHead = obj.removeNthFromEnd(head3, 1);
	printList(newHead);


	//Test 4
	ListNode* head4 = new ListNode(1);
	head4->next = new ListNode(2);
	printList(head4);

	cout << "Removing 2nd node from end" << endl;
	newHead = obj.removeNthFromEnd(head4, 2);
	printList(newHead);

	return 0;
}