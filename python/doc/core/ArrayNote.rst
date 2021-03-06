.. vim: set fileencoding=utf-8 :
.. Andre Anjos <andre.anjos@idiap.ch>
.. Laurent El Shafey <laurent.el-shafey@idiap.ch>
.. Tue Apr 5 09:16:14 2011 +0200
.. 
.. Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
.. 
.. This program is free software: you can redistribute it and/or modify
.. it under the terms of the GNU General Public License as published by
.. the Free Software Foundation, version 3 of the License.
.. 
.. This program is distributed in the hope that it will be useful,
.. but WITHOUT ANY WARRANTY; without even the implied warranty of
.. MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
.. GNU General Public License for more details.
.. 
.. You should have received a copy of the GNU General Public License
.. along with this program.  If not, see <http://www.gnu.org/licenses/>.

=================================================
 Note on Supported Array Data Types (``dtypes``)
=================================================

Because `Blitz++`_ arrays (and :py:class:`numpy.ndarray`) are template types,
we must fix the set of supported combinations of element type and number of
dimensions that are supported by |project| and subsequently at the python
bridge. `Blitz++`_ arrays a flexible containers that support a different range
of base element types and up to 11 dimensions. At |project|, we limit the
support of provided code to manipulate arrays **up to 4 dimensions** and using
the following element types. These element types and ranks should cover most of
the functionality needed by machine learning algorithms and signal processing
utilities.

+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| Common name  |   C++                       | `NumPy`_     | Meaning                                                      |
+==============+=============================+==============+==============================================================+
| bool         | bool                        | bool         | a boolean                                                    |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| int8         | int8_t                      | int8         | a signed integer, with 8 bits                                |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| int16        | int16_t                     | int16        | a signed integer, with 16 bits                               |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| int32        | int32_t                     | int32        | a signed integer, with 32 bits                               |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| int64        | int64_t                     | int64        | a signed integer, with 64 bits                               |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| uint8        | uint8_t                     | uint8        | a unsigned integer, with 8 bits                              |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| uint16       | uint16_t                    | uint16       | a unsigned integer, with 16 bits                             |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| uint32       | uint32_t                    | uint32       | a unsigned integer, with 32 bits                             |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| uint64       | uint64_t                    | uint64       | a unsigned integer, with 64 bits                             | 
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| float32      | float                       | float32      | a real number with single precision, with 32 bits            |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| float64      | double                      | float64      | a real number with double precision, with 64 bits            |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| complex64    | std::complex<float>         | complex64    | a complex number with each part using each a 32-bit float    |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+
| complex128   | std::complex<double>        | complex128   | a complex number with each part using each a 64-bit float    |
+--------------+-----------------------------+--------------+--------------------------------------------------------------+

.. dropped support:
  +--------------+-----------------------------+--------------+--------------------------------------------------------------+
  | ~~float128~~ | ~~long double~~             | ~~float128~~ | ~~a real number with quadruple precision, with 128 bits~~    |
  +--------------+-----------------------------+--------------+--------------------------------------------------------------+
  | -complex256- | -std::complex<long double>- | -complex256- | -a complex number with each part using each a 128-bit float- |
  +--------------+-----------------------------+--------------+--------------------------------------------------------------+

.. note::

  We have decided not to support ``long double`` and
  ``std::complex<long double>`` because of variations between 32 and 64-bit
  architectures in the representation of ``long double``'s. A simple 
  experiment with gdb can show you the problem. Under a 32-bit Linux machine,
  the sizes of the types listed above are:

  .. code-block:: none
  
    Size of built-in types: 
    bool: 1
    uint8_t: 1
    uint16_t: 2
    uint32_t: 4
    uint64_t: 8
    int8_t: 1
    int16_t: 2
    int32_t: 4
    int64_t: 8
    float: 4
    double: 8
    long double: 12
    std::complex<float>: 8
    std::complex<double>: 16
    **std::complex<long double>: 24**

    size_t: 4
    unsigned int: 4
    int: 4

  Whereas in a 64-bit machine, this is what you would see:

  .. code-block:: none
  
    Size of built-in types: 
    bool: 1
    uint8_t: 1
    uint16_t: 2
    uint32_t: 4
    uint64_t: 8
    int8_t: 1
    int16_t: 2
    int32_t: 4
    int64_t: 8
    float: 4
    double: 8
    long double: 12
    std::complex<float>: 8
    std::complex<double>: 16
    **std::complex<long double>: 32**

    size_t: 8
    unsigned int: 4
    int: 4

  This made it hard to write code that can I/O data properly. Moreover, long
  doubles are not widely popular, making this choice an easy one.

.. include:: ../links.rst
