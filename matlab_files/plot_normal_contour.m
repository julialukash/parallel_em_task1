function [] =  plot_normal_contour(m, S, levels)
    if nargin < 3
       levels = [1 2 3]';
    end
    [U, diag, ~] = svd(S); 
    angle = acos(U(1,1));
    if U(2,1) <  0
        angle = 2*pi - angle;
    end
    
    for i = 3 : 3
       ellipse(sqrt(diag(1,1))*levels(i),sqrt(diag(2,2))*levels(i),angle,m(1),m(2),'r', 300);
    end
    
