/**
 * @file cxx/io/src/HDF5File.cc
 * @date Wed Jun 22 17:50:08 2011 +0200
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief Implementation of the read/write functionality for HDF5 files
 *
 * Copyright (C) 2011-2012 Idiap Research Institute, Martigny, Switzerland
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "io/HDF5File.h"

namespace io = bob::io;
namespace fs = boost::filesystem;
namespace ca = bob::core::array;

static unsigned int getH5Access (io::HDF5File::mode_t v) {
  switch(v)
  {
    case 0: return H5F_ACC_RDONLY;
    case 1: return H5F_ACC_RDWR;
    case 2: return H5F_ACC_TRUNC;
    case 4: return H5F_ACC_EXCL;
    default:
      throw io::HDF5InvalidFileAccessModeError(v);
  }
}

io::HDF5File::HDF5File(const std::string& filename, mode_t mode):
  m_file(new io::detail::hdf5::File(filename, getH5Access(mode))),
  m_index(),
  m_cwd("/") ///< we start by looking at the root directory
{
  //makes sure we will shut-up the HDF5 automatic logging before we start
  io::detail::hdf5::index(m_file, m_index);
}

io::HDF5File::~HDF5File() {
}

void io::HDF5File::cd(const std::string& path) {
  m_cwd = resolve(path);
}

const std::string& io::HDF5File::cwd() const {
  return m_cwd.string();
}

static fs::path trim_one(const fs::path& p) {
  if (p == p.root_path()) return p;
  fs::path retval;
  for (fs::path::iterator it = p.begin(); it!=p.end(); ++it) {
    fs::path::iterator next = it;
    ++next; //< for the lack of better support in boost::filesystem V2
    if (next == p.end()) break; //< == skip the last bit
    retval /= *it;
  }
  return retval;
}

std::string io::HDF5File::resolve(const std::string& path) const {
  //the path to be solved is what the user inputs, unless (s)he inputs a
  //relative path, in which case we complete from him/her.
  fs::path completed(path);
  if (! completed.is_complete()) completed = fs::complete(completed, m_cwd);

  //now we prune the path to make sure we don't have relative bits inside, like
  //'..' or '.'
  fs::path retval;
  for (fs::path::iterator it = completed.begin(); it != completed.end(); ++it) {
    if (*it == "..") {
      retval = trim_one(retval);
      continue;
    }
    if (*it == ".") { //ignore '.'
      continue;
    }
    retval /= *it;
  }
  return retval.string();
}

bool io::HDF5File::contains (const std::string& path) const {
  return m_index.find(resolve(path)) != m_index.end();
}

const std::vector<io::HDF5Descriptor>& io::HDF5File::describe 
(const std::string& path) const {
  std::string absolute = resolve(path);
  if (!contains(path)) 
    throw io::HDF5InvalidPath(m_file->m_path.string(), absolute);
  return m_index.find(absolute)->second->m_descr;
}

void io::HDF5File::unlink (const std::string& path) {
  std::string absolute = resolve(path);
  if (!contains(path)) throw io::HDF5InvalidPath(m_file->m_path.string(), absolute);
  m_file->unlink(absolute);
  m_index.erase(absolute);
}

void io::HDF5File::rename (const std::string& from, const std::string& to) {
  std::string absfrom = resolve(from);
  std::string absto = resolve(to);
  if (!contains(absfrom)) 
    throw io::HDF5InvalidPath(m_file->m_path.string(), absfrom);
  m_file->rename(absfrom, absto);
  m_index[absto] = m_index[absfrom];
  m_index.erase(absfrom);
}

void io::HDF5File::copy (HDF5File& other) {
  //TODO
}

void io::HDF5File::create (const std::string& path, const ca::typeinfo& ti,
    bool list, size_t compression) {
  std::string absolute = resolve(path);
  if (!contains(absolute)) {
    m_index[absolute] =
      boost::make_shared<detail::hdf5::Dataset>(boost::ref(m_file),
          absolute, io::HDF5Type(ti), list, compression);
  }
  else {
    //still make sure the type is usable -- that will throw if not
    m_index[absolute]->size(io::HDF5Type(ti));
  }
}

void io::HDF5File::read_buffer (const std::string& path, size_t pos, 
    ca::interface& b) {
  std::string absolute = resolve(path);
  if (!contains(absolute)) 
    throw bob::io::HDF5InvalidPath(m_file->m_path.string(), absolute);
  m_index[absolute]->read_buffer(pos, io::HDF5Type(b.type()), b.ptr());
}

void io::HDF5File::write_buffer (const std::string& path, 
    size_t pos, const ca::interface& b) {
  std::string absolute = resolve(path);
  if (!contains(absolute)) 
    throw bob::io::HDF5InvalidPath(m_file->m_path.string(), absolute);
  m_index[absolute]->write_buffer(pos, io::HDF5Type(b.type()), b.ptr());
}

void io::HDF5File::extend_buffer(const std::string& path,
    const ca::interface& b) {
  std::string absolute = resolve(path);
  if (!contains(absolute)) 
    throw bob::io::HDF5InvalidPath(m_file->m_path.string(), absolute);
  m_index[absolute]->extend_buffer(io::HDF5Type(b.type()), b.ptr());
}