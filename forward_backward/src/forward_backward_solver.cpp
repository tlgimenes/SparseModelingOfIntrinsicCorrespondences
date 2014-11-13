/*
 * =====================================================================================
 *       Filename:  forward_backward_solver.cpp
 *    Description:  File for solving the forward_backward problem
 *        Created:  2014-11-13 00:02
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "forward_backward_solver.hpp"

////////////////////////////////////////////////////////////////////////////////////////

ForwardBackwardSolver::ForwardBackwardSolver(float lambda, float mu) :
    _lambda(lambda), _mu(mu)
{
    /* Nothing to do here */
}

////////////////////////////////////////////////////////////////////////////////////////

void ForwardBackwardSolver::min(std::shared_ptr<Eigen::MatrixXd>& B, 
        std::shared_ptr<Eigen::MatrixXd>& A, std::shared_ptr<Eigen::MatrixXd>& C, 
        std::shared_ptr<Eigen::MatrixXd>& O)
{
    /* Set parameters to internal variables */
    _B = B; _A = A; _C = C; _O = O;

    /* FINISH HERE ! */

    return;
}

////////////////////////////////////////////////////////////////////////////////////////
