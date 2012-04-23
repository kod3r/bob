/**
 * @file python/ip/src/HOG.cc
 * @date Wed Apr 18 18:35:48 2012 +0200
 * @author Laurent El Shafey <Laurent.El-Shafey@idiap.ch>
 *
 * @brief Binds HOG descriptors into python
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

#include <boost/python.hpp>
#include "core/python/ndarray.h"
#include "ip/HOG.h"

using namespace boost::python;
namespace bp = bob::python;
namespace ip = bob::ip;
namespace ca = bob::core::array;

static const char* gradientmaps_doc = "Objects of this class, after configuration, can extract\
  gradient magnitude and orientation maps.";
static const char* hog_doc = "Objects of this class, after configuration, can extract\
  Histogram of Gradients (HOG) descriptors.";

static void hog_compute_histogram_(bp::const_ndarray mag, bp::const_ndarray ori,
    bp::ndarray hist, const bool init_hist=true, const bool full_orientation=false)
{
  const ca::typeinfo& infoMag = mag.type();
  const ca::typeinfo& infoOri = ori.type();
  const ca::typeinfo& infoHist = hist.type();

  if(infoMag.nd != 2 || infoOri.nd !=2)
    PYTHON_ERROR(TypeError, "hog_compute_histogram_ requires 2D input arrays.");
  if(infoHist.nd !=1)
    PYTHON_ERROR(TypeError, "hog_compute_histogram_ requires a 1D output array.");

  if(infoMag.dtype != ca::t_float64 || infoOri.dtype != ca::t_float64 || 
      infoHist.dtype != ca::t_float64)
    PYTHON_ERROR(TypeError, "hog_compute_histogram_ requires input arrays of type float64.");

  blitz::Array<double,1> hist_ = hist.bz<double,1>();
  ip::hogComputeHistogram_(mag.bz<double,2>(), ori.bz<double,2>(), hist_, 
    init_hist, full_orientation);
}

static void hog_compute_histogram(bp::const_ndarray mag, bp::const_ndarray ori,
    bp::ndarray hist, const bool init_hist=true, const bool full_orientation=false)
{
  const ca::typeinfo& infoMag = mag.type();
  const ca::typeinfo& infoOri = ori.type();
  const ca::typeinfo& infoHist = hist.type();

  if(infoMag.nd != 2 || infoOri.nd !=2)
    PYTHON_ERROR(TypeError, "hog_compute_histogram requires 2D input arrays.");
  if(infoHist.nd !=1)
    PYTHON_ERROR(TypeError, "hog_compute_histogram requires a 1D output array.");

  if(infoMag.dtype != ca::t_float64 || infoOri.dtype != ca::t_float64 || 
      infoHist.dtype != ca::t_float64)
    PYTHON_ERROR(TypeError, "hog_compute_histogram requires input arrays of type float64.");

  blitz::Array<double,1> hist_ = hist.bz<double,1>();
  ip::hogComputeHistogram(mag.bz<double,2>(), ori.bz<double,2>(), hist_, 
    init_hist, full_orientation);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(hog_compute_histogram__overloads, hog_compute_histogram_, 3, 5) 
BOOST_PYTHON_FUNCTION_OVERLOADS(hog_compute_histogram_overloads, hog_compute_histogram, 3, 5) 

template <int D> static void inner_normalize_block_( 
  bp::const_ndarray hist, bp::ndarray norm_hist, const ip::BlockNorm block_norm, 
  const double eps, const double threshold)
{
  blitz::Array<double,1> norm_hist_ = norm_hist.bz<double,1>();
  ip::normalizeBlock_(hist.bz<double,D>(), norm_hist_, block_norm, eps, threshold);
}

static void normalize_block_(bp::const_ndarray hist, bp::ndarray norm_hist,
  const ip::BlockNorm block_norm=ip::L2, const double eps=1e-10, 
  const double threshold=0.2)
{
  const ca::typeinfo& infoHist = hist.type();
  const ca::typeinfo& infoNormHist = norm_hist.type();

  if(infoNormHist.nd !=1)
    PYTHON_ERROR(TypeError, "normalize_block_ requires a 1D output array.");

  if(infoHist.dtype != ca::t_float64 || infoNormHist.dtype != ca::t_float64)
    PYTHON_ERROR(TypeError, "normalize_block_ requires input arrays of type float64.");

  switch(infoHist.nd)
  {
    case 1:
      inner_normalize_block_<1>(hist, norm_hist, block_norm, 
        eps, threshold);
      break;
    case 2:
      inner_normalize_block_<2>(hist, norm_hist, block_norm, 
        eps, threshold);
      break;
    case 3:
      inner_normalize_block_<3>(hist, norm_hist, block_norm, 
        eps, threshold);
      break;
    default:
      PYTHON_ERROR(TypeError, "normalize_block requires a 1D, 2D or 3D input array.");
  } 
}


template <int D> static void inner_normalize_block( 
  bp::const_ndarray hist, bp::ndarray norm_hist, const ip::BlockNorm block_norm, 
  const double eps, const double threshold)
{
  blitz::Array<double,1> norm_hist_ = norm_hist.bz<double,1>();
  ip::normalizeBlock(hist.bz<double,D>(), norm_hist_, block_norm, eps, threshold);
}

static void normalize_block(bp::const_ndarray hist, bp::ndarray norm_hist,
  const ip::BlockNorm block_norm=ip::L2, const double eps=1e-10, 
  const double threshold=0.2)
{
  const ca::typeinfo& infoHist = hist.type();
  const ca::typeinfo& infoNormHist = norm_hist.type();

  if(infoNormHist.nd !=1)
    PYTHON_ERROR(TypeError, "normalize_block_ requires a 1D output array.");

  if(infoHist.dtype != ca::t_float64 || infoNormHist.dtype != ca::t_float64)
    PYTHON_ERROR(TypeError, "normalize_block_ requires input arrays of type float64.");

  switch(infoHist.nd)
  {
    case 1:
      inner_normalize_block<1>(hist, norm_hist, block_norm, 
        eps, threshold);
      break;
    case 2:
      inner_normalize_block<2>(hist, norm_hist, block_norm, 
        eps, threshold);
      break;
    case 3:
      inner_normalize_block<3>(hist, norm_hist, block_norm, 
        eps, threshold);
      break;
    default:
      PYTHON_ERROR(TypeError, "normalize_block requires a 1D, 2D or 3D input array.");
      break;
  } 
}


BOOST_PYTHON_FUNCTION_OVERLOADS(normalize_block__overloads, normalize_block_, 2, 5) 
BOOST_PYTHON_FUNCTION_OVERLOADS(normalize_block_overloads, normalize_block, 2, 5) 

template <typename T> static void inner_gradient_maps_call1(ip::GradientMaps& obj, 
    bp::const_ndarray input, bp::ndarray magnitude, bp::ndarray orientation)
{
  blitz::Array<double,2> magnitude_ = magnitude.bz<double,2>();
  blitz::Array<double,2> orientation_ = orientation.bz<double,2>();
  obj.forward(input.bz<T,2>(), magnitude_, orientation_);
}

static void gradient_maps_call1(ip::GradientMaps& obj, bp::const_ndarray input,
    bp::ndarray magnitude, bp::ndarray orientation) 
{
  const ca::typeinfo& info = input.type();
  switch (info.dtype) {
    case ca::t_uint8: 
      return inner_gradient_maps_call1<uint8_t>(obj, input, magnitude, orientation);
    case ca::t_uint16:
      return inner_gradient_maps_call1<uint16_t>(obj, input, magnitude, orientation);
    case ca::t_float64: 
      return inner_gradient_maps_call1<double>(obj, input, magnitude, orientation);
    default: PYTHON_ERROR(TypeError, "GradientMaps does not support array with type '%s'", info.str().c_str());
  }
}

template <typename T> static void inner_gradient_maps_call2(ip::GradientMaps& obj, 
    bp::const_ndarray input, bp::ndarray magnitude, bp::ndarray orientation)
{
  blitz::Array<double,2> magnitude_ = magnitude.bz<double,2>();
  blitz::Array<double,2> orientation_ = orientation.bz<double,2>();
  obj.forward_(input.bz<T,2>(), magnitude_, orientation_);
}

static void gradient_maps_call2(ip::GradientMaps& obj, bp::const_ndarray input,
    bp::ndarray magnitude, bp::ndarray orientation) 
{
  const ca::typeinfo& info = input.type();
  switch (info.dtype) {
    case ca::t_uint8: 
      return inner_gradient_maps_call2<uint8_t>(obj, input, magnitude, orientation);
    case ca::t_uint16:
      return inner_gradient_maps_call2<uint16_t>(obj, input, magnitude, orientation);
    case ca::t_float64: 
      return inner_gradient_maps_call2<double>(obj, input, magnitude, orientation);
    default: PYTHON_ERROR(TypeError, "GradientMaps does not support array with type '%s'", info.str().c_str());
  }
}

template <typename T> 
static void inner_hog_call1(ip::HOG<double>& obj, 
    bp::const_ndarray input, bp::ndarray output)
{
  blitz::Array<double,3> output_ = output.bz<double,3>();
  obj.forward(input.bz<T,2>(), output_);
}

static void hog_call1(ip::HOG<double>& obj, bp::const_ndarray input,
    bp::ndarray output) 
{
  const ca::typeinfo& info = input.type();
  switch (info.dtype) {
    //case ca::t_uint8: 
    //  return inner_hog_call1<uint8_t>(obj, input, output);
    //case ca::t_uint16:
    //  return inner_hog_call1<uint16_t>(obj, input, output);
    case ca::t_float64: 
      return inner_hog_call1<double>(obj, input, output);
    default: PYTHON_ERROR(TypeError, "HOG does not support array with type '%s'", info.str().c_str());
  }
}

template <typename T> 
static void inner_hog_call2(ip::HOG<double>& obj, 
    bp::const_ndarray input, bp::ndarray output)
{
  blitz::Array<double,3> output_ = output.bz<double,3>();
  obj.forward_(input.bz<T,2>(), output_);
}

static void hog_call2(ip::HOG<double>& obj, bp::const_ndarray input,
    bp::ndarray output) 
{
  const ca::typeinfo& info = input.type();
  switch (info.dtype) {
    //case ca::t_uint8: 
    //  return inner_hog_call2<uint8_t>(obj, input, output);
    //case ca::t_uint16:
    //  return inner_hog_call2<uint16_t>(obj, input, output);
    case ca::t_float64: 
      return inner_hog_call2<double>(obj, input, output);
    default: PYTHON_ERROR(TypeError, "HOG does not support array with type '%s'", info.str().c_str());
  }
}


void bind_ip_hog() {
  boost::python::enum_<bob::ip::GradientMagnitudeType>("GradientMagnitudeType")
    .value("Magnitude", bob::ip::Magnitude)
    .value("MagnitudeSquare", bob::ip::MagnitudeSquare)
    .value("SqrtMagnitude", bob::ip::SqrtMagnitude);
 
  boost::python::enum_<bob::ip::BlockNorm>("BlockNorm")
    .value("L2", bob::ip::L2)
    .value("L2Hys", bob::ip::L2Hys)
    .value("L1", bob::ip::L1)
    .value("L1sqrt", bob::ip::L1sqrt)
    .value("None", bob::ip::None);

  def("hog_compute_histogram_", &hog_compute_histogram_, 
    hog_compute_histogram__overloads((arg("mag"), arg("ori"), 
    arg("init_hist")=true, arg("full_orientation")=false), 
    "Computes an Histogram of Gradients for a given 'cell'. The inputs are \
    the gradient magnitudes and the orientations for each pixel of the cell. \
    This variant does NOT check the inputs."));
  def("hog_compute_histogram", &hog_compute_histogram, 
    hog_compute_histogram_overloads((arg("mag"), arg("ori"), 
    arg("init_hist")=true, arg("full_orientation")=false), 
    "Computes an Histogram of Gradients for a given 'cell'. The inputs are the \
    gradient magnitudes and the orientations for each pixel of the cell."));

  def("normalize_block_", &normalize_block_, 
    normalize_block__overloads((arg("hist"), arg("norm_hist"), 
    arg("block_norm")=ip::L2, arg("eps")=1e-10, arg("threshold")=0.2), 
    "normalizes a set of cells (Histogram of Gradients), and returns \
    the corresponding block descriptor. This variant does NOT check the inputs."));
  def("normalize_block", &normalize_block, 
    normalize_block_overloads((arg("hist"), arg("norm_hist"), 
    arg("block_norm")=ip::L2, arg("eps")=1e-10, arg("threshold")=0.2), 
    "normalizes a set of cells (Histogram of Gradients), and returns \
    the corresponding block descriptor."));

  class_<ip::GradientMaps, boost::shared_ptr<ip::GradientMaps> >("GradientMaps", 
      gradientmaps_doc, 
      init<const size_t, const size_t, optional<const ip::GradientMagnitudeType> >(
        (arg("height"), arg("width"), arg("mag_type")=ip::Magnitude),
        "Constructs a new Gradient maps extractor."))
    .add_property("height", &ip::GradientMaps::getHeight, &ip::GradientMaps::setHeight)
    .add_property("width", &ip::GradientMaps::getWidth, &ip::GradientMaps::setWidth)
    .add_property("magnitude_type", &ip::GradientMaps::getGradientMagnitudeType, 
      &ip::GradientMaps::setGradientMagnitudeType)
    .def("resize", &ip::GradientMaps::resize, (arg("height"), arg("width")))
    .def("__call__", &gradient_maps_call1, (arg("input"), arg("magnitude"), arg("orientation")),
      "Extract the gradient magnitude and orientation maps.")
    .def("forward", &gradient_maps_call1, (arg("input"), arg("magnitude"), arg("orientation")),
      "Extract the gradient magnitude and orientation maps.")
    .def("forward_", &gradient_maps_call2, (arg("input"), arg("magnitude"), arg("orientation")),
      "Extract the gradient magnitude and orientation maps. This variant does not check the inputs.");

  class_<ip::HOG<double>, boost::shared_ptr<ip::HOG<double> > >("HOG", 
      hog_doc, 
      init<const size_t, const size_t, 
        optional<const size_t, const bool, const size_t, const size_t, const size_t,
          const size_t, const size_t, const size_t, const size_t, const size_t> >(
        (arg("height"), arg("width"), arg("nb_bins")=8, arg("full_orientation")=false,
         arg("cell_y")=4, arg("cell_x")=4, arg("cell_ov_y")=0, arg("cell_ov_x")=0,
         arg("block_y")=4, arg("block_x")=4, arg("block_ov_y")=0, arg("block_ov_x")=0),
        "Constructs a new HOG extractor."))
    .add_property("height", &ip::HOG<double>::getHeight, &ip::HOG<double>::setHeight)
    .add_property("width", &ip::HOG<double>::getWidth, &ip::HOG<double>::setWidth)
    .add_property("magnitude_type", &ip::HOG<double>::getGradientMagnitudeType, 
      &ip::HOG<double>::setGradientMagnitudeType)
    .add_property("cell_dim", &ip::HOG<double>::getCellDim, &ip::HOG<double>::setCellDim)
    .add_property("full_orientation", &ip::HOG<double>::getFullOrientation, &ip::HOG<double>::setFullOrientation)
    .add_property("cell_y", &ip::HOG<double>::getCellHeight, &ip::HOG<double>::setCellHeight)
    .add_property("cell_x", &ip::HOG<double>::getCellWidth, &ip::HOG<double>::setCellWidth)
    .add_property("cell_ov_x", &ip::HOG<double>::getCellOverlapWidth, &ip::HOG<double>::setCellOverlapWidth)
    .add_property("cell_ov_y", &ip::HOG<double>::getCellOverlapHeight, &ip::HOG<double>::setCellOverlapHeight)
    .add_property("block_y", &ip::HOG<double>::getBlockHeight, &ip::HOG<double>::setBlockHeight)
    .add_property("block_x", &ip::HOG<double>::getBlockWidth, &ip::HOG<double>::setBlockWidth)
    .add_property("block_ov_x", &ip::HOG<double>::getBlockOverlapWidth, &ip::HOG<double>::setBlockOverlapWidth)
    .add_property("block_ov_y", &ip::HOG<double>::getBlockOverlapHeight, &ip::HOG<double>::setBlockOverlapHeight)
    .add_property("block_norm", &ip::HOG<double>::getBlockNorm, &ip::HOG<double>::setBlockNorm)
    .add_property("block_norm_eps", &ip::HOG<double>::getBlockNormEps, &ip::HOG<double>::setBlockNormEps)
    .add_property("block_norm_threshold", &ip::HOG<double>::getBlockNormThreshold, &ip::HOG<double>::setBlockNormThreshold)
    .def("resize", &ip::HOG<double>::resize, (arg("height"), arg("width")))
    .def("disable_block_normalization", &ip::HOG<double>::disableBlockNormalization)
    .def("get_output_shape", &ip::HOG<double>::getOutputShape)
    .def("__call__", &hog_call1, (arg("input"), arg("output")),
      "Extract the HOG descriptors.")
    .def("forward", &hog_call1, (arg("input"), arg("output")),
      "Extract the HOG descriptors.")
    .def("forward_", &hog_call2, (arg("input"), arg("output")),
      "Extract the HOG descriptors. This variant does not check the inputs.")
  ;
}
