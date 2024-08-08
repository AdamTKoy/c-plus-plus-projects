#include <cassert>
#include <iostream>

#include "cord-utilities.hpp"
#include "cord.hpp"

int main() {

  // 'CONSTRUCTOR' WORKS
  // std::shared_ptr<Cord> t1 = std::make_shared<Cord>("he");
  // std::shared_ptr<Cord> t2 = std::make_shared<Cord>("llo");
  // std::shared_ptr<Cord> t3 = std::make_shared<Cord>("wor");
  // std::shared_ptr<Cord> t4 = std::make_shared<Cord>("ld");
  // std::shared_ptr<Cord> j1 = ConcatCords(t1, t2);
  // std::shared_ptr<Cord> j2 = ConcatCords(t3, t4);
  // std::shared_ptr<Cord> j = ConcatCords(j1, j2);

  // std::shared_ptr<Cord> t1_sub = t1->SubString(0,2);
  // std::cout << t1_sub->ToString() << std::endl;

  // std::shared_ptr<Cord> t2_sub = t2->SubString(0,3);
  // std::cout << t2_sub->ToString() << std::endl;

  // std::shared_ptr<Cord> t3_sub = t3->SubString(0,3);
  // std::cout << t3_sub->ToString() << std::endl;

  // std::shared_ptr<Cord> t4_sub = t4->SubString(0,2);
  // std::cout << t4_sub->ToString() << std::endl;

  // std::shared_ptr<Cord> j1_sub = j1->SubString(0,5);
  // std::cout << j1_sub->ToString() << std::endl;

  // std::shared_ptr<Cord> j2_sub = j2->SubString(0,5);
  // std::cout << j2_sub->ToString() << std::endl;
  
  // std::cout << j->ToString() << std::endl;
  // std::cout << "Length: " << j->Length() << std::endl;

  // 'TOSTRING' WORKS
  // std::shared_ptr<Cord> c4 = std::make_shared<Cord>("8 is awe");
  // std::shared_ptr<Cord> c5 = std::make_shared<Cord>("some");
  // std::shared_ptr<Cord> c2 = std::make_shared<Cord>("CS12");
  // std::shared_ptr<Cord> c3 = ConcatCords(c4, c5);
  // std::shared_ptr<Cord> c1 = ConcatCords(c2, c3);

  // std::cout << c1->ToString() << std::endl;
  // std::cout << "Length: " << c1->Length() << std::endl;

  // 'SUBSTRING' WORKS
  // std::shared_ptr<Cord> j_sub28 = j->SubString(2,8);
  // std::cout << j_sub28->ToString() << std::endl;

  // std::shared_ptr<Cord> j_sub27 = j->SubString(2,7);
  // std::cout << j_sub27->ToString() << std::endl;

  // std::shared_ptr<Cord> j_sub36 = j->SubString(3,6);
  // std::cout << j_sub36->ToString() << std::endl;

  // std::shared_ptr<Cord> j_sub35 = j->SubString(3,5);
  // std::cout << j_sub35->ToString() << std::endl;

  // std::shared_ptr<Cord> j_sub39 = j->SubString(3,9);
  // std::cout << j_sub39->ToString() << std::endl;

  std::shared_ptr<Cord> p1 = std::make_shared<Cord>("pre");
  std::shared_ptr<Cord> p2 = std::make_shared<Cord>("po");
  std::shared_ptr<Cord> p3 = std::make_shared<Cord>("sse");
  std::shared_ptr<Cord> p4 = std::make_shared<Cord>("ssion");
  std::shared_ptr<Cord> k1 = ConcatCords(p3, p4);
  std::shared_ptr<Cord> k2 = ConcatCords(p2, k1);
  std::shared_ptr<Cord> k = ConcatCords(p1, k2);

  std::cout << k->ToString() << std::endl;

  // std::shared_ptr<Cord> k_sub = k->SubString(1,1);
  // std::cout << k_sub->ToString() << std::endl;

  // 'AT' WORKS
  // std::cout << "j at index 0: " << j->At(0) << std::endl;
  // std::cout << "j at index 1: " << j->At(1) << std::endl;
  // std::cout << "j at index 2: " << j->At(2) << std::endl;
  // std::cout << "j at index 3: " << j->At(3) << std::endl;
  // std::cout << "j at index 4: " << j->At(4) << std::endl;
  // std::cout << "j at index 5: " << j->At(5) << std::endl;
  // std::cout << "j at index 6: " << j->At(6) << std::endl;
  // std::cout << "j at index 7: " << j->At(7) << std::endl;
  // std::cout << "j at index 8: " << j->At(8) << std::endl;
  // std::cout << "j at index 9: " << j->At(9) << std::endl;

  // testing ReduceCords
  // std::shared_ptr<Cord> a1 = std::make_shared<Cord>("pre");
  // std::shared_ptr<Cord> a2 = std::make_shared<Cord>("po");
  // std::shared_ptr<Cord> a3 = std::make_shared<Cord>("sse");
  // std::shared_ptr<Cord> a4 = std::make_shared<Cord>("ssion");
  // std::shared_ptr<Cord> aa1 = ConcatCords(a3, a4);
  // std::shared_ptr<Cord> aa2 = ConcatCords(a2, aa1);
  // std::shared_ptr<Cord> a = ConcatCords(a1, aa2);

  // std::shared_ptr<Cord> b1 = std::make_shared<Cord>("nonpo");
  // std::shared_ptr<Cord> b2 = std::make_shared<Cord>("ssession");
  // std::shared_ptr<Cord> b = ConcatCords(b1, b2);

  // std::shared_ptr<Cord> c = std::make_shared<Cord>("possession");
  // std::shared_ptr<Cord> c_sub = c->SubString(0,7);
  // std::cout << c_sub->ToString() << std::endl;


  // std::shared_ptr<Cord> d1 = std::make_shared<Cord>("fe");
  // std::shared_ptr<Cord> d2 = std::make_shared<Cord>("ssion");
  // std::shared_ptr<Cord> d3 = std::make_shared<Cord>("pro");
  // std::shared_ptr<Cord> dd1 = ConcatCords(d1, d2);
  // std::shared_ptr<Cord> d = ConcatCords(d3, dd1);

  // std::cout << "a: " << a->ToString() << std::endl;
  // std::cout << "b: " << b->ToString() << std::endl;
  // std::cout << "c: " << c->ToString() << std::endl;
  // std::cout << "d: " << d->ToString() << std::endl;

  // cs128::ReferenceList<std::shared_ptr<Cord>> lst = {a, b, c, d};
  // ReduceCords(lst);

  // std::cout << "a: " << a->ToString() << std::endl;
  // std::cout << "b: " << b->ToString() << std::endl;
  // std::cout << "c: " << c->ToString() << std::endl;
  // std::cout << "d: " << d->ToString() << std::endl;

  return 0;
}
