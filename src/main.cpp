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

  return calculate_height(node->right_child) -
         calculate_height(node->left_child);
}

void print_tree(Node *node) {
  if (node == nullptr) {
    return;
  }

  int bf = calculate_balance_factor(node);

  print_tree(node->right_child);

  std::cout << "bal(" << node->value << ") = " << bf;

  if (bf > 1 || bf < -1) {
    std::cout << " (AVL violation!)";
  }

  std::cout << '\n';

  print_tree(node->left_child);
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

Node *find_by_value(Node *node, int val, std::vector<Node *> *path) {
  if (node == nullptr) {
    return nullptr;
  }

  if (path != nullptr) {
    path->push_back(node);
  }

  if (node->value == val) {
    return node;
  }

  if (node->value > val) {
    return find_by_value(node->left_child, val, path);
  }

  return find_by_value(node->right_child, val, path);
}

void find_subtree(Node *ptr, std::vector<int> &values) {
  for (size_t i = 0; i < values.size(); i++) {
    struct Node *p = find_by_value(ptr, values[i], nullptr);

    if (p == nullptr) {
      std::cout << "Subtree not found!";
      return;
    }
  }

  std::cout << "Subtree found";
}

Node *find_biggest_node(Node *node) {
  if (node == nullptr) {
    return node;
  }

  if (node->right_child == nullptr) {
    return node;
  } else {
    return find_biggest_node(node->right_child);
  }
}

Node *find_smallest_node(Node *node) {
  if (node == nullptr) {
    return node;
  }

  if (node->left_child == nullptr) {
    return node;
  } else {
    return find_biggest_node(node->left_child);
  }
}

bool is_tree_avl(Node *node) {
  if (node == nullptr) {
    return false;
  }

  int bf = calculate_balance_factor(node);
  if (bf > 1 || bf < -1) {
    return false;
  }

  is_tree_avl(node->left_child);
  is_tree_avl(node->right_child);

  return true;
}

void calculate_tree_avg(Node *node, int &sum, int &count) {
  if (node == nullptr) {
    return;
  }

  count += 1;
  sum += node->value;

  calculate_tree_avg(node->left_child, sum, count);
  calculate_tree_avg(node->right_child, sum, count);
}

void free_tree(Node *node) {
  if (node == nullptr) {
    return;
  }

  free_tree(node->left_child);
  free_tree(node->right_child);
  delete node;
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

  values.clear();

  if (argc == 2) {
    struct Node *ptr_max = find_biggest_node(root);
    struct Node *ptr_min = find_smallest_node(root);
    int sum = 0;
    int count = 0;
    std::string is_avl = is_tree_avl(root) ? "yes" : "no";
    calculate_tree_avg(root, sum, count);

    print_tree(root);
    std::cout << "AVL: " << is_avl << '\n';
    std::cout << "min: " << ptr_min->value << ", ";
    std::cout << "max: " << ptr_max->value << ", ";
    std::cout << "avg: " << (double)sum / count;

    free_tree(root);

    return 0;
  }

  std::vector<Node *> path;
  std::vector<int> search_values = load_file(argv[2]);
  struct Node *ptr = find_by_value(root, search_values[0], &path);

  if (search_values.size() == 1) {
    if (ptr == nullptr) {
      std::cout << search_values[0] << " not found!";
      free_tree(root);
      return 0;
    }

    std::cout << ptr->value << " found ";

    for (const auto &node : path) {
      std::cout << node->value;

      if (node->value != ptr->value) {
        std::cout << ", ";
      }
    }

    free_tree(root);
    return 0;
  }

  find_subtree(ptr, search_values);

  free_tree(root);
  return 0;
}
