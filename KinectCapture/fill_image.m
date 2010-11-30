function image = fill_image(image)
    full = false;
    new_image = zeros(size(image));
    while ~full
        full = true;
        for i=1:size(image, 1)
            for j=1:size(image, 2)
                if image(i, j) == 0
                    full = false;
                    up = 0;
                    down = 0;
                    left = 0;
                    right = 0;
                    if i ~= 1
                        left = image(i - 1, j);
                    end
                    if j ~= 1
                        up = image(i, j - 1);
                    end
                    if i ~= size(image, 1)
                        right = image(i + 1, j);
                    end
                    if j ~= size(image, 2)
                        down = image(i, j + 1);
                    end
                    values = [up down left right];
                    values = values(values > 0);
                    m = mean(values);
                    if ~isnan(m)
                        new_image(i, j) = mean(values);
                    end
                else
                    new_image(i, j) = image(i, j);
                end
            end
        end
        image = new_image;
        %imagesc(image);
        %drawnow
    end
end