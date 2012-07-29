/**
 * @file visioner/visioner/model/trainers/lutproblems/lut_problem_var.h
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

#ifndef BOB_VISIONER_LUT_PROBLEM_VAR_H
#define BOB_VISIONER_LUT_PROBLEM_VAR_H

#include "visioner/model/trainers/lutproblems/lut_problem_ept.h" 

namespace bob { namespace visioner {

  ////////////////////////////////////////////////////////////////////////////////
  // LUTProblemVAR: 
  //      minimizes the cumulated expectation loss
  //      regularized with the loss variance.
  ////////////////////////////////////////////////////////////////////////////////

  class LUTProblemVAR : public LUTProblemEPT
  {
    public:

      // Constructor
      LUTProblemVAR(const DataSet& data, const param_t& param, scalar_t lambda);

      // Destructor
      virtual ~LUTProblemVAR() {} 

    protected:

      // Update loss values and derivatives (for some particular scores)
      virtual void update_loss_deriv(const scalar_mat_t& scores);
      virtual void update_loss(const scalar_mat_t& scores);

    protected:

      // Attributes
      scalar_t                        m_lambda;       // Regularization factor
  };	

}}

#endif // BOB_VISIONER_LUT_PROBLEM_VAR_H