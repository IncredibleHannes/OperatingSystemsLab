package main.java;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jonas on 23.02.17.
 */
public class MatrixMultiplicator {

    public static void main(String[] args) {
        double [][] a = {{ 1, 2, 3, 4, 5},
                         { 6, 7, 8, 9, 10},
                         { 1, 2, 3, 4, 5},
                         { 6, 7, 8, 9, 10},
                         { 1, 2, 3, 4, 5} };
        new MatrixMultiplicator(a);
    }

    private final double[][] result;
    private final double[][] matrix;

    public MatrixMultiplicator(double [][] matrix){
        assert(matrix != null);
        assert(matrix.length == matrix[0].length);
        assert(0 < matrix.length && matrix.length < 10 );

        this.matrix = matrix;
        this.result = new double[matrix.length][matrix.length];

        ArrayBlockingQueue<Runnable> tasks = new ArrayBlockingQueue<Runnable>(matrix.length * matrix.length);

        ThreadPoolExecutor tpe = new ThreadPoolExecutor( 4, 8, 0, TimeUnit.SECONDS, tasks);

        for(int i = 0; i < matrix.length; i++)
            for(int j = 0; j < matrix.length; j++)
                tpe.execute(new Multiplicator( i, j, matrix.length));


        prettyPrintMatrix(result);


    }

    private void prettyPrintMatrix(double[][] data) {
        for(int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++)
                System.out.print(data[i][j] + ", ");

            System.out.println();
        }
    }

    private class Multiplicator implements Runnable {

        private final int i;
        private final int j;
        private final int n;

        public Multiplicator(int i, int j, int n) {
            this.i = i;
            this.j = j;
            this.n = n;
        }

        @Override
        public void run() {
            double res = 0;
            for(int k = 0; k < n; k++){
                res += matrix[i][k] * matrix[k][j];
            }
            synchronized (result){
                result[i][j] = res;
            }
        }
    }



}
