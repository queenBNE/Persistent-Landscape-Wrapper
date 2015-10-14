function [ landscape ] = barcodeToLandscape( barcode )
%TOLANDSCAPE Computes the landscape corresponding to the given barcode.
%A barcode is a matrix with 2 columns, each row corresponds to the birth
%and death pair of an interval. 
%A landscape is represented as a list of matrices with 2
%columns. Each matrix, landscape{k} respresents the non-differentiable
%points of the piece-wise linear function \lambda_k. 
    [points, ks] = barcodeToLandscape_(barcode);
    landscape = interfaceToMatlabLandscape(points, ks);

end

