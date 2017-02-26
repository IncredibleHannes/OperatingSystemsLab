package main.java;

import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Johannes Hartmann, Jonas Einig
 */
public class MatrixMultiplicator {

    static double[][] testMatrix =
            {{1, 2, 3, 4, 5, 6},
                    {6, 7, 8, 9, 10},
                    {1, 2, 3, 4, 5},
                    {6, 7, 8, 9, 10},
                    {1, 2, 3, 4, 5}};

    private final double[][] result;
    private final double[][] matrix;

    /**
     * mode == true : One task is produced for every value that has to be calculated
     * mode == false : One task is produced for every core of the ThreadPoolExecutor (respectively for each logical Processor)
     */
    static final boolean mode = true;

    public static void main(String[] args) {
        new MatrixMultiplicator(testMatrix);
    }

    private MatrixMultiplicator(double[][] matrix) {
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
        ThreadPoolExecutor tpe;
        if (mode) { //one task for each value
            tpe = new ThreadPoolExecutor(sysCores, sysCores, 0, TimeUnit.SECONDS, new ArrayBlockingQueue<Runnable>(matrix.length * matrix.length));
            executeOneValOneTask(tpe);
        } else { // one task for each core
            tpe = new ThreadPoolExecutor(sysCores, sysCores, 0, TimeUnit.SECONDS, new ArrayBlockingQueue<Runnable>(sysCores));
            executeOneCoreOneTask(sysCores, tpe);
        }
        prettyPrintMatrix(result);
        tpe.shutdown();
    }

    /*#######OneValOneTask#####*/

    /**
     * generates one task for each value in result matrix
     * */
    private void executeOneValOneTask(ThreadPoolExecutor tpe) {
        for (int i = 0; i < matrix.length; i++)
            for (int j = 0; j < matrix.length; j++)
                tpe.execute(new Multiplicator(i, j, matrix.length));
    }

    private class Multiplicator implements Runnable {

        private final int iMatrixIndex;
        private final int jMatrixIndex;
        private final int matrixLength;

        Multiplicator(int i, int j, int n) {
            this.iMatrixIndex = i;
            this.jMatrixIndex = j;
            this.matrixLength = n;
        }

        @Override
        public void run() {
            double res = 0;
            for (int i = 0; i < matrixLength; i++) {
                res += matrix[iMatrixIndex][i] * matrix[i][jMatrixIndex];
            }
            synchronized (result) {
                result[iMatrixIndex][jMatrixIndex] = res;
            }
        }
    }

    /*######OneTaskPerCore########*/

    /**
     * generates one Task for each core in the ThreadPoolExecutor
     * */
    private void executeOneCoreOneTask(int sysCores, ThreadPoolExecutor tpe) {
//        create all computations
        ArrayList<MatrixEntry> allEntries = new ArrayList<>();
        for (int i = 0; i < matrix.length; i++)
            for (int j = 0; j < matrix.length; j++)
                allEntries.add(new MatrixEntry(i, j));


        ArrayList<ArrayList<MatrixEntry>> workTasks = new ArrayList<>();
        //create actual workTasks
        for (int i = 0; i < sysCores; i++)
            workTasks.add(new ArrayList<MatrixEntry>());

        //fill workTasks with content -- round robin
        int ctr = 0;
        for (MatrixEntry me : allEntries) {
            workTasks.get(ctr).add(me);
            ctr = (ctr + 1) % sysCores;
        }

        for (int i = 0; i < sysCores; i++) {
            tpe.execute(new MultiMultiplicator(workTasks.get(i), matrix.length));
        }
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

    //#######PRINTING###########

    // Super magic pretty print!
    static void prettyPrintMatrix(double[][] data) {
        String printString = "";
        int maxValueLength = getMaxValueLength(data);
        for (int i = 0; i < data.length; i++) {
            printString = "| ";
            for (int j = 0; j < data.length; j++) {
                int numberOfWhitespace = maxValueLength - (data[i][j] + "").length();
                printString += data[i][j] + new String(new char[numberOfWhitespace]).replace("\0", " ") + " | ";
            }
            System.out.println(new String(new char[printString.length() - 1]).replace("\0", "-"));
            System.out.println(printString);
        }
        System.out.println(new String(new char[printString.length() - 1]).replace("\0", "-"));
    }

    // Returns the length of the string of the greatest value of a matrix
    private static int getMaxValueLength(double[][] data) {
        int maxValue = 0;
        for (int i = 0; i < data.length; i++) {
            for (int j = 0; j < data[0].length; j++) {
                if (Double.toString(data[i][j]).length() > maxValue) {
                    maxValue = Double.toString(data[i][j]).length();
                }
            }
        }
        return maxValue;
    }
}
