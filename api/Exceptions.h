#pragma once

#include <stdexcept>

namespace recombinant
{
namespace api
{
    /**
     * Exception that represents a failure to import a file.
     */
    class FileImportError : public std::runtime_error
    {
    public:
        FileImportError(const std::string& err)
            : std::runtime_error(err)
        {}
    };

    /**
     * Exception that represents a FileFormat export error.
     * This exception will typically indicate an error condition
     * where the exporter must be allowed to remove/truncate features
     */
        class FileExportError : public std::runtime_error
    {
    public:
        FileExportError(const std::string& err)
            : std::runtime_error(err)
        {}
    };

    /**
     * Specalized version of FileFormatError, that indicates that
     * feature loss is required for export for this type!
     */
    class FeatureLossRequired : public FileExportError
    {
    public:
        FeatureLossRequired(const std::string& err)
            : FileExportError(err)
        {}
    };

    /**
     * Specalized version of FileFormatError that indicates
     * that some form of feature truncation is required for export.
     */
    class FeatureTruncationRequired : public FileExportError
    {
    public:
        FeatureTruncationRequired(const std::string& err)
            : FileExportError(err)
        {}
    };

}  // namespace api
}  // namespace recombinant