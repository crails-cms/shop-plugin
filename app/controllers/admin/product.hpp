#pragma once
#include <crails/cms/admin/resource.hpp>
#include "app/controllers/admin/application.hpp"
#include "../models/product_traits.hpp"

typedef Crails::Cms::AdminResourceController<
  ProductTraits,
  Product,
  AdminApplicationController
> AdminTaxControllerSuper;

class AdminProductController : public AdminProductControllerSuper
{
  typedef AdminProductControllerSuper Super;
public:
  static constexpr const char* scope = "product";

  AdminProductController(Crails::Context& context) : Super(context)
  {
  }

  std::string get_view_scope() const override
  {
    return scope;
  }
};
