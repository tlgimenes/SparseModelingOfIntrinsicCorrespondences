/*
 * =====================================================================================
 *       Filename:  main.cpp
 *    Description:  Main file 
 *        Created:  2014-11-12 23:21 
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include <igl/readOFF.h>
#include <igl/viewer/Viewer.h>
#include <igl/jet.h>

#include <fstream>
#include <string>
#include <memory>

#include "forward_backward_solver.hpp"
#include "linear_assignement_solver.hpp"
#include "model_to_real.hpp"

////////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_MODEL_PATH "../models/0001.affine.1.off"

////////////////////////////////////////////////////////////////////////////////////////

/**
 * Global variables 
 * */
std::shared_ptr<Eigen::MatrixXd> V;
std::shared_ptr<Eigen::MatrixXi> F;
std::shared_ptr<Eigen::MatrixXd> C;

float lambda = 1;
float mu = 1;

////////////////////////////////////////////////////////////////////////////////////////

void read_input(int argc, const char** argv);

////////////////////////////////////////////////////////////////////////////////////////

/* ======= Function ==================================================
 *   Name: main
 *   Description: main entry Function
 * =================================================================== 
 */
int main(int argc, const char **argv)
{
    // Allocates global shared_ptr 
    V = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd());
    F = std::make_shared<Eigen::MatrixXi>(Eigen::MatrixXi());
    C = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd());

    // Load a mesh in OFF format
    read_input(argc, argv);

    // Instantiates the solvers
    ForwardBackwardSolver fbs(lambda, mu);
    LinearAssignementSolver las;

    // f : X -> R
    // g : Y -> R
    ModelToReal f(V,F),g(V,F);

    // Plot the mesh
    igl::Viewer viewer;
    viewer.data.set_mesh(*V, *F);

    // Use the z coordinate as a scalar field over the surface
    Eigen::VectorXd Z = V->col(2);

    // Compute per-vertex colors
    igl::jet(Z,true,*C);

    // Add per-vertex colors
    viewer.data.set_colors(*C);

    // Launch the viewer
    viewer.launch();
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

void read_input(int argc, const char** argv)
{
    std::string path = DEFAULT_MODEL_PATH;

    if(argc > 1) 
    {
        std::ifstream file(argv[1], std::ios_base::in);
        if(file.is_open()) {
            path = argv[1];
        }
    }

    igl::readOFF(path, *V, *F);
}
