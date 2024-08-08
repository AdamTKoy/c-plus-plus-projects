#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;

  CircularLinkedList(const CircularLinkedList<T>& source) {
    node_order_ = source.node_order_;
    if (source.head_ == nullptr) {
      return;
    }

    Node<T>* tmp = new Node<T>(source.head_->data);
    Node<T>* current = source.head_;
    head_ = tail_ = tmp;

    while (current->next != source.head_) {
      tmp = new Node<T>(current->next->data);
      tail_->next = tmp;
      tail_ = tmp;
      current = current->next;
    }
    tail_->next = head_;
  }

  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source) {
    if (this == &source) {
      return *this;
    }
    Clear();
    node_order_ = source.node_order_;
    if (source.head_ == nullptr) {
      return *this;
    }

    Node<T>* tmp = new Node<T>(source.head_->data);
    Node<T>* current = source.head_;
    head_ = tail_ = tmp;

    while (current->next != source.head_) {
      tmp = new Node<T>(current->next->data);
      tail_->next = tmp;
      tail_ = tmp;
      current = current->next;
    }
    tail_->next = head_;
    return *this;
  }

  ~CircularLinkedList() {
    if (head_ != nullptr) Clear();
  }

  void InsertInOrder(const T& data) {
    Node<T>* nn = new Node<T>(data);

    // add first Node to EMPTY LIST
    if (head_ == nullptr) {
      head_ = tail_ = nn;
      nn->next = head_;
      return;
    }

    // add to SINGLE NODE LIST
    if (head_ == tail_) {
      InsertToSingleNodeList(nn);
      return;
    }

    // add to MULTI-NODE LIST
    InsertToMultiNodeList(nn);
  }

  void Reverse() {
    if (node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }

    if (head_ == nullptr || head_ == tail_) return;

    Node<T>* curr = head_;
    Node<T>* nxt = curr->next;
    Node<T>* nxt_nxt = nxt->next;

    while (nxt != head_) {
      nxt->next = curr;
      curr = nxt;
      nxt = nxt_nxt;
      nxt_nxt = nxt->next;
    }
    nxt->next = curr;
    head_ = curr;
    tail_ = nxt;
  }

  void Clear() {
    Node<T>* nxt = nullptr;

    while (head_ != tail_) {
      nxt = head_->next;
      delete head_;
      head_ = nxt;
    }
    delete head_;

    node_order_ = Order::kASC;
    head_ = tail_ = nullptr;
  }

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;

  // template <typename T>
  void InsertToSingleNodeList(Node<T>* nn) {
    T val = head_->data;
    T data = nn->data;
    // add to FRONT
    if ((data <= val && node_order_ == Order::kASC) ||
        (data >= val && node_order_ == Order::kDESC)) {
      head_ = nn;
      head_->next = tail_;
      tail_->next = nn;
    } else {  // add to BACK
      tail_ = nn;
      head_->next = tail_;
      tail_->next = head_;
    }
  }

  void InsertToMultiNodeList(Node<T>* nn) {
    T data = nn->data;
    T head_val = head_->data;
    // First check if adding to FRONT:
    if ((node_order_ == Order::kASC && data <= head_val) ||
        (node_order_ == Order::kDESC && data >= head_val)) {
      nn->next = head_;
      head_ = nn;
      tail_->next = nn;
      return;
    }
    // Then check if adding to BACK:
    T tail_val = tail_->data;
    if ((node_order_ == Order::kASC && data >= tail_val) ||
        (node_order_ == Order::kDESC && data <= tail_val)) {
      tail_->next = nn;
      tail_ = nn;
      tail_->next = head_;
      return;
    }
    Node<T>* curr = head_;
    Node<T>* nxt = head_->next;
    T nxt_val = nxt->data;
    if (node_order_ == Order::kASC) {
      while ((nxt_val < data) && (nxt != head_)) {
        curr = nxt;
        nxt = curr->next;
        nxt_val = nxt->data;
      }
    } else {
      while ((nxt_val > data) && (nxt != head_)) {
        curr = nxt;
        nxt = curr->next;
        nxt_val = nxt->data;
      }
    }
    curr->next = nn;
    nn->next = nxt;
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif