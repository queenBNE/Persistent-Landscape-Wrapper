function [ d ] = landscapeBottleneckDistance( l1, l2)
%BOTTLENECK_DISTANCE Computes the bottleneck distance between two barcodes:
%barcode1 and barcode2 should be a 2xN1 and 2xN2 matrix of doubles with
%each row representing an interval (birth,death). 
    [points1, ks1] = matlabToInterfaceLandscape(l1);
    [points2, ks2] = matlabToInterfaceLandscape(l2);
    d = landscapeBottleneckDistance_(points1, ks1, points2, ks2);
end