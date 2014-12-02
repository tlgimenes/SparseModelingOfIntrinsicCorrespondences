%/*
% * =====================================================================================
% *       Filename:  hungarian.m
% *    Description:  Maximisation of the second problem of the paper 
% *        Created:  2014-11-29 00:10
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

%////////////////////////////////////////////////////////////////////////////////////////

global A;
global B;
global C;

%////////////////////////////////////////////////////////////////////////////////////////

% hungarian algorithm
[assignment, cost]=munkres(-(A*C+O)*B');

% shows assignment
assignment

% Evaluates PI * B
for i=1:length(assignment)
    B_tmp(i, :) = B(assignment(i), :);
end

% Assigns B = PI * B
B = B_tmp;

%////////////////////////////////////////////////////////////////////////////////////////


