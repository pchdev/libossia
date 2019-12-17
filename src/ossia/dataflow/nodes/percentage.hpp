#pragma once
#include <ossia/dataflow/graph_node.hpp>
#include <ossia/dataflow/port.hpp>
#include <ossia/network/value/destination.hpp>

namespace ossia::nodes
{
class percentage final : public ossia::graph_node
{
public:
  percentage(ossia::destination d)
  {
    outputs().push_back(new ossia::value_outlet(&d.address()));
  }

  void
  run(const ossia::token_request& tk, ossia::exec_state_facade e) noexcept override
  {
    outputs().back()->target<ossia::value_port>()->write_value(
        (float)tk.position(), e.physical_start(tk));
  }
};
}
