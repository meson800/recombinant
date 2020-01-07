#pragma once

#include <iostream>

#include "Sequence.h"
namespace recombinant
{
namespace api
{
    /**
     * Generic interface class that is inherited to specalize
     * to handle different file formats.
     *
     * File format classes are expected to have an import command that
     * creates a Sequence object from a local file and an export
     * command that creates a file from a Sequence object.
     *
     * Not all file formats may handle the full feature set! On export,
     * the export command must take one of the export flags
     */
    class FileFormat
    {
    public:
        /**
         * When passed to FileFormat::importSequence,
         * possibly allows a "permissive" mode that allows some
         * file format errors to be allowed
         */
        enum class ImportFlags
        {
            None,        /// The file format must be strictly imported
            Permissive,  /// Some standard-breaking import problems are allowed
        };

        /**
         * When passed to FileFormat::exportSequence,
         * ExportFlags allows the file format exporter to either
         * remove any features in the sequence (e.g. when exporting to FASTA)
         * or to truncate extra feature information (for a limited file format).
         */
        enum class ExportFlags
        {
            None,  /// The file format must exactly represent the sequence
            FeatureLossAllowed,       /// The file format is allowed to remove
                                      /// features
            FeatureTruncationAllowed  /// The file format is allowed to truncate
                                      /// some feature information
        };

        /**
         * Given a filename, outputs Sequence(s) based on reading the file.
         *
         * This is a convience override that creates a istream from the
         * filename, then trying to repeatedly import sequences until finished.
         *
         * This is useful for file formats that may contain several sequences
         * in a single file.
         */
        virtual std::vector<Sequence> importFile(
            const std::string& filename, ImportFlags flags = ImportFlags::None);

        /**
         * Given a input stream, attempts to read several sequences from a
         * single file. If this is overriden in subclasses, the file format
         * cannot import/export multiple sequences in a single file.
         */
        virtual std::vector<Sequence> importFile(
            std::istream& stream, ImportFlags flags = ImportFlags::None);

        /**
         * Given a std::istream, outputs a Sequence based on reading the file.
         *
         * Throws a FileImportError if the file cannot be imported with the
         * desired set of flags. The default import flags is none (e.g.
         * requiring that the import follows the strict specification)
         *
         * This is the function that inherited file types should use!
         */
        virtual Sequence importFileSingle(
            std::istream& stream, ImportFlags flags = ImportFlags::None) = 0;

        /**
         * Given a filename and a Sequence, exports the Sequence to that file.
         *
         * This is a convienence override that creates an ostream from the
         * filename
         */
        virtual void exportSequence(const std::string& filename,
            const Sequence& sequence, ExportFlags flags = ExportFlags::None);

        /**
         * Given a filename and a vector of Sequences, exports them to
         * the same filename.
         *
         */
        virtual void exportSequences(const std::string& filename,
            const std::vector<Sequence>& sequences,
            ExportFlags = ExportFlags::None);

        /**
         * Given an output stream and a vector of Sequences, exports them
         * to the same stream.
         *
         * This function may be overriden to return FileExportErrors
         * in file formats that do not allow multiple sequences in
         * a single file.
         */
        virtual void exportSequences(std::ostream& stream,
            const std::vector<Sequence>& sequences,
            ExportFlags = ExportFlags::None);


        /**
         * Given a std::ostream and a Sequence, writes the
         * sequence to the file. ExportFlags that are set allow imports
         * that remove some information about the full sequence.
         *
         * If the sequence cannot be exported under the current ExportFlags,
         * this raises a FileExportError.
         */
        virtual void exportSequence(std::ostream& stream,
            const Sequence& sequence,
            ExportFlags flags = ExportFlags::None) = 0;
    };

    /**
     * Handles import/export to Genbank Flat File formats.
     *
     * This format is a "full-featured" file format for genetic elements.
     * It handles arbitrary features and is the default filetype for
     * Recombinant.
     *
     * Import reference documents:
     * Specification: Section 3.4 in ftp://ftp.ncbi.nih.gov/genbank/gbrel.txt
     * Example annotated record:
     * https://www.ncbi.nlm.nih.gov/Sitemap/samplerecord.html Specification for
     * the feature table: http://www.insdc.org/files/feature_table.html
     * Currently defined features: https://www.ebi.ac.uk/ena/WebFeat/
     */
    class GenbankFlatFile : public FileFormat
    {
    public:
        virtual Sequence importFileSingle(std::istream& stream,
            ImportFlags flags = ImportFlags::None) override;
        virtual void exportSequence(std::ostream& stream,
            const Sequence& sequence,
            ExportFlags flags = ExportFlags::None) override;
    };

    /**
     * Handles import/export to the FASTA file format.
     *
     * This format is *not* a full-featured file format! It cannot
     * handle features!
     *
     * Reference docs:
     * https://www.ncbi.nlm.nih.gov/BLAST/fasta.shtml
     * https://zhanglab.ccmb.med.umich.edu/FASTA/
     */
    class FastaFile : public FileFormat
    {
    public:
        virtual Sequence importFileSingle(std::istream& stream,
            ImportFlags flags = ImportFlags::None) override;
        virtual void exportSequence(std::ostream& stream,
            const Sequence& sequence,
            ExportFlags flags = ExportFlags::None) override;
    };

}  // namespace api
}  // namespace recombinant