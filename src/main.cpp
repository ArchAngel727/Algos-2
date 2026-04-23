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

std::vector<int> load_file(const char *str) {
  std::ifstream infile(str);
  std::string line;
  std::vector<int> values;

  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string str;

    iss >> str;

    values.push_back(std::stoi(str));
  }

  return values;
}

Node *find_by_value(Node *node, int val, std::vector<Node *> &path) {
  if (node == nullptr) {
    return nullptr;
  }

  path.push_back(node);

  if (node->value == val) {
    return node;
  }

  if (node->value > val) {
    return find_by_value(node->left_child, val, path);
  } else {
    return find_by_value(node->right_child, val, path);
  }

  return nullptr;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return 0;
  }

  std::vector<int> values = load_file(argv[1]);
  struct Node *root = new Node{values[0], nullptr, nullptr};

  for (const auto &val : values) {
    add_value(root, val);
  }

  if (argc == 2) {
    print_tree(root);
    return 0;
  }

  std::vector<Node *> path;
  std::vector<int> search_values = load_file(argv[2]);

  struct Node *ptr = find_by_value(root, search_values[0], path);

  if (ptr != nullptr) {
    std::cout << ptr->value << " found ";

    for (const auto &node : path) {
      std::cout << node->value;

      if (node->value != ptr->value) {
        std::cout << ", ";
      }
    }
  } else {
    std::cout << search_values[0] << " not found!";
  }

  return 0;
}
