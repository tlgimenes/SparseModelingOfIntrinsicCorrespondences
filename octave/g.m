%/*
% * =====================================================================================
% *       Filename:  g.m
% *    Description:  Evaluates the function gi of the segmentation for the model 2
% *        Created:  2014-12-02 01:39
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

%%
%   i: Index of the segmentation function in the segmentation file
%   seg: Vector with the segmentation file
function gi=g(i, segB)

%////////////////////////////////////////////////////////////////////////////////////////

% Indicatrice function in the segmentation
for j=1:length(segB)
    if segB(j) == (i-1)
        gi(j) = 1;
    else
        gi(j) = 0;
    end
end

%////////////////////////////////////////////////////////////////////////////////////////

end
