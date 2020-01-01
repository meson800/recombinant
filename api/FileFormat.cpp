#include "FileFormat.h"

#include <fstream>

namespace recombinant
{
namespace api
{
    std::vector<Sequence> FileFormat::importFile(
        const std::string& filename, ImportFlags flags)
    {
        std::ifstream stream(filename);
        std::vector<Sequence> output;
        while (!stream.eof())
        {
            output.push_back(this->importFile(stream, flags));
        }
        return output;
    }

    void FileFormat::exportSequence(const std::string& filename,
        const Sequence& sequence, ExportFlags flags)
    {
        exportSequences(filename, std::vector<Sequence>{sequence}, flags);
    }

    void FileFormat::exportSequences(const std::string& filename,
        std::vector<Sequence> sequences, ExportFlags flags)
    {
        std::ofstream stream(filename);
        for (Sequence seq : sequences)
        {
            this->exportSequence(stream, seq, flags);
        }
    }
}  // namespace api
}  // namespace recombinant