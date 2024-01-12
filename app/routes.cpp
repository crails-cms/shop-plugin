#include <crails/router.hpp>
#include "controllers/admin/product.hpp"
#include "controllers/admin/tax.hpp"
#include "lib/plugin-odb.hxx"

void initialize_plugin_routes()
{
  auto& router = Crails::Router::singleton::require();
  auto& cms_routes = Crails::Cms::Routes::singleton::require();
  auto& admin_menu = Crails::Cms::AdminMenu::singleton::require();

  router.scope(AdminApplicationController::scope, [&]()
  {
    router.scope("shop", [&]()
    {
      admin_menu.add({3, "shop", router.get_current_scope());
      // add index
      router.scope(AdminTaxController::scope, [&]()
      {
        cms_routes.set_path_for<AdminTaxController>(router);
        router.libcrails_cms_admin_crud("/", AdminTaxController);
      });
      router.scope(AdminProductController::scope, [&]()
      {
        cms_routes.set_path_for<AdminProductController>(router);
        router.libcrails_cms_admin_crud("/", AdminProductController);
      });
    }
  });
  // insert plugin routes here
}
