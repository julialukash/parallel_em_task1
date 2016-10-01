number_of_classes = 4;
procents_of_classes = [0.2, 0.3, 0.1, 0.4];
number_of_clouds_in_classes = [1, 1, 1, 1];
params.nFeatures = 2;
params.distance ='far';
params.width ='fat';
model = create_model(number_of_classes, procents_of_classes, number_of_clouds_in_classes, params);

N = 100000;
[features, label] =gen_sample(model, N);

Y = [label, features];
plotSample(features, label);
header  = zeros(1, size(Y,2));
header(1) = size(Y, 1);
header(2) = size(Y, 2) - 1;
Y = [header; Y];

test = 1;
filename = strcat('../data/test_set_', int2str(test), '.csv');
dlmwrite(filename,Y,'delimiter',' ');
save(strcat('ts', int2str(test), '.mat'));