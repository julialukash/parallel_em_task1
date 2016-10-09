avg_values = [];
params = unique(performance2(:, 1:2),'rows');
for i = 1 : size(params, 1)
    current_param_lines = performance2(performance2(:, 1) == params(i, 1) & performance2(:, 2) == params(i, 2), :);
    means = mean(current_param_lines);
    avg_values = [avg_values; means]; %#ok<AGROW>
end 
x =  unique(avg_values(:, 1));
y =  unique(avg_values(:, 2));
z = zeros(numel(x), numel(y));
for i = 1 : numel(x) 
    for j = 1 : numel(y) 
        z(i, j) = avg_values(avg_values(:, 1) == x(i) & avg_values(:, 2) == y(j), 3);
    end
end
surf(y,x,z);
xlabel('n objects');
ylabel('n threads');
zlabel('perfomance');
title('EM-clustering perfomance');