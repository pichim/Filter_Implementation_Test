clc, clear variables
%%

% x = [10.1, 4.5, 5.6, 8.8, 6.7, 11.2, 26.3];
% N = length(x);

N = 26;
x = 100.0 * rand(N, 1);
% x = x.^2;

figure(1)
subplot(311)
plot(x)
subplot(312)
histfit(x)
subplot(313)
plot(sort(x, 'ascend'))


%%

k = N - 5;

display('--- matlab sort');
tic
[x_sorted, ind] = sort(x, 'ascend');
% ind = ind(1:k);
toc

display(' ');


display('--- find_k_smallest_and_sort_indices');
tic
[ind_, k_smallest_in_x_] = find_k_smallest_and_sort_indices(x, N, k);
x(ind_);
toc

norm(x(ind(1:k)) - x(ind_))


% display('--- findKSmallestElements');
% tic
% x_ = findKSmallestElements(x, k);
% toc
% 
% norm(x - x_)


display('--- shellSortWithIndices')
tic
[x_sorted_, ind_] = shellSortWithIndices(x);
toc

norm(x(ind) - x(ind_))


display('--- insertionSortWithIndices')
tic
[x_sorted_, ind_, counts_] = insertionSortWithIndices(x);
toc

counts_
norm(x(ind) - x(ind_))
