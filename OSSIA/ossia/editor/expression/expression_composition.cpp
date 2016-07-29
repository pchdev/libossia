#include <ossia/editor/expression/expression_composition.hpp>
#include <ossia/editor/expression/expression.hpp>

namespace ossia
{
namespace expressions
{
expression_composition::~expression_composition() = default;

expression_composition::expression_composition(
    std::unique_ptr<expression_base> expr1,
    expression_composition::Operator op,
    std::unique_ptr<expression_base> expr2):
  mFirstExpression(std::move(expr1)),
  mOperator(op),
  mSecondExpression(std::move(expr2))
{

}

bool expression_composition::evaluate() const
{
  return do_evaluation(expressions::evaluate(*mFirstExpression), expressions::evaluate(*mSecondExpression));
}

void expression_composition::update() const
{
  expressions::update(*mFirstExpression);
  expressions::update(*mSecondExpression);
}

expression_base& expression_composition::getFirstOperand() const
{
  return *mFirstExpression;
}

expression_composition::Operator expression_composition::getOperator() const
{
  return mOperator;
}

expression_base& expression_composition::getSecondOperand() const
{
  return *mSecondExpression;
}


void expression_composition::onFirstCallbackAdded()
{
  // start first expression observation
  mFirstResultCallbackIndex =
      expressions::addCallback(
        *mFirstExpression,
        [&] (bool result) { firstResultCallback(result); });

  // start second expression observation
  mSecondResultCallbackIndex =
      expressions::addCallback(
        *mSecondExpression,
        [&] (bool result) { secondResultCallback(result); });
}


void expression_composition::onRemovingLastCallback()
{
  // stop first expression observation
  expressions::removeCallback(*mFirstExpression, mFirstResultCallbackIndex);

  // stop second expression observation
  expressions::removeCallback(*mSecondExpression, mSecondResultCallbackIndex);
}


bool expression_composition::do_evaluation(bool first, bool second) const
{
  switch (mOperator)
  {
    case Operator::AND :
    {
      return first && second;
    }
    case Operator::OR :
    {
      return first || second;
    }
    case Operator::XOR :
    {
      return first ^ second;
    }
    default :
      return false;
  }
}


void expression_composition::firstResultCallback(bool first_result)
{
  bool result = do_evaluation(first_result, expressions::evaluate(*mSecondExpression));
  send(result);
}


void expression_composition::secondResultCallback(bool second_result)
{
  bool result = do_evaluation(expressions::evaluate(*mFirstExpression), second_result);
  send(result);
}

}
}
