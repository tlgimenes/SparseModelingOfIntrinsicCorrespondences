%/*
% * =====================================================================================
% *       Filename:  eigenDecomposition.m
% *    Description:  Decomposes the Laplacian operator in the file in_file in a base 
% of k eigen values/eigen vectors
% *        Created:  2014-11-25 16:45
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

%%
%   in_file: input file with the sparse laplacian operator
%   k: number of eigen vectors to decompose the Laplacian
%   out_file: ouput file where to save the eigen vectors
%
%   V: eigen vectors
%   D: eigen values
%   L: Laplacian (debug purposes)
function [V,D,L]=eigenDecomposition(in_file, k, out_file)

%////////////////////////////////////////////////////////////////////////////////////////

% builds Laplacian from file 
L = matrixConstructor(in_file);

% Eigen values decomposition
[V,D]=eigs(L, k, -1e-10);

% write to file
dlmwrite(out_file, V, ' ');

end
