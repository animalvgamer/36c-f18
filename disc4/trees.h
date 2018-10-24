#ifndef __TREES_H__
#define __TREES_H__

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class SiblingTree;

template <typename T>
std::ostream &operator<<(std::ostream& out, SiblingTree<T> &tree);

template <typename T>
class SiblingTree {
 public:
  class Node {
   public:
    std::unique_ptr<Node> firstChild;
    std::unique_ptr<Node> sibling;
    T data;

    size_t getBreadth();
  };
  class Path {
   public:
    std::vector<size_t> childIndices;
  };
 protected:
  std::unique_ptr<Node> root;

 public:
  bool empty() const;
  T &getItem(Path p);
  void insertItem(Path p, const T &item);
  void removeNode(Path p);
  void preOrderTraverse(std::function<void(T&)> func);

  friend std::ostream &operator<<<T>(std::ostream& out, SiblingTree<T> &tree);
};

#include "trees.cc"

#endif