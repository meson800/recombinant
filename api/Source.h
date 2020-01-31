#pragma once

#include <string>
#include <memory>
#include <vector>

namespace recombinant
{
namespace api
{
    /**
     * Represents an abstract tracked piece of data.
     *
     * The underlying object can be a Sequence, a folder, or something else.
     *
     * This gives us the flexibility to load sequence information
     * (such as vectors or genomes), annotations, sequencing data,
     * or unknown data.
     */
    struct Entity
    {
        /// Stores the type of this entity.
        enum class Type
        {
            Sequence,
            Container,
            Tabular,
            Unknown
        } type;

        /// Stores the name of this entity
        std::string name;

        /// Parent pointer stored as raw, to prevent loop leaks.
        Entity* parent;

        /// Stores the children of this entity. All entity types can have
        /// children!
        std::vector<std::unique_ptr<Entity>> children;

        /// Default constructor creates a Container with nullptr parent
        Entity();

        /// Deleted copy constructor to prevent mistakes
        Entity(const Entity&) = delete;
    };

    /**
     * Defines a source of sequence/protein information.
     *
     * This interface defines a standard way to interact with
     * sequence information. It supports arbitrary nesting,
     * storing several sequences inside single 'files', etc.
     *
     * At the core of a Source is a recursive listing of
     * file-like objects.
     *
     * Different backends can be written that match into this format.
     * Several different methods for operating on entities must
     * be implemented for a valid source.
     *
     * Backend implementations may wish to implement a map between
     * raw pointers of items and the real underlying item to perform
     * the requested operations.
     *
     * The core "file" returned by this are Entity classes.
     */
    class Source
    {
    public:
        /**
         * The root of the "tree" represented by this source.
         * Any items of this source should be children of this root entity.
         *
         * The name of the source is taken from the name of this root entity.
         */
        std::shared_ptr<Entity> root;

        /// Virtual constructor so sources are destroyed correctly.
        virtual ~Source() = default;
    };

}  // namespace api
}  // namespace recombinant