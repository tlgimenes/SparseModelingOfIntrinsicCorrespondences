%/*
% * =====================================================================================
% *       Filename:  A.m
% *    Description:  Generates matrix A
% *        Created:  2014-12-02 01:11
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

%%
%   V: Eigen vectors of the shape 1
%   segA: Segmentation of the shape 1
function mat=genA(V, segA)

%////////////////////////////////////////////////////////////////////////////////////////

n_reg = max(segA) + 1;  % number of regions

n_eigs = size(V)(2); % number of eigen values

% calculates all functions fi
for i=1:n_reg
    fi(:,i)=f(i, segA);
end

% scalar product between fi and the eigenvectors to find the coefficients
for i=1:n_reg
    for j=1:n_eigs
        mat(i,j) = fi(:,i)'*V(:,j);
    end
end

%////////////////////////////////////////////////////////////////////////////////////////

end
