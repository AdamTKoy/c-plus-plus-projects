#include "illini_book.hpp"

#include <fstream>
#include <queue>

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream ifs(people_fpath, std::ios::in);
    std::string vtx;
    
    while (std::getline(ifs, vtx)) {
        // inserts a vertex with associated blank 2d vector
        std::vector<std::vector<std::string>> vec;
        int id = stoi(vtx);
        graph_.insert(std::pair<int, std::vector<std::vector<std::string>>>(id, vec));
    }
    ifs.close();

    std::ifstream ifs2(relations_fpath, std::ios::in);
    std::string rel;
    std::vector<std::string> splt_ln;

    while (std::getline(ifs2, rel)) {
        std::vector<std::string> splt = utilities::Split(rel, ',');
        // splt.at(0) is first vertex, splt.at(1) is second vertex
        // splt.at(2) is relationship
        int v0 = stoi(splt.at(0));
        int v1 = stoi(splt.at(1));

        std::vector<std::string> r1 = { splt.at(1), splt.at(2)};
        std::vector<std::string> r2 = { splt.at(0), splt.at(2)};
        graph_.find(v0)->second.push_back(r1);
        graph_.find(v1)->second.push_back(r2);
    }
    ifs2.close();
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    return (GetRelated(uin_1, uin_2) != -1);
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    return (GetRelated(uin_1, uin_2, relationship) != -1);
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    if (graph_.find(uin_1)->second.empty()) return -1;  // unconnected vertices
    if (graph_.find(uin_2)->second.empty()) return -1;
    std::queue<int> q;
    std::vector<int> seen;
    q.push(uin_1);
    seen.push_back(uin_1);

    std::map<int, int> dist;  // map of dist from 'uin_1' for each vertex
    dist.insert(std::pair<int, int>(uin_1, 0));

    std::map<int, int> prev;  // map of prev vertices for each
    prev.insert(std::pair<int, int>(uin_1, 0));

    while (!q.empty()) {
        int curr = q.front();
        std::vector<std::vector<std::string>> relations = graph_.find(curr)->second;
        q.pop();

        if (curr != uin_1) {
            int pvd = dist.find(prev.find(curr)->second)->second + 1;
            dist.insert(std::pair<int, int>(curr, pvd));
        }

        if (curr == uin_2) return dist.find(curr)->second;

        for (const auto& row : relations) {
            int v = stoi(row.at(0));
            if (!AlreadySeen(v, seen)) {
                q.push(v);
                seen.push_back(v);
                prev.insert(std::pair<int, int>(v, curr));
            }
        }
    }
    return -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (graph_.find(uin_1)->second.empty()) return -1;  // unconnected vertices
    if (graph_.find(uin_2)->second.empty()) return -1;
    std::queue<int> q;
    std::vector<int> seen;
    q.push(uin_1);
    seen.push_back(uin_1);

    std::map<int, int> dist;  // map of dist from 'uin_1' for each vertex
    dist.insert(std::pair<int, int>(uin_1, 0));

    std::map<int, int> prev;  // map of prev vertices for each
    prev.insert(std::pair<int, int>(uin_1, 0));

    while (!q.empty()) {
        int curr = q.front();
        std::vector<std::vector<std::string>> relations = graph_.find(curr)->second;
        q.pop();

        if (curr != uin_1) {
            int pvd = dist.find(prev.find(curr)->second)->second + 1;
            dist.insert(std::pair<int, int>(curr, pvd));
        }

        if (curr == uin_2) return dist.find(curr)->second;

        for (const auto& row : relations) {
            int v = stoi(row.at(0));
            if (!AlreadySeen(v, seen) && row.at(1) == relationship) {
                q.push(v);
                seen.push_back(v);
                prev.insert(std::pair<int, int>(v, curr));
            }
        }
    }
    return -1;
}

bool IlliniBook::AlreadySeen(const int& vertex, std::vector<int>& seen) const {
  for (const auto& vtx : seen) {
    if (vtx == vertex) return true;
  }
  return false;
}

