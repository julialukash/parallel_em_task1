% plot(X(:,1),X(:,2),'g+');
%     for j = 1:k
%        plot_normal_contour(thetaOptimal.mus(j,:),...
%                 thetaOptimal.sigmas(:,:,j));
%        hold on;
%     end
     
% m Ц мат.ожидание, вектор-столбец длины 2;
% S Ц матрица ковариации, матрица размера 2x2;
% levels Ц линии уровн€, измер€емые в количестве стандартных отклонений, вектор-столбец действительных чисел, по умолчанию = [1 2 3]Т.
function [] =  plot_normal_contour(m, S, levels)
    if nargin < 3
       levels = [1 2 3]';
    end
    [U, diag, ~] = svd(S); 
    angle = acos(U(1,1));
    if U(2,1) <  0
        angle = 2*pi - angle;
    end
    colors = ['r','g','b','y'];
    
    for i = 3 : 3%size(levels,1)
       ellipse(sqrt(diag(1,1))*levels(i),sqrt(diag(2,2))*levels(i),angle,m(1),m(2),...
                     'color',colors( randi([1,4],[1,1])));
    end
    
