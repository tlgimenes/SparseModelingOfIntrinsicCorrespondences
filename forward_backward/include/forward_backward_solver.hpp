/*
 * =====================================================================================
 *       Filename:  forward_backward_solver.hpp
 *    Description:  Class for solving the forward backward problem
 *        Created:  2014-11-13 00:03
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef FORWARD_BACKWARD_SOLVER_HPP
#define FORWARD_BACKWARD_SOLVER_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <Eigen/Dense>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////

class ForwardBackwardSolver
{
    private:
        std::shared_ptr<Eigen::MatrixXd> _W;
        std::shared_ptr<Eigen::MatrixXd> _B, _A, _C, _O;

        float _lambda, _mu;

    public:
        ForwardBackwardSolver(float lambda = 1, float mu = 1);

        void min(std::shared_ptr<Eigen::MatrixXd>& B, std::shared_ptr<Eigen::MatrixXd>& A,
                std::shared_ptr<Eigen::MatrixXd>& C, std::shared_ptr<Eigen::MatrixXd>& O);
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !FORWARD_BACKWARD_SOLVER_HPP */

////////////////////////////////////////////////////////////////////////////////////////

