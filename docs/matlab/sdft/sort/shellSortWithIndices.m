function [sorted, sortedIdx] = shellSortWithIndices(arr)
%SHELLSORTWITHINDICES Sorts the array ARR in ascending order using Shell sort,
% and also returns a permutation of indices that describe the sorted order.
%
% USAGE:
%   [sorted, sortedIdx] = shellSortWithIndices(arr)
%
%   'sorted'    is the sorted version of 'arr'.
%   'sortedIdx' is an array of the same length as 'arr', where sorted(k) == arr(sortedIdx(k)).

    n = length(arr);
    % Create an index array: initially [1,2,3,...,n]
    idx = 1:n;

    gap = floor(n/2);
    % Loop over gap sizes, reducing by ~half each time
    while gap >= 1
        % Gapped insertion sort for this gap size
        for i = gap+1 : n
            tempVal = arr(i);
            tempIdx = idx(i);

            j = i;
            % Shift elements of arr[j-gap], arr[j-2*gap], ... that are greater than tempVal
            while j > gap && arr(j - gap) > tempVal
                arr(j) = arr(j - gap);
                idx(j) = idx(j - gap);
                j = j - gap;
            end

            % Insert the element at the correct position
            arr(j) = tempVal;
            idx(j) = tempIdx;
        end
        gap = floor(gap/2);
    end

    sorted    = arr;
    sortedIdx = idx;
end
