package main.java;

import java.util.*;

public class SiebDesEratosthenes {

    private int n;

    public static void main(String[] args) {
        int n = 0;
        if(args.length == 1) {
            n = Integer.parseInt(args[0]);
        } else {
            //read from console
            System.out.println("Bis zu welcher oberen Grenze sollen Primzahlen berechnet werden?");
            Scanner scanner = new Scanner(System.in);
            n = Integer.parseInt(scanner.next());
        }
        SiebDesEratosthenes sde = new SiebDesEratosthenes(n);
    }



    public SiebDesEratosthenes(int n) {
        Worker test = new Worker(n, 2);
        test.start();
        for(int i = 2; i <= n+1; i++){
            test.values.add(i);
        }
        test.parentStopped = true;

    }



    private class Worker extends Thread{
        private Worker child;
        private int n;
        private int prime;
        Pipeline values;
        private boolean parentStopped = false;


        Worker(int n, int prime){
            this.n = n;
            this.prime = prime;
            values = new Pipeline();
        }


        @Override
        public void run() {
            while(!parentStopped || !values.isEmpty()){
               this.checkValue();
            }
        }

        private void checkValue() {
            int k =values.getNext(parentStopped);

            if(k <= n ) {
                if (k % prime != 0) {
                    if (child == null) {
                        System.out.println("child sporned");
                        child = new Worker(n, k);
                        child.start();
                    } else {//(Math.pow(k, 2) < n)
                        child.values.add(k);
                    }//2 3 5 7 11 13 17
                }
            }else{
                this.end();
            }
        }

        void end(){

            System.out.print( prime + ", ");
            if(child != null){
                synchronized (child.values){
                    child.parentStopped = true;
                    child.end();
                    child.values.notifyAll();
                }
            }
        }

    }

    private class Pipeline{
        private ArrayDeque<Integer> elements = new ArrayDeque<>();

        synchronized int getNext(boolean stopped){
            while(elements.isEmpty() && !stopped ){
                try {
                    wait();
                }catch (InterruptedException e){
                    e.printStackTrace();
                }
            }
            return elements.poll();
        }

        synchronized void add(int newVal){
            elements.add(newVal);
            notifyAll();
        }

        boolean isEmpty(){
            return elements.isEmpty();
        }

    }

}