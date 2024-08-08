#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  // std::cout << first->ToString() << std::endl;  // hi
  // std::cout << first->Size() << std::endl;      // 2

  // /////////////////////////////////////

  // first->Join(1, second);

  // std::cout << first->ToString() << std::endl;  // hii!@
  // std::cout << first->Size() << std::endl;      // 5

  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  BLL* first_clone = new BLL();
  *first_clone = *first;

  std::cout << first_clone->ToString() << std::endl;  // hi
  std::cout << first_clone->Size() << std::endl;      // 2

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  std::cout << second->ToString() << std::endl;  // i!@
  std::cout << second->Size() << std::endl;      // 3

  *first_clone = *second;
  std::cout << first_clone->ToString() << std::endl;  // i!@
  std::cout << first_clone->Size() << std::endl;      // 3

  // testing self-assignment
  *first_clone = *first_clone;
  std::cout << first_clone->ToString() << std::endl;  // i!@
  std::cout << first_clone->Size() << std::endl;      // 3

  BLL* empt = new BLL();
  *first_clone = *empt;
  std::cout << first_clone->ToString() << std::endl;  //
  std::cout << first_clone->Size() << std::endl;      // 0

  // /////////////////////////////////////

  // testing copy constructor:
  // BLL* third = new BLL(*second);

  // std::cout << third->ToString() << std::endl;  // i!@
  // std::cout << third->Size() << std::endl;      // 3

  // /////////////////////////////////////

  // testing GetAt
  // std::cout << first->GetAt(3) << std::endl;   // !
  // std::cout << second->GetAt(2) << std::endl;  // @

  // /////////////////////////////////////

  // testing SetAt
  // >>> if I 'join' two BLLs, does that mean I can modify via 2 objects?
  // first->SetAt(2, 'p');
  // second->SetAt(0, 'x');
  // std::cout << first->ToString() << std::endl;   // hix!@ (?)
  // std::cout << second->ToString() << std::endl;  // x!@

  // /////////////////////////////////////

  // testing IsBLLAcyclic
  // BLL* t1 = new BLL();
  // t1->PushBack('V');
  // t1->PushBack('I');

  // BLL* t2 = new BLL();
  // t2->PushBack('B');

  // BLL* t3 = new BLL();
  // t3->PushBack('E');

  // t1->Join(1, t2);
  // std::cout << t1->ToString() << std::endl;

  // t2->Join(0, t3);
  // std::cout << t1->ToString() << std::endl;

  // This works and will cause logic_error to be thrown
  // t3->Join(0, t2);

  return 0;
}
