for N = 10000:10000:200000
    number_of_classes = 4;
    procents_of_classes = [0.2, 0.3, 0.1, 0.4];
    number_of_clouds_in_classes = [1, 1, 1, 1];
    params.nFeatures = 2;
    params.distance ='far';
    params.width ='fat';
    model = create_model(number_of_classes, procents_of_classes, number_of_clouds_in_classes, params);

    [features, label] = gen_sample(model, N);

    Y = [label, features];
    h = plotSample(features, label);
    header  = zeros(1, size(Y,2));
    header(1) = size(Y, 1);
    header(2) = size(Y, 2) - 1;
    Y = [header; Y];

    filename = strcat('../data_performance/set', int2str(N), '.csv');
    dlmwrite(filename,Y,'delimiter',' ');
    %save(strcat('../data_performance/ts', int2str(test), '.mat'));
    saveas(h,sprintf('../data_performance/fig%d.png', N));
end