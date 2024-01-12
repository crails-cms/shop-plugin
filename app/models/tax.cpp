#include "tax.hpp"
#include "lib/tax-odb.hxx"

odb_instantiable_impl(Tax)

const std::string Tax::scope = "tax";
const std::string Tax::plural_scope = "taxes";
const std::string Tax::view = "tax/show";

void Tax::edit(Data params)
{
  if (data["percent"].exists())
    set_percent(params["percent"].as<unsigned short>());
  if (data["name"].exists())
    set_name(params["name"]);
}

void Tax::merge_data(Data out) const
{
  out["name"] = name;
  out["percent"] = static_cast<unsigned short>(value);
}
