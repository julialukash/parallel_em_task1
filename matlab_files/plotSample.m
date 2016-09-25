% INPUT:
% X - generated sample, size NxD
% t - tags for classes, size Nx1

function [] = plotSample(X, t)
figure;
hold on;
    classes = unique(t);
    for i = 1 : size(classes, 1)
        temp = X(t == classes(i), :);
        plot(temp(:, 1), temp(:, 2), 'o', 'color', rand(1, 3));
    end
hold off;
end
