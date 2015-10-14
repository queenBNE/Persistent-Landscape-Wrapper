function [ landscape ] = landscapeAverage( landscapes )
%ADDLANDSCAPES Returns the sum of landscape l1 and l2. 
%A landscape is represented as a list of matrices with 2
%columns. Each matrix, landscape{k} respresents the non-differentiable
%points of the piece-wise linear function \lambda_k. 
    
    args = cell(1, 2*length(landscapes));  
    for i=1:length(landscapes)
       [points, ks] = matlabToInterfaceLandscape(landscapes{i});
       args{i*2-1}=points;
       args{i*2}=ks;
    end
    [points, ks] = landscapeAverage_(args{:});
    
    landscape = interfaceToMatlabLandscape(points, ks);
end

