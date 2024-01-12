#pragma once
#include <crails/odb/model.hpp>
#include <crails/datatree.hpp>

#pragma db model
class Tax : public Crails::Odb::ModelBase
{
  odb_instantiable()
public:
  static const std::string scope;
  static const std::string plural_scope;
  static const std::string view;

  #pragma db view object(Tax)
  struct Count
  {
    #pragma db column("count(" + Tax::id + ")")
    size_t value;
  };

  template<typename QUERY>
  static QUERY default_order_by(QUERY query)
  {
    return query + "ORDER BY" + QUERY::name;
  }

  void edit(Data);
  void merge_data(Data) const;

  const std::string& get_name() const { return name; }
  float get_rate() const { return static_cast<float>(value) / 100; }
  unsigned char get_percent() const { return value; }
  void set_percent(unsigned char value) { value = value; }
  void set_name(const std::string& vaue) { name = value; }

private:
  std::string   name;
  unsigned char value = 0;
};
