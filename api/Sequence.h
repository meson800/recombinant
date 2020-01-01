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
            V
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
        };

        std::string name;  /// Stores a short name describing this sequence.
        std::string description;  /// A longer description of this sequence
        Type type; /// The type of sequence stored
        std::vector<SeqUnit> sequence; /// The actual sequence stored inside
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