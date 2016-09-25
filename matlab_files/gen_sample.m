% √енераци€ выборки из модели генеральной совокупности
% m Ц модель генеральной совокупности, структура;
% N Ц объем выборки, число;
% X Ц сгенерированна€ выборка, матрица размера NxD;
% t Ц метки классов дл€ сгенерированной выборки, вектор-столбец длины N.
function [X, t] = gen_sample(m, N)
   X = [];
   t = [];
   procentsOfClasses = m.procentsOfClasses;
   for i = 1 : m.classes
        sizeOfClass = N * procentsOfClasses(i);
        sigma = m.sigmas{i};
        if sizeOfClass ~= 0
            for j = 1 : m.clouds(i)
                sizeOfCloud = sizeOfClass / m.clouds(i);
                mu = m.evs{ sum(m.clouds(1:i-1)) + j };
                
                x = gen_normal_sample(mu, sigma, sizeOfCloud);      
                X = cat(1,X,x);
            end
            
            t = cat(1,t,i*ones(sizeOfClass,1));
        end
    end
