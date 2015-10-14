function [ absValue ] = landscapeAbsoluteValue(landscape)
%UNTITLED3 Returns a landscape corresponding to the absolute value of the
%given landscape. 
%A landscape is represented as a list of matrices with 2
%columns. Each matrix, landscape{k} respresents the non-differentiable
%points of the piece-wise linear function \lambda_k. 
%   
    [points, ks] = matlabToInterfaceLandscape(landscape);
    [points_abs, ks_abs] = landscapeAbsoluteValue_(points,ks);
    absValue = interfaceToMatlabLandscape(points_abs,ks_abs);
end


