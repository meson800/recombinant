#include "Sequence.h"

#include <locale>
#include <map>

#include "Exceptions.h"

#include "../doctest.h"
namespace recombinant
{
namespace api
{
    std::pair<std::vector<Sequence::SeqUnit>, Sequence::Type>
    Sequence::stringToSeq(const std::string& str)
    {
        // Guess the type of string by iterating over it
        // We do this by comparing to the following "use tables", based on:
        // https://zhanglab.ccmb.med.umich.edu/FASTA/
        //
        // ABCDEFGHIJKLMNOPQRSTUVWXYZ*-
        // x x   x      x     x       x DNA (classic)
        // x x   x      x      x      x RNA (classic)
        // xxxx  xx  x xx   xxx xx x  x DNA
        // xxxx  xx  x xx   xx xxx x  x RNA
        // xxxxxxxxx xxxx xxxxxxxxxxxxx Protein

        bool dna_consistent         = true;
        bool classic_dna_consistent = true;  // classic = ACTGN-
        bool rna_consistent         = true;
        bool classic_rna_consistent = true;  // classic = ACTUN-

        for (size_t i = 0; i < str.size(); ++i)
        {
            char c = std::toupper(str.at(i));
            switch (c)
            {
                case 'A':
                case 'C':
                case 'G':
                case 'N':
                case '-':
                    break;  // Uninformative cases

                case 'B':
                case 'D':
                case 'H':
                case 'K':
                case 'M':
                case 'R':
                case 'S':
                case 'V':
                case 'W':
                case 'Y':
                    classic_dna_consistent = false;
                    classic_rna_consistent = false;
                    break;

                case 'E':
                case 'F':
                case 'I':
                case 'L':
                case 'P':
                case 'Q':
                case 'X':
                case 'Z':
                case '*':
                    classic_dna_consistent = false;
                    classic_rna_consistent = false;
                    dna_consistent         = false;
                    rna_consistent         = false;
                    break;

                case 'T':
                    classic_rna_consistent = false;
                    rna_consistent         = false;
                    break;

                case 'U':
                    classic_dna_consistent = false;
                    dna_consistent         = false;
                    break;

                default:
                    // Some weird character we didn't expect
                    throw SequenceImportError(
                        std::string("Sequence had unknown character:" + c));
                    break;
            }
        }

        // Prefer returning the following in order:
        // classic DNA, classic RNA, DNA, RNA, protein
        if (classic_dna_consistent)
        {
            return std::pair<std::vector<SeqUnit>, Type>(
                typedStringToSeq(str, Type::DNA), Type::DNA);
        }
        if (classic_rna_consistent)
        {
            return std::pair<std::vector<SeqUnit>, Type>(
                typedStringToSeq(str, Type::RNA), Type::RNA);
        }
        if (dna_consistent)
        {
            return std::pair<std::vector<SeqUnit>, Type>(
                typedStringToSeq(str, Type::DNA), Type::DNA);
        }
        if (rna_consistent)
        {
            return std::pair<std::vector<SeqUnit>, Type>(
                typedStringToSeq(str, Type::RNA), Type::RNA);
        }
        return std::pair<std::vector<SeqUnit>, Type>(
            typedStringToSeq(str, Type::Protein), Type::Protein);
    }

