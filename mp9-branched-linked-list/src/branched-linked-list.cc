#include "branched-linked-list.hpp"

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = InsertNode(to_copy.head_);
}

Node* BLL::InsertNode(Node* node) {
  Node* new_node = new Node(node->data_);

  if (node->next_bll_ != nullptr) {
    BLL* b = new BLL(*node->next_bll_);
    new_node->next_bll_ = b;
  }

  if (node->next_node_ != nullptr) {
    new_node->next_node_ = InsertNode(node->next_node_);
  }

  return new_node;
}

BLL::~BLL() {
  if (head_ == nullptr) return;

  DeleteNodes(head_);
  head_ = nullptr;
}

void BLL::DeleteNodes(Node* node) {
  delete node->next_bll_;

  if (node->next_node_ != nullptr) {
    DeleteNodes(node->next_node_);
  }

  delete node;
  node = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }

  if (head_ != nullptr) {
    DeleteNodes(head_);
    head_ = nullptr;
  }

  if (rhs.head_ != nullptr) {
    head_ = InsertNode(rhs.head_);
  }

  return *this;
}

Node* BLL::PushBack(char dat) {
  if (head_ == nullptr) {
    head_ = new Node(dat);
    return head_;
  }

  Node* curr = head_;

  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }

  curr->next_node_ = new Node(dat);

  return curr->next_node_;
}

char BLL::GetAt(size_t idx) const {
  if (idx < 0 || head_ == nullptr) {
    throw std::invalid_argument("negative index or empty BLL");
  }

  Node* curr = head_;
  size_t curr_idx = 0;

  curr = MoveTo(curr, idx, curr_idx);

  if (curr == nullptr) {
    throw std::invalid_argument("index out of range (too big)");
  }

  return curr->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0) {
    throw std::invalid_argument("negative index");
  }

  Node* curr = head_;
  size_t curr_idx = 0;

  curr = MoveTo(curr, idx, curr_idx);

  if (curr == nullptr) {
    throw std::invalid_argument("index out of range (too big)");
  }

  curr->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0) {
    throw std::invalid_argument("negative index");
  }

  Node* curr = head_;
  size_t curr_idx = 0;

  curr = MoveTo(curr, idx, curr_idx);

  if (curr == nullptr) {
    throw std::invalid_argument("index out of range (too big)");
  }

  if (curr->next_bll_ != nullptr) {
    throw std::invalid_argument("BLL already exists there");
  }

  curr->next_bll_ = list;

  if (!IsBLLAcyclic()) {
    throw std::logic_error("BLL is cyclic");
  }
}

Node* BLL::MoveTo(Node* curr, size_t idx, size_t& curr_idx) const {
  if (idx == curr_idx) return curr;

  Node* result = nullptr;
  curr_idx++;

  if (curr->next_bll_ != nullptr) {
    result = MoveTo(curr->next_bll_->head_, idx, curr_idx);
  }

  if (curr->next_node_ != nullptr) {
    result = MoveTo(curr->next_node_, idx, curr_idx);
  }

  return result;
}

bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) return true;
  if (head_->next_bll_ == nullptr && head_->next_node_ == nullptr) return true;

  Node* hare = GetNextNode(head_);

  return TortHare(head_, hare);
}

bool BLL::TortHare(Node* tortoise, Node* hare) const {
  if (tortoise == hare) return false;

  tortoise = GetNextNode(tortoise);

  hare = GetNextNode(hare);
  if (hare == nullptr) return true;
  hare = GetNextNode(hare);
  if (hare == nullptr) return true;

  return TortHare(tortoise, hare);
}

Node* BLL::GetNextNode(Node* first) const {
  if (first->next_bll_ != nullptr) {
    if (first->next_bll_->head_ != nullptr) return first->next_bll_->head_;
  }
  if (first->next_node_ != nullptr) {
    return first->next_node_;
  }
  return nullptr;
}

std::string BLL::ToString() const {
  std::string result;
  if (head_ == nullptr) return result;

  Convert(head_, result);
  return result;
}

void BLL::Convert(Node* curr, std::string& output) const {
  output += curr->data_;

  if (curr->next_bll_ != nullptr) {
    Convert(curr->next_bll_->head_, output);
  }

  if (curr->next_node_ != nullptr) {
    Convert(curr->next_node_, output);
  }
}

size_t BLL::Size() const {
  size_t sz = 0;
  if (head_ == nullptr) return sz;

  CountNodes(head_, sz);
  return sz;
}

void BLL::CountNodes(Node* node, size_t& count) const {
  count++;

  if (node->next_bll_ != nullptr) {
    CountNodes(node->next_bll_->head_, count);
  }

  if (node->next_node_ != nullptr) {
    CountNodes(node->next_node_, count);
  }
}
