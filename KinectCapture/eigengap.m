function clusters = eigengap (values)
    x = sort(abs(diag(values)));
    clusters = 0;
    gap = 0;
    for i=numel(x):-1:2
        if x(i) - x(i - 1) > gap
            gap = x(i) - x(i - 1);
            clusters = numel(x) - i + 1;
        end
    end
end