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

#define DEFAULT_MODEL_PATH1 "../models/0001.affine.1.off"
#define DEFAULT_MODEL_PATH2 "../models/0001.null.0.off"

////////////////////////////////////////////////////////////////////////////////////////

/**
 * Global variables 
 * */
std::shared_ptr<Eigen::MatrixXd> Xv, Yv;
std::shared_ptr<Eigen::MatrixXi> Xf, Yf;
std::shared_ptr<Eigen::MatrixXd> Xc, Yc;

float lambda = 1;
float mu = 1;

////////////////////////////////////////////////////////////////////////////////////////

void read_input(int argc, const char** argv);
bool key_down_cb(igl::Viewer& viewer, unsigned char key, int modifier);
void set_model_1(igl::Viewer& viewer);
void set_model_2(igl::Viewer& viewer);

////////////////////////////////////////////////////////////////////////////////////////

/* ======= Function ==================================================
 *   Name: main
 *   Description: main entry Function
 * =================================================================== 
 */
int main(int argc, const char **argv)
{
    // Allocates global shared_ptr 
    Xv = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd());
    Xf = std::make_shared<Eigen::MatrixXi>(Eigen::MatrixXi());
    Xc = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd());
    Yv = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd());
    Yf = std::make_shared<Eigen::MatrixXi>(Eigen::MatrixXi());
    Yc = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd());

    // Load a mesh in OFF format
    read_input(argc, argv);

    // Instantiates the solvers
    ForwardBackwardSolver fbs(lambda, mu);
    LinearAssignementSolver las;

    // f : X -> R
    // g : Y -> R
    ModelToReal f(Xv,Xf), g(Yv,Yf);

    // Plot the mesh
    igl::Viewer viewer;
    set_model_1(viewer);

    // Set callbacks
    viewer.callback_key_down = &key_down_cb;

    // Launch the viewer
    viewer.launch();
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

void set_model_1(igl::Viewer& viewer)
{
    viewer.data.clear();
    viewer.data.set_mesh(*Xv, *Xf);
    viewer.core.align_camera_center(*Xv, *Xf);
 
    // Use the z coordinate as a scalar field over the surface
    Eigen::VectorXd Z = Xv->col(2);

    // Compute per-vertex colors
    igl::jet(Z,true,*Xc);

    // Add per-vertex colors
    viewer.data.set_colors(*Xc);
}

////////////////////////////////////////////////////////////////////////////////////////

void set_model_2(igl::Viewer& viewer)
{
    viewer.data.clear();
    viewer.data.set_mesh(*Yv, *Yf);
    viewer.core.align_camera_center(*Yv, *Yf);
 
    // Use the z coordinate as a scalar field over the surface
    Eigen::VectorXd Z = Yv->col(2);

    // Compute per-vertex colors
    igl::jet(Z,true,*Yc);

    // Add per-vertex colors
    viewer.data.set_colors(*Yc);
}

////////////////////////////////////////////////////////////////////////////////////////

bool key_down_cb(igl::Viewer& viewer, unsigned char key, int modifier)
{
    switch(key)
    {
        case '1':
            set_model_1(viewer);
            break;
        case '2':
            set_model_2(viewer);
            break;
        case 'q': case 'Q':
            exit(EXIT_SUCCESS);
        default:
            std::cout << "please, press 1,2 or q(quit)" << std::endl;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////

void read_input(int argc, const char** argv)
{
    std::string path1 = DEFAULT_MODEL_PATH1;
    std::string path2 = DEFAULT_MODEL_PATH2;

    if(argc > 1) 
    {
        std::ifstream file(argv[1], std::ios_base::in);
        if(file.is_open()) {
            path1 = argv[1];
        }
    }
    if(argc > 2)
    {
        std::ifstream file(argv[2], std::ios_base::in);
        if(file.is_open()) {
            path2 = argv[2];
        }
    }

    igl::readOFF(path1, *Xv, *Xf);
    igl::readOFF(path2, *Yv, *Yf);
}
