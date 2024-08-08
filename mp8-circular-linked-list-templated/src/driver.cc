#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll;
  cll.InsertInOrder(12);
  cll.InsertInOrder(10);
  cll.InsertInOrder(13);
  cll.InsertInOrder(11);
  cll.InsertInOrder(14);
  std::cout << cll << std::endl;
  cll.Reverse();
  std::cout << cll << std::endl;

  CircularLinkedList<int> cll1;
  cll1.InsertInOrder(13);
  cll1.InsertInOrder(1);
  cll1.InsertInOrder(21);
  cll1.InsertInOrder(2);
  cll1.InsertInOrder(5);

  CircularLinkedList<int> cll2(cll);
  std::cout << cll2 << std::endl;

  CircularLinkedList<int> cll3 = cll;
  std::cout << cll3 << std::endl;

  cll3 = cll1;
  std::cout << cll3 << std::endl;
}
