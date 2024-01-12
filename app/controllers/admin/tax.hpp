#pragma once
#include <crails/cms/admin/resource.hpp>
#include "app/controllers/admin/application.hpp"
#include "../models/tax_traits.hpp"

typedef Crails::Cms::AdminResourceController<
  TaxTraits,
  Tax,
  AdminApplicationController
> AdminTaxControllerSuper;

class AdminTaxController : public AdminTaxControllerSuper
{
  typedef AdminTaxControllerSuper Super;
public:
  static constexpr const char* scope = "tax";

  AdminTaxController(Crails::Context& context) : Super(context)
  {
  }

  std::string get_view_scope() const override
  {
    return scope;
  }
};
