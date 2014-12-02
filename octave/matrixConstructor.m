%/*
% * =====================================================================================
% *       Filename:  matrixConstructor.m
% *    Description:  Creates matrix after a laplacian file matrix. 
%             TODO:  Get rid of this file. Find a new way to evaluate the laplacian 
%   operator
% *        Created:  2014-11-25 21:56
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

function L=matrixConstructor(in_file)

%////////////////////////////////////////////////////////////////////////////////////////

data=load(in_file); % reads matrix

% allocates sparse matrix
m=max(data); m(3) = []; 
n=max(m)+1;
L=sparse(n,n);

for k=1:length(data)
    i = data(k,1)+1;
    j = data(k,2)+1;
    val = data(k,3);
    L(i,j) = L(i,j) + val;
    L(j,i) = L(j,i) + val;
    L(i,i) = L(i,i) - val;
    L(j,j) = L(j,j) - val;
end 

%////////////////////////////////////////////////////////////////////////////////////////

end
