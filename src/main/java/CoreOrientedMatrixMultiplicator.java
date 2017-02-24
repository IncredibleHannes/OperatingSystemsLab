package main.java;

import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jonas on 23.02.17.
 */
public class CoreOrientedMatrixMultiplicator  {

    private final double[][] result;
    private final double[][] matrix;

    public static void main(String[] args) {
        new CoreOrientedMatrixMultiplicator(MatrixMultiplicator.testMatrix);
    }

    private CoreOrientedMatrixMultiplicator(double[][] matrix) {
        // check matrix does fulfill requirements
        try {
            assert (matrix != null);
            assert (matrix.length == matrix[0].length);
            assert (0 < matrix.length && matrix.length < 10);
        } catch (AssertionError e) {
            System.out.println("Illegal input matrix");
            System.exit(0);
        }


        this.matrix = matrix;
        this.result = new double[matrix.length][matrix.length];


        int sysCores = Runtime.getRuntime().availableProcessors();
        ThreadPoolExecutor tpe = new ThreadPoolExecutor(sysCores, sysCores, 0, TimeUnit.SECONDS, new ArrayBlockingQueue<Runnable>(sysCores));

        ArrayList<MatrixEntry> allEntries = new ArrayList<>();
        for (int i = 0; i < matrix.length; i++)
            for (int j = 0; j < matrix.length; j++)
                allEntries.add(new MatrixEntry(i, j));


        ArrayList<ArrayList<MatrixEntry>> workTasks = new ArrayList<>();

        for (int i = 0; i < sysCores; i++)
            workTasks.add(new ArrayList<MatrixEntry>());

        int ctr = 0;
        for (MatrixEntry me : allEntries) {
            workTasks.get(ctr).add(me);
            ctr = (ctr + 1) % sysCores;
        }

        for (int i = 0; i < sysCores; i++) {
            tpe.execute(new MultiMultiplicator(workTasks.get(i), matrix.length));
        }

        MatrixMultiplicator.prettyPrintMatrix(result);
        tpe.shutdown();
    }

    private class MultiMultiplicator implements Runnable {

        private final ArrayList<MatrixEntry> workEntries = new ArrayList<>();
        private final int matrixSize;

        MultiMultiplicator(ArrayList<MatrixEntry> workEntries, int n) {
            this.workEntries.addAll(workEntries);
            this.matrixSize = n;
        }

        @Override
        public void run() {
            for (MatrixEntry me : this.workEntries) {
                double res = 0;
                for (int k = 0; k < matrixSize; k++) {
                    res += matrix[me.fst][k] * matrix[k][me.snd];
                }
                synchronized (result) {
                    result[me.fst][me.snd] = res;
                }
            }
        }
    }

    private class MatrixEntry {
        final int fst;
        final int snd;

        MatrixEntry(int f, int s) {
            this.fst = f;
            this.snd = s;
        }
    }
}
