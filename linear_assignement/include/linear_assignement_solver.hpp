/*
 * =====================================================================================
 *       Filename:  linear_assignement_solver.hpp
 *    Description:  Class for solving the linear problem
 *        Created:  2014-11-13 00:04
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef LINEAR_ASSIGNEMENT_SOLVER_HPP
#define LINEAR_ASSIGNEMENT_SOLVER_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <Eigen/Dense>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////

class LinearAssignementSolver
{
    private:
        std::shared_ptr<Eigen::MatrixXd> _E;
        std::shared_ptr<Eigen::MatrixXd> _PI;

    public:
        LinearAssignementSolver();

        void max(std::shared_ptr<Eigen::MatrixXd>& E, std::shared_ptr<Eigen::MatrixXd>& PI);
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !LINEAR_ASSIGNEMENT_SOLVER_HPP */

////////////////////////////////////////////////////////////////////////////////////////

