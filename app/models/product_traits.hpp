#pragma once
#include "app/models/traits.hpp"
#include "product.hpp"

struct ProductTraits : public ApplicationTraits
{
  typedef Product Model;
  typedef Product IndexModel;
};
