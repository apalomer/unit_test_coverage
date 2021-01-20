#ifndef FOO_H_
#define FOO_H_

class Foo
{
public:
  Foo(const double& value);

  double times(const double& value) const;

  bool isPositive() const;

private:
  double m_value;
};

#endif  // FOO_H_
