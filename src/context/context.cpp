#include "context/context.hpp"

#include <eul/logger/logger_stream_registry.hpp>


namespace msboot
{
namespace context
{

Context::Context(eul::kernel::kernel& kernel)
    : logger_factory_(time_)
    , kernel_(kernel)
{
    eul::logger::logger_stream_registry::get().register_stream(stdout_stream_);
}

const eul::logger::logger_factory& Context::logger_factory() const
{
    return logger_factory_;
}

eul::kernel::kernel& Context::kernel()
{
    return kernel_;
}


} // namespace context
} // namespace msboot
