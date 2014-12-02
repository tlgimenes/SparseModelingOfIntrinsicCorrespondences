%/*
% * =====================================================================================
% *       Filename:  iterate.m
% *    Description:  Iterates the algorithm 1 of the paper
% *        Created:  2014-11-28 15:04
% *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
% * =====================================================================================
% */

global C;
global W; 
global O;
global A;
global I;
global B;
global lambda;
global alpha;
global mu;

% algorithm 1
%////////////////////////////////////////////////////////////////////////////////////////

C_tmp = C;
C = ((I-(1/alpha)*A'*A)*C_tmp - (1/alpha)*A'*(O-B));
O = ((1-1/alpha)*O - (1/alpha)*(A*C_tmp-B));

C = max(abs(C) - (lambda / alpha)*W, 0) .* sign(C);
O = generateP2(O, mu, alpha);

% Sanity check of the norm
%norm(C-C_tmp);

%////////////////////////////////////////////////////////////////////////////////////////
