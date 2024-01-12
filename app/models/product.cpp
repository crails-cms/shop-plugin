#include "product.hpp"

odb_instantiable_impl(Product)

const std::string Product::scope = "product";
const std::string Product::plural_scope = "products";
const std::string Product::view = "product/show";

void Product::edit(Data params)
{
  Crails::Cms::Editable::edit(data);
  if (params["unit_price"].exists())
    set_unit_price(params["unit_price"]);
  if (params["pricing_type"].exists())
    set_pricing_type(static_cast<PricingType>(params["pricing_type"].as<short>()));
  if (params["quantity_step"].exists())
    set_quantity_step(params["quantity_step"]);
  if (params["granularity"].exists())
    set_granularity(params["granularity"]);
  if (params["tax_id"].exists())
    set_tax_id(params["tax_id"]);
}

void Product::merge_data(Data data)
{
  Crails::Cms::Editable::merge_data(data);
  out["unit_price"] = get_unit_price();
  out["pricing_type"] = static_cast<short>(pricing_type);
  out["quantity_step"] = get_quantity_step();
  out["granularity"] = get_granularity();
  if (tax)
    out["tax_id"] = tax->get_id();
}

void Product::set_tax_id(Crails::Odb::id_type id)
{
  Crails::Odb::ConnectionHandle database;

  database.find_one(tax, id);
}
