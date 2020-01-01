#include "FileFormat.h"

#include <fstream>

namespace recombinant
{
namespace api
{
    Sequence FileFormat::importFile(
        const std::string& filename, ImportFlags flags)
    {
        return this->importFile(std::ifstream(filename), flags);
    }

    void FileFormat::exportSequence(const std::string& filename,
        const Sequence& sequence, ExportFlags flags)
    {
        return this->exportSequence(std::ofstream(filename), sequence, flags);
    }
}  // namespace api
}  // namespace recombinant