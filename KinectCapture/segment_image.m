files = dir('images/*.txt');
files(randperm(numel(files))) = files;
for index=1:numel(files)
    name = files(index).name;
    X = load(['images/' name]);
    name = strrep(name, '.txt', '');
    Z = imreadbw(['images/' name '.jpg']);
    factor = 16;
    a = X;
    b = Z;
    a(X == 2047) = 0;
    a = downsample(a, factor);
    b = downsample(b, factor);
    a = downsample (a', factor)';
    b = downsample (b', factor)';
        
    c = spectral_clusters (b, 0.05, 80);
    d = spectral_clusters (a, 5, 6);
    middle = d(size(a,1)/2, size(a,2)/2);
    selected_pixels = find(d == middle);
    selected_clusters = zeros(20);
    for i=1:numel(selected_pixels)
        selected_clusters(c(selected_pixels(i))) = 1;
    end
    selected_clusters = find(selected_clusters == 1);
    final = zeros(size(c));
    for i=1:numel(selected_clusters)
        final(c == selected_clusters(i)) = 1;
    end
    imagesc(final);
    drawnow
end

exit
