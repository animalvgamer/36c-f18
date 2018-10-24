#include <numeric>
#include <sstream>
#include <stack>
#include <string>

#define FIXED_WIDTH 6

template <typename T>
size_t SiblingTree<T>::Node::getBreadth() {
  if (!firstChild) return 1;

  Node* node_itr = firstChild.get();
  size_t breadth_sum = node_itr->getBreadth();
  while (node_itr = node_itr->sibling.get()) {
    breadth_sum += node_itr->getBreadth();
  }

  return breadth_sum;
}

template <typename T>
bool SiblingTree<T>::empty() const {
  return !static_cast<bool>(root);
}

template <typename T>
T& SiblingTree<T>::getItem(SiblingTree<T>::Path p) {
  Node* cur_node = root.get();
  for (int i = 0; i < p.childIndices.size(); ++i) {
    cur_node = cur_node->firstChild.get();
    for (int j = 0; j < p.childIndices[i]; ++j) {
      cur_node = cur_node->sibling.get();
    }
  }
  return cur_node->data;
}

template <typename T>
void SiblingTree<T>::insertItem(SiblingTree<T>::Path p, const T& item) {
  if (empty()) {
    root.reset(new Node);
    root->data = item;
    return;
  }

  Node* cur_node = root.get();
  for (int i = 0; i < p.childIndices.size(); ++i) {
    cur_node = cur_node->firstChild.get();
    for (int j = 0; j < p.childIndices[i]; ++j) {
      cur_node = cur_node->sibling.get();
    }
  }

  if (!cur_node->firstChild) {
    cur_node->firstChild.reset(new Node);
    cur_node->firstChild->data = item;
  } else {
    cur_node = cur_node->firstChild.get();
    while(cur_node->sibling) cur_node = cur_node->sibling.get();
    cur_node->sibling.reset(new Node);
    cur_node->sibling->data = item;
  }
}

template <typename T>
void SiblingTree<T>::removeNode(SiblingTree<T>::Path p) {
  if (p.childIndices.empty()) {
    root.reset();
    return;
  }

  Node* cur_node = root.get();
  for (int i = 0; i < p.childIndices.size() - 1; ++i) {
    cur_node = cur_node->firstChild.get();
    for (int j = 0; j < p.childIndices[i]; ++j) {
      cur_node = cur_node->sibling.get();
    }
  }

  const size_t final_index = p.childIndices.back();
  if (final_index == 0) {
    cur_node->firstChild = std::move(cur_node->firstChild->sibling);
  } else {
    cur_node = cur_node->firstChild.get();
    for (int i = 0; i < final_index - 1; ++i) {
      cur_node = cur_node->sibling.get();
    }
    cur_node->sibling = std::move(cur_node->sibling->sibling);
  }
}

static void produceIntermediateLine(std::ostream& out,
                                    std::vector<size_t> widths) {
  for (size_t gap : widths) {
    for (int i = 0; i < gap; ++i) out << ' ';
    out << '|';
  }
  out << std::endl;
  for (int i = 0; i < widths.size() - 1; ++i) {
    const size_t gap = widths[i];
    for (int i = 0; i < gap; ++i) out << ' ';
    out << '|';
  }
    for (int i = 0; i < widths.back(); ++i) out << ' ';
  out << "+-";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, SiblingTree<T>& tree) {
  if (tree.empty()) return out << "(empty tree)";

  std::stack<typename SiblingTree<T>::Node*> traverser;
  std::vector<size_t> additional_widths;

  out << std::endl;
  typename SiblingTree<T>::Node *cur_node = tree.root.get();
  while (cur_node) {
    std::stringstream stringifier;
    stringifier << cur_node->data;
    std::string stringified_value = stringifier.str();
    out << '[' << stringified_value << ']';
    if (cur_node->firstChild) {
      if (cur_node->sibling || additional_widths.empty()) {
        additional_widths.push_back(stringified_value.length() + 4 -
                                    (cur_node == tree.root.get() ? 1 : 0));
      } else {
        size_t merged_width = additional_widths.back() +
                              stringified_value.length() + 5 -
                              (cur_node == tree.root.get() ? 2 : 0);
        additional_widths.pop_back();
        additional_widths.push_back(merged_width);
      }
      traverser.push(cur_node);
      out << "-+-";
      cur_node = cur_node->firstChild.get();
      continue;
    }

    out << std::endl;
    if (cur_node->sibling) {
      cur_node = cur_node->sibling.get();
      produceIntermediateLine(out, additional_widths);
    } else {
      additional_widths.pop_back();
      while (!traverser.empty()) {
        cur_node = traverser.top();
        traverser.pop();
        if (cur_node->sibling) {
          cur_node = cur_node->sibling.get();
          produceIntermediateLine(out, additional_widths);
          break;
        }
      }
      if (traverser.empty()) {
        break;
      }
    }
  }

  return out;
}