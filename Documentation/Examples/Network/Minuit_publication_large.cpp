// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <ossia/ossia.hpp>
int main(int argc, char** argv)
{
  auto local_proto_ptr = std::make_unique<ossia::net::multiplex_protocol>();
  ossia::net::multiplex_protocol& local_proto = *local_proto_ptr;
  // declare this program "B" as Local device
  ossia::net::generic_device device{std::move(local_proto_ptr), "newDevice"};

  auto localTestNode = device.create_child("test");

  for(int k : {10, 100})
  {
      auto n1 = localTestNode->create_child(std::to_string(k));
      for(int i = 0; i < k; i++)
      {
          auto n2 = n1->create_child(std::to_string(k));
          auto addr = n2->create_address(ossia::val_type::INT);
          addr->push_value(i);
      }
  }

  localTestNode->create_child(std::to_string(1000));

  for(int k = 1; k <= 9; k++)
  {
      auto node = localTestNode->create_child(std::string(k, k + '0'));
      auto addr = node->create_address(ossia::val_type::INT);
      addr->push_value(k);
  }
  // declare a distant program as a Minuit device
  local_proto.expose_to(std::make_unique<ossia::net::minuit_protocol>("newDevice", "127.0.0.1", 13579, 9998));

  while (true)
    ;
}
