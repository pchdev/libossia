// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once

#include <servus/servus.h>
#include <memory>

#include <ossia/network/generic/generic_device.hpp>
#include <ossia/network/zeroconf/zeroconf.hpp>

namespace ossia
{
namespace max
{
class ZeroconfMinuitListener final : servus::Listener
{
  public:
    ZeroconfMinuitListener();
    ~ZeroconfMinuitListener() override;

    static ossia::net::minuit_connection_data* find_device(const std::string& name);

    void browse();

  private:
    void instanceAdded(const std::string& instance) final override;
    void instanceRemoved(const std::string& instance) final override;
    void process_new_devices(const std::string& instance);

    static std::vector<ossia::net::minuit_connection_data> m_devices;
    static std::vector<std::vector<ossia::net::minuit_connection_data>::iterator> m_zombie_devices;
    static std::vector<std::string> m_embryo_devices;

    servus::Servus service;
    static std::mutex m_mutex;
};

} // namespace pd
} // namespace ossia
