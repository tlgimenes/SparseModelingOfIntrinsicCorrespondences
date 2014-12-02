%/*
% * =====================================================================================
% *       Filename:  f.m
% *    Description:  Evaluates the function fi of the segmentation for the model 1
% *        Created:  2014-12-02 01:06
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

%%
%   i: Index of the segmentation function in the segmentation file
%   seg: Vector with the segmentation file
function fi=f(i, seg)

%////////////////////////////////////////////////////////////////////////////////////////

% Indicatrice function in the segmentation
for j=1:length(seg)
    if seg(j) == (i-1)
        fi(j) = 1;
    else
        fi(j) = 0;
    end
end

%////////////////////////////////////////////////////////////////////////////////////////

end
