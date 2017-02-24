package main.java;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jonas on 23.02.17.
 */
public class MatrixMultiplicator {

    public static void main(String[] args) {

    }

    private double[][] matrix;

    public MatrixMultiplicator(double [][] matrix){
        this.matrix = matrix;

        ArrayBlockingQueue<Runnable> tasks = new ArrayBlockingQueue<Runnable>(matrix.length * matrix.length);







        ThreadPoolExecutor tpe = new ThreadPoolExecutor(matrix.length * matrix.length,matrix.length * matrix.length,0, TimeUnit.SECONDS, tasks);
    }




}
