function draw_optimal_model(test)
    load(strcat('ts', int2str(test), '.mat'));

    plotSample(features, label);

    optimal_model = load(strcat('../data/result_test_set_', int2str(test), '.csv'));
    k = size(optimal_model, 1) / 3;

    for i = 1 : k
        mu = optimal_model(i, :)
        sigma = optimal_model(2 * i + k - 1 : 2 * i + k, :)
    
        plot_normal_contour(mu, sigma);
    end
end