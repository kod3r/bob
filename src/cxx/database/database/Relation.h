/**
 * @file database/Relation.h
 * @author <a href="mailto:andre.anjos@idiap.ch">Andre Anjos</a> 
 *
 * @brief Declares the Relation class for the Torch Dataset system.
 */

#ifndef TORCH_DATABASE_RELATION_H 
#define TORCH_DATABASE_RELATION_H

#include <list>
#include <string>
#include <cstdlib>
#include <boost/shared_ptr.hpp>

namespace Torch { namespace database {

  /**
   * The relation class for a dataset combines Members (array/arrayset
   * pointers) to indicate relationship between database arrays and arraysets.
   */
  class Relation {

    //I promise this exists
    class Rule;

    public:
      /**
       * Constructor, builds an empty Relation. 
       */
      Relation();

      /**
       * Copy constructor
       */
      Relation (const Relation& other);

      /**
       * Destructor
       */
      virtual ~Relation();

      /**
       * Assignment operation
       */
      Relation& operator= (const Relation& other);

      /**
       * Adds a member to the Relation. If a member with a given role already
       * exists, it we add to it.
       */
      inline void add (size_t arraysetid) {
        m_member.push_back(std::make_pair(arraysetid, 0));
      }

      inline void add (size_t arraysetid, size_t arrayid) {
        m_member.push_back(std::make_pair(arraysetid, arrayid));
      }

      /**
       * Removes a member, given the role. If the member does not exist, this
       * is a noop. Please note we will remove all members associated with a
       * given role.
       */
      void remove (size_t index);

      /**
       * Gets the id for this relation
       */
      inline size_t getId() const { return m_id; }

      /**
       * Given the index, returns a std::pair<size_t, size_t> where 'first' is
       * the arrayset id and 'second' is the array id. If the array id is set
       * to zero, it means this member points to an arrayset instead of a
       * single array. This will throw an exception if the id was not
       * registered in this Relation.
       */
      const std::pair<size_t, size_t>& operator[] (size_t index) const;

      /**
       * How to get a handle to all my roles. You must provide a container that
       * accepts push_back() and has std::string elements (e.g.
       * std::vector<std::string> or std::list<std::string>)
       */
      template <typename T> inline void index(T& container) const {
        for (std::list<std::pair<size_t,size_t> >::const_iterator it=m_member.begin(); it!=m_member.end(); ++it) container.push_back(it->first);
      }

      /**
       * A handle to all my members
       */
      inline const std::list<std::pair<size_t,size_t> >& members() const {
        return m_member;
      }

      //The next methods are sort of semi-private: Only to be used by the
      //Database loading system. You can adventure yourself, but really not
      //recommended to set the id or the parent of an array. Be sure to
      //understand the consequences.
 
      /**
       * Sets the id for this relation. This is some sort of semi-private
       * method and is intended only for database parsers. Use it with care.
       */
      inline void setId(const size_t id) { m_id = id; }

    private:
      size_t m_id; ///< my identifier
      std::list<std::pair<size_t, size_t> > m_member; ///< my members

  };

} }

#endif /* TORCH_DATABASE_RELATION_H */
