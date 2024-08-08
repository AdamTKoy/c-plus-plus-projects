#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;
  bool TortHare(Node* tortoise, Node* hare) const;
  Node* GetNextNode(Node* first) const;

  Node* MoveTo(Node* curr, size_t idx, size_t& curr_idx) const;
  void Convert(Node* curr, std::string& output) const;
  void CountNodes(Node* node, size_t& count) const;
  void DeleteNodes(Node* node);
  Node* InsertNode(Node* node);
};

#endif
