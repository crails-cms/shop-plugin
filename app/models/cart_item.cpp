#include "cart.hpp"
#include "lib/plugin-odb.hxx"

odb_instantiable_impl(CartItem)

const std::string CartItem::scope = "cart_item";
const std::string CartItem::plural_scope = "cart_items";
const std::string CartItem::view = "cart/item";

typedef float (*PricingFunction)(const CartItem&);

static float quantity_price(const CartItem& item)
{
  auto unit_price = item.get_article()->get_unit_price();

  return unit_price * item.get_quantity();
}

static float surface_price(const CartItem& item)
{
  auto unit_price = item.get_article()->get_unit_price();

  return unit_price * item.get_width() * item.get_height();
}

static float volume_price(const CartItem& item)
{
  auto unit_price = item.get_article()->get_unit_price();

  return unit_price * item.get_width() * item.get_height() * item.get_depth();
}

static const std::map<Product::PricingType, PricingFunction> pricing_functions{
  {Product::QuantityPricing, &quantity_price},
  {Product::SurfacePricing, &surface_price},
  {Product::VolumePricing, &volume_price}
};

void CartItem::edit(Data params)
{
  if (params["quantity"].exists())
    set_quantity(params["quantity"]);
  if (params["width"].exists())
    set_width(params["width"]);
  if (params["height"].exists())
    set_height(params["height"]);
  if (params["depth"].exists())
    set_depth(params["depth"]);
}

void CartItem::merge_data(Data out) const
{
  if (quantity > 1)
    out["quantity"] = quantity;
  if (width > 0)
    out["width"] = width;
  if (height > 0)
    out["height"] = height;
  if (depth > 0)
    out["depth"] = depth;
}

float CartItem::round_price(float value) const
{
  return std::round(value * 100) / 100;
}

float CartItem::round_quantity(float value) const
{
  if (article)
  {
    int factor = std::pow(10, article->get_granularity());

    return std::trunc(value * factor) / factor;
  }
  return value;
}

float CartItem::get_amount() const
{
  if (article)
  {
    auto it = pricing_functions.find(article->get_pricing_type());

    if (it != pricing_functions.end())
    {
      PricingFunction function = it->second;
      float price = function(*this);

      return round_price(price);
    }
  }
  return 0;
}

float CartItem::get_total_amount() const
{
  if (article)
  {
    float base = get_amount();
    float factor = 1 + article->get_tax_rate();

    return round_price(base * factor);
  }
  return 0;
}
