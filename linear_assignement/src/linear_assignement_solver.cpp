/*
 * =====================================================================================
 *       Filename:  linear_assignement_solver.cpp
 *    Description:  Class for solving the linear problem
 *        Created:  2014-11-13 00:04
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "linear_assignement_solver.hpp"

////////////////////////////////////////////////////////////////////////////////////////

LinearAssignementSolver::LinearAssignementSolver()
{
    /* Nothing to do here */
}

////////////////////////////////////////////////////////////////////////////////////////

void LinearAssignementSolver::max(std::shared_ptr<Eigen::MatrixXd>& E,
        std::shared_ptr<Eigen::MatrixXd>& PI)
{
    _E = E;
    _PI = PI;

    /* FINISH HERE ! */

    return;
}

///////////////////////////////////////////////////////////////////////////////////////
