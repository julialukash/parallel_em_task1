optimal_model = load('../data/result_test_set_5.csv');
k = 5;

for i = 1 : k
    mu = optimal_model(i, :)
    sigma = optimal_model(2 * i + 4 : 2 * i + 5, :)
    
    plot_normal_contour(mu, sigma);
end