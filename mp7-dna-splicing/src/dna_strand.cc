#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  Node* nxt = nullptr;
  while (head_ != nullptr) {
      nxt = head_->next;
      delete head_;
      head_ = nullptr;
      head_ = nxt;
  }
  head_ = tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    unsigned int sz = StrLen(pattern);
    unsigned int idx = MatchingIndex(pattern);

    Node* current = head_;
    Node* nxt = nullptr;

    if (idx == 0) {
        for (unsigned int i = 0; i < sz; i++) {
            nxt = current->next;
            delete current;
            current = nullptr;
            current = nxt;
        }
        head_ = to_splice_in.head_;
        to_splice_in.tail_->next = current;  

    } else {
        for (unsigned int i = 0; i < idx-1; i++) {
            current = current->next;
        }

        nxt = current->next;
        current->next = to_splice_in.head_;
        current = nxt;

        for (unsigned int i = 0; i < sz; i++) {
            nxt = current->next;
            delete current;
            current = nxt;
        }
        to_splice_in.tail_->next = current;
    }

    to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}


unsigned int DNAstrand::StrLen(const char* c_str) {
  const char kDelim = '\0';
  unsigned int count = 0;
  while (c_str[count] != kDelim) {
    count++;
  }
  return count;
}

const char* DNAstrand::ListToString() {
    if (head_ == nullptr) {
        throw std::invalid_argument("Cannot convert empty list to c-style string");
    }

    unsigned int sz = GetListLength();
    char* list_cstr = new char[sz+1];
    Node* current = head_;
    for (unsigned int i = 0; i < sz; i++) {
        list_cstr[i] = current->data;
        current = current->next;
    }
    list_cstr[sz] = '\0';
    return list_cstr;
}

unsigned int DNAstrand::GetListLength() {
    unsigned int sz = 0;
    Node* current = head_;
    while (current != nullptr) {
        sz++;
        current = current->next;
    }
    return sz;
}

unsigned int DNAstrand::MatchingIndex(const char* pattern) {
    const char* lst = ListToString();
    unsigned int pattern_sz = StrLen(pattern);
    unsigned int list_sz = StrLen(lst);

    if (pattern_sz > list_sz) {
        delete lst;
        throw std::invalid_argument("Pattern larger than strand.");
    }
  
    unsigned int num_found_char = 0;
    unsigned int pattern_idx = pattern_sz - 1;
    bool done = false;
    unsigned int lst_idx = list_sz - 1;

    while (!done) {
        if (lst_idx == 0) done = true;
        // look for last char of pattern
        if (lst[lst_idx] == pattern[pattern_idx]) {
            num_found_char++;
            if (pattern_idx > 0) pattern_idx--;
        } else {
            num_found_char = 0;
            pattern_idx = pattern_sz - 1;
            if (lst[lst_idx] == pattern[pattern_idx]) {
                num_found_char++;
                if (pattern_idx > 0) pattern_idx--;
            }
        }
        if (num_found_char == pattern_sz) {
            delete lst;
            return lst_idx;
        } 
        if (lst_idx > 0) lst_idx--;
    }
    delete lst;
    throw std::invalid_argument("Pattern not in list.");
}

void DNAstrand::SetHead(Node* start) {
    head_ = start;
}

void DNAstrand::SetTail(Node* stop) {
    tail_ = stop;
}