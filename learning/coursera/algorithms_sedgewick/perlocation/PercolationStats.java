import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;
import edu.princeton.cs.algs4.Stopwatch;
import java.math.*;
import java.util.*;

public class PercolationStats {
	private int trials;
	private double trial_results[];

	public PercolationStats(int n, int trials)    // perform trials independent experiments on an n-by-n grid
	{
		if( n <= 0 || trials <= 0 ) throw new IllegalArgumentException();
		this.trials = trials;
		this.trial_results = new double[trials];

		int total_cells = n*n;
		for( int t = 0; t < trials; ++t ) {
			Percolation percolator = new Percolation(n);
			int num_open_cells = 0;
			while( percolator.percolates() == false ) {
				int i = StdRandom.uniform(n)+1;
				int j = StdRandom.uniform(n)+1;
				if( !percolator.isOpen(i,j) ) {
					percolator.open(i,j);
					++num_open_cells;
				}
			}
			trial_results[t] = ((double)num_open_cells)/total_cells;
			//System.out.println( num_open_cells + " " + total_cells + " " + trial_results[t]);
		}
	}

	public double mean()                          // sample mean of percolation threshold
	{
		double res = 0;
		for( int t = 0; t < trials; ++t )
			res += trial_results[t];
		return res/trials;

		//return StdStats.mean(trial_results);
	}

	private double variance()
	{
		if( trials == 1 )
			return Double.NaN;
		double sigma_squared = 0;
		double mu = mean();
		for( int t = 0; t < trials; ++t )
			sigma_squared += Math.pow( trial_results[t]-mu, 2.0 );

		sigma_squared /= (trials-1);
		return sigma_squared;
	}

	public double stddev()                        // sample standard deviation of percolation threshold
	{
		double sigma_squared = variance();
		return Math.sqrt(sigma_squared); // sigma
	}

	public double confidenceLo()                  // low  endpoint of 95% confidence interval
	{
		double mu = mean();
		double sigma = stddev();
		return mu-(1.96*sigma/Math.sqrt(trials));
	}

	public double confidenceHi()                  // high endpoint of 95% confidence interval
	{
		double mu = mean();
		double sigma = stddev();
		return mu+(1.96*sigma/Math.sqrt(trials));
	}

	public static void main(String[] args)    // test client (described below)
	{
		Stopwatch clock = new Stopwatch();
		if( args.length != 2 )
			throw new IllegalArgumentException();
		int n = Integer.parseInt(args[0]);
		int t = Integer.parseInt(args[1]);
		PercolationStats ps = new PercolationStats(n,t);
		System.out.println("mean                    = " + ps.mean());
		System.out.println("stddev                  = " + ps.stddev());
		System.out.println("95% confidence interval = " + ps.confidenceLo() + ", " + ps.confidenceHi());
		//System.out.println("Elapsed Time            = " + clock.elapsedTime() + "secs" );
	}
}


