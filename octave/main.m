%/*
% * =====================================================================================
% *       Filename:  main.m
%
% *    Description:  Instantiates necessary variables. Please, read the message bellow 
% to understand how to use this algorithm:
%
%      -> This file was created with the purpose of being like a main function of a C file,
%   so, it instantiates needed variables like the size of vector basis, alpha, lambda and
%   mu. 
%      -> This file also decomposes the laplacian in the eigenvectors basis, sets the 
%   segmentation variables, and than generates the A,B matrices 
%      -> For solving the algorithm open MATLAB/octave and type "solve". At each call of solve 
%   you will iterate once the algorithm. Stop iterating when convergence is done
%      -> For finding the correspondence call the function "correspond" with the needed 
%   parameters and be happy !!!
%
% *        Created:  2014-11-19 18:51
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

global C;
global W; 
global O;
global A;
global I;
global B;
global lambda;
global alpha;
global mu;
global segA;
global segB;

%////////////////////////////////////////////////////////////////////////////////////////

n=10000; % maximal number of iterations of the solver
k=20;    % number of eigenvectors in the base

% Paths for shapes
shape_path0 = '../models/TOSCA/shapes/cat0.off';
shape_path1 = '../models/TOSCA/shapes/cat1.off';

% Paths for segmentations
segmentation_path0 = '../models/TOSCA/segmentations/cat0_wks_5_pers_8_seg.txt';
segmentation_path1 = '../models/TOSCA/segmentations/cat1_wks_5_pers_8_seg.txt';

% Reads the off files
printf('Reading off files...');
[faces0, vertices0]=read_off(shape_path0);
[faces1, vertices1]=read_off(shape_path1);
printf('done\n');

% Calculating the laplacian matrix
L0=laplacian(vertices0, faces0);
L1=laplacian(vertices0, faces0);

printf('Decomposing the Laplacian of shape 0...');
[V0, D0] = eigenDecomposition(L0,k);
printf('done\n');
printf('Decomposing the Laplacian of shape 1...');
[V1,D1]=eigenDecomposition(L1, k); % Decompose the Laplacian operator in its eigenvectors
printf('done\n');

printf('Loading segmentations...');
segA = load(segmentation_path0); % loads the segmentations
segB = load(segmentation_path1); % loads the segmentations
printf('done\n');

printf('generating matrix A and B...')
A=genA(V0, segA); % generates matrix A
B=genB(V1, segB); % generates matrix B
printf('done\n');

printf('Now run <solve> and <correspond> for solving the problem and finding the correspondence\n');
printf('Have a nice day !\n');

% Sets matrices
C = zeros(k);
W = 1*ones(k) - 0.999*eye(k);
I = eye(k);
O=B;

lambda = 100;
alpha  = 8000;
mu     = 100;
epsilon = 0.1;

% Evaluates the maximal value of alpha
[V,D]=eig([[A'*A A']; [eye(7) A]]);
alpha_max=max(max(D));

