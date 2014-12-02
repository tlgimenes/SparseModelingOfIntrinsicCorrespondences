% This is the implementation of the Wave Kernel Signature described
% in the paper:
% 
%    The Wave Kernel Signature: A Quantum Mechanical Approach To Shape Analysis 
%    M. Aubry, U. Schlickewei, D. Cremers
%    In IEEE International Conference on Computer Vision (ICCV) - Workshop on 
%    Dynamic Shape Capture and Analysis (4DMOD), 2011
% 
% Please refer to the publication above if you use this software. 
% 
% This work is licensed under a Creative Commons
% Attribution-NonCommercial 3.0 Unported License  
% ( http://creativecommons.org/licenses/by-nc/3.0/ )
% 
% The WKS is patented and violation to the license agreement would
% imply a patent infringement.
%
% THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY EXPRESSED OR IMPLIED WARRANTIES
% OF ANY KIND, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
% OUT OF OR IN CONNECTION WITH THIS SOFTWARE OR THE USE OR OTHER DEALINGS IN
% THIS SOFTWARE.


function L = laplacian(vertices,faces)

% function [WKS,E,PHI] = compute_WKS(vertices,faces) compute
%   the Wave Kernel Signature of triangle mesh given by
%   [vertices,faces]
%   
%   INPUT:
%   vertices is (number of vertices) x 3 matrix
%   faces is a (number of faces) x 3 matrix
%   
%   OUTPUT:
%   L is the cotan Laplace-Beltrami matrix
%
%   The main parameter to adjust depending on your task is wks_variance


%% parameters

n_eigenvalues=300; % number of eigenvalues used for computations
% depending on the application, you can use less than 300
N = 100; % number of evaluations of WKS
wks_variance = 6; % variance of the WKS gaussian (wih respect to the 
% difference of the two first eigenvalues). For easy or precision tasks 
% (eg. matching with only isometric deformations) you can take it smaller



%% basic quantities

num_vertices = size(vertices,1);
num_faces = size(faces,1);



%% detect boundary vertices

% Calculate the (directed) adjacency matrix. adjacency_matrix(m,n) = 1 if the oriented
% boundary of a triangle contains the directed edge from vertex m to vertex
% n, and 0 otherwise. This matrix is not quite symmetric due to boundary edges.
adjacency_matrix = sparse([faces(:,1); faces(:,2); faces(:,3)], ...
                         [faces(:,2); faces(:,3); faces(:,1)], ...
    	                 ones(3 * num_faces, 1), ...
                         num_vertices, num_vertices, 3 * num_faces);
if any(any(adjacency_matrix > 1))
    error('Triangles must be oriented consistently.')
end
clear adjacency_matrix;


%% compute cotan LB matrix

fprintf('Computing Laplace-Beltrami operator...');

% first compute inner face angles and squared edge lengthes
pp = zeros(num_faces,3);
qq = zeros(num_faces,3);
angles = 0*faces;
squared_edge_length = 0*faces;

for i=1:3
    i1 = mod(i-1,3)+1;
    i2 = mod(i  ,3)+1;
    i3 = mod(i+1,3)+1;
    pp = vertices(faces(:,i2),:) - vertices(faces(:,i1),:);
    qq = vertices(faces(:,i3),:) - vertices(faces(:,i1),:);
    % normalize the vectors
    pp = pp ./ repmat( max(sqrt(sum(pp.^2,2)),eps), [1 3] );
    qq = qq ./ repmat( max(sqrt(sum(qq.^2,2)),eps), [1 3] );
    % compute angles
    angles(:,i1) = acos(sum(pp.*qq,2));
    squared_edge_length(:,i1) = sum((vertices(faces(:,i2)) - vertices(faces(:,i3))).^2,2);
end
clear pp qq;

%then compute L
L = sparse(num_vertices,num_vertices);
for i=1:3
    i1 = mod(i-1,3)+1;
    i2 = mod(i  ,3)+1;
    i3 = mod(i+1,3)+1;
    L = L + sparse(faces(:,i1),faces(:,i2),-cot(angles(:,i3)),...
        num_vertices,num_vertices,num_faces);       
end

L = 1/2 * (L + L');
L = sparse(1:num_vertices,1:num_vertices,-sum(L,2),num_vertices,num_vertices,...
    num_vertices) + L;

fprintf('done. \n');

