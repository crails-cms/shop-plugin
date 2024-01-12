#pragma once
#include "cart_item.hpp"

#pragma db model
class Cart : public Crails::Odb::Model
{
  odb_instantiable()
public:
  static const std::string scope;
  static const std::string plural_scope;
  static const std::string view;

  #pragma db view object(Cart)
  struct Count
  {
    #pragma db column("count(" + Cart::id + ")")
    size_t value;
  };

  template<typename QUERY>
  static QUERY default_order_by(QUERY query)
  {
    return query;
  }

  void before_destroy() override;
  void add_item(const std::shared_ptr<CartItem>&);
  void remove_item(const std::shared_ptr<CartItem>&);
  void remove_item(Crails::Odb::id_type);

private:
  std::vector<std::shared_ptr<CartItem>> items;
};
