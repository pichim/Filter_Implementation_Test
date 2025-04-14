function [sortedArr, sortedIdx, counts] = insertionSortWithIndices(arr)
%INSERTIONSORTWITHINDICES Sorts the array in ascending order using Insertion Sort,
% and also returns a corresponding array of original indices.
%
% USAGE:
%   [sortedArr, sortedIdx] = insertionSortWithIndices(arr)
%
%   sortedArr  - the values of 'arr', sorted in ascending order
%   sortedIdx  - a permutation of [1..n], so that sortedArr(k) = arr(sortedIdx(k))

    n = length(arr);

    % Create an array of indices
    idx = 1:n;

    c0 = 0;
    c1 = 0;

    % Insertion sort
    for i = 2 : n
        currVal = arr(i);
        currIdx = idx(i);

        j = i - 1;
        % Shift elements to the right while they are greater than currVal
        while (j >= 1) && (arr(j) > currVal)
            arr(j+1) = arr(j);
            idx(j+1) = idx(j);
            j = j - 1;
            c0 = c0 + 1;
        end

        % Insert at the correct position
        arr(j+1) = currVal;
        idx(j+1) = currIdx;
        c1 = c1 + 1;
    end

    sortedArr = arr;
    sortedIdx = idx;
    counts = c0 + c1;
end
