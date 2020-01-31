#include "LocalFileSource.h"

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
