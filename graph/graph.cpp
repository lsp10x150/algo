#include "graph.h"

namespace graph {
    bool DepthFirstPaths::hasPathTo(int v) const {
        return marked_.at(v);
    }

    std::vector<int> DepthFirstPaths::pathTo(int v) {
        if (!hasPathTo(v)) return {};
        std::vector<int> path;
        for (int x = v; x != s_; x = edgeTo_[x])
            path.push_back(x);
        path.push_back(s_);
        return path;
    }

    void DepthFirstPaths::dfs(const Graph &g, int v) {
        marked_.at(v) = true;
        for (auto w : g.adj(v)) {
            if (!marked_.at(w)) {
                edgeTo_.at(w) = v;
                dfs(g, w);
            }
        }
    }

    int degree(const Graph &g, int v) {
        return static_cast<int>(g.adj(v).size());
    }

    int maxDegree(const Graph &g) {
        int max = std::numeric_limits<int>::lowest();
        for (int i = 0; i < g.V(); ++i) {
            if (auto d = degree(g, i); d > max) max = d;
        }
        return max;
    }

    int avgDegree(const Graph &g) {
        return 2 * g.E() / g.V();
    }

    int numberofSelfLoops(const Graph &g) {
        int count = 0;
        for (int v = 0; v < g.V(); ++v) {
            for (auto w : g.adj(v))
                if (v == w) ++count;
        }
        return count/2;
    }

    graph::Graph::Graph(int nVerticies)
            : v_(nVerticies)
            , e_{0}
            , adj_(nVerticies)
    {}
    graph::Graph::Graph(std::istream &in)
            : v_{0}
            , e_{0}
    {
        auto size = 0;
        in >> v_ >> size;
        std::fill_n(std::back_inserter(adj_), v_, std::vector<int>());
        for (int i = 0; i < size; ++i) {
            int v, w;
            in >> v >> w;
            addEdge(v, w);
        }
    }

    void Graph::addEdge(int v, int w) {
        adj_.at(v).push_back(w);
        adj_.at(w).push_back(v);
        ++e_;
    }

    int Graph::V() const {
        return v_;
    }

    int Graph::E() const {
        return e_;
    }

    const std::vector<int> &Graph::adj(int v) const {
        return adj_.at(v);
    }

    std::ostream &operator<<(std::ostream &os, const Graph &graph) {
        os << graph.V() << " verticies, " << graph.E() << " edges\n";
        for (int v = 0; v < graph.V(); ++v) {
            os << v << ": ";
            for (int w : graph.adj(v))
                os << w << ' ';
            os << '\n';
        }
        return os;
    }

    DepthFirstSearch::DepthFirstSearch(const Graph &g, int s)
            : marked_(g.V(), false)
            , count_{0}
    {
        dfs(g, s);
    }

    bool DepthFirstSearch::marked(int w) const {
        return marked_.at(w);
    }

    int DepthFirstSearch::count() const {
        return count_;
    }

    void DepthFirstSearch::dfs(const Graph &g, int v) {
        marked_.at(v) = true;
        ++count_;
        for (auto w : g.adj(v))
            if (!marked(w))
                dfs(g, w);
    }

    DepthFirstPaths::DepthFirstPaths(const Graph &g, int s)
            : marked_(g.V(), false)
            , edgeTo_(g.V())
            , s_(s)
    {
        dfs(g, s);
    }

    BreadthFirstPaths::BreadthFirstPaths(const Graph &g, int s)
            : marked_(g.V(), false)
            , edgeTo_(g.V())
            , s_(s)
    {
        bfs(g, s_);
    }

    bool BreadthFirstPaths::hasPathTo(int v) {
        return marked_.at(v);
    }

    std::vector<int> BreadthFirstPaths::pathTo(int v) {
        if (!hasPathTo(v)) return {};
        std::vector<int> path;
        for (int x = v; x != s_; x = edgeTo_[x])
            path.push_back(x);
        path.push_back(s_);
        return path;
    }

