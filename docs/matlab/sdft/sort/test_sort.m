clc, clear variables
%%

% x = [10.1, 4.5, 5.6, 8.8, 6.7, 11.2, 26.3];
% N = length(x);

N = 100;
x = 1.0 * (rand(N, 1) - 0.5);
% x = x.^2;

figure(1)
subplot(311)
plot(x)
subplot(312)
histfit(x)
subplot(313)
plot(sort(x, 'ascend'))


%%

k = N/2;

tic
ind = find_k_smallest_and_sort_indices(x, N, k);
x(ind);
toc

tic
[~, ind_] = sort(x, 'ascend');
ind_ = ind_(1:k);
x(ind_);
toc

norm(x(ind)- x(ind_))

tic
ind = find_k_smallest_indices(x, N, k);
x(ind);
toc

tic
temp = findKSmallestElements(x, k);
toc

sum(x(ind_)) - sum(x(ind))
sum(x(ind_)) - sum(temp)

