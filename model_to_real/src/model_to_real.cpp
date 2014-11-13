/*
 * =====================================================================================
 *       Filename:  model_to_real.cpp
 *    Description:  Transforms the model to real valued values
 *        Created:  2014-11-13 00:05
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "model_to_real.hpp"

////////////////////////////////////////////////////////////////////////////////////////

ModelToReal::ModelToReal(std::shared_ptr<Eigen::MatrixXd> &V, 
        std::shared_ptr<Eigen::MatrixXi> &F)
{
    /* FINISH HERE ! */
}

////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Eigen::MatrixXd>& ModelToReal::coeffs()
{
    return _coeffs;
}

////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Eigen::MatrixXd>& ModelToReal::base()
{
    return _base;
}

////////////////////////////////////////////////////////////////////////////////////////
