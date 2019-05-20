#include <algorithm>
#include <iostream>

#include <cassert>

using namespace std;

template < class K, class C = less< K > >
struct RedBlackTree {

  enum class Color {
    BLACK,
    RED,
  };

  struct Node;

  struct Node {
    Node * left = nullptr,
         * right = nullptr,
         * parent = nullptr;
    Color color;
    K key;

    explicit Node(Node * const p, K k) : parent(p), color(Color::RED), key(k) {
      assert(nullptr != parent);
    }

    Node(K k) : color(Color::BLACK), key(k) { }

    Node * const grandparent(void) const {
      return nullptr != parent ? parent->parent : nullptr;
    }

    Node * const sibling(void) const {
      return nullptr != parent ? ( this == parent->right ? parent->left : parent->right ) : nullptr;
    }

    Node * const uncle(void) const {
      const Node * const gp = grandparent();
      return nullptr != gp ? ( parent == gp->right ? gp->left : gp->right ) : nullptr;
    }

    bool isRed(void) const {
      return Color::RED == color;
    }

    void rotate_left(void) {
      Node * const nnew = right,
           * const p = parent;

      assert(nullptr != nnew);
      right = nnew->left;
      nnew->left = this;
      parent = nnew;

      if (nullptr != right)
        right->parent = this;

      if (nullptr != p)
        if (this == p->left)
          p->left = nnew;

        else if (this == p->right)
          p->right = nnew;

      nnew->parent = p;
    }

    void rotate_right(void) {
      Node * const nnew = left,
           * const p = parent;

      assert(nullptr != nnew);
      left = nnew->right;
      nnew->right = this;
      parent = nnew;

      if (nullptr != left)
        left->parent = this;

      if (nullptr != p)
        if (this == p->left)
          p->left = nnew;

        else if (this == p->right)
          p->right = nnew;

      nnew->parent = p;
    }

    friend RedBlackTree;
  };

  Node * root;

  ~RedBlackTree() {
    walkPostOrder([](Node * const n, const size_t) {
      assert(nullptr != n);
      delete n;
    });
  }
  RedBlackTree(void) : root(nullptr) { }

  void insert(K && k) {
    if (nullptr == root)
      root = new Node(forward< K >(k));

    else {
      Node * n = insert_recurse(root, k);
      insert_repair_tree(n);

      while (nullptr != n->parent)
        n = n->parent;

      root = n;
    }
  }


  template < class F >
  void walkPreOrder(const F & f) {
    if (nullptr != root)
      walkPreOrder(f, root);
  }

  template < class F >
  void walkInOrder(const F & f) {
    if (nullptr != root)
      walkInOrder(f, root);
  }

  template < class F >
  void walkPostOrder(const F & f) {
    if (nullptr != root)
      walkPostOrder(f, root);
  }

private:
  template < class F >
  void walkPreOrder(const F & f, Node * const n, const size_t h = 0) {
    assert(nullptr != n);
    f(n, h);
    if (nullptr != n->left)
      walkPreOrder(f, n->left, h + 1);
    if (nullptr != n->right)
      walkPreOrder(f, n->right, h + 1);
  }

  template < class F >
  void walkInOrder(const F & f, Node * const n, const size_t h = 0) {
    assert(nullptr != n);
    if (nullptr != n->left)
      walkInOrder(f, n->left, h + 1);
    f(n, h);
    if (nullptr != n->right)
      walkInOrder(f, n->right, h + 1);
  }

  template < class F >
  void walkPostOrder(const F & f, Node * const n, const size_t h = 0) {
    assert(nullptr != n);
    if (nullptr != n->left)
      walkPostOrder(f, n->left, h + 1);
    if (nullptr != n->right)
      walkPostOrder(f, n->right, h + 1);
    f(n, h);
  }

  Node * const insert_recurse(Node * const root, K & k) const {
    const C c;
    assert(nullptr != root);
    if (c(k, root->key))
      if (nullptr != root->left)
        return insert_recurse(root->left, k);
      else
        return root->left = new Node(root, k);

    else
      if (nullptr != root->right)
        return insert_recurse(root->right, k);
      else
        return root->right = new Node(root, k);

    assert( ! "unreachable");
  }

  void insert_repair_tree(Node * n) const {
    Node * const p = n->parent;

    if (nullptr == p)
      n->color = Color::BLACK;

    else if (p->isRed()) {
      Node * const gp = p->parent,
           * const u = p->sibling();

      assert(nullptr != gp);

      if (nullptr != u && u->isRed()) {
        p->color = Color::BLACK;
        u->color = Color::BLACK;
        gp->color = Color::RED;
        insert_repair_tree(gp);

      } else {
        if (n == p->right && p == gp->left) {
          p->rotate_left();
          n = n->left;

        } else if (n == p->left && p == gp->right) {
          p->rotate_right();
          n = n->right;
        }

        Node * const p2 = n->parent,
             * const gp2 = p2->parent;

        if (n == p2->left)
          gp2->rotate_right();

        else
          gp2->rotate_left();

        p2->color = Color::BLACK;
        gp2->color = Color::RED;
      }
    }
  }
};

int main(void) {
  RedBlackTree< int > myTree;

  myTree.insert(2);
  myTree.insert(7);
  myTree.insert(1);
  myTree.insert(0);
  myTree.insert(5);
  myTree.insert(3);
  myTree.insert(8);

  myTree.insert(4);
  myTree.insert(9);
  myTree.insert(10);
  myTree.insert(11);
  myTree.insert(12);
  myTree.insert(14);
  myTree.insert(15);

  myTree.insert(6);
  myTree.insert(13);

  myTree.walkInOrder([&](const auto a, const size_t h) {
    assert(nullptr != a);
    cout << a->key << " " << h << endl;
  });

  return 0;
}
