
// 0
expensive_operation();



// 1
for (int i = 0; i < n; ++i) {
  expensive_operation();
}



// 2
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < i; ++j) {
    expensive_operation();
  }
}



// 3
for (int i = 1; i <= n; i *= 2) {
  expensive_operation();
}



// 4
for (int i = 0; i < n; ++i) {
  for (int j = 1; j <= i; j *= 2) {
    expensive_operation();
  }
}



// 5
for (int i = 1; i <= n; i *= 2) {
  for (int j = 0; j < i; ++j) {
    expensive_operation();
  }
}



// 6
class LinkedList {
  struct Node {
    struct Node* next;
  }

  Node* head = nullptr;

public:
  void addNode()
  {
    if (head == nullptr) { // branches are often expensive operations.
      head = new Node;
    } else {
      Node* cur = head;
      while (cur->next) { // while loops are also branches.
        cur = cur->next;
      }
      cur->next = new Node;
    }
  }
};

LinkedList list;
for (int i = 0; i < n; ++i) {
  list.addNode();
}