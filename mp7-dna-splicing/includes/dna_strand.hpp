#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  // HELPERS
  unsigned int StrLen(const char* c_str);
  unsigned int MatchingIndex(const char* pattern);
  const char* ListToString();
  unsigned int GetListLength();
  void SetHead(Node* start);
  void SetTail(Node* stop);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif