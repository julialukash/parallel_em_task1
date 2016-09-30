% c++ random 1985
number_of_features = 2;
wStart = ones(1, number_of_classes) / number_of_classes;
means = zeros(number_of_classes, number_of_features);
covs = zeros(number_of_features, number_of_features, number_of_classes);
% 
% means(1, :) = [-22.7302, 3.74324];
% means(2, :) = [25.525, -13.3906];
% means(3, :) = [18.7551, -8.05391];

means(1, :) = [-28.7218, 12.8311];
means(2, :) = [20.6751, -14.1026];
means(3, :) = [13.7451, -5.71355];

covs(:, :, 1)  = [[1, 0]; [0, 1]];
covs(:, :, 2)  = [[1, 0]; [0, 1]];
covs(:, :, 3)  = [[1, 0]; [0, 1]];

thetaStart.mus = means;
thetaStart.sigmas = covs;
[wOptimal, thetaOptimal] = EM(features, number_of_classes, wStart, thetaStart);
plot(features(:,1),features(:,2),'g+');
    for j = 1:number_of_classes
       plot_normal_contour(thetaOptimal.mus(j,:),...
                thetaOptimal.sigmas(:,:,j));
       hold on;
    end
     