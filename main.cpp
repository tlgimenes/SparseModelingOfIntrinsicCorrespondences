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

////////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_MODEL_PATH "../models/0001.affine.1.off"

////////////////////////////////////////////////////////////////////////////////////////

Eigen::MatrixXd V;
Eigen::MatrixXi F;
Eigen::MatrixXd C;

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
    // Load a mesh in OFF format
    read_input(argc, argv);

    // Plot the mesh
    igl::Viewer viewer;
    viewer.data.set_mesh(V, F);

    // Use the z coordinate as a scalar field over the surface
    Eigen::VectorXd Z = V.col(2);

    // Compute per-vertex colors
    igl::jet(Z,true,C);

    // Add per-vertex colors
    viewer.data.set_colors(C);

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

    igl::readOFF(path, V, F);
}
