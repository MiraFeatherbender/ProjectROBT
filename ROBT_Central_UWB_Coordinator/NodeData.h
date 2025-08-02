#ifndef NODEDATA_H
#define NODEDATA_H

enum class NodeState { WAITING_FOR_MEAS,
                       WAITING_FOR_MEAS_RESPONSE,
                       WAITING_FOR_READ,
                       WAITING_FOR_READ_RESPONSE,
                       COMPLETE };

enum class CollectState { INIT,
                          COLLECT,
                          WAIT };

enum class PrefilterState { INIT,
                            PREFILTER,
                            WAIT };

struct NodeData {
  int x, y;         // Coordinates
  NodeState state;  // Current state
  int distance;     // Distance reading
};

#endif  // NODEDATA_H