    std::vector<Sequence::SeqUnit> Sequence::typedStringToSeq(
        const std::string& str, Sequence::Type type)
    {
        static const std::map<char, SeqUnit> dna = {{'A', SeqUnit(DNABase::A)},
            {'T', SeqUnit(DNABase::T)}, {'C', SeqUnit(DNABase::C)},
            {'G', SeqUnit(DNABase::G)}, {'R', SeqUnit(DNABase::R)},
            {'Y', SeqUnit(DNABase::Y)}, {'K', SeqUnit(DNABase::K)},
            {'M', SeqUnit(DNABase::M)}, {'S', SeqUnit(DNABase::S)},
            {'W', SeqUnit(DNABase::W)}, {'B', SeqUnit(DNABase::B)},
            {'D', SeqUnit(DNABase::D)}, {'H', SeqUnit(DNABase::H)},
            {'V', SeqUnit(DNABase::V)}, {'N', SeqUnit(DNABase::N)},
            {'-', SeqUnit(DNABase::Gap)}};

        static const std::map<char, SeqUnit> rna = {{'A', SeqUnit(RNABase::A)},
            {'U', SeqUnit(RNABase::U)}, {'C', SeqUnit(RNABase::C)},
            {'G', SeqUnit(RNABase::G)}, {'R', SeqUnit(RNABase::R)},
            {'Y', SeqUnit(RNABase::Y)}, {'K', SeqUnit(RNABase::K)},
            {'M', SeqUnit(RNABase::M)}, {'S', SeqUnit(RNABase::S)},
            {'W', SeqUnit(RNABase::W)}, {'B', SeqUnit(RNABase::B)},
            {'D', SeqUnit(RNABase::D)}, {'H', SeqUnit(RNABase::H)},
            {'V', SeqUnit(RNABase::V)}, {'N', SeqUnit(RNABase::N)},
            {'-', SeqUnit(RNABase::Gap)}};

        static const std::map<char, SeqUnit> protein = {
            {'A', SeqUnit(AminoAcid::A)},
            {'R', SeqUnit(AminoAcid::R)},
            {'N', SeqUnit(AminoAcid::N)},
            {'D', SeqUnit(AminoAcid::D)},
            {'B', SeqUnit(AminoAcid::B)},
            {'C', SeqUnit(AminoAcid::C)},
            {'E', SeqUnit(AminoAcid::E)},
            {'Q', SeqUnit(AminoAcid::Q)},
            {'Z', SeqUnit(AminoAcid::Z)},
            {'G', SeqUnit(AminoAcid::G)},
            {'H', SeqUnit(AminoAcid::H)},
            {'I', SeqUnit(AminoAcid::I)},
            {'L', SeqUnit(AminoAcid::L)},
            {'K', SeqUnit(AminoAcid::K)},
            {'M', SeqUnit(AminoAcid::M)},
            {'F', SeqUnit(AminoAcid::F)},
            {'P', SeqUnit(AminoAcid::P)},
            {'S', SeqUnit(AminoAcid::S)},
            {'T', SeqUnit(AminoAcid::T)},
            {'W', SeqUnit(AminoAcid::W)},
            {'Y', SeqUnit(AminoAcid::Y)},
            {'V', SeqUnit(AminoAcid::V)},
            {'U', SeqUnit(AminoAcid::U)},
            {'X', SeqUnit(AminoAcid::X)},
            {'*', SeqUnit(AminoAcid::Stop)},
            {'-', SeqUnit(AminoAcid::Gap)},
        };

        std::vector<SeqUnit> result;
        result.reserve(str.size());
        const std::map<char, SeqUnit>* usedMap = nullptr;
        switch (type)
        {
            case Type::DNA:
                usedMap = &dna;
                break;
            case Type::RNA:
                usedMap = &rna;
                break;
            case Type::Protein:
                usedMap = &protein;
                break;
            default:
                throw SequenceImportError("Invalid branch!");
                break;
        }

        for (size_t i = 0; i < str.size(); ++i)
        {
            result.push_back(usedMap->at(std::toupper(str[i])));
        }
        return result;
    }

    bool Sequence::operator==(const Sequence& other) const
    {
        if (other.name != name || other.description != description ||
            other.sequence.size() != sequence.size() || other.type != type)
        {
            return false;
        }
        // check sequence now
        for (size_t i = 0; i < sequence.size(); ++i)
        {
            switch (type)
            {
                case Type::DNA:
                    if (sequence[i].db != other.sequence[i].db)
                    {
                        return false;
                    }
                    break;
                case Type::RNA:
                    if (sequence[i].rb != other.sequence[i].rb)
                    {
                        return false;
                    }
                    break;
                case Type::Protein:
                    if (sequence[i].aa != other.sequence[i].aa)
                    {
                        return false;
                    }
                    break;
            }
        }
        // Nothing was different! Return success
        return true;
    }

    bool Sequence::operator!=(const Sequence& other) const
    {
        return !(*this == other);
    }

