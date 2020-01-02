#include "FileFormat.h"

#include <sstream>

#include "../doctest.h"
namespace recombinant
{
namespace api
{
    Sequence FastaFile::importFileSingle(std::istream& stream, ImportFlags flags)
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
                    line.erase(0, 1);  // remove leading >
                    // separate description from name with the pipe symbol
                    size_t first_pipe = line.find_first_of('|');
                    result.name       = line.substr(0, first_pipe);
                    if (first_pipe != std::string::npos)
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
        auto convertSeq = Sequence::stringToSeq(accum.str());
        result.sequence = convertSeq.first;
        result.type     = convertSeq.second;
        return result;
    }

    void FastaFile::exportSequence(
        std::ostream& stream, const Sequence& sequence, ExportFlags flags)
    {
        stream << ">" << sequence.name << "|" << sequence.description << "\n";
    }

    TEST_CASE("Fasta format: DNA import")
    {
        std::istringstream stream(">Test|with description\nATTCGACGTACCA");
        FastaFile converter;
        Sequence fastaSeq = converter.importFileSingle(stream);

        Sequence compare;
        compare.name        = "Test";
        compare.description = "with description";
        compare.type        = Sequence::Type::DNA;
        compare.sequence =
            Sequence::typedStringToSeq("ATTCGACGTACCA", Sequence::Type::DNA);
        CHECK_EQ(fastaSeq, compare);
    }

    TEST_CASE("Fasta format: import without description")
    {
        std::istringstream stream(">Test with a long name, no description\nA");
        FastaFile converter;
        Sequence fastaSeq = converter.importFileSingle(stream);

        CHECK_EQ(fastaSeq.name, "Test with a long name, no description");
        CHECK_EQ(fastaSeq.description.size(), 0);
    }

    TEST_CASE("Fasta format: import with line breaks in sequence")
    {
        std::istringstream stream(">Test\nATTCGACGA\nGGATACACATA\nACATTAGAAAG");
        FastaFile converter;
        Sequence fastaSeq = converter.importFileSingle(stream);

        Sequence compare;
        compare.name = "Test";
        compare.type = Sequence::Type::DNA;
        compare.sequence = Sequence::typedStringToSeq(
            "ATTCGACGAGGATACACATAACATTAGAAAG", Sequence::Type::DNA);
        CHECK_EQ(fastaSeq, compare);
    }
}  // namespace api
};  // namespace recombinant
