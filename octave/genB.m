%/*
% * =====================================================================================
% *       Filename:  genB.m
% *    Description:  Generates matrix B
% *        Created:  2014-12-02 01:37
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

%%
%   V: Eigen vectors of the shape 2
%   segA: Segmentation of the shape 2
function mat=genB(V, segB)

%////////////////////////////////////////////////////////////////////////////////////////

n_reg = max(segB) + 1;  % number of regions

n_eigs = size(V)(2); % number of eigen values

% calculates all functions fi
for i=1:n_reg
    gi(:,i)=g(i, segB);
end

% scalar product between fi and the eigenvectors to find the coefficients
for i=1:n_reg
    for j=1:n_eigs
        mat(i,j) = gi(:,i)'*V(:,j);
    end
end


%////////////////////////////////////////////////////////////////////////////////////////

end
