#include "FileFormat.h"
#include "../doctest.h"
namespace recombinant
{
namespace api
{
    Sequence GenbankFlatFile::importFile(
        std::istream& stream, ImportFlags flags)
    {
        return Sequence();
    }

    void GenbankFlatFile::exportSequence(std::ostream& stream,
        const Sequence& sequence, ExportFlags flags)
    {}
}  // namespace api
};  // namespace recombinant

TEST_CASE("Checking for import")
{
    CHECK(1 == 1);
}