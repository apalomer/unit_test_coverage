#pragma once

class Foo
{
public:
  Foo(const double& value);

  double times(const double& value) const;

  bool isPositive() const;

private:
  double m_value;
};

