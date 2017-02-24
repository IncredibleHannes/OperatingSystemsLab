package main.java;

import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jonas on 23.02.17.
 */
public class CoreOrientedMatrixMultiplicator {

    public static void main(String[] args) {
        double [][] a = {{ 1, 2, 3, 4, 5},
                         { 6, 7, 8, 9, 10},
                         { 1, 2, 3, 4, 5},
                         { 6, 7, 8, 9, 10},
                         { 1, 2, 3, 4, 5} };
        new CoreOrientedMatrixMultiplicator(a);
    }

    private final double[][] result;
    private final double[][] matrix;

    private CoreOrientedMatrixMultiplicator(double[][] matrix){
        assert(matrix != null);
        assert(matrix.length == matrix[0].length);
        assert(0 < matrix.length && matrix.length < 10 );

        this.matrix = matrix;
        this.result = new double[matrix.length][matrix.length];

        ArrayBlockingQueue<Runnable> tasks = new ArrayBlockingQueue<>(matrix.length * matrix.length);

        int sysCores = Runtime.getRuntime().availableProcessors();
        ThreadPoolExecutor tpe = new ThreadPoolExecutor( sysCores, sysCores, 0, TimeUnit.SECONDS, tasks);

        ArrayList<MatrixEntry> allEntries = new ArrayList<>();
        for(int i = 0; i < matrix.length; i++)
            for(int j = 0; j < matrix.length; j++)
                allEntries.add(new MatrixEntry(i,j));


        ArrayList< ArrayList<MatrixEntry> > workTasks = new ArrayList<>();

        for(int i = 0 ; i < sysCores ; i++)
            workTasks.add(new ArrayList<MatrixEntry>());

        int ctr = 0 ;
        for (MatrixEntry me : allEntries) {
            workTasks.get(ctr).add(me);
            ctr = (ctr +1) % sysCores;
        }

        for(int i = 0 ; i < sysCores ; i++){
            tpe.execute(new MultiMultiplicator( workTasks.get(i) , matrix.length));
        }



        prettyPrintMatrix(result);

        tpe.shutdown();


    }

    private void prettyPrintMatrix(double[][] data) {
        for(int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++)
                System.out.print(data[i][j] + ", ");

            System.out.println();
        }
    }

    private class MultiMultiplicator implements Runnable {

        private final ArrayList<MatrixEntry> workEntries = new ArrayList<>();
        private final int n;

        MultiMultiplicator(ArrayList<MatrixEntry> workEntries, int n) {
            this.workEntries.addAll(workEntries);
            this.n = n;
        }

        @Override
        public void run() {
            for (MatrixEntry me : this.workEntries) {
                double res = 0;
                for(int k = 0; k < n; k++){
                    res += matrix[me.fst][k] * matrix[k][me.snd];
                }
                synchronized (result){
                    result[me.fst][me.snd] = res;
                }
            }
        }
    }

    private class MatrixEntry{
        final int fst;
        final int snd;
        MatrixEntry(int f, int s){
            fst = f;
            snd = s;
        }
    }



}
