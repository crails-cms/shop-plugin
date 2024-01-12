#pragma once
#include "app/models/traits.hpp"
#include "tax.hpp"

struct TaxTraits : public ApplicationTraits
{
  typedef Tax Model;
  typedef Tax IndexModel;
};
