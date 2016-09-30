number_of_classes = 5;
procents_of_classes = [0.1, 0.1, 0.2, 0.05, 0.55];
number_of_clouds_in_classes = [1, 1, 1, 1, 1];
params.nFeatures = 2;
params.distance ='close';
params.width ='slim';
model = create_model(number_of_classes, procents_of_classes, number_of_clouds_in_classes, params);
N = 10000;
[features, label] =gen_sample(model, N);
Y = [label, features];
plotSample(features, label);
header  = zeros(1, size(Y,2));
header(1) = size(Y, 1);
header(2) = size(Y, 2) - 1;
Y = [header; Y];
filename = '../data/test_set_5.csv';
% dlmwrite(filename,Y,'delimiter',' ');
% csvwrite(filename,Y);
% [predicted_label,x1,x2] = importfile_2dim('result_test_set_1.csv',1, 10000);
% new_features = [x1 x2];
% plotSample(new_features, predicted_label);

% sigma = [1, 0; 0, 2];
% 
% xR = X * inv(sigma);

% b * inv(A)= b/A