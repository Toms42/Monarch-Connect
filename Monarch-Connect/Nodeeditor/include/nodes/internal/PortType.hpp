#pragma once

#include <QtCore/QUuid>
#include <utility>

namespace QtNodes {

enum class PortDirection
{
  None,
  In,
  Out
};

static const int INVALID = -1;

using PortIndex = int;

struct Port
{
  PortDirection type;

  PortIndex index;

  Port()
    : type(PortDirection::None)
    , index(INVALID)
  {}

  Port(PortDirection t, PortIndex i)
    : type(t)
    , index(i)
  {}

  bool indexIsValid() { return index != INVALID; }

  bool portTypeIsValid() { return type != PortDirection::None; }
};

// using PortAddress = std::pair<QUuid, PortIndex>;

inline PortDirection
oppositePort(PortDirection port)
{
  PortDirection result = PortDirection::None;

  switch (port) {
    case PortDirection::In:
      result = PortDirection::Out;
      break;

    case PortDirection::Out:
      result = PortDirection::In;
      break;

    default:
      break;
  }

  return result;
}
}
