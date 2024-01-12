#pragma once
#include "product.hpp"

#pragma db model
class CartItem : public Crails::Odb::ModelBase
{
  odb_instantiable()
public:
  static const std::string scope;
  static const std::string plural_scope;
  static const std::string view;

  #pragma db view object(CartItem)
  struct Count
  {
    #pragma db column("count(" + CartItem::id + ")")
    size_t value;
  };

  template<typename QUERY>
  static QUERY default_order_by(QUERY query)
  {
    return query;
  }

  void edit(Data);
  void merge_data(Data) const;

  const std::shared_ptr<Product>& get_article() const { return article; }
  float get_quantity() const { return round_quantity(quantity); }
  float get_width() const { return round_quantity(width); }
  float get_height() const { return round_quantity(height); }
  float get_depth() const { return round_quantity(depth); }

  void set_quantity(float value) { quantity = value; }
  void set_width(float value) { width = value; }
  void set_height(float value) { height = value; }
  void set_depth(float value) { depth = value; }

  float get_total_amount() const;
  float get_amount() const; 

private:
  float round_price(float) const;
  float round_quantity(float) const;

  std::shared_ptr<Product> article;
  float quantity = 1;
  float width = 0;
  float height = 0;
  float depth = 0;
};
