#include "FileFormat.h"

#include <sstream>

#include "../doctest.h"
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

        std::ostringstream accum;

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
                    // separate description from name with the pipe symbol
                    size_t first_pipe = line.find_first_of('|');
                    result.name       = line.substr(0, first_pipe);
                    if (first_pipe != line.size())
                    {
                        result.description = line.substr(first_pipe + 1);
                    }
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
            // Process the line as text. If it is empty, assume we got to the
            // end
            if (line.size() == 0)
            {
                done = true;
            }

            // If it's not, accumulate characters.
            accum << line;
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
