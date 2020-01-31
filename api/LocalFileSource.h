#pragma once

#ifndef __GNUC__
#include <filesystem>
#elif
#include <experimental/filesystem>
#endif

#include "Source.h"

namespace recombinant
{
namespace api
{
    /**
     * An example implementation of a item source based on the local filesystem.
     * Given a path, this Source represents all files beneath the given path
     * through the Source system.
     */
    class LocalFileSource : public Source
    {
    public:
#ifndef __GNUC__
        /// Initalizes this LocalFileSource using a filesystem path
        LocalFileSource(std::filesystem::path);
#elif
        LocalFileSource(std::experimential::filesystem::path);
#endif
    };

}  // namespace api
}  // namespace recombinant