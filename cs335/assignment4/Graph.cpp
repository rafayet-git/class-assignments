#include "Graph.hpp"

Graph VertexCover::readFromFile(const std::string filename){
  std::ifstream fin(filename);
  if (!fin.is_open()) throw std::runtime_error(filename + " - File not found");
  Graph g;
  std::string line;
  while (std::getline(fin, line)) {
    // Get first positions of both airports
    int pos1 = (line.find('-')) + 2;
    int pos2 = (line.find('-',pos1)) + 2;
    // Insert to both
    g[line.substr(pos1, 3)].insert(line.substr(pos2, 3));
    g[line.substr(pos2, 3)].insert(line.substr(pos1, 3));
  }
  fin.close();
  return g;
}

std::unordered_set<Vertex> VertexCover::cover_graph(Graph g){
  std::unordered_set<Vertex> cover;
  while (!g.empty()) {
    // Element with most vertices
    auto maxV = std::max_element(
      g.begin(),
      g.end(),
      [](const auto& a, const auto& b) {
        return a.second.size() < b.second.size();
      });
    cover.insert(maxV->first);

    // Remove all neighbors
    for (const auto& conn : maxV->second) {
      g[conn].erase(maxV->first);
      if (g[conn].empty()) {
        g.erase(conn);
      }
    }
    g.erase(maxV->first);

  }
  return cover;
}
