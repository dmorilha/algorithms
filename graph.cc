#include <iostream>
#include <set>
#include <vector>

#include <cassert>

using namespace std;

template < class C >
struct Graph {
  struct Node;

  struct Node {
    vector< Node * > peers_;

    C content;

    template < class ... C2 >
    Node(C2 && ... c) : content(forward< C2 >(c)...) { }

    void add(Node & n) {
      peers_.emplace_back(&n);
    }

    template < class ... C2 >
    Node & add(C2 && ... c) {
      peers_.emplace_back(new Node(forward< C2 >(c)...));
      Node * const back = peers_.back();
      assert(nullptr != back);
      return *back;
    }

    template < class ... C2 >
    Node & add_bidirectionally(C2 && ... c) {
      Node & back = add(forward< C >(c)...);
      back.peers_.emplace_back(this);
      return back;
    }

    void remove(void) {
      removed_ = true;
    }

  private:
    bool removed_ = false;
    friend Graph;
  };

  ~Graph() {
    if (nullptr != node) {
      depth_first_walk< true >([](Node & n) {
        delete &n;
      });
    }
  }

  template < class ... C2 >
  Graph(C2 && ... c) : node(new Node(forward< C2 >(c)...)) {
    assert(nullptr != node);
  }

  Node & root(void) {
    assert(nullptr != node);
    return *node;
  }

  template < bool Removed = false, class Z = set< const Node * >, class F >
  void breath_first_walk(const F & f) {
    assert(nullptr != node);
    if (Removed || ! node->removed_) {
      Z z({node});
      f(*node);
      breath_first_walk< Removed >(node, z, f);
    }
  }

  template < bool Removed = false, class Z = set< const Node * >, class F >
  void depth_first_walk(const F & f) {
    assert(nullptr != node);
    if (Removed || ! node->removed_) {
      Z z({node});
      depth_first_walk< Removed >(node, z, f);
    }
  }

private:
  Node * node = nullptr;

  template < bool R, class Z, class F >
  void breath_first_walk(Node * const n, Z & z, const F & f) {
    assert(nullptr != n);
    vector< Node * > peers;
    for (Node * const peer : n->peers_) {
      if ((R || ! peer->removed_) && z.cend() == z.find(peer)) {
        z.insert(peer);
        peers.push_back(peer);
        f(*peer);
      }
    }
    for (Node * const peer : peers)
      breath_first_walk< R >(peer, z, f);
  }

  template < bool R, class Z, class F >
  void depth_first_walk(Node * const n, Z & z, const F & f) {
    assert(nullptr != n);
    for (Node * const peer : n->peers_) {
      if ((R || ! n->removed_) && z.cend() == z.find(peer)) {
        z.insert(peer);
        depth_first_walk< R >(peer, z, f);
      }
    }
    f(*n);
  }
};

int main(void) {
  using MyGraph = Graph< int >;
  MyGraph graph(1000);
  {
    MyGraph::Node & n = graph.root().add_bidirectionally(1001);
    graph.root().add_bidirectionally(1004);
    MyGraph::Node & n2 = n.add(1003);
    graph.root().add(n2);
    n.add(1002);

    {
      graph.depth_first_walk([](MyGraph::Node & n) {
          cout << n.content << " ";
          });
      cout << endl;
    }

    {
      graph.breath_first_walk([](MyGraph::Node & n) {
        cout << n.content << " ";
      });
      cout << endl;
    }

    n2.remove();
  }

  {
    graph.breath_first_walk([](MyGraph::Node & n) {
      cout << n.content << " ";
    });
    cout << endl;
  }

  return 0;
}
