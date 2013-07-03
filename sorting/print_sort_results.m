% Plots and prints graphs with sort time statistics. For example:
%
%   print_sort_results({'shuffled'}, {'insertion', 'merge'}, {'median'}, 'shuffled_median_simple')
function print_sort_results(types_to_plot, algs_to_plot, stats_to_plot, file)

  shuffled_results = dlmread('shuffled_results.csv', ';');
  partially_sorted_results = dlmread('partially_sorted_results.csv', ';');
  sorted_results = dlmread('sorted_results.csv', ';');

  sizes = shuffled_results(:, 1);

  results = [shuffled_results(:, 2 : end) partially_sorted_results(:, 2 : end) sorted_results(:, 2 : end)];

  types = {'shuffled', 'partially sorted', 'sorted'};
  types_colors = {'1', '2', '3'};
  n_types = columns(types);

  algs = {'bubble', 'selection', 'insertion', 'shell', 'quick', 'merge'};
  algs_long = {'bubble sort', 'selection sort', 'insertion sort', 'Shell sort', 'quicksort', 'merge sort'};
  algs_marks = {'.', 'o', 'x', '*', '+', '^'};
  n_algs = columns(algs);

  stats = {'comparisons', 'swaps', 'copies', 'runs', 'repetitions', 'average', 'stddev', 'median', 'minimum', 'maximum'};
  n_stats = columns(stats);

  types_index = ismember(types, types_to_plot);
  n_types_to_plot = sum(types_index);

  algs_index = ismember(algs, algs_to_plot);
  n_algs_to_plot = sum(algs_index);

  stats_index = ismember(stats, stats_to_plot);
  n_stats_to_plot = sum(stats_index);

  styles = cell(1, n_types * n_algs * n_stats);
  headers = cell(1, n_types * n_algs * n_stats);
  for t = 1 : n_types,
    for a = 1 : n_algs,
      for s = 1 : n_stats,
        header = '';
        if n_algs_to_plot != 1,
          header = [header algs_long{1, a}];
        endif
        if n_types_to_plot != 1,
          if !isempty(header) header = [header '/']; endif
          header = [header types{1, t} ' files'];
        endif
        if n_stats_to_plot != 1,
          if !isempty(header) header = [header '/']; endif
          header = [header stats{1, s}];
        endif
        i = (t - 1) * n_algs * n_stats + (a - 1) * n_stats + s;
        headers{1, i} = header;
        styles{1, i} = [algs_marks{a} types_colors{t}];
      endfor
    endfor
  endfor

  if n_stats_to_plot != 1,
    plot_title = 'Sort time';
  else
    plot_title = ['Sort ' stats_to_plot{1} ' time'];
  endif

  if n_algs_to_plot == 1,
    plot_title = [plot_title ' with ' algs_long{algs_index}];
  endif

  if n_types_to_plot == 1,
    plot_title = [plot_title ' for ' types{types_index} ' files'];
  endif

  index = logical(kron(types_index, algs_index, stats_index));

  figure('Position',[0, 0, 1800, 900]);

  loglog(sizes, results(:, index), styles(:, index));

  legend(headers(:, index), 'location', 'northeastoutside');

  title(plot_title);

  xlabel('Array size [no. of items]')
  ylabel('Sort time [seconds]')

  grid
  print('-dpng', '-S2600,1200', [ file '.png']);
end