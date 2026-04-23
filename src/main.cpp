#include <algorithm>
#include <fstream>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>
#include <sstream>
#include <string>
#include <vector>

struct Node {
  int value = 0;
  Node *left_child = nullptr;
  Node *right_child = nullptr;
};

void add_value(Node *parent, int val) {
  if (parent == nullptr) {
    return;
  }

  if (parent->value == val) {
    return;
  }

  if (parent->value > val) {
    if (parent->left_child != nullptr) {
      add_value(parent->left_child, val);
      return;
    } else {
      struct Node *node = new Node{val, nullptr, nullptr};
      parent->left_child = node;
      return;
    }
  }

  if (parent->value < val) {
    if (parent->right_child != nullptr) {
      add_value(parent->right_child, val);
      return;
    } else {
      struct Node *node = new Node{val, nullptr, nullptr};
      parent->right_child = node;
      return;
    }
  }
}

int calculate_height(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  return std::max(calculate_height(node->left_child),
                  calculate_height(node->right_child)) +
         1;
}

int calculate_balance_factor(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  return calculate_height(node->left_child) -
         calculate_height(node->right_child);
}

void print_tree(Node *node) {
  if (node == nullptr) {
    return;
  }

  int bf = calculate_balance_factor(node);

  print_tree(node->left_child);

  std::cout << "bal(" << node->value << ") = " << bf;

  if (bf > 1 || bf < -1) {
    std::cout << " (AVL violation!)";
  }

  std::cout << '\n';

  print_tree(node->right_child);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return 0;
  }

  std::ifstream infile(argv[1]);
  std::string line;
  std::vector<int> values;

  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string str;

    iss >> str;

    values.push_back(std::stoi(str));
  }

  struct Node *root = new Node{values[0], nullptr, nullptr};

  for (const auto &val : values) {
    add_value(root, val);
  }

  print_tree(root);

  return 0;
}
