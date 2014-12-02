%/*
% * =====================================================================================
% *       Filename:  correspond.m
% *    Description:  Finds the correspondence between two index in the off file
% *        Created:  2014-12-02 02:05
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

%%
%   i: index in object 1
%   k: number of vectors in the base 
%   segA: Segmentation of model 1
%   V0: Eigen vectors of the laplacian operator in model 1
%   V1: Eigen vectors of the laplacian operator in model 2
function id=correspond(i, k, segA, V0, V1, C)

%////////////////////////////////////////////////////////////////////////////////////////

ind=indic(i, segA); %indicatrice function for a given point

% coefficients of this indicatrice function in base V0
for i=1:k
    a(i) = ind'*V0(:,i);
end

% coefficients in the base V1
b = C'*a';

% Function g
g = V1 * b;

% g must be an indicatrice function, so get the max
[V,I]=max(g);

% the index is the corresponding found
id = I;

%////////////////////////////////////////////////////////////////////////////////////////

end