    std::string Sequence::getSpan(size_t start) const
    {
        return getSpan(start, sequence.size());
    }

    std::string Sequence::getSpan() const
    {
        return getSpan(0, sequence.size());
    }

    std::string Sequence::getSpan(size_t start, size_t end) const
    {
        if (end < start || start > sequence.size() || end > sequence.size())
        {
            throw std::runtime_error("Selected invalid span");
        }

        std::string result;
        result.reserve(end - start);

        // Just two boring nested switch statements
        switch (type)
        {
            case Type::DNA:
            {
                for (auto it = sequence.begin() + start;
                     it != sequence.begin() + end; ++it)
                {
                    switch (it->db)
                    {
                        case DNABase::A:
                            result.push_back('A');
                            break;
                        case DNABase::T:
                            result.push_back('T');
                            break;
                        case DNABase::C:
                            result.push_back('C');
                            break;
                        case DNABase::G:
                            result.push_back('G');
                            break;
                        case DNABase::R:
                            result.push_back('R');
                            break;
                        case DNABase::Y:
                            result.push_back('Y');
                            break;
                        case DNABase::K:
                            result.push_back('K');
                            break;
                        case DNABase::M:
                            result.push_back('M');
                            break;
                        case DNABase::S:
                            result.push_back('S');
                            break;
                        case DNABase::W:
                            result.push_back('W');
                            break;
                        case DNABase::B:
                            result.push_back('B');
                            break;
                        case DNABase::D:
                            result.push_back('D');
                            break;
                        case DNABase::H:
                            result.push_back('H');
                            break;
                        case DNABase::V:
                            result.push_back('V');
                            break;
                        case DNABase::N:
                            result.push_back('N');
                            break;
                        case DNABase::Gap:
                            result.push_back('-');
                            break;
                    }
                }
            }
            break;

            case Type::RNA:
            {
                for (auto it = sequence.begin() + start;
                     it != sequence.begin() + end; ++it)
                {
                    switch (it->rb)
                    {
                        case RNABase::A:
                            result.push_back('A');
                            break;
                        case RNABase::U:
                            result.push_back('U');
                            break;
                        case RNABase::C:
                            result.push_back('C');
                            break;
                        case RNABase::G:
                            result.push_back('G');
                            break;
                        case RNABase::R:
                            result.push_back('R');
                            break;
                        case RNABase::Y:
                            result.push_back('Y');
                            break;
                        case RNABase::K:
                            result.push_back('K');
                            break;
                        case RNABase::M:
                            result.push_back('M');
                            break;
                        case RNABase::S:
                            result.push_back('S');
                            break;
                        case RNABase::W:
                            result.push_back('W');
                            break;
                        case RNABase::B:
                            result.push_back('B');
                            break;
                        case RNABase::D:
                            result.push_back('D');
                            break;
                        case RNABase::H:
                            result.push_back('H');
                            break;
                        case RNABase::V:
                            result.push_back('V');
                            break;
                        case RNABase::N:
                            result.push_back('N');
                            break;
                        case RNABase::Gap:
                            result.push_back('-');
                            break;
                    }
                }
            }
            break;

            case Type::Protein:
            {
                for (auto it = sequence.begin() + start;
                     it != sequence.begin() + end; ++it)
                {
                    switch (it->aa)
                    {
                        case AminoAcid::A:
                            result.push_back('A');
                            break;
                        case AminoAcid::R:
                            result.push_back('R');
                            break;
                        case AminoAcid::N:
                            result.push_back('N');
                            break;
                        case AminoAcid::D:
                            result.push_back('D');
                            break;
                        case AminoAcid::B:
                            result.push_back('B');
                            break;
                        case AminoAcid::C:
                            result.push_back('C');
                            break;
                        case AminoAcid::E:
                            result.push_back('E');
                            break;
                        case AminoAcid::Q:
                            result.push_back('Q');
                            break;
                        case AminoAcid::Z:
                            result.push_back('Z');
                            break;
                        case AminoAcid::G:
                            result.push_back('G');
                            break;
                        case AminoAcid::H:
                            result.push_back('H');
                            break;
                        case AminoAcid::I:
                            result.push_back('I');
                            break;
                        case AminoAcid::L:
                            result.push_back('L');
                            break;
                        case AminoAcid::K:
                            result.push_back('K');
                            break;
                        case AminoAcid::M:
                            result.push_back('M');
                            break;
                        case AminoAcid::F:
                            result.push_back('F');
                            break;
                        case AminoAcid::P:
                            result.push_back('P');
                            break;
                        case AminoAcid::S:
                            result.push_back('S');
                            break;
                        case AminoAcid::T:
                            result.push_back('T');
                            break;
                        case AminoAcid::W:
                            result.push_back('W');
                            break;
                        case AminoAcid::Y:
                            result.push_back('Y');
                            break;
                        case AminoAcid::V:
                            result.push_back('V');
                            break;
                        case AminoAcid::U:
                            result.push_back('U');
                            break;
                        case AminoAcid::X:
                            result.push_back('X');
                            break;
                        case AminoAcid::Stop:
                            result.push_back('*');
                            break;
                        case AminoAcid::Gap:
                            result.push_back('-');
                            break;
                    }
                }
            }
            break;
        }
        return result;
    }

