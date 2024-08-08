#include "illini_book.hpp"
#include "utilities.hpp"
#include <iostream>

int main() {

  IlliniBook ib("/Users/adam/Desktop/cs128env/src/mp-illini-book-AdamTKoy/example/persons.csv", 
                "/Users/adam/Desktop/cs128env/src/mp-illini-book-AdamTKoy/example/relations.csv");

  
  // std::cout << "are 1 and 3 related? " << ib.AreRelated(1, 3) << std::endl;
  // std::cout << "are 1 and 9 related? " << ib.AreRelated(1, 9) << std::endl;

  // std::cout << "are 1 and 3 related by 128? " << ib.AreRelated(1, 3, "128") << std::endl;
  // std::cout << "are 2 and 7 related by 128? " << ib.AreRelated(2, 7, "128") << std::endl;

  std::cout << "CountGroups(): " << ib.CountGroups() << std::endl;
  std::cout << "CountGroups(128): " << ib.CountGroups("128") << std::endl;
  std::cout << "CountGroups(124): " << ib.CountGroups("124") << std::endl;
  std::cout << "CountGroups(173): " << ib.CountGroups("173") << std::endl;

  std::cout << "CountGroups(128, 173): " 
            << ib.CountGroups(std::vector<std::string>{ "128", "173" }) << std::endl;

  std::cout << "CountGroups(128, 124, 173): " 
            << ib.CountGroups(std::vector<std::string>{ "128", "124", "173" }) << std::endl;


  std::cout << "GetRelated(1, 7): " << ib.GetRelated(1, 7) << std::endl;
  std::cout << "GetRelated(15, 9): " << ib.GetRelated(15, 9) << std::endl;
  std::cout << "GetRelated(11, 15): " << ib.GetRelated(11, 15) << std::endl;

  std::vector<int> gs = ib.GetSteps(1,2);
  std::cout << "GetSteps(1, 2): { ";
  for (const auto& x : gs) {
    std::cout << x << " ";
  }
  std::cout << "}" << std::endl;

  std::vector<int> gs2 = ib.GetSteps(1,1);
  std::cout << "GetSteps(1, 1): { ";
  for (const auto& x : gs2) {
    std::cout << x << " ";
  }
  std::cout << "}" << std::endl;

  std::vector<int> gs3 = ib.GetSteps(1,3);
  std::cout << "GetSteps(1, 3): { ";
  for (const auto& x : gs3) {
    std::cout << x << " ";
  }
  std::cout << "}" << std::endl;

  std::vector<int> gs4 = ib.GetSteps(9,1);
  std::cout << "GetSteps(9, 1): { ";
  for (const auto& x : gs4) {
    std::cout << x << " ";
  }
  std::cout << "}" << std::endl;


  std::cout << "More examples from site: " << std::endl;
  std::cout << "ib.AreRelated(1,2): " << ib.AreRelated(1,2) << std::endl;
  std::cout << "ib.AreRelated(3,2): " << ib.AreRelated(3,2) << std::endl;
  std::cout << "ib.AreRelated(1,9): " << ib.AreRelated(1,9) << std::endl;

  std::cout << "ib.AreRelated(1,2,128): " << ib.AreRelated(1,2,"128") << std::endl;
  std::cout << "ib.AreRelated(1,2,124): " << ib.AreRelated(1,2,"124") << std::endl;
  std::cout << "ib.AreRelated(1,6,128): " << ib.AreRelated(1,6,"128") << std::endl;
  std::cout << "ib.AreRelated(1,6,124): " << ib.AreRelated(1,6,"124") << std::endl;
  
  std::cout << "ib.GetRelated(1,2): " << ib.GetRelated(1,2) << std::endl;
  std::cout << "ib.GetRelated(3,2): " << ib.GetRelated(3,2) << std::endl;
  std::cout << "ib.GetRelated(1,9): " << ib.GetRelated(1,9) << std::endl;
  
  std::cout << "ib.GetRelated(1,2,128): " << ib.GetRelated(1,2,"128") << std::endl;
  std::cout << "ib.GetRelated(1,2,124): " << ib.GetRelated(1,2,"124") << std::endl;
  std::cout << "ib.GetRelated(1,6,128): " << ib.GetRelated(1,6,"128") << std::endl;
  std::cout << "ib.GetRelated(1,6,124): " << ib.GetRelated(1,6,"124") << std::endl;

  //std::cout << ib;

  return 0;
}
