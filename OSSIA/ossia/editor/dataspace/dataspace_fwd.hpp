#pragma once
#include <ossia/editor/dataspace/dataspace_base_fwd.hpp>
#include <ossia/editor/dataspace/dataspace_base.hpp>
#include <eggs/variant.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/algorithms/fold.hpp>
#include <brigand/functions/arithmetic.hpp>
#include <brigand/adapted/list.hpp>
#include <type_traits>
#include <ratio>

namespace brigand
{
template <typename... T>
using eggs_variant_wrapper = typename eggs::variant<T...>;

template <typename L>
using as_eggs_variant = brigand::wrap<L, eggs_variant_wrapper>;
}

namespace ossia
{
template<typename T>
using add_value = brigand::transform<T, brigand::bind<ossia::strong_value, brigand::_1>>;

using angle = add_value<angle_u>;
using distance = add_value<distance_u>;
using orientation = add_value<orientation_u>;
using position = add_value<position_u>;
using color = add_value<color_u>;
using speed = add_value<speed_u>;
using gain = add_value<gain_u>;
using time = add_value<time_u>;

// Basically eggs::variant<ossia::value, ossia::distance, ossia::position, ossia::speed...>
using value_with_unit =
brigand::as_eggs_variant<
  brigand::append<
    brigand::list<ossia::value>,
    brigand::as_list<
      brigand::transform<
        unit_t,
        brigand::bind<ossia::add_value, brigand::_1>
      >
    >
  >
>;
}

