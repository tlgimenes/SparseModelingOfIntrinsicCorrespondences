/*
 * =====================================================================================
 *       Filename:  model_to_real.hpp
 *    Description:  Transforms the model to real valued values
 *        Created:  2014-11-13 00:06
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MODEL_TO_REAL_HPP
#define MODEL_TO_REAL_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <Eigen/Dense>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////

class ModelToReal
{
    private:
        std::shared_ptr<Eigen::MatrixXd> _coeffs, _base;

    public:
        /**
         * Constructor: 
         * @params V : Vertices of the model
         * @params F : Faces of the model 
         * */
        ModelToReal(std::shared_ptr<Eigen::MatrixXd> &V, std::shared_ptr<Eigen::MatrixXi> &F);

        /**
         * Gets  
         * */
        std::shared_ptr<Eigen::MatrixXd>& coeffs();
        std::shared_ptr<Eigen::MatrixXd>& base();
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MODEL_TO_REAL_HPP */

////////////////////////////////////////////////////////////////////////////////////////
