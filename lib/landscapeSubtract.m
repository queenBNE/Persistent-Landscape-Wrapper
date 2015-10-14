function [ landscape ] = landscapeSubtract( l1, l2 )
%ADDLANDSCAPES Returns the difference l1-l2 of landscape l1 and l2, 
%A landscape is represented as a list of matrices with 2
%columns. Each matrix, landscape{k} respresents the non-differentiable
%points of the piece-wise linear function \lambda_k. 
    [points1, ks1] = matlabToInterfaceLandscape(l1);
    [points2, ks2] = matlabToInterfaceLandscape(l2);
    [points, ks] = landscapeSubtract_(points1, ks1, points2, ks2);
    
    landscape = interfaceToMatlabLandscape(points, ks);
end

