package main.java;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jonas on 23.02.17.
 */
public class MatrixMultiplicator {

    static double [][] testMatrix =
            {{ 1, 2, 3, 4, 5},
            { 6, 7, 8, 9, 10},
            { 1, 2, 3, 4, 5 },
            { 6, 7, 8, 9, 10},
            { 1, 2, 3, 4, 5 }};

    private final double[][] result;
    private final double[][] matrix;

    public static void main(String[] args) {
        new MatrixMultiplicator(testMatrix);
    }

    private MatrixMultiplicator(double[][] matrix){
        try {
            assert (matrix != null);
            assert (matrix.length == matrix[0].length);
            assert (0 < matrix.length && matrix.length < 10);
        } catch (AssertionError e) {
            System.out.println("Illegal input matrix");
        }

        this.matrix = matrix;
        this.result = new double[matrix.length][matrix.length];

        ArrayBlockingQueue<Runnable> tasks = new ArrayBlockingQueue<Runnable>(matrix.length * matrix.length);

        int sysCores = Runtime.getRuntime().availableProcessors();
        ThreadPoolExecutor tpe = new ThreadPoolExecutor( sysCores, sysCores, 0, TimeUnit.SECONDS, tasks);

        for(int i = 0; i < matrix.length; i++)
            for(int j = 0; j < matrix.length; j++)
                tpe.execute(new Multiplicator( i, j, matrix.length));


        prettyPrintMatrix(result);

        tpe.shutdown();
    }

    private class Multiplicator implements Runnable {

        private final int i;
        private final int j;
        private final int n;

        Multiplicator(int i, int j, int n) {
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

    // Super magic pretty print!
    static void prettyPrintMatrix(double[][] data) {
        String printString = "";
        int maxValueLength = getMaxValueLength(data);
        for(int i = 0; i < data.length; i++) {
            printString = "| ";
            for (int j = 0; j < data.length; j++){
                int numberOfWhitespace = maxValueLength - (data[i][j] + "").length();
                printString += data[i][j] + new String(new char[numberOfWhitespace]).replace("\0", " ") + " | ";
            }
            System.out.println(new String(new char[printString.length() - 1]).replace("\0", "-"));
            System.out.println(printString);
        }
        System.out.println(new String(new char[printString.length() - 1]).replace("\0", "-"));
    }

    // Returns the length of the string of the greatest value of a matrix
    private static int getMaxValueLength(double[][] data){
        int maxValue = 0;
        for (int i = 0; i < data.length; i++){
            for(int j = 0; j < data[0].length; j++){
                if (Double.toString(data[i][j]).length() > maxValue) {
                    maxValue = Double.toString(data[i][j]).length() ;
                }
            }
        }
        return maxValue;
    }
}
