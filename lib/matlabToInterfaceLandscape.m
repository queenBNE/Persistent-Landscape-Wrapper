function [ points,ks ] = matlabToInterfaceLandscape( landscape )
%MATLAB_TO_INTERFACE_LANDSCAPE
    % Vector of zeros, one for each lambda_k, fill with the number of 
    % points in each lambda_k
    k_max = length(landscape);
    ks = zeros(1,k_max);
    for i=1:length(landscape)
        ks(i) = length(landscape{i});
    end  
    
    % Matrix to contain all points for all lambda k's  
    points = zeros(2, sum(ks));
    idx_s = 1;
    
    
    for i=1:k_max
        points_k = landscape{i}';
        idx_t=idx_s+ ks(i) - 1;
        if ks(i) > 1
            points(1,idx_s:idx_t) = points_k(1,:);
            points(2,idx_s:idx_t) = points_k(2,:);
        else 
            points(1,idx_s) = 0;
            points(2,idx_s) = 0;
        end
        idx_s = idx_t+1;
    end  
    
end

