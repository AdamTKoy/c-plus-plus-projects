#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include "utilities.hpp"

#include <map>
#include <set>
#include <string>
#include <vector>

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

private:
  // mapping a single vertex to a 2d vector (2 COLUMN) of other vertices and their relation
  std::map<int, std::vector<std::vector<std::string>>> graph_;
  bool AlreadySeen(const int& vertex, std::vector<int>& seen) const;
  bool AlreadySeen(const int& vertex, std::set<int>& seen) const;
  bool InRelationVector(const std::string& rel, const std::vector<std::string>& rel_vec) const;
};

#endif
