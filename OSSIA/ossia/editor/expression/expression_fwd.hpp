#pragma once
#include <ossia/detail/callback_container.hpp>

#include <eggs/variant.hpp>
#include <functional>
#include <ossia_export.h>

namespace ossia
{
namespace expressions
{
/*! to get the result back
 \param the returned result */
using expression_result_callback = std::function<void(bool)>;
using expression_callback_iterator = typename callback_container<expression_result_callback>::iterator;
class expression_atom;
class expression_bool;
class expression_composition;
class expression_not;
class expression_pulse;

using expression_base = eggs::variant<
  expression_atom,
  expression_bool,
  expression_composition,
  expression_not,
  expression_pulse>;

//concept expression_base :
//    public callback_container<expression_result_callback>
//{
//public:

//  /*! evaluate the expression
//   \return bool result of the evaluation */
//  virtual bool evaluate() const = 0;

//  /*! pull the value of any #Destination operand */
//  virtual void update() const = 0;

//  virtual bool operator== (const expression_base&) const = 0;
//  virtual bool operator!= (const expression_base&) const = 0;
//};
}
}
