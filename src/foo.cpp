#include "foo.h"

Foo::Foo(const double& value) : m_value(value){};

double Foo::times(const double& value) const
{
  return m_value * value;
}

bool Foo::isPositive() const
{
  return m_value > 0;
}