    TEST_CASE("Sequence::getSpan: ")
    {
        Sequence seq;
        seq.type = Sequence::Type::DNA;
        seq.sequence =
            Sequence::typedStringToSeq("ATCGGTCA", Sequence::Type::DNA);

        SUBCASE("Handles bounds checking")
        {
            CHECK_THROWS(seq.getSpan(10, 10));
            CHECK_THROWS(seq.getSpan(5, 2));
            CHECK_THROWS(seq.getSpan(0, 20));
        }

        SUBCASE("Returns subspans correctly")
        {
            CHECK_EQ(seq.getSpan(0, 3), "ATC");
            CHECK_EQ(seq.getSpan(0, 8), "ATCGGTCA");
            CHECK_EQ(seq.getSpan(4, 8), "GTCA");
        }

        SUBCASE("Overloads work properly")
        {
            CHECK_EQ(seq.getSpan(4), "GTCA");
            CHECK_EQ(seq.getSpan(), "ATCGGTCA");
        }
    }

    TEST_CASE("Sequence::typedStringToSeq: DNA string encoding")
    {
        std::vector<Sequence::SeqUnit> seq =
            Sequence::typedStringToSeq("ATCGRYKMSWBDHVN-", Sequence::Type::DNA);
        std::vector<Sequence::DNABase> compare{Sequence::DNABase::A,
            Sequence::DNABase::T, Sequence::DNABase::C, Sequence::DNABase::G,
            Sequence::DNABase::R, Sequence::DNABase::Y, Sequence::DNABase::K,
            Sequence::DNABase::M, Sequence::DNABase::S, Sequence::DNABase::W,
            Sequence::DNABase::B, Sequence::DNABase::D, Sequence::DNABase::H,
            Sequence::DNABase::V, Sequence::DNABase::N, Sequence::DNABase::Gap};
        REQUIRE_EQ(seq.size(), compare.size());
        bool same = true;
        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (seq[i].db != compare[i])
            {
                same = false;
            }
        }
        CHECK(same);

        Sequence fullseq;
        fullseq.type     = Sequence::Type::DNA;
        fullseq.sequence = seq;
        CHECK_EQ(fullseq.getSpan(), "ATCGRYKMSWBDHVN-");
    }

    TEST_CASE("Sequence::typedStringToSeq: RNA string encoding")
    {
        std::vector<Sequence::SeqUnit> seq =
            Sequence::typedStringToSeq("AUCGRYKMSWBDHVN-", Sequence::Type::RNA);
        std::vector<Sequence::RNABase> compare{Sequence::RNABase::A,
            Sequence::RNABase::U, Sequence::RNABase::C, Sequence::RNABase::G,
            Sequence::RNABase::R, Sequence::RNABase::Y, Sequence::RNABase::K,
            Sequence::RNABase::M, Sequence::RNABase::S, Sequence::RNABase::W,
            Sequence::RNABase::B, Sequence::RNABase::D, Sequence::RNABase::H,
            Sequence::RNABase::V, Sequence::RNABase::N, Sequence::RNABase::Gap};
        REQUIRE_EQ(seq.size(), compare.size());
        bool same = true;
        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (seq[i].rb != compare[i])
            {
                same = false;
            }
        }
        CHECK(same);

