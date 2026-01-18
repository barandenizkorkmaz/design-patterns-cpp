#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::builder()
{
  return PersonBuilder{};
}