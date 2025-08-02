#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <memory>
#include <vector>
#include "OuterNode.h"

class NodeFactory {
public:
  static std::vector<std::unique_ptr<OuterNode>> createNodes();
};

#endif  // NODEFACTORY_H
