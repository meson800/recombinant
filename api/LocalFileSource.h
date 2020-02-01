#pragma once

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
        /// Initalizes this LocalFileSource using a string for the path
        LocalFileSource(std::string path);
    };

}  // namespace api
}  // namespace recombinant