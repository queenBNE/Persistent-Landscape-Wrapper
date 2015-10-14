function [ integralValue ] = landscapeIntegral(landscape)
%COMPUTE_INTEGRAL_OF_LANDSCAPE Returns the integral of a landscape. 
%%A landscape is represented as a list of matrices with 2
%columns. Each matrix, landscape{k} respresents the non-differentiable
%points of the piece-wise linear function \lambda_k.  
    [points,ks] = matlabToInterfaceLandscape(landscape);
    integralValue = landscapeIntegral_(points,ks);
end

