#ifndef ALGO_GRAPH_H
#define ALGO_GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <sstream>
#include <memory>
#include "../data_structures/priority_queue.h"

namespace graph {
    struct Edge {
    private:
        int v_, w_;
        double weight_;
    public:
        Edge() : v_(0), w_(0), weight_(0)
        {}

        explicit Edge(double weight);
        Edge(int v, int w, double weight);
        [[nodiscard]]
        double weight() const noexcept;
        [[nodiscard]]
        int either() const noexcept;
        [[nodiscard]]
        int other(int v) const;
        bool operator<(const Edge& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Edge& e);
    };
}

template<>
struct data_structures::CompPolicy<graph::Edge, false>{
    static inline const graph::Edge reverse_extremum = graph::Edge(0,0,std::numeric_limits<double>::lowest());
    bool comp(const graph::Edge& lhs, const graph::Edge& rhs) const {
        return lhs < rhs;
    }
};
template<>
struct data_structures::CompPolicy<graph::Edge, true>{
    static inline const graph::Edge reverse_extremum = graph::Edge(0,0,std::numeric_limits<double>::max());
    bool comp(const graph::Edge& lhs, const graph::Edge& rhs) const {
        return rhs < lhs;
    }
};

namespace graph {
    /** Undirected graphs ********************************************************
     */
    class Graph {
    public:
        explicit Graph(int nVerticies);
        explicit Graph(std::istream& in);
        void addEdge(int v, int w);
        [[nodiscard]]
        int V() const;
        [[nodiscard]]
        int E() const;
        [[nodiscard]]
        const std::vector<int>& adj(int v) const;
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    private:
        int v_{};
        int e_;
        std::vector<std::vector<int>> adj_;
    };

    /** *****************some free funcs************************
    */
    int degree(const Graph& g, int v);
    int maxDegree(const Graph& g);
    int avgDegree(const Graph& g);
    int numberofSelfLoops(const Graph& g);

    /** ********************************************************
     */
    class DepthFirstSearch {
    private:
        std::vector<bool> marked_;
        int count_;
    public:
        DepthFirstSearch(const Graph& g, int s);
        [[nodiscard]]
        bool marked(int w) const;
        [[nodiscard]]
        int count() const;
    private:
        void dfs(const Graph& g, int v);
    };

    /** ********************************************************
     */
    class DepthFirstPaths {
    private:
        std::vector<bool> marked_;
        std::vector<int> edgeTo_;
        const int s_;
    public:
        DepthFirstPaths(const Graph& g, int s);
        [[nodiscard]]
        bool hasPathTo(int v) const;
        std::vector<int> pathTo(int v);
    private:
        void dfs(const Graph& g, int v);
    };

    /** ********************************************************
     */
    class BreadthFirstPaths {
    private:
        std::vector<bool> marked_;
        std::vector<int> edgeTo_;
        const int s_;
    public:
        BreadthFirstPaths(const Graph& g, int s);
        bool hasPathTo(int v);
        std::vector<int> pathTo(int v);

    private:
        void bfs(const Graph& g, int s);
    };

    /** ********************************************************
     */
    class CC {
    private:
        std::vector<bool> marked_;
        std::vector<int> id_;
        int count_;
    public:
        explicit CC(const Graph& g);
    private:
        void dfs(const Graph& g, int v);
    public:
        [[nodiscard]]
        bool connected(int v, int w) const;
        [[nodiscard]]
        int id(int v) const;
        [[nodiscard]]
        int count() const;
    };

    /** ********************************************************
     */
    class Cycle {
    private:
        std::vector<bool> marked_;
        bool hasCycle_ = false;
    public:
        explicit Cycle(const Graph& g);
        [[nodiscard]]
        bool hasCycle() const;
    private:
        void dfs(const Graph& g, int v, int u);
    };

    /** ********************************************************
     */
    class TwoColor {
    private:
        std::vector<bool> marked_;
        std::vector<bool> color_;
        bool isTwoColorable_ = true;
    public:
        explicit TwoColor(const Graph& g);
        [[nodiscard]]
        bool isBipartite() const;
    private:
        void dfs(const Graph& g, int v);
    };

    /** Directed graphs ********************************************************
    */
    class Digraph {
        int v_;
        int e_;
        std::vector<std::vector<int>> adj_;
    public:
        explicit Digraph(int v);
        explicit Digraph(std::istream& in);

