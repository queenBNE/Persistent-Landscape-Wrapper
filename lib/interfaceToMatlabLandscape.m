function [ landscape ] = interfaceToMatlabLandscape( points, ks )
%INTERFACE_TO_MATLAB_LANDSCAPE 
    landscape = {length(ks)};
    
    idx_start = 1;
    for i=1:length(ks)
       idx_end = idx_start+ks(i)-1;
       landscape{i} = points(1:2,idx_start:idx_end)';
       idx_start = idx_end+1;
    end
    
end

