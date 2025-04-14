function [ind, k_smallest_in_x] = find_k_smallest_and_sort_indices(x, N, k)
    % Initialize the result array with the first k elements of x and their indices
    k_smallest_in_x = x(1:k);
    ind = 1:k;
    
    % Iterate through the remaining elements of the array
    for i = (k+1):N
        % Find the maximum element in the result array using a for loop
        val_max = k_smallest_in_x(1);
        ind_max = 1;
        for j = 2:k
            if k_smallest_in_x(j) > val_max
                val_max = k_smallest_in_x(j);
                ind_max = j;
            end
        end
        
        % If the current element in x is smaller than the maximum element in result
        if x(i) < val_max
            % Replace the maximum element with the current element and update the index
            k_smallest_in_x(ind_max) = x(i);
            ind(ind_max) = i;
        end
    end
    
    % sort the indices array based on the corresponding values in x using a simple bubble sort
    for i = 1:k-1
        for j = 1:k-i
            if k_smallest_in_x(j) > k_smallest_in_x(j+1)
                % swap elements in k_smallest_in_x
                temp_val = k_smallest_in_x(j);
                k_smallest_in_x(j) = k_smallest_in_x(j+1);
                k_smallest_in_x(j+1) = temp_val;
                
                % swap corresponding indices in ind
                temp_ind = ind(j);
                ind(j) = ind(j+1);
                ind(j+1) = temp_ind;
            end
        end
    end
end