    void BreadthFirstPaths::bfs(const Graph &g, int s) {
        std::queue<int> q;
        marked_[s] = true;
        q.push(s);
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for (auto w : g.adj(v)) {
                if (!marked_[w]) {
                    edgeTo_[w] = v;
                    marked_[w] = true;
                    q.push(w);
                }
            }
        }
    }

    CC::CC(const Graph &g)
            : id_(g.V())
            , marked_(g.V(), false)
            , count_{0}
    {
        for (int s = 0; s < g.V(); ++s) {
            if (!marked_[s]) {
                dfs(g, s);
                ++count_;
            }
        }
    }

    void CC::dfs(const Graph &g, int v) {
        marked_.at(v) = true;
        id_.at(v) = count_;
        for (auto w : g.adj(v)) {
            if (!marked_.at(w))
                dfs(g, w);
        }
    }

    bool CC::connected(int v, int w) const {
        return id_.at(v) == id_.at(w);
    }

    int CC::id(int v) const {
        return id_.at(v);
    }

    int CC::count() const {
        return count_;
    }

    Cycle::Cycle(const Graph &g) : marked_(g.V(), false) {
        for (int s = 0; s < g.V(); ++s) {
            if (!marked_[s])
                dfs(g, s, s);
        }
    }

    bool Cycle::hasCycle() const {
        return hasCycle_;
    }

    void Cycle::dfs(const Graph &g, int v, int u) {
        marked_[v] = true;
        for (int w : g.adj(v)) {
            if (!marked_[w])
                dfs(g, w, v);
            else if (w != u) hasCycle_ = true;
        }
    }

    TwoColor::TwoColor(const Graph &g)
            : marked_(g.V(), false)
            , color_(g.V(), false)
    {
        for (int s = 0; s < g.V(); ++s)
            if (!marked_[s])
                dfs(g, s);
    }

    bool TwoColor::isBipartite() const {return isTwoColorable_;}

    void TwoColor::dfs(const Graph &g, int v) {
        marked_[v] = true;
        for (auto w : g.adj(v)) {
            if (!marked_[w]) {
                color_[w] = !color_[v];
                dfs(g, w);
            } else if (color_[w] == color_[v]) {
                isTwoColorable_ = false;
            }
        }
    }

    Digraph::Digraph(int v)
            : v_(v)
            , e_{0}
    {
        std::fill_n(std::back_inserter(adj_), v_, std::vector<int>{});
    }

    Digraph::Digraph(std::istream &in)
            : v_{0}
            , e_{0}
    {
        auto size = 0;
        in >> v_ >> size;
        std::fill_n(std::back_inserter(adj_), v_, std::vector<int>());
        for (int i = 0; i < size; ++i) {
            int v, w;
            in >> v >> w;
            addEdge(v, w);
        }
    }

    int Digraph::V() const noexcept {
        return v_;
    }

    int Digraph::E() const noexcept {
        return e_;
    }

    void Digraph::addEdge(int v, int w) {
        adj_[v].push_back(w);
        e_++;
    }

    const std::vector<int> &Digraph::adj(int v) const {
        return adj_.at(v);
    }

    Digraph Digraph::reverse() const {
        Digraph R(v_);
        for (int v = 0; v < v_; ++v)
            for (int w : adj(v))
                R.addEdge(w, v);
        return R;
    }

    DirectedDFS::DirectedDFS(const Digraph &g, int s) : marked_(g.V(), false)
    {
        dfs(g, s);
    }

    DirectedDFS::DirectedDFS(const Digraph &g, std::vector<int> &&sources)
            : marked_(g.V(), false)
    {
        for (int s : sources)
            if (!marked_[s])
                dfs(g, s);
    }

    void DirectedDFS::dfs(const Digraph &g, int v) {
        marked_[v] = true;
        for (int w : g.adj(v))
            if (!marked_[w])
                dfs(g, w);
    }

    bool DirectedDFS::marked(int v) const noexcept {
        return marked_[v];
    }

    DirectedCycle::DirectedCycle(const Digraph &g)
            : marked_(g.V(), false)
            , edgeTo_(g.V())
            , onStack_(g.V())
    {
        for (int v = 0; v < g.V(); ++v)
            if (!marked_[v]) dfs(g, v);
    }

    void DirectedCycle::dfs(const Digraph &g, int v) {
        onStack_[v] = true;
        marked_[v] = true;
        for (auto w : g.adj(v)) {
            if (hasCycle()) return;
            else if (!marked_[w]) {
                edgeTo_[w] = v;
                dfs(g, w);
            } else if (onStack_[w]) {
                for (int x = v; x != w; x = edgeTo_[x])
                    cycle_.push_back(x);
                cycle_.push_back(w);
                cycle_.push_back(v);
            }
        }
        onStack_[v] = false;
    }

    bool DirectedCycle::hasCycle() const noexcept {
        return !cycle_.empty();
    }

    std::vector<int> DirectedCycle::cycle() const noexcept {
        return cycle_;
    }

    DepthFirstOrder::DepthFirstOrder(const Digraph &g)
            : pre_{}
            , post_{}
            , reversePost_{}
            , marked_(g.V(), false)
    {
        for (int v = 0; v < g.V(); ++v)
            if (!marked_[v]) dfs(g, v);
        reversePost_.reserve(post_.size());
        std::copy(post_.rbegin(), post_.rend(), std::back_inserter(reversePost_));
    }

    void DepthFirstOrder::dfs(const Digraph &g, int v) {
        pre_.push_back(v);
        marked_[v] = true;
        for (int w : g.adj(v))
            if (!marked_[w])
                dfs(g, w);
        post_.push_back(v);
    }

    std::vector<int> DepthFirstOrder::pre() const noexcept {
        return pre_;
    }

    std::vector<int> DepthFirstOrder::post() const noexcept {
        return post_;
    }

    std::vector<int> DepthFirstOrder::reversePost() const noexcept {
        return reversePost_;
    }

    Topological::Topological(const Digraph &g) {
        DirectedCycle c(g);
        if (!c.hasCycle()) {
            DepthFirstOrder dfs(g);
            order_ = dfs.reversePost();
        }
    }

    std::vector<int> Topological::order() const noexcept {
        return order_;
    }

    bool Topological::isDAG() {
        return !order_.empty();
    }

    KosarajuSCC::KosarajuSCC(const Digraph &g)
            : marked_(g.V(), false)
            , id_(g.V(), 0)
            , count_{0}
    {
        DepthFirstOrder order(g.reverse());
        for (auto s : order.reversePost())
            if (!marked_[s]) {
                dfs(g, s);
                ++count_;
            }
    }

    void KosarajuSCC::dfs(const Digraph &g, int v) {
        marked_[v] = true;
        id_[v] = count_;
        for (auto w : g.adj(v))
            if (!marked_[w])
                dfs(g, w);
    }

    bool KosarajuSCC::stronglyConnected(int v, int w) const noexcept {
        return id_[v] == id_[w];
    }

    int KosarajuSCC::id(int v) const noexcept { return id_[v]; }

    int KosarajuSCC::count() const noexcept { return count_; }

    TransitiveClosure::TransitiveClosure(const Digraph &g)
            : all_(g.V(), nullptr)
    {
        for (int v = 0; v < g.V(); ++v)
            all_[v] = std::make_shared<DirectedDFS>(g, v);
    }

    bool TransitiveClosure::reachable(int v, int w) const noexcept {
        return all_[v]->marked(w);
    }
}
