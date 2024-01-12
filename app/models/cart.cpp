#include "cart.hpp"
#include "lib/plugin-odb.hxx"

odb_instantiable_impl(Cart)

const std::string Cart::scope = "cart";
const std::string Cart::plural_scope = "carts";
const std::string Cart::view = "cart/show";

void Cart::before_destroy()
{
  Crails::Odb::Connection database;

  for (auto item : items)
    database.destroy(*item);
}

void Cart::add_item(const std::shared_ptr<CartItem>& item)
{
  if (item)
  {
    remove_item(item->get_id());
    items.push_back(item);
  }
}

void Cart::remove_item(const std::shared_ptr<CartItem>& item)
{
  if (item)
    remove_item(item->get_id());
}

void Cart::remove_item(Crails::Odb::id_type id)
{
  auto it = items.begin();

  while (it != items.end())
  {
    if ((*it)->get_id() == id)
    {
      items.erase(it);
      return ;
    }
    ++it;
  }
}
