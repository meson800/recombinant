#include "../doctest.h"
#include "FileFormat.h"
namespace recombinant
{
namespace api
{
    Sequence FastaFile::importFile(std::istream& stream, ImportFlags flags)
    {
        Sequence result;

        std::string line;
        bool readingSeq = false;
        bool done       = false;

        while (!done)
        {
            // Check if next character is a >
            if (stream.peek() == '>')
            {
                if (!readingSeq)
                {
                    // Read in the name of this sequence
                    readingSeq = true;
                    std::getline(stream, line);
                    line.erase(0);  // remove leading >
                    result.name = line;
                } else
                {
                    // We reached the end of the file!
                    readingSeq = false;
                    done       = true;
                }
                continue;
            }
            // If we're here, the next line is not a start/end character.
            // Try reading a line
            if (!std::getline(stream, line))
            {
                // Exit if we reached EOF
                done = true;
                continue;
            }
            // Process the line as text.
        }
        return result;
    }

    void FastaFile::exportSequence(
        std::ostream& stream, const Sequence& sequence, ExportFlags flags)
    {
        stream << ">" << sequence.name << "|" << sequence.description << "\n";
    }
}  // namespace api
};  // namespace recombinant

TEST_CASE("Checking for import")
{
    CHECK(1 == 1);
}
