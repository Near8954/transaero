//
// Created by Роман Балдин on 16.12.2024.
//

#ifndef CHECKER_H
#define CHECKER_H

#include "../tid/tid.h"

class checker {
public:
  checker() { cur_ = new Node; }

  ~checker() {
    while (cur_->p != nullptr)
      cur_ = cur_->p;
    clear(cur_);
  }

  bool checkId(std::string &id) { return checkIdRec(cur_, id); }

  void pushId(lexemeType type, std::string id) { cur_->td.pushId(type, id); }

  lexemeType getType(std::string id) {
    if (!checkId(id))
      throw 6;
    Node *pointer = cur_;
    while (!pointer->td.checkId(id))
      pointer = pointer->p;
    return pointer->td.getType(id);
  }

  void createScope() {
    cur_->children.push_back(new Node);
    cur_->children.back()->p = cur_;
    cur_ = cur_->children.back();
  }

  void exitScope() { cur_ = cur_->p; }

  struct Node {
    tid td = tid();
    std::vector<Node *> children;
    Node *p = nullptr;
  };

  bool checkIdRec(Node *node, std::string &id) {
    if (node == nullptr)
      return false;
    if (node->td.checkId(id))
      return true;
    return checkIdRec(node->p, id);
  }

  void clear(Node *node) {
    for (Node *child : node->children)
      clear(child);
    delete node;
  }

  Node *cur_;
};



#endif //CHECKER_H
