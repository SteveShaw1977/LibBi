% Copyright (C) 2011
% Author: Lawrence Murray <lawrence.murray@csiro.au>
% $Rev$
% $Date$

% -*- texinfo -*-
% @deftypefn {Function File} plot_simulate (@var{in}, @var{invars})
%
% Plot output of the simulate program.
%
% @itemize
% @bullet{ @var{in} Input file. Gives the name of a NetCDF file output by
% simulate.}
%
% @bullet{ @var{invars} Cell array of strings naming the variables
% of this file to plot. Empty strings may be used to produce empty plots.}
% @end itemize
% @end deftypefn
%
function plot_simulate (in, invars)
    % check arguments
    if (nargin != 2)
        print_usage ();
    end

    % input file
    nci = netcdf(in, 'r');

    t = nci{'time'}(:)'; % times
    P = [0.025 0.5 0.975]'; % quantiles (median and 95%)
    for i = 1:length(invars)
        if (!strcmp(invars{i}, ''))
            X = nci{invars{i}}(:,:);
            Q = quantile(X, P, 2);
        
            % plot
            if length(invars) > 1
                subplot(length(invars), 1, i);
            end
            hold on;
            
            area_between(t, Q(:,1), Q(:,3), watercolour(1, 0.5));
            plot(t, Q(:,2), 'linewidth', 3, 'color', watercolour(1));
            title(invars{i});
            plot_defaults;
        end
    end
    
    ncclose(nci);
end