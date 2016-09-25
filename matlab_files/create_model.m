% Создание модели генеральной совокупности
% K – число классов;
% (param1, param2, …) – другие параметры модели (вид разделяющей поверхности, уровень шума, количество признаков и т.д.);
% m - модель генеральной совокупности, структура.
% param1 - отдаленность друг от друга
% param2 - широта
% procentsOfClasses - массив с процентами, от классов, 
% сумма  = 100
function [m] = create_model(K, procentsOfClasses,clouds, params)
        m.procentsOfClasses = procentsOfClasses;
        if sum(procentsOfClasses) ~= 1
            error ('The sum of procents must be 1');
        end
        nFeatures = params.nFeatures;
        m.nFeatures = nFeatures; 
        param1 = params.distance;
        param2 = params.width;
        m.classes = K;
        m.nClouds = sum(clouds);
        m.clouds = clouds;
        
        m.evs = cell(m.nClouds,1);
        m.sigmas = cell(K,1);
        if strcmp(param1,'myOwn')
           m.evs = params.evs; 
        else
            if strcmp(param1,'far')
                s = 30;
            end
            if strcmp(param1,'close')
                s = 15;
            end
            MU = randi([-s,s],[nFeatures*m.nClouds*10,1]);
            indexes = randi([1,nFeatures*m.nClouds*10],...
                            [m.nClouds*nFeatures,1]);
            MU = MU(indexes);
            
            MU = reshape(MU,m.nClouds,nFeatures);
        end
    for i = 1 : K
        if strcmp(param2,'myOwn')
           diagMatrix = diag(params.lambdas{i});
        end
        if strcmp(param2,'fat')
            diag1 = randi([4 10],1);
            diagMatrix = diag(diag1 * ones(nFeatures,1));
        end
        if strcmp(param2,'slim')
            diagMatrix = diag(randi([1 10],[1 nFeatures]));
        end
        help = orth(rand(nFeatures,nFeatures));
        sigma = help*diagMatrix*help';
        m.sigmas{i} = sigma;
        
    end
    for i = 1: m.nClouds
        if ~strcmp(param1,'myOwn')
            mu = MU(1,:);
            MU(1,:) = [];
            m.evs{i} = mu';
        end
    end
