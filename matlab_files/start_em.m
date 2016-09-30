% c++ random 1985
number_of_features = 2;
wStart = ones(1, number_of_classes) / number_of_classes;
means = zeros(number_of_classes, number_of_features);
covs = zeros(number_of_features, number_of_features, number_of_classes);

means(1, :) = [-22.7302, 3.74324];
means(2, :) = [25.525, -13.3906];
means(3, :) = [18.7551, -8.05391];

covs(:, :, 1)  = [[0.227011, 0]; [0, 0.0466506]];
covs(:, :, 2)  = [[0.868738, 0]; [0, 0.872216]];
covs(:, :, 3)  = [[0.752323, 0]; [0, 0.374008]];

thetaStart.mus = means;
thetaStart.sigmas = covs;
[wOptimal, thetaOptimal] = EM(features, number_of_classes, wStart, thetaStart);