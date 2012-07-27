/**
 * @file visioner/visioner/cv/cv_draw.h
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
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

#ifndef BOB_VISIONER_CV_DRAW_H
#define BOB_VISIONER_CV_DRAW_H

#include "visioner/cv/cv_detector.h"

namespace bob { namespace visioner {

  /////////////////////////////////////////////////////////////////////////////////////////
  // Utility drawing functions:
  //      - ground truth objects
  //      - detections
  //      - keypoint localizations
  //      - predicted labels
  /////////////////////////////////////////////////////////////////////////////////////////

  QImage draw_gt(const ipscale_t& ipscale);
  void draw_detection(QImage& qimage, const detection_t& det, const param_t& param, bool label);
  void draw_detections(QImage& qimage, const detections_t& dets, const param_t& param, const bools_t& labels);
  void draw_points(QImage& qimage, const points_t& points);
  void draw_label(QImage& qimage, const detection_t& detection, const param_t& param, 
      index_t gt_label, index_t dt_label);

}}

#endif // BOB_VISIONER_CV_DRAW_H
