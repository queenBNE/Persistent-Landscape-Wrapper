function [ d ] = landscapeDistance( l1, l2, n)
%LANDSCAPE_DISTANCE Computes the distance between the landscapes of two barcodes
%using the L^n norm. 
%barcode1 and barcode2 should be a 2xN1 and 2xN2 matrix of doubles with
%each row representing an interval (birth,death). 
    [points1, ks1] = matlabToInterfaceLandscape(l1);
    [points2, ks2] = matlabToInterfaceLandscape(l2);    
    d = landscapeDistance_(points1, ks1, points2, ks2, n);
end

