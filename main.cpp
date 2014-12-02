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

#define DEFAULT_MODEL_PATH1 "../../Project/code/shape_segmentation/TOSCA/shapes/cat0.off"
#define DEFAULT_MODEL_PATH2 "../../Project/code/shape_segmentation/TOSCA/shapes/cat1.off"

////////////////////////////////////////////////////////////////////////////////////////

/**
 * Global variables 
 * */
std::shared_ptr<Eigen::MatrixXd> Xv, Yv;
std::shared_ptr<Eigen::MatrixXi> Xf, Yf;
std::shared_ptr<Eigen::MatrixXd> Xc, Yc;

/**
 * Ids of the correlated points in the two shapes
 * */
int id1 = 0;
int id2 = 0;

/**
 * Future work
 * */
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

int getIndex(const Eigen::Vector3d& point, const std::shared_ptr<Eigen::MatrixXd> model)
{
    float curr, dist;
    int i=0, id = 0;
    Eigen::Vector3d d;

    d = model->row(i);
    d -= point;
    dist = d.squaredNorm();
    for(i=1; i < model->rows(); i++)
    {
        d = model->row(i);
        d -= point;
        curr = d.squaredNorm();
        if( curr < dist ) {
            id = i;
            dist = curr;
        }
    }

    return id;
}

////////////////////////////////////////////////////////////////////////////////////////

void set_model_1(igl::Viewer& viewer)
{
    viewer.data.clear();
    viewer.data.set_mesh(*Xv, *Xf);
    viewer.core.align_camera_center(*Xv, *Xf);
 
    // Use the z coordinate as a scalar field over the surface
    Eigen::VectorXd Z = Eigen::VectorXd::Zero(Xv->rows());
    Eigen::Vector3d point;

    for(int i=0; i < Xv->rows(); i++) {
        point = Xv->row(i) - Xv->row(id1);
        Z(i) = point.norm();
    }
    Z(id1) = Z.maxCoeff();

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
    Eigen::VectorXd Z = Eigen::VectorXd::Zero(Yv->rows());
    Eigen::Vector3d point;

    for(int i=0; i < Yv->rows(); i++) {
        point = Yv->row(i) - Yv->row(id2);
        Z(i) = point.norm();
    }
    Z(id2) = Z.maxCoeff();
    
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
    bool is_num = true;

    for(int i=1; i < argc; i++)
    {
        if(strcmp(argv[i], "-f1") == 0) {
            i++;
            std::ifstream file(argv[i], std::ios_base::in);
            if(file.is_open()) {
                path1 = argv[i];
            }
        }
        else if(strcmp(argv[i], "-f2") == 0) {
            i++;
            std::ifstream file(argv[i], std::ios_base::in);
            if(file.is_open()) {
                path2 = argv[i];
                is_num = false;
            }
        }
        else if(strcmp(argv[i], "-n1") == 0) {
            i++;
            id1 = std::stoi(argv[i]);
        }
        else if(strcmp(argv[i], "-n2") == 0) {
            i++;
            id2 = std::stoi(argv[i]);
        }
        else if(strcmp(argv[i], "-h") == 0) {
            std::cout << "-f1 for path 1" << std::endl \
                      << "-f2 for path 2" << std::endl \
                      << "-n1 for index 1" << std::endl \
                      << "-n2 for index 2" << std::endl;
        }
    }

    igl::readOFF(path1, *Xv, *Xf);
    igl::readOFF(path2, *Yv, *Yf);
}

////////////////////////////////////////////////////////////////////////////////////////
