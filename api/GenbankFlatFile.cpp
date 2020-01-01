#include "FileFormat.h"
#include "../doctest.h"
namespace recombinant
{
namespace api
{
    Sequence GenbankFlatFile::importFile(
        const std::string& filename, ImportFlags flags)
    {
        return Sequence();
    }

    void GenbankFlatFile::exportSequence(const std::string& filename,
        const Sequence& sequence, ExportFlags flags)
    {}
}  // namespace api
};  // namespace recombinant

TEST_CASE("Checking for import")
{
    CHECK(1 == 1);
}