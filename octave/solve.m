%/*
% * =====================================================================================
% *       Filename:  solve.m
% *    Description:  Makes one iteration of the algorithm presented in the paper
% *        Created:  2014-11-29 00:35
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

global C;
global O;
global B;

%////////////////////////////////////////////////////////////////////////////////////////

% runs the hungarian algorithm
hungarian

% Initialization of the algorithm
C=zeros(k);
O=B;

% iterates n times the algorithm for finding C
for i=1:n
    iterate
end

% Sanity check in the norms
norm(A*C-B+O)
norm(C-C_tmp)

%////////////////////////////////////////////////////////////////////////////////////////

