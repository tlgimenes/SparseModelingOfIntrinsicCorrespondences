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

printf('Decomposing the Laplacian of cat0...\n');
[V0,D0,L0]=eigenDecomposition('matcat0.txt', k, 'eigencat0.txt'); % Decompose the Laplacian operator in its eigenvectors
printf('done\n');
printf('Decomposing the Laplacian of cat1...\n');
[V1,D1,L1]=eigenDecomposition('matcat1.txt', k, 'eigencat1.txt'); % Decompose the Laplacian operator in its eigenvectors
printf('done\n');

printf('Loading segmentations...\n');
segA = load('cat0_wks_5_pers_8_seg.txt'); % loads the segmentations
segB = load('cat1_wks_5_pers_8_seg.txt'); % loads the segmentations
printf('done\n');

printf('generating matrix A and B...\n')
A=genA(V0, segA); % generates matrix A
B=genB(V1, segB); % generates matrix B
printf('done\n');

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
alpha_max=max(max(D))