        [[nodiscard]]
        int V() const noexcept;
        [[nodiscard]]
        int E() const noexcept;
        void addEdge(int v, int w);
        [[nodiscard]]
        const std::vector<int>& adj(int v) const;;
        [[nodiscard]]
        Digraph reverse() const;
    };
    /** ********************************************************
    */
    class DirectedDFS {
        std::vector<bool> marked_;
    public:
        DirectedDFS(const Digraph& g, int s);
        DirectedDFS(const Digraph& g, std::vector<int>&& sources);
    private:
        void dfs(const Digraph& g, int v);
    public:
        [[nodiscard]]
        bool marked(int v) const noexcept;

    };
    /** ********************************************************
    */
    class DirectedCycle {
    private:
        std::vector<bool> marked_;
        std::vector<int> edgeTo_;
        std::vector<int> cycle_;
        std::vector<bool> onStack_;
    public:
        explicit DirectedCycle(const Digraph& g);
    private:
        void dfs(const Digraph& g, int v);
    public:
        [[nodiscard]]
        bool hasCycle() const noexcept;
        [[nodiscard]]
        std::vector<int> cycle() const noexcept;
    };
    /** ********************************************************
    */
    class DepthFirstOrder {
        std::vector<bool> marked_;
        std::vector<int> pre_;
        std::vector<int> post_;
        std::vector<int> reversePost_;
    public:
        explicit DepthFirstOrder(const Digraph& g);
    private:
        void dfs(const Digraph& g, int v);
    public:
        [[nodiscard]]
        std::vector<int> pre() const noexcept;
        [[nodiscard]]
        std::vector<int> post() const noexcept;
        [[nodiscard]]
        std::vector<int> reversePost() const noexcept;
    };
    /** ********************************************************
    */
    class Topological {
    private:
        std::vector<int> order_;
    public:
        explicit Topological(const Digraph& g);
        [[nodiscard]]
        std::vector<int> order() const noexcept;
        [[nodiscard]]
        bool isDAG();
    };
    /** ********************************************************
    */
    class KosarajuSCC {
    private:
        std::vector<bool> marked_;
        std::vector<int> id_;
        int count_;
    public:
        explicit KosarajuSCC(const Digraph& g);
        [[nodiscard]]
        bool stronglyConnected(int v, int w) const noexcept;
        [[nodiscard]]
        int id(int v) const noexcept;
        [[nodiscard]]
        int count() const noexcept;
    private:
        void dfs(const Digraph& g, int v);
    };
    /** ********************************************************
    */
    class TransitiveClosure {
    private:
        std::vector<std::shared_ptr<DirectedDFS>> all_;
    public:
        explicit TransitiveClosure(const Digraph& g);
        [[nodiscard]]
        bool reachable(int v, int w) const noexcept;
    };
    /** Minimum spanning trees ********************************************************
    */


    class EdgeWeightedGraph {
    private:
        int V_, E_;
        std::vector<std::vector<Edge>> adj_;

    public:
        explicit EdgeWeightedGraph(int v);
        explicit EdgeWeightedGraph(std::istream& is);
        [[nodiscard]]
        int V() const noexcept;
        [[nodiscard]]
        int E() const noexcept;
        void addEdge(Edge e);
        [[nodiscard]]
        const std::vector<Edge>& adj(int v) const;
        [[nodiscard]]
        std::vector<Edge> edges();
        friend std::ostream& operator<<(std::ostream& os, const EdgeWeightedGraph& ewg);
    };

    class LazyPrimMST {
    private:
        std::vector<bool> marked_;
        std::queue<Edge> mst_;
        data_structures::MinPriorityQueue<Edge> pq_;
    public:
        explicit LazyPrimMST(EdgeWeightedGraph& g);
        double weight() const noexcept;
        const std::queue<Edge>& edges() const;

    private:
        void visit(EdgeWeightedGraph& g, int v);
    };

    //! @todo don't forget to implement the IndexMinPriorityQueue
//    class PrimMST {
//        std::vector<Edge> edgeTo_;
//        std::vector<double> distTo_;
//        std::vector<bool> marked_;
//        data_structures::MinPriorityQueue<Double> pq_;
//    public:
//        explicit PrimMST(EdgeWeightedGraph& g);
//        std::vector<Edge>& edges() const;
//        double weight() const noexcept;
//    private:
//        void visit(EdgeWeightedGraph g, int v);
//    };
    class KruskalMST {
    private:
        std::queue<Edge> mst_;
    public:
        explicit KruskalMST(EdgeWeightedGraph& g);
        const std::queue<Edge>& edges() const;
        double weight() const noexcept;
    };

    /** Shortest paths ********************************************************
    */
    struct DirectedEdge {
    private:
        int v_, w_;
        double weight_;
    public:
        DirectedEdge();
        DirectedEdge(int v, int w, double weight);
        double weight() const;
        int from() const;
        int to() const;
        friend std::ostream& operator<<(std::ostream& os, const DirectedEdge& de);
    };
}

#endif //ALGO_GRAPH_H