        Sequence fullseq;
        fullseq.type     = Sequence::Type::RNA;
        fullseq.sequence = seq;
        CHECK_EQ(fullseq.getSpan(), "AUCGRYKMSWBDHVN-");
    }

    TEST_CASE("Sequence::typedStringToSeq: Protein string encoding")
    {
        std::vector<Sequence::SeqUnit> seq = Sequence::typedStringToSeq(
            "ARNDBCEQZGHILKMFPSTWYVUX*-", Sequence::Type::Protein);
        std::vector<Sequence::AminoAcid> compare{Sequence::AminoAcid::A,
            Sequence::AminoAcid::R, Sequence::AminoAcid::N,
            Sequence::AminoAcid::D, Sequence::AminoAcid::B,
            Sequence::AminoAcid::C, Sequence::AminoAcid::E,
            Sequence::AminoAcid::Q, Sequence::AminoAcid::Z,
            Sequence::AminoAcid::G, Sequence::AminoAcid::H,
            Sequence::AminoAcid::I, Sequence::AminoAcid::L,
            Sequence::AminoAcid::K, Sequence::AminoAcid::M,
            Sequence::AminoAcid::F, Sequence::AminoAcid::P,
            Sequence::AminoAcid::S, Sequence::AminoAcid::T,
            Sequence::AminoAcid::W, Sequence::AminoAcid::Y,
            Sequence::AminoAcid::V, Sequence::AminoAcid::U,
            Sequence::AminoAcid::X, Sequence::AminoAcid::Stop,
            Sequence::AminoAcid::Gap};
        REQUIRE_EQ(seq.size(), compare.size());
        bool same = true;
        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (seq[i].aa != compare[i])
            {
                same = false;
            }
        }
        CHECK(same);

        Sequence fullseq;
        fullseq.type     = Sequence::Type::Protein;
        fullseq.sequence = seq;
        CHECK_EQ(
            fullseq.getSpan(), "ARNDBCEQZGHILKMFPSTWYVUX*-");
    }

    TEST_CASE("Sequence::typedStringToSeq: Lowercase letters properly encoded")
    {
        std::vector<Sequence::SeqUnit> seq =
            Sequence::typedStringToSeq("Aa", Sequence::Type::DNA);
        REQUIRE_EQ(seq.size(), 2);
        CHECK_EQ(seq[0].db, Sequence::DNABase::A);
        CHECK_EQ(seq[1].db, Sequence::DNABase::A);
    }

    TEST_CASE(
        "Sequence::typedStringToSeq: Throw an exception when invalid "
        "character "
        "present")
    {
        CHECK_THROWS(Sequence::typedStringToSeq("T", Sequence::Type::RNA));
        CHECK_THROWS(Sequence::typedStringToSeq("U", Sequence::Type::DNA));
        CHECK_THROWS(Sequence::typedStringToSeq("O", Sequence::Type::Protein));
    }

    TEST_CASE(
        "Sequence::stringToSeq: Throws when string has completely invalid "
        "characters")
    {
        CHECK_THROWS_AS(Sequence::stringToSeq("O~ "), SequenceImportError);
    }

    TEST_CASE("Sequence::stringToSeq: Inferrs sequence type")
    {
        auto result = Sequence::stringToSeq("ACTGNGGTACA");
        CHECK_EQ(result.second, Sequence::Type::DNA);

        result = Sequence::stringToSeq("ACUGNGGUACA");
        CHECK_EQ(result.second, Sequence::Type::RNA);

        result = Sequence::stringToSeq(
            "MALWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQ"
            "GSLQ"
            "PLALEGSLQKRGIVEQCCTSICSLYQLENYCN");
        CHECK_EQ(result.second, Sequence::Type::Protein);
    }

}  // namespace api
}  // namespace recombinant