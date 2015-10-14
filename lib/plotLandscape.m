function [ ] = plotLandscape( landscape )
%PLOT_LANDSCAPE Plot a landscape
%A landscape is represented as a list of matrices with 2
%columns. Each matrix, landscape{k} respresents the non-differentiable
%points of the piece-wise linear function \lambda_k. 
    for i=1:length(landscape)
        points = landscape{i};
        x = points(1:length(points), 1);
        y = points(1:length(points), 2);
        plot(x,y,'-');
        hold all;
    end
    hold off;
end

