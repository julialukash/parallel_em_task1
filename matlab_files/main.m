number_of_classes = 5;
procents_of_classes = [0.1, 0.05, 0.05, 0.1, 0.7];
number_of_clouds_in_classes = [1, 1, 1, 1, 2];
params.nFeatures = 2;
params.distance ='far';
params.width ='fat';
model = create_model(number_of_classes, procents_of_classes, number_of_clouds_in_classes, params);
N = 10000;
[X, t] =gen_sample(model, N);
Y = [t, X];
plotSample(X, t);
header  = zeros(1, size(Y,2));
header(1) = size(Y, 1);
header(2) = size(Y, 2) - 1;
Y = [header; Y];
%filename = 'test_set_1.csv';
%csvwrite(filename,Y);
 