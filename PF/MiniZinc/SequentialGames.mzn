% Sequential Games:

int: num;                       %  Number n ∈ N of games;
set of int: games = 1..num; 
array [games] of int: fun;      % Fun value vi ∈ Z for each game i ∈ [n];
int: cap;                       % Pocket Capacity C ∈ N;
int: refill;                    % Refill amount R ∈ N;
% set of int: x_range = 0..cap; 
set of int: x_range = 0..(cap + refill); 
int: K;                        % Goal K ∈ N;

array[games] of var int: t;
array[games] of var int: plays;



% The constraints on t and p are:

% 1. ∑i∈[n] pivi ≥ K:
constraint sum(i in games) (plays[i] * fun[i]) >= K;



% 2. The number of tokens ti available to play game i is C when we start playing the first game, and for i > 1 is the minimum of C and ti−1 − pi−1 + R:
constraint (t[1] = cap) /\ 
forall(i in games)(
  (1<i /\ i<=num) -> exists(x in x_range)(
    (x = (t[i-1] - plays[i-1] + refill)) /\ 
    ((x > cap) -> (t[i] = cap)) /\
    ((x <= cap) -> (t[i] = x))
  )
);



% 3. We play each game at least once, and at most ti times
constraint forall (i in games)(
  (1 <= i /\ i <= num) -> (1 <= plays[i] /\ plays[i] <= t[i])
);



% 4. Additional constraint:
constraint forall (i in games) (fun[i] < 1 -> plays[i] = 1);




% Result:
% If you want the optimal solution, you just need to comment the first constraint, and then use the second solve function to get the optimal solution.

solve satisfy;
% solve maximize sum(i in games)(plays[i] * fun[i]);
output [show (sum(i in games)(plays[i] * fun[i]))];
% output [show (plays)];