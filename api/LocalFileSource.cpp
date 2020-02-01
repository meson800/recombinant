#include "LocalFileSource.h"

#ifndef OLDSCHOOL_FILESYSTEM
#include <filesystem>
#else
#endif

namespace recombinant
{
namespace api
{
    LocalFileSource::LocalFileSource(std::string path)
    {
#ifndef OLDSCHOOL_FILESYSTEM
        std::filesystem::path fspath(path);
#endif

        root         = std::unique_ptr<Entity>(new Entity);
        root->name   = "Local";
        root->parent = nullptr;
        root->type   = Entity::Type::Container;
    }
}  // namespace api
}  // namespace recombinant
