#include "cord-utilities.hpp"

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord, std::shared_ptr<Cord> right_cord) {
  if (!left_cord->IsValidCord() || !right_cord->IsValidCord()) {
    throw std::invalid_argument("Invalid cord provided");
  }
  std::shared_ptr<Cord> new_left = std::move(left_cord);
  std::shared_ptr<Cord> new_right = std::move(right_cord);
  return std::make_shared<Cord>(new_left, new_right);
}

void ReduceCords (cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  // traverse cords in order and replace any duplicates you've seen before
  std::map<std::string, std::shared_ptr<Cord>> cord_map;
  for (std::shared_ptr<Cord>& c : cords) {
    InsertCords(c, cord_map);
  }
}

void InsertCords(std::shared_ptr<Cord>& c, std::map<std::string, std::shared_ptr<Cord>>& cm) {
  if (cm.find(c->ToString()) != cm.end()) { // already exists in map!
    c = cm.find(c->ToString())->second;
  } else {  // not already in map; add
    cm.insert(std::pair<std::string, std::shared_ptr<Cord>>(c->ToString(), c));
    if (c->left_ != nullptr) {
      InsertCords(c->left_, cm);
    }
    if (c->right_ != nullptr) {
      InsertCords(c->right_, cm);
    }
  }
}
