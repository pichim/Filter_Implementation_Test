function kSmallest = findKSmallestElements(arr, k)
    % Edge cases
    if k == 0 || isempty(arr)
        kSmallest = [];
        return;
    end
    if k >= length(arr)
        kSmallest = arr;
        return;
    end

    % Create a max-heap with the first k elements
    maxHeap = arr(1:k);
    heapSize = k;
    maxHeap = buildMaxHeap(maxHeap, heapSize);

    % Iterate over the rest of the array
    for i = k+1:length(arr)
        if arr(i) < maxHeap(1) % Compare with the maximum element in the max-heap
            maxHeap(1) = arr(i); % Replace the max element with the new one
            maxHeap = maxHeapify(maxHeap, 1, heapSize);
        end
    end

    % Return the k smallest elements from the max-heap
    kSmallest = maxHeap; % The order is not guaranteed
end

function heap = buildMaxHeap(arr, n)
    % Build a max-heap from an array
    for i = floor(n/2):-1:1
        arr = maxHeapify(arr, i, n);
    end
    heap = arr;
end

function arr = maxHeapify(arr, i, n)
    % Maintain the max-heap property iteratively
    while true
        largest = i;
        left = 2 * i;
        right = 2 * i + 1;

        if left <= n && arr(left) > arr(largest)
            largest = left;
        end
        if right <= n && arr(right) > arr(largest)
            largest = right;
        end
        if largest ~= i
            % Swap
            temp = arr(i);
            arr(i) = arr(largest);
            arr(largest) = temp;
            % Move to the next node to heapify
            i = largest;
        else
            break; % If no swap is needed, heap property is satisfied
        end
    end
end