#include "cord.hpp"
#include "cord-utilities.hpp"

Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord, const std::shared_ptr<Cord>& right_cord):
          left_(left_cord), right_(right_cord), length_(left_cord->length_ + right_cord->length_) {}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
    // case: cord is a leaf
    if (left_ == nullptr && right_ == nullptr)
      return data_;

    std::string output;
    if (left_ != nullptr)
      GetContents(output, left_);
    if (right_ != nullptr)
      GetContents(output, right_);
    return output;
}

void Cord::GetContents(std::string& out, const std::shared_ptr<Cord>& current) const {
  if (current->left_ == nullptr && current->right_ == nullptr) { // Leaf
    out += current->data_;
  } else {  // Non-leaf; keep drilling down
    if (current->left_ != nullptr) {
      GetContents(out, current->left_);
    }
    if (current->right_ != nullptr) {
      GetContents(out, current->right_);
    }
  }
}

std::shared_ptr<Cord> Cord::SubString(size_t lower_idx, size_t upper_idx) {
  if (lower_idx == 0 && upper_idx == length_) return shared_from_this();
  if (upper_idx > length_ || lower_idx < 0 || lower_idx >= length_ || lower_idx > upper_idx)
    throw std::invalid_argument("Error: invalid indices");
  if (lower_idx == upper_idx) return std::make_shared<Cord>("");
  std::map<size_t, std::shared_ptr<Cord>> cm;
  size_t curr_idx = 0, running_length = 0;

  if (left_ == nullptr && right_ == nullptr) {  // partial leaf
    std::string sub;
    for (size_t i = lower_idx; i < upper_idx; i++)
      sub += data_[i];
    return std::make_shared<Cord>(sub);
  }

  if (lower_idx < left_->length_) // only if necessary, check left child
    CheckChild(curr_idx, running_length, lower_idx, upper_idx, left_, cm);
  else running_length += left_->length_;
  if (running_length < upper_idx) // only if necessary, check right child
    CheckChild(curr_idx, running_length, lower_idx, upper_idx, right_, cm);

  std::map<size_t, std::shared_ptr<Cord>> cords;
  while (cm.size() != 1) {
    size_t i = 0, j = 0;
    while (!cm.empty()) {
      if (cm.size() > 1) {
        std::shared_ptr<Cord> c1 = ConcatCords(cm.at(i), cm.at(i+1));
        cm.erase(i);
        cm.erase(i+1);
        cords.insert(std::pair<size_t, std::shared_ptr<Cord>>(j, c1));
        i += 2;
        j++;
      } else {  // odd one left over
        cords.insert(std::pair<size_t, std::shared_ptr<Cord>>(j, cm.at(i)));
        cm.erase(i);  // cm should be empty now
      }
    }
    cords.swap(cm);
  }
  return cm.begin()->second;
}

void Cord::CheckChild(size_t& idx, size_t& rl, const size_t& lower, 
                      const size_t& upper, const std::shared_ptr<Cord>& current,
                      std::map<size_t, std::shared_ptr<Cord>>& cord_map) const {
  if (current->left_ == nullptr && current->right_ == nullptr) { // Leaf!
    if (lower < rl + current->length_) { // ok, at correct leaf
      if (lower <= rl && rl + current->length_ <= upper) {  // can re-use entire leaf!
        cord_map.insert(std::pair<size_t, std::shared_ptr<Cord>>(idx, current));
        idx++;
      } else {   // create NEW shared_ptr to Cord w/ partial data_ and push to MAP
        std::string dat = current->data_;
        std::string new_dat;
        size_t start_idx = 0;
        if (lower > rl) start_idx = lower - rl;
        for (size_t i = start_idx, j = rl + start_idx; (i < current->length_ && j < upper); i++, j++) {
          new_dat += dat[i];
        }
        std::shared_ptr<Cord> nd = std::make_shared<Cord>(new_dat);
        cord_map.insert(std::pair<size_t, std::shared_ptr<Cord>>(idx, nd));
        idx++;
      }
    }
    rl += current->length_;
  } else {   // NOT a leaf
    if (lower <= rl && upper >= rl + current->length_) { // include entire 'branch'
      cord_map.insert(std::pair<size_t, std::shared_ptr<Cord>>(idx, current));
      rl += current->length_;
      idx++;
    } else {
      if (current->left_ != nullptr && lower < rl + current->left_->length_) {
        CheckChild(idx, rl, lower, upper, current->left_, cord_map);
      } else {
        rl += current->left_->length_;
      }
      if (current->right_ != nullptr && rl < upper)
        CheckChild(idx, rl, lower, upper, current->right_, cord_map);
    }
  }
}

char Cord::At(size_t idx) const {
    // first check that idx is valid
    if (idx < 0 || idx >= length_) {
      throw std::invalid_argument("invalid index selection");
    }

    size_t rl = 0;

    if (left_ != nullptr && idx < left_->length_) { // it's within left child
      return FindChar(idx, rl, left_);
    } else if (right_ != nullptr) {  // it's within right child
      rl += left_->length_;
      return FindChar(idx, rl, right_);
    } else {   // at Leaf already
      return FindChar(idx, rl, shared_from_this());
    }
}

char Cord::FindChar(const size_t& idx, size_t& rl, const std::shared_ptr<const Cord>& current) const {
  if (current->left_ == nullptr && current->right_ == nullptr) {  // Leaf!
    size_t leaf_idx = idx - rl;
    return current->data_[leaf_idx];
  } else {    // keep drilling
    if (idx < rl + current->left_->length_) { // it's within left child
      return FindChar(idx, rl, current->left_);
    } else {  // it's within right child
      rl += current->left_->length_;
      return FindChar(idx, rl, current->right_);
    }
  }
}

bool Cord::IsValidCord() const {
  // cyclic: left or right child would point back to itself
  if (left_ == shared_from_this() || right_ == shared_from_this()) return false;
  
  // data exists in non-child
  if ((left_ != nullptr || right_ != nullptr) && !data_.empty()) return false;

  // not valid if length_ (of NON-leaf) is not sum of childrens' lengths
  if (left_ != nullptr || right_ != nullptr)
    if (length_ != left_->Length() + right_->Length()) return false;

  return true;
}

