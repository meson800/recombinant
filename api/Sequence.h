#pragma once
#include <stdint.h>

#include <string>
#include <vector>

namespace recombinant
{
namespace api
{
    /**
     * Stores genetic or protein information
     * in addition to feature information.
     */
    class Sequence
    {
    public:
        /**
         * Enum storing the standard DNA base pairs
         */
        enum class DNABase : uint8_t
        {
            A = 0,
            T,
            C,
            G,
            R,  // Purine
            Y,  // Pyrimidine
            K,  // Keto
            M,  // Amino
            S,  // Strong
            W,  // Weak
            B,  // Not A
            D,  // Not C
            H,  // Not G
            V,  // Not T
            N,
            Gap,
        };

        /**
         * Enum storing the standard RNA base pairs
         */
        enum class RNABase : uint8_t
        {
            A = 0,
            U,
            C,
            G,
            R,  // Purine
            Y,  // Pyrimidine
            K,  // Keto
            M,  // Amino
            S,  // Strong
            W,  // Weak
            B,  // Not A
            D,  // Not C
            H,  // Not G
            V,  // Not U
            N,
            Gap,
        };
        /**
         * Enum storing the standard protein amino acids
         */
        enum class AminoAcid : uint8_t
        {
            A = 0,
            R,
            N,
            D,
            B,
            C,
            E,
            Q,
            Z,
            G,
            H,
            I,
            L,
            K,
            M,
            F,
            P,
            S,
            T,
            W,
            Y,
            V,
            U,  // selenocysteine
            X,  // any
            Stop,
            Gap,
        };

        /**
         * This enum stores the possible types of sequences
         */
        enum class Type
        {
            DNA,
            RNA,
            Protein,
        };

        /**
         * This union stores all possible "units" of a sequence.
         * For a DNA/RNA sequence, these are base pairs. For a protein,
         * these are amino acids.
         */
        union SeqUnit
        {
            DNABase db;
            RNABase rb;
            AminoAcid aa;
            SeqUnit(DNABase b)
                : db(b)
            {}
            SeqUnit(RNABase b)
                : rb(b)
            {}
            SeqUnit(AminoAcid a)
                : aa(a)
            {}
        };

        /**
         * Takes an input string filled with an unknown sequence of values.
         * Attempts to guess the type of sequence (DNA/RNA/protein) and return
         * that, and otherwise returns a SequenceImportError
         */
        static std::pair<std::vector<SeqUnit>, Type> stringToSeq(
            const std::string& str);

        /**
         * Takes an input string with a given type (DNA/RNA/protein) and returns
         * the converted sequence. Raises a SequenceImportError if unsuccessful.
         */
        static std::vector<SeqUnit> typedStringToSeq(
            const std::string& str, Type type);

        /**
         * Compares two sequences, returning true if the two
         * sequences are identical (same name/description/sequence/features)
         */
        bool operator==(const Sequence& other) const;

        /**
         * Returns true if the two sequences are not equal. See
         * Sequence::operator== for details
         */
        bool operator!=(const Sequence& other) const;

        std::string name;  /// Stores a short name describing this sequence.
        std::string description;  /// A longer description of this sequence
        Type type;                /// The type of sequence stored
        std::vector<SeqUnit> sequence;  /// The actual sequence stored inside
    };

    /**
     * Stores information on a feature. Features
     * are formed out of a (not necessarily continuous)
     * span of a sequence, and can contain extra information.
     */
    class Feature
    {
    };

}  // namespace api
}  // namespace recombinant