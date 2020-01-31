#include "LocalFileSource.h"

#ifndef __GNUC__
using namespace std::filesystem;
#else
namespace std::experimental::filesystem;
#endif

namespace recombinant
{
namespace api
{
    LocalFileSource::LocalFileSource(std::filesystem::path)
    {
        root         = std::unique_ptr<Entity>(new Entity);
        root->name = "Local";
        root->parent = nullptr;
        root->type   = Entity::Type::Container;
    }
}  // namespace api
}  // namespace recombinant
