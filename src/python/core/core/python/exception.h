/**
 * @author <a href="mailto:andre.dos.anjos@gmail.com">Andre Anjos</a> 
 * @date Fri 25 Mar 15:05:55 2011 
 *
 * @brief Implements a few classes that are useful for binding Torch exceptions
 * to python.
 */

#ifndef TORCH_PYTHON_CORE_EXCEPTION_H 
#define TORCH_PYTHON_CORE_EXCEPTION_H

#include <boost/python.hpp>

/**
  * Raise a python exception from c++
  */
#define PYTHON_ERROR(TYPE, REASON) \
{ \
  PyErr_SetString(PyExc_##TYPE, REASON); \
  throw boost::python::error_already_set(); \
} 

namespace Torch { namespace core { namespace python {

  /**
   * The following lines of code implement exception translation from C++ into
   * python using Boost.Python and the instructions found on this webpage:
   * http://stackoverflow.com/questions/2261858/boostpython-export-custom-exception.
   * They were just slightly modified to make it easier to apply the code for
   * different situations.
   */
  template <typename T> struct BaseCxxToPythonTranslator {

    /**
     * This static class variable will hold a pointer to the exception type as
     * defined by the boost::python
     */
    static PyObject* pyExceptionType;

    /**
     * Do the exception translation for the specific exception we are trying to
     * tackle.
     */
    static void translateException(const T& ex) {
      assert(pyExceptionType != NULL);
      boost::python::object pythonExceptionInstance(ex);
      PyErr_SetObject(pyExceptionType, pythonExceptionInstance.ptr());
    }

    /**
     * Constructor will instantiate all required parameters for this standard
     * exception handler and create the pythonic bindings in one method call
     */
    BaseCxxToPythonTranslator(const char* python_name, const char* python_doc) {
      boost::python::class_<T> pythonEquivalentException(python_name, python_doc, boost::python::init<>("Creates a new exception of this type"));
      pythonEquivalentException.def("__str__", &T::what);
      pyExceptionType = pythonEquivalentException.ptr();
      boost::python::register_exception_translator<T>(&translateException);
    }

  };

  /**
   * The same as CxxBaseToPythonTranslator, but has includes a base-class
   * inheritance.
   */
  template <typename T, typename Base> struct CxxToPythonTranslator {

    /**
     * This static class variable will hold a pointer to the exception type as
     * defined by the boost::python
     */
    static PyObject* pyExceptionType;

    /**
     * Do the exception translation for the specific exception we are trying to
     * tackle.
     */
    static void translateException(const T& ex) {
      assert(pyExceptionType != NULL);
      boost::python::object pythonExceptionInstance(ex);
      PyErr_SetObject(pyExceptionType, pythonExceptionInstance.ptr());
    }

    /**
     * Constructor will instantiate all required parameters for this standard
     * exception handler and create the pythonic bindings in one method call
     */
    CxxToPythonTranslator(const char* python_name, const char* python_doc) {
      boost::python::class_<T, boost::python::bases<Base> > pythonEquivalentException(python_name, python_doc, boost::python::init<>("Creates a new exception of this type"));
      pythonEquivalentException.def("__str__", &T::what);
      pyExceptionType = pythonEquivalentException.ptr();
      boost::python::register_exception_translator<T>(&translateException);
    }

  };

  /**
   * If your exception has a 1 constructor parameter, use this variant
   */
  template <typename T, typename Base, typename TPar> struct CxxToPythonTranslatorPar {
    /**
     * This static class variable will hold a pointer to the exception type as
     * defined by the boost::python
     */
    static PyObject* pyExceptionType;

    /**
     * Do the exception translation for the specific exception we are trying to
     * tackle.
     */
    static void translateException(const T& ex) {
      assert(pyExceptionType != NULL);
      boost::python::object pythonExceptionInstance(ex);
      PyErr_SetObject(pyExceptionType, pythonExceptionInstance.ptr());
    }

    /**
     * Constructor will instantiate all required parameters for this standard
     * exception handler and create the pythonic bindings in one method call
     */
    CxxToPythonTranslatorPar(const char* python_name, const char* python_doc) {
      boost::python::class_<T, boost::python::bases<Base> > pythonEquivalentException(python_name, python_doc, boost::python::init<TPar>("Creates a new exception of this type"));
      pythonEquivalentException.def("__str__", &T::what);
      pyExceptionType = pythonEquivalentException.ptr();
      boost::python::register_exception_translator<T>(&translateException);
    }

  };

  /**
   * If your exception has a 2 constructor parameter, use this variant
   */
  template <typename T, typename Base, typename TPar1, typename TPar2> struct CxxToPythonTranslatorPar2 {
    /**
     * This static class variable will hold a pointer to the exception type as
     * defined by the boost::python
     */
    static PyObject* pyExceptionType;

    /**
     * Do the exception translation for the specific exception we are trying to
     * tackle.
     */
    static void translateException(const T& ex) {
      assert(pyExceptionType != NULL);
      boost::python::object pythonExceptionInstance(ex);
      PyErr_SetObject(pyExceptionType, pythonExceptionInstance.ptr());
    }

    /**
     * Constructor will instantiate all required parameters for this standard
     * exception handler and create the pythonic bindings in one method call
     */
    CxxToPythonTranslatorPar2(const char* python_name, const char* python_doc) {
      boost::python::class_<T, boost::python::bases<Base> > pythonEquivalentException(python_name, python_doc, boost::python::init<TPar1, TPar2>("Creates a new exception of this type"));
      pythonEquivalentException.def("__str__", &T::what);
      pyExceptionType = pythonEquivalentException.ptr();
      boost::python::register_exception_translator<T>(&translateException);
    }

  };

  /**
   * If your exception has a 3 constructor parameter, use this variant
   */
  template <typename T, typename Base, typename TPar1, typename TPar2, typename TPar3> struct CxxToPythonTranslatorPar3 {
    /**
     * This static class variable will hold a pointer to the exception type as
     * defined by the boost::python
     */
    static PyObject* pyExceptionType;

    /**
     * Do the exception translation for the specific exception we are trying to
     * tackle.
     */
    static void translateException(const T& ex) {
      assert(pyExceptionType != NULL);
      boost::python::object pythonExceptionInstance(ex);
      PyErr_SetObject(pyExceptionType, pythonExceptionInstance.ptr());
    }

    /**
     * Constructor will instantiate all required parameters for this standard
     * exception handler and create the pythonic bindings in one method call
     */
    CxxToPythonTranslatorPar3(const char* python_name, const char* python_doc) {
      boost::python::class_<T, boost::python::bases<Base> > pythonEquivalentException(python_name, python_doc, boost::python::init<TPar1, TPar2, TPar3>("Creates a new exception of this type"));
      pythonEquivalentException.def("__str__", &T::what);
      pyExceptionType = pythonEquivalentException.ptr();
      boost::python::register_exception_translator<T>(&translateException);
    }

  };

  /**
   * If your exception has a 4 constructor parameter, use this variant
   */
  template <typename T, typename Base, typename TPar1, typename TPar2, typename TPar3, typename TPar4> struct CxxToPythonTranslatorPar4 {
    /**
     * This static class variable will hold a pointer to the exception type as
     * defined by the boost::python
     */
    static PyObject* pyExceptionType;

    /**
     * Do the exception translation for the specific exception we are trying to
     * tackle.
     */
    static void translateException(const T& ex) {
      assert(pyExceptionType != NULL);
      boost::python::object pythonExceptionInstance(ex);
      PyErr_SetObject(pyExceptionType, pythonExceptionInstance.ptr());
    }

    /**
     * Constructor will instantiate all required parameters for this standard
     * exception handler and create the pythonic bindings in one method call
     */
    CxxToPythonTranslatorPar4(const char* python_name, const char* python_doc) {
      boost::python::class_<T, boost::python::bases<Base> > pythonEquivalentException(python_name, python_doc, boost::python::init<TPar1, TPar2, TPar3, TPar4>("Creates a new exception of this type"));
      pythonEquivalentException.def("__str__", &T::what);
      pyExceptionType = pythonEquivalentException.ptr();
      boost::python::register_exception_translator<T>(&translateException);
    }

  };

  template <typename T> PyObject* BaseCxxToPythonTranslator<T>::pyExceptionType = 0;
  template <typename T, typename Base> PyObject* CxxToPythonTranslator<T,Base>::pyExceptionType = 0;
  template <typename T, typename Base, typename TPar> PyObject* CxxToPythonTranslatorPar<T,Base,TPar>::pyExceptionType = 0;
  template <typename T, typename Base, typename TPar1, typename TPar2> PyObject* CxxToPythonTranslatorPar2<T,Base,TPar1,TPar2>::pyExceptionType = 0;
  template <typename T, typename Base, typename TPar1, typename TPar2, typename TPar3> PyObject* CxxToPythonTranslatorPar3<T,Base,TPar1,TPar2,TPar3>::pyExceptionType = 0;
  template <typename T, typename Base, typename TPar1, typename TPar2, typename TPar3, typename TPar4> PyObject* CxxToPythonTranslatorPar4<T,Base,TPar1,TPar2,TPar3,TPar4>::pyExceptionType = 0;

}}}

#endif /* TORCH_PYTHON_CORE_EXCEPTION_H */
