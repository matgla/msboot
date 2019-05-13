#include "app/app.hpp"

#include "modules/booting/booting_module.hpp"
#include "modules/settings/settings_module.hpp"

namespace msboot
{
namespace app
{

App::App()
    : context_(kernel_)
{
}

int App::run()
{
    modules::settings::SettingsModule settings_module(context_);
    kernel_.register_module(settings_module);

    modules::booting::BootingModule booting_module(context_);
    kernel_.register_module(booting_module);

    return 0;
}

} // namespace app
} // namespace msboot