bool IlliniBook::AlreadySeen(const int& vertex, std::set<int>& seen) const {
  for (const auto& vtx : seen) {
    if (vtx == vertex) return true;
  }
  return false;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int> steps;
    if (graph_.find(uin)->second.empty()) return steps; // returns empty vector
    std::queue<int> q;
    std::vector<int> seen;
    q.push(uin);
    seen.push_back(uin);
    std::map<int, int> dist;  // map of dist from 'uin' for each vertex
    dist.insert(std::pair<int, int>(uin, 0));
    std::map<int, int> prev;  // map of prev vertices for each
    prev.insert(std::pair<int, int>(uin, 0));

    while (!q.empty()) {
        int curr = q.front();
        std::vector<std::vector<std::string>> relations = graph_.find(curr)->second;
        q.pop();

        if (curr != uin) {
            int pvd = dist.find(prev.find(curr)->second)->second + 1;
            dist.insert(std::pair<int, int>(curr, pvd));
        }

        for (const auto& row : relations) {
            int v = stoi(row.at(0));
            if (!AlreadySeen(v, seen)) {
                q.push(v);
                seen.push_back(v);
                prev.insert(std::pair<int, int>(v, curr));
            }
        }
    }

    for (const auto& item : dist) {
        if (item.second == n)
            steps.push_back(item.first);
    }
    return steps;
}

size_t IlliniBook::CountGroups() const {
    std::vector<std::vector<int>> grps;
    std::set<int> seen;
    
    for (const auto& node : graph_) {
        if (!AlreadySeen(node.first, seen)) {
            std::vector<int> box;
            box.push_back(node.first);
            std::queue<int> q;
            q.push(node.first);
            seen.insert(node.first);
            
            while (!q.empty()) {
                int x = q.front();
                std::vector<std::vector<std::string>> relations = graph_.find(x)->second;
                q.pop();

                for (const auto& row : relations) {
                    int v = stoi(row.at(0));
                    if (!AlreadySeen(v, seen)) {
                        q.push(v);
                        seen.insert(v);
                        box.push_back(v);
                    }
                }
            }
            grps.push_back(box);
        }
        
    }
    return grps.size();
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::vector<std::vector<int>> grps;
    std::set<int> seen;
    
    for (const auto& node : graph_) {
        if (!AlreadySeen(node.first, seen)) {
            std::vector<int> box;
            box.push_back(node.first);
            std::queue<int> q;
            q.push(node.first);
            seen.insert(node.first);
            
            while (!q.empty()) {
                int x = q.front();
                std::vector<std::vector<std::string>> relations = graph_.find(x)->second;
                q.pop();

                for (const auto& row : relations) {
                    int v = stoi(row.at(0));
                    if (!AlreadySeen(v, seen) && row.at(1) == relationship) {
                        q.push(v);
                        seen.insert(v);
                        box.push_back(v);
                    }
                }
            }
            grps.push_back(box);
        }
        
    }
    return grps.size();
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::vector<std::vector<int>> grps;
    std::set<int> seen;
    
    for (const auto& node : graph_) {
        if (!AlreadySeen(node.first, seen)) {
            std::vector<int> box;
            box.push_back(node.first);
            std::queue<int> q;
            q.push(node.first);
            seen.insert(node.first);
            
            while (!q.empty()) {
                int x = q.front();
                std::vector<std::vector<std::string>> relations = graph_.find(x)->second;
                q.pop();

                for (const auto& row : relations) {
                    int v = stoi(row.at(0));
                    if (!AlreadySeen(v, seen) && InRelationVector(row.at(1), relationships)) {
                        q.push(v);
                        seen.insert(v);
                        box.push_back(v);
                    }
                }
            }
            grps.push_back(box);
        }
    }
    return grps.size();
}

bool IlliniBook::InRelationVector(const std::string& rel, const std::vector<std::string>& rel_vec) const {
    for (const auto& item : rel_vec) {
        if (item == rel) return true;
    }
    return false;
}

