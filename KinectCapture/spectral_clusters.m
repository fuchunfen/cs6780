function clusters = spectral_clusters (image, sigma, num_clusters)
    sigma_d = 50;
    S = sparse(numel(image), numel(image));
    for i=1:size(image, 1)
        for j=1:size(image, 2)
            minx = max([1 i-5]);
            miny = max([1 j-5]);
            maxx = min([i+5 size(image, 1)]);
            maxy = min([j+5 size(image, 2)]);
            for x=minx:maxx
                for y=miny:maxy
                    if x == i && y == j
                        continue
                    end
                    d = norm([x y] - [i j]);
                    if d < 5
                        S((i - 1)*size(image, 2) + j, (x - 1)*size(image, 2) + y) = ...
                            exp(-1/(2*sigma_d^2)*d^2);  
                        if image(x, y) > 0 && image(i, j) > 0 
                            S((i - 1)*size(image, 2) + j, (x - 1)*size(image, 2) + y) = ...
                                S((i - 1)*size(image, 2) + j, (x - 1)*size(image, 2) + y)*exp(-1/(2*sigma^2)*norm(image(i, j) - image(x, y))^2);
                        end
                    end
                end
            end
        end
    end
    imagesc(S);
    drawnow
    sqrtiD = zeros(numel(image), numel(image));
    for j=1:numel(image)
        sqrtiD(j, j) = sqrt(1/sum(S(j, :)));
    end
    [vectors values] = eig (sqrtiD*S*sqrtiD);
    num_clusters = eigengap(values);
    [Y I] = sort(diag(values),  'descend');
    v = vectors(:, I(1:num_clusters));
    v_prime = v;
    for j=1:size(v, 1)
        v_prime(j,:) = v(j,:)./norm(v(j,:));
    end
    c = kmeans (v_prime, num_clusters, 'emptyaction', 'drop');
    clusters = reshape(c, size(image, 2), size(image, 1))';
    imagesc(clusters);
    drawnow
end