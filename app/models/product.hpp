#pragma once
#include <crails/cms/models/editable.hpp>
#include "tax.hpp"

#pragma db model
class Product : public Crails::Cms::Editable
{
  odb_instantiable()
public:
  static const std::string scope;
  static const std::string plural_scope;
  static const std::string view;

  #pragma db view object(Product)
  struct Count
  {
    #pragma db column("count(" + Product::id + ")")
    size_t value;
  };

  enum PricingType
  {
    QuantityPricing = 0,
    SurfacePricing,
    VolumePricing
  };

  void edit(Data) override;
  void merge_data(Data) const override;

  const std::shared_ptr<Tax>& get_tax() const { return tax; }
  void set_tax(const std::shared_ptr<Tax>& value) { tax = value; }
  void set_tax_id(Crails::Odb::id_type);

  float          get_tax_rate() const { return tax ? tax->get_rate() : 0; }
  float          get_unit_price() const { return unit_price; }
  PricingType    get_pricing_type() const { return pricing_type; }
  float          get_quantity_step() const { return quantity_step; }
  unsigned short get_granularity() const { return granularity; } 

  void set_quantity_step(float value) { quantity_step = value; }
  void set_unit_price(float value) { unit_price = value; }
  void set_pricing_type(PricingType value) { pricing_type = value; }
  void set_granularity(unsigned short value) { granularity = value; }

private:
  float          unit_price = 0;
  PricingType    pricing_type = QuantityPricing;
  float          quantity_step = 1;
  unsigned short granularity = 0;
  std::shared_ptr<Tax> tax;
};
