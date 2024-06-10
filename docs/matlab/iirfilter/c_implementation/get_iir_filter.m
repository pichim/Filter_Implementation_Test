function filter = get_iir_filter()

 filter.order = [];
 filter.A = zeros(2,1); % [a1, a2], a0 is always 1.0
 filter.B = zeros(3,1); % [b0, b1, b2]
 filter.w = zeros(2,1); % [w1, w2]

end